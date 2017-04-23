#define DARWIN_FORCE_BUILTIN
#include "../include/darwin/darwin.hpp"
#include "../include/mozart/switcher.hpp"
#ifndef CBS_DARWIN_EXT
#include "./extension.hpp"
#endif
static cov_basic::extension darwin_ext;
namespace darwin_cbs_ext {
	using namespace cov_basic;
// Graphics
	darwin::sync_clock clock(30);
	cov::any load(array& args)
	{
		if(args.empty())
			darwin::runtime.load("./darwin.module");
		else
			darwin::runtime.load(args.at(0).const_val<std::string>());
		return number(0);
	}
	cov::any fit_drawable(array& args)
	{
		darwin::runtime.fit_drawable();
		return number(0);
	}
	cov::any set_frame_limit(array& args)
	{
		clock.set_freq(args.at(0).const_val<number>());
		return number(0);
	}
	cov::any update_drawable(array& args)
	{
		darwin::runtime.update_drawable();
		clock.sync();
		clock.reset();
		return number(0);
	}
	cov::any clear_drawable(array& args)
	{
		if(args.empty())
			darwin::runtime.get_drawable()->clear();
		else
			args.at(0).val<darwin::picture>(true).clear();
		return number(0);
	}
	cov::any fill_drawable(array& args)
	{
		if(args.size()==1&&args.at(0).type()==typeid(darwin::pixel))
			darwin::runtime.get_drawable()->fill(args.at(0).const_val<darwin::pixel>());
		else if(args.size()==2&&args.at(0).type()==typeid(darwin::picture)&&args.at(1).type()==typeid(darwin::pixel))
			args.at(0).val<darwin::picture>(true).fill(args.at(1).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any resize_drawable(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->resize(args.at(0).const_val<number>(),args.at(1).const_val<number>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).resize(args.at(1).const_val<number>(),args.at(2).const_val<number>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any get_height(array& args)
	{
		if(args.empty())
			return number(darwin::runtime.get_drawable()->get_height());
		else
			return number(args.at(0).const_val<darwin::picture>().get_height());
	}
	cov::any get_width(array& args)
	{
		if(args.empty())
			return number(darwin::runtime.get_drawable()->get_width());
		else
			return number(args.at(0).const_val<darwin::picture>().get_width());
	}
	cov::any draw_point(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->draw_pixel(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<darwin::pixel>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).draw_pixel(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any draw_picture(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->draw_picture(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<darwin::picture>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).draw_picture(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<darwin::picture>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any draw_line(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->draw_line(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<darwin::pixel>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).draw_line(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<number>(),args.at(5).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any draw_rect(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->draw_rect(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<darwin::pixel>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).draw_rect(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<number>(),args.at(5).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any fill_rect(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->fill_rect(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<darwin::pixel>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).fill_rect(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<number>(),args.at(5).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any draw_triangle(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->draw_triangle(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<number>(),args.at(5).const_val<number>(),args.at(6).const_val<darwin::pixel>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).draw_triangle(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<number>(),args.at(5).const_val<number>(),args.at(6).const_val<number>(),args.at(7).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any fill_triangle(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->fill_triangle(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<number>(),args.at(5).const_val<number>(),args.at(6).const_val<darwin::pixel>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).fill_triangle(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<number>(),args.at(4).const_val<number>(),args.at(5).const_val<number>(),args.at(6).const_val<number>(),args.at(7).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any draw_string(array& args)
	{
		if(args.at(0).type()==typeid(number))
			darwin::runtime.get_drawable()->draw_string(args.at(0).const_val<number>(),args.at(1).const_val<number>(),args.at(2).const_val<string>(),args.at(3).const_val<darwin::pixel>());
		else if(args.at(0).type()==typeid(darwin::picture))
			args.at(0).val<darwin::picture>(true).draw_string(args.at(1).const_val<number>(),args.at(2).const_val<number>(),args.at(3).const_val<string>(),args.at(4).const_val<darwin::pixel>());
		else
			throw syntax_error("Arguments error.");
		return number(0);
	}
	cov::any log(array& args)
	{
		Darwin_Log(args.front().to_string().c_str());
		return number(0);
	}
	cov::any is_kb_hit(array& args)
	{
		return darwin::runtime.is_kb_hit();
	}
	cov::any get_kb_hit(array& args)
	{
		return number(darwin::runtime.get_kb_hit());
	}
	cov::any get_ascii(array& args)
	{
		return number(args.at(0).val<string>().at(0));
	}
	cov::any pixel(array& args)
	{
		return darwin::pixel(args.at(0).const_val<std::string>().at(0),args.at(1).const_val<bool>(),args.at(2).const_val<bool>(),args.at(3).const_val<darwin::colors>(),args.at(4).const_val<darwin::colors>());
	}
	cov::any picture(array& args)
	{
		if(args.empty())
			return darwin::picture();
		else
			return darwin::picture(args.at(0).const_val<number>(),args.at(1).const_val<number>());
	}
	void init()
	{
		darwin_ext.add_var("load",native_interface(load));
		darwin_ext.add_var("fit_drawable",native_interface(fit_drawable));
		darwin_ext.add_var("set_frame_limit",native_interface(set_frame_limit));
		darwin_ext.add_var("update_drawable",native_interface(update_drawable));
		darwin_ext.add_var("clear_drawable",native_interface(clear_drawable));
		darwin_ext.add_var("fill_drawable",native_interface(fill_drawable));
		darwin_ext.add_var("resize_drawable",native_interface(resize_drawable));
		darwin_ext.add_var("get_height",native_interface(get_height));
		darwin_ext.add_var("get_width",native_interface(get_width));
		darwin_ext.add_var("draw_point",native_interface(draw_point));
		darwin_ext.add_var("draw_picture",native_interface(draw_picture));
		darwin_ext.add_var("draw_line",native_interface(draw_line));
		darwin_ext.add_var("draw_rect",native_interface(draw_rect));
		darwin_ext.add_var("fill_rect",native_interface(fill_rect));
		darwin_ext.add_var("draw_triangle",native_interface(draw_triangle));
		darwin_ext.add_var("fill_triangle",native_interface(fill_triangle));
		darwin_ext.add_var("draw_string",native_interface(draw_string));
		darwin_ext.add_var("log",native_interface(log));
		darwin_ext.add_var("is_kb_hit",native_interface(is_kb_hit));
		darwin_ext.add_var("get_kb_hit",native_interface(get_kb_hit));
		darwin_ext.add_var("get_ascii",native_interface(get_ascii));
		darwin_ext.add_var("pixel",native_interface(pixel));
		darwin_ext.add_var("picture",native_interface(picture));
		darwin_ext.add_var("black",darwin::colors::black);
		darwin_ext.add_var("white",darwin::colors::white);
		darwin_ext.add_var("red",darwin::colors::red);
		darwin_ext.add_var("green",darwin::colors::green);
		darwin_ext.add_var("blue",darwin::colors::blue);
		darwin_ext.add_var("pink",darwin::colors::pink);
		darwin_ext.add_var("yellow",darwin::colors::yellow);
		darwin_ext.add_var("cyan",darwin::colors::cyan);
	}
}
#ifndef CBS_DARWIN_EXT
cov_basic::extension* cbs_extension()
{
	darwin_cbs_ext::init();
	return &darwin_ext;
}
#endif
