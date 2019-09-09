/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>
#include <functional>

// framework includes
#include "element.hh"

namespace fgui {

	class tabs : public fgui::element {
	public:
		tabs();

		// draw the element
		void draw();

		// adds a new tab
		void add_tab(std::string tab_name);

		// get the current tab selected
		int get_index();

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

		int m_selected_tab;
		std::vector<fgui::item_info> m_info;
	};
}