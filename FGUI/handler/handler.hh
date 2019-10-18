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
#include "../dependencies/input.hh"
#include "../dependencies/definitions.hh"
#include "../notifications/notifications.hh"

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
		std::array<fgui::color, 4> notifications = { fgui::color(85, 85, 85), fgui::color(45, 45, 45), fgui::color(25, 25, 25), fgui::color(61, 158, 255) };

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

	// Man that's nasty. I should probably remake this as soon as possible.
	inline fgui::style m_window_style;
	inline fgui::input_state m_input_state;
	inline fgui::cursor_type m_cursor_type;
	inline std::shared_ptr<fgui::element> m_focused_element;
	inline std::vector<std::shared_ptr<fgui::container>> m_windows;
	inline std::map<int, std::shared_ptr<fgui::container>> m_binds;
	inline std::shared_ptr<fgui::notification> m_notifications;

	namespace handler {

		// register a new window
		inline const void register_window(const std::shared_ptr<fgui::container> &window) noexcept {
			
			m_windows.push_back(window);
		}

		// register the notifications
		inline const void register_notifications(const int &x, const int &y, const fgui::element_font &notification_font) noexcept {

			m_notifications = std::make_shared<fgui::notification>();
			m_notifications->set_position(x, y);
			m_notifications->set_font(notification_font);
		}

		// render window
		void render_window();

		// set a toggle key for the window
		inline const void set_key(const fgui::key &key, const std::shared_ptr<fgui::container> &window) noexcept {

			if (window)
				m_binds[key] = window;
			else
				m_binds.erase(key);
		}

		// sets the cursor type that will be displayed on the window
		inline const void set_cursor(const fgui::cursor_type &cursor_type) noexcept {

			m_cursor_type = cursor_type;
		}

		// handle the cursors
		static void draw_cursors();

		// enable/disable the keyboard and mouse input
		inline const void set_input_state(const fgui::input_state &input_state) noexcept {

			m_input_state = input_state;
		}

		// get the window style
		inline const fgui::style get_style() noexcept {

			return m_window_style;
		}

		// call a notification
		inline const void call_notification(const std::string_view notification_text, const fgui::animation_type &animation_type) noexcept {	
			
			m_notifications->add_notification(notification_text, animation_type);
		}
	}
}