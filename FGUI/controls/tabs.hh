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

	class tabs final : public fgui::element {
	public:
		tabs();

		// draw the element
		void draw() override final;

		// adds a new tab
		inline void add_tab(const std::string_view tab_name) noexcept {

			m_info.push_back( { tab_name } );
		}

		// get the current tab selected
		inline std::size_t get_index() const noexcept {

			return m_index;
		} 

		// set the tab layout
		inline void set_layout(const fgui::tab_layout tab_layout) {
			
			m_tab_layout = tab_layout;
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
		fgui::tab_layout m_tab_layout;
		std::vector<fgui::detail::item_info> m_info;
	};
}