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

	class checkbox final : public fgui::element {
	public:
		checkbox();

		// draw the element
		void draw() override final;

		// defines the state of the checkbox
		inline void set_bool(const bool &onoff) noexcept {
			
			m_checked = onoff;
		}

		// returns the checkbox state
		inline bool get_bool() const noexcept {

			return m_checked;
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
		bool m_checked;
	};
}