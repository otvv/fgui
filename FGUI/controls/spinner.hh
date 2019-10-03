/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>

// framework includes
#include "element.hh"

namespace fgui {

    class spinner : public fgui::element {
    public:
        spinner();

        // draw the element
        void draw();

        // set a custom value for the element
		inline void set_value(const int &value) noexcept {

            m_value = value;
        }

		// get the current value of the element
		inline int get_value() const noexcept {

            return m_value;
        }

		// set the boundaries of the element
		void set_boundaries(const int &min, const int &max) noexcept {

            m_min = min;
            m_max = max;
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
        int m_value;
        int m_min, m_max;
        int m_holding_ticks;
        fgui::state m_normal_click;
        fgui::state m_holding_click;
    };
}