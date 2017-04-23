#pragma once
/*
* Covariant Mozart Utility Library: Switcher
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (C) 2016 Michael Lee(李登淳)
* Email: China-LDC@outlook.com
* Github: https://github.com/mikecovlee
* Website: http://ldc.atd3.cn
*
* Version: 17.1.0
*/
#include "./base.hpp"
#include "./any.hpp"
#include "./function.hpp"
#include "./tuple.hpp"
#include <deque>

namespace cov {
	class switcher final {
	public:
		typedef cov::function<void()> case_type;
	private:
		std::deque<cov::tuple<cov::any,cov::function<void()>>> mCases;
		cov::function<void()> mDefault;
		const cov::any mCondition;
	public:
		switcher()=delete;
		switcher(const cov::any& val):mCondition(val) {}
		switcher(switcher&&) noexcept=delete;
		switcher(const switcher&)=delete;
		~switcher()=default;
		void add_case(const cov::any& head,const case_type& body)
		{
			if(object::show_warning&&head.type()!=mCondition.type())
				throw cov::warning("W0001");
			bool exsist=false;
			for(auto& it:mCases) {
				if(it.get<0>()==head) {
					exsist=true;
					if(object::show_warning)
						throw cov::warning("W0002");
					else
						it.get<1>()=body;
					break;
				}
			}
			if(!exsist)
				mCases.push_back(tuple<cov::any,cov::function<void()>>(head,body));
		}
		void add_default(const case_type& body)
		{
			if(mDefault.callable()&&object::show_warning)
				throw cov::warning("W0002");
			mDefault=body;
		}
		void perform()
		{
			for(auto& it:mCases) {
				if(it.get<0>()==mCondition&&it.get<1>().callable()) {
					it.get<1>().call();
					return;
				}
			}
			if(mDefault.callable())
				mDefault.call();
		}
	};
	class switcher_stack final {
		std::deque<switcher*> mStack;
	public:
		switcher_stack()=default;
		switcher_stack(switcher_stack&&) noexcept=delete;
		switcher_stack(const switcher_stack&)=delete;
		~switcher_stack()
		{
			for(auto&it:mStack)
				delete it;
		}
		switcher& top()
		{
			return *mStack.front();
		}
		void push(const cov::any& val)
		{
			mStack.push_front(new switcher(val));
		}
		void pop()
		{
			delete mStack.front();
			mStack.pop_front();
		}
	};
	switcher_stack cov_switchers;
}

#define CovSwitch(obj) cov::cov_switchers.push(obj);
#define EndCovSwitch cov::cov_switchers.top().perform();cov::cov_switchers.pop();
#define CovCase(obj) cov::cov_switchers.top().add_case(obj,[&]{
#define CovDefault cov::cov_switchers.top().add_default([&]{
#define EndCovCase });