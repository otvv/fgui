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

	class listbox final : public fgui::element {
	public:
		listbox();

		// draw the element
		void draw() override final;

		// add a new item in the element
		inline void add_item(const std::string_view item, const int &value = 0) noexcept {

			m_info.push_back( {item, value } );
		}

		// returns the name of the selected item
		inline std::string_view get_item() const noexcept {

			return m_info[m_index].item;
		}

		// get the index of the selected item
		inline int get_index() const noexcept {

			return m_index;
		}

		// get the value of a selected item
		inline int get_value() const noexcept {

			return m_info[m_index].value;
		}

		// set a pre-selected item for the element
		inline void set_index(const int &index) noexcept {

			m_index = index;
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
		std::vector<fgui::detail::item_info> m_info;
	};
}
