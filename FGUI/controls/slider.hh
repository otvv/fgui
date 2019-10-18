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

	class slider final : public fgui::element {
	public:
		slider();

		// draw the element
		void draw() override final;

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

		float m_value;
		bool m_dragging;
		float m_min, m_max;
		std::string m_min_text, m_max_text;
	};
}