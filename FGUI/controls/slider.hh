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
		void set_value(float value);

		// get the current value of the element
		float get_value();

		// set the boundaries of the element
		void set_boundaries(float min, float max);

		// set the min and max custom text
		void set_boundaries_text(std::string min_text, std::string max_text);

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

		float m_value;
		bool m_dragging;
		float m_min, m_max;
		std::string m_min_text, m_max_text;
	};
}