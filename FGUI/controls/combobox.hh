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

	class combobox final : public fgui::element {
	public:
		combobox();

		// draw the element
		void draw() override final;
		
		// add a new entry in the combobox
		inline void add_item(const std::string_view item, const int &value = 0) noexcept {

			m_info.push_back({ item, value }); 
		}

		// clear all entries of the combobox
		inline void clear_items() noexcept {

			m_info.clear();
		}

		// this will trigger a function when the user selects a new item
		inline void set_function(const std::function<void()> &callback) noexcept {
			
			m_callback = callback;
		}

		// select a specific entry of the combobox
		inline void set_index(int index) noexcept {

			m_index = index;
		}

		// get the index of the current selected entry
		inline int get_index() const noexcept {

			return m_index;
		}

		// get the value of the selected item
		inline int get_value() const noexcept {

			return m_info[m_index].value;
		}

		// sets a custom state for the combobox (if the dropdown list is opened or not)
		inline void set_state(fgui::state state) {

			m_opened = state;
		}

		// returns the current state of the combobox (if the dropdown list is opened or not)
		inline fgui::state get_state() const noexcept {
			
			return m_opened;
		}

		// handle keyboard and mouse input
		void handle_input() override final;

		// handle the element updates
		void update() override final;

		// element tooltip
		void tooltip() override final;

		// save the element state
		void save(nlohmann::json& json_module) override final;

		// load the element state
		void load(const std::string_view file_name) override final;
	private:

		std::size_t m_index;
		bool m_dragging;
		int m_slider_top;
		int m_item_height;
		fgui::state m_opened;
		std::function<void()> m_callback;
		std::vector<fgui::detail::item_info> m_info;
	};
}
