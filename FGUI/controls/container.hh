/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <functional>

// framework includes
#include "element.hh"

namespace fgui {

	class container : public fgui::element {
	public:
		container();

		// draw the element
		void draw();

		// set the container state (on/off)
		void set_state(bool state);

		// returns the state of the container
		bool get_state();

		// save all elements inside a config file
		void save_config(const std::string& file_name);

		// add a new control in the container
		void add_control(std::shared_ptr<fgui::element> control, int page_index = -1, bool manual_size = false);

		// checks if the user is hovering a container
		bool hovering();

		// set whether or not the scrollbar should be used
		void set_scrollbar_state(bool state);

		// enable/disable the resizeable option of the container
		void set_resize_state(bool state);

		// returns true if the container has a scrollbar
		bool get_scrollbar_state();

		// get the amount that a element is suposed to move according with the scrollbar
		int get_scroll_offset();

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

		int m_scroll_offset, m_bottom_element_pos;
		bool m_opened, m_dragging_container;
		bool m_resizeable, m_size_changing;
		bool m_scrollbar_state, m_dragging_scrollbar;
		std::vector<std::shared_ptr<fgui::element>> m_elements;
	};
}