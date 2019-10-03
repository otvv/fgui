/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>
#include <vector>
#include <functional>

// framework includes
#include "element.hh"

namespace fgui {

	class button : public fgui::element {
	public:
		button();

		// draw the element
		void draw();

		// set the function that the button will call when clicked
		inline void set_function(const std::function<void()> &callback) noexcept {

			m_callback = callback; 
		}

		// handle keyboard and mouse input
		void handle_input();

		// handle the element updates
		void update();

		// element tooltip
		void tooltip();

		// save the element state
		void save(nlohmann::json& json_module);

		// load the element state
		void load(const std::string_view file_name);
	private:
		std::function<void()> m_callback;
	};
}