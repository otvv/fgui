/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <map>
#include <array>
#include <string>
#include <memory>

// framework includes
#include "../controls/element.hh"
#include "../controls/container.hh"
#include "../dependencies/color.hh"
#include "../dependencies/definitions.hh"

namespace fgui {

	struct style {

		/*
		* You can add your own styles here.
		*
		* Just follow the template above:
		*
		* std::array<fgui::color, 2> button = { fgui::color(45, 45, 45), fgui::color(25, 25, 25) };
		* 
		* In case you want to remove or add a new color just increase/decrease the array size.
		*/

		/*
		 * Usage: fgui::handler::style st = get_style();
		 *
		 * to apply the style into something:
		 * fgui::color(st.button.at(0)); 
		 * or 
		 * { st.button.at(0) }
		 *
		 *
		 * to edit the color:
		 * st.button.at(0) = fgui::color(25, 200, 75);
		 * or
		 * st.button.at(0) = { 25, 200, 75 }; 
		 * 
		 * NOTE: When using braces inicializations the framework will always use the default constructor from the color class.
		 * (R, G, B, A = 255)
		 *
		 */

		// general
		std::array<fgui::color, 5> text = { fgui::color(181, 181, 181), fgui::color(215, 215, 100), fgui::color(65, 135, 255), fgui::color(245, 245, 245), fgui::color(137, 162, 204) };
		std::array<fgui::color, 2> cursor = { fgui::color(255, 255, 255), fgui::color(0, 0, 0) };

		// elements
		std::array<fgui::color, 4> button = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 5> checkbox = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255), fgui::color(46, 119, 191) };
		std::array<fgui::color, 4> colorlist = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 4> colorpicker = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 4> combobox = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 3> container = { fgui::color(85, 85, 85), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 4> keybinder = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 6> label = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(181, 181, 181), fgui::color(65, 158, 255), fgui::color(65, 135, 255) };
		std::array<fgui::color, 4> listbox = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 4> multibox = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 5> slider = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255), fgui::color(46, 119, 191) };
		std::array<fgui::color, 4> spinner = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 5> tabs = { fgui::color(85, 85, 85), fgui::color(15, 15, 15), fgui::color(40, 40, 40), fgui::color(35, 35, 35), fgui::color(60, 60, 60) };
		std::array<fgui::color, 4> textbox = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };
		std::array<fgui::color, 5> window = { fgui::color(25, 25, 25), fgui::color(40, 40, 40), fgui::color(61, 200, 255), fgui::color(61, 158, 255), fgui::color(46, 119, 191) };
	};

	namespace handler {

		// register a new window
		void register_window(std::shared_ptr<fgui::container> window);

		// render window
		void render_window();

		// set a toggle key for the window
		void set_key(fgui::key key, std::shared_ptr<fgui::container> window);

		// sets the cursor type that will be displayed on the window
		void set_cursor(fgui::cursor_type type);

		// handle the cursors
		void draw_cursors();

		// enable/disable the keyboard and mouse input
		void set_input_state(fgui::input_state state);

		// get the window style
		fgui::style get_style();
	}

	inline fgui::style m_window_style;
	inline fgui::input_state m_input_state;
	inline fgui::cursor_type m_cursor_type;
	inline std::shared_ptr<fgui::element> m_focused_element;
	inline std::vector<std::shared_ptr<fgui::container>> m_windows;
	inline std::map<int, std::shared_ptr<fgui::container>> m_binds;
}