/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>

// framework includes
#include "element.hh"

namespace fgui {

	class label : public fgui::element {
	public:
		label();

		// draw the element
		void draw();

		// sets a custom text in the label
		inline void set_text(const std::string_view text) noexcept {

			m_text = text;
		}

		// sets a custom type for the label
		inline void set_type(const fgui::label_type &label_type) noexcept {

			m_type = label_type;
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

		std::string_view m_text;
		fgui::label_type m_type;
	};
}