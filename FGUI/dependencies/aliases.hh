/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>
#include <functional>

// framework includes
#include "color.hh"
#include "definitions.hh"

namespace fgui {

	/*
	 * Thanks to @zxvnme for giving me the idea to use this.
	 *
	 * 
	 * NOTE1: If you don't have a function to match the template, you don't have to do anything.
	 * (Same thing goes for the input aliases.)
	 * 
	 * 
	 * NOTE2: You can use WINAPI functions for the input system too. 
	 */

	// render manager aliases
	using create_font_alias = std::add_pointer_t<void(fgui::font& font, std::string font_family, int size, int flags, bool bold)>; // only call this once!
	using screen_size_alias = std::add_pointer_t<void(int& width, int& height)>;
	using text_size_alias = std::add_pointer_t<void(fgui::font font, std::string text, int& width, int& height)>;
	using rectangle_alias = std::add_pointer_t<void(int x, int y, int width, int height, fgui::color color)>;
	using colored_gradient_alias = std::add_pointer_t<void(int x, int y, int width, int height, fgui::color color1, fgui::color color2, int gradient_type)>;
	using outline_alias = std::add_pointer_t<void(int x, int y, int width, int height, fgui::color color)>;
	using line_alias = std::add_pointer_t<void(int x, int y, int x2, int y2, fgui::color color)>;
	using polygon_alias = std::add_pointer_t<void(int count, fgui::vertex* vertex, fgui::color color)>;
	using text_alias = std::add_pointer_t<void(int x, int y, fgui::color color, fgui::font font, std::string text)>;
	using alpha_alias = std::add_pointer_t<void(int x, int y, int width, int height)>;
	using circle_alias = std::add_pointer_t<void(int x, int y, int radius, int segments, fgui::color color)>;
	using texture_alias = std::add_pointer_t<void(unsigned char* data, int x, int y, int width, int height, float scale)>;
	using gradient_alias = std::add_pointer_t<void(int x, int y, int w, int h, int alpha1, int alpha2, fgui::color color, bool is_horizontal)>;
	using rounded_rectangle_alias = std::add_pointer_t<void(int x, int y, int width, int height, int radius, fgui::color color)>;
	using clip_rect_alias = std::add_pointer_t<void(int x, int y, int width, int height)>;

	struct rendering_functions {

		create_font_alias create_font; // *
		screen_size_alias get_screen_size; // *
		text_size_alias get_text_size; // *
		rectangle_alias rect; // *
		outline_alias outline; // *
		line_alias line; // *
		polygon_alias polygon;
		text_alias text; // *
		circle_alias circle;
		texture_alias texture;
		gradient_alias gradient;
		colored_gradient_alias colored_gradient; // *
		rounded_rectangle_alias rounded_rect;
		alpha_alias alpha; /**/ 
		// ^ (The framework is using this function, but it's not necessary.)
		clip_rect_alias clip_rect; /**/
		// ^ (The framework is also using this function, if you remove it, scrolling will be affected, but it will still work.)

	}; inline rendering_functions render;

	// input system aliases
	using poll_input_alias = std::add_pointer_t<void()>;
	using mouse_position_alias = std::add_pointer_t<void(int& x, int& y)>;
	using mouse_delta_alias = std::add_pointer_t<fgui::point()>;
	using key_hold_alias = std::add_pointer_t<bool(fgui::key key)>;
	using key_press_alias = std::add_pointer_t<bool(fgui::key key)>;
	using in_bounds_alias = std::add_pointer_t<bool(fgui::rect area)>;
	using scroll_delta_alias = std::add_pointer_t<int()>;

	struct input_functions {

		poll_input_alias poll_input; // *
		mouse_position_alias get_mouse_position; // *
		mouse_delta_alias get_mouse_delta; // *
		key_hold_alias get_key_state; // *
		key_press_alias get_key_press; // *
		in_bounds_alias is_mouse_in_region; // *

		scroll_delta_alias get_scroll_delta; /**/
		// ^ (This is not necessary either. If you remove it, you won't be able to scroll with your scroll wheel.)

	}; inline input_functions input;
}
