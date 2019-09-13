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

	class multibox : public fgui::element {
	public:
		multibox();

		// draw the element
		void draw();

		// add a new item in the element
		void add_item(std::string item, bool state);

		// select a specific item at a given position
		void set_selected(int index, bool state);

		// get the item selected at a given position
		bool get_selected(int index);

		// sets a custom state for the multibox (if the dropdown list is opened or not)
		void set_state(fgui::state state);

		// returns the current state of the multibox (if the dropdown list is opened or not)
		fgui::state get_state();

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

		int m_item_height;
		fgui::state m_opened;
		std::vector<fgui::item_info> m_info;
	};
}