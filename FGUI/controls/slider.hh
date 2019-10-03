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

	class slider : public fgui::element {
	public:
		slider();

		// draw the element
		void draw();

		// set a custom value for the element
		inline void set_value(const float &value) noexcept {

			m_value = value;
		}

		// get the current value of the element
		inline float get_value() const noexcept {

			return m_value;
		}

		// set the boundaries of the element
		inline void set_boundaries(const float &min, const float &max) noexcept {

			m_min = min;
			m_max = max;
		}

		// set the min and max custom text
		inline void set_boundaries_text(const std::string_view min_text, const std::string_view max_text) noexcept {

			m_min_text = min_text;
			m_max_text = max_text;
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

		float m_value;
		bool m_dragging;
		float m_min, m_max;
		std::string m_min_text, m_max_text;
	};
}