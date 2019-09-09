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

	class listbox : public fgui::element {
	public:
		listbox();

		// draw the element
		void draw();

		// add a new item in the element
		void add_item(std::string item, int value = 0);

		// returns the name of the selected item
		std::string get_item();

		// get the index of the selected item
		int get_index();

		// get the value of a selected item
		int get_value();

		// set a pre-selected item for the element
		void set_index(int index);

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
		std::vector<std::pair<std::string, int>> m_items;
	};
}
