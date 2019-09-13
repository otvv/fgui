/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>
#include <vector>

// framework includes
#include "element.hh"

namespace fgui {

	class checkbox : public fgui::element {
	public:
		checkbox();

		// draw the element
		void draw();

		// defines the state of the checkbox
		void set_bool(bool onoff);

		// returns the checkbox state
		bool get_bool();

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
		bool m_checked;
	};
}