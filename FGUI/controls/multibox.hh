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

	class multibox final : public fgui::element {
	public:
		multibox();

		// draw the element
		void draw() override final;

		// add a new item in the element
		inline void add_item(const std::string_view item, const fgui::state &state) noexcept {

			m_info.push_back( { item, state } );
		}

		// select a specific item at a given position
		inline void set_selected(const int &index, const bool &onoff) noexcept {

			m_info[index].checked = onoff;
		}

		// get the item selected at a given position
		inline bool get_selected(int index) const noexcept {

			return m_info[index].checked;
		}

		// sets a custom state for the multibox (if the dropdown list is opened or not)
		inline void set_state(const fgui::state &state) noexcept {

			m_opened = state;
		}

		// returns the current state of the multibox (if the dropdown list is opened or not)
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

		int m_item_height;
		fgui::state m_opened;
		std::vector<fgui::detail::item_info> m_info;
	};
}