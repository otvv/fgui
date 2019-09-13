/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>
#include <vector>
#include <algorithm>

// framework includes
#include "element.hh"

namespace fgui {

	class combobox : public fgui::element {
	public:
		combobox();

		// draw the element
		void draw();
		
		// add a new entry in the combobox
		void add_item(std::string item, int value = 0);

		// clear all entries of the combobox
		void clear_items();

		// this will trigger a function whenever you select a new item 
		void set_function(std::function<void()> callback);

		// select a specific entry of the combobox
		void set_index(int index);

		// get the index of the current selected entry
		int get_index();

		// get the value of the selected item
		int get_value();

		// sets a custom state for the combobox (if the dropdown list is opened or not)
		void set_state(fgui::state state);

		// returns the current state of the combobox (if the dropdown list is opened or not)
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

		int m_index;
		bool m_dragging;
		int m_slider_top;
		int m_item_height;
		fgui::state m_opened;
		std::function<void()> m_callback;
		std::vector<fgui::item_info> m_info;
	};
}
