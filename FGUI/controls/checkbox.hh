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
		void draw();

		// defines the state of the checkbox
		inline void set_bool(const bool &onoff) noexcept {
			
			m_checked = onoff;
		}

		// returns the checkbox state
		inline bool get_bool() const noexcept {

			return m_checked;
		}

		// handle keyboard and mouse input
		void handle_input();

		// handle the element updates
		void update();

		// element tooltip
		void tooltip();

		// save the element state
		void save(nlohmann::json& json_module);

		// load the element state
		void load(const std::string_view file_name);
	private:
		bool m_checked;
	};
}