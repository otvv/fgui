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

		// sets a custom function for the button
		void set_function(std::function<void()> callback);

		// handle keyboard and mouse input
		void handle_input();

		// handle the element updates
		void update();

		// element tooltip
		void tooltip();

		// save the element state
		void save(const std::string& file_name, nlohmann::json& json_module);

		// load the element state
		void load(const std::string& file_name);
	private:
		std::function<void()> m_callback;
	};
}