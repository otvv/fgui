/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <array>
#include <algorithm>

// framework includes
#include "aliases.hh"
#include "definitions.hh"

namespace fgui {

    // you are not suposed to edit the contents of this namespace, unless you know what you are doing.
    namespace detail {
        
        inline fgui::rect m_hovered_area;
        inline fgui::point m_mouse_position, m_mouse_position_delta;
        inline fgui::delta m_scroll_wheel_delta;
        inline std::array<bool, 256> m_key_state, m_old_key_state;
    }

    namespace input_system {

        inline void listen() {

            static fgui::point last_known_position = {0, 0};

            // copy new keys (current being pressed) to old keys (already pressed)
            std::copy(fgui::detail::m_key_state.begin(), fgui::detail::m_key_state.end(), fgui::detail::m_old_key_state.begin());

            for (std::size_t i = 0; i < 256 /* KEY_MAX */; i++)
                fgui::detail::m_key_state.at(i) = fgui::input.get_key_state(i);

            // get mouse position
            fgui::detail::m_mouse_position = fgui::input.get_mouse_position();

            // calculate the cursor delta
            fgui::detail::m_mouse_position_delta = {(fgui::detail::m_mouse_position.x - last_known_position.x), (fgui::detail::m_mouse_position.y - last_known_position.y)};

            // get scroll message delta
            fgui::detail::m_scroll_wheel_delta = fgui::input.get_scroll_delta();

            // get last known cursor position
            last_known_position = fgui::detail::m_mouse_position;
        }

        // check if a specific key is being held
        inline fgui::state key_held(const fgui::key &key) noexcept {

            return (fgui::detail::m_key_state[key]);
        }

        // check if a specific key is pressed (clicked)
        inline const fgui::state key_press(const fgui::key &key) noexcept {
            
            return (fgui::detail::m_key_state[key] && !fgui::detail::m_old_key_state[key]);
        }
        
        // check if a specific key was released
        inline const fgui::state key_released(const fgui::key &key) noexcept {

            return (!fgui::detail::m_key_state[key] && fgui::detail::m_old_key_state[key]);
        }

        // check if the mouse cursor is on a certain area
        inline const fgui::state mouse_in_area(const fgui::rect &area) noexcept {
            return (fgui::detail::m_mouse_position.x > area.left && fgui::detail::m_mouse_position.y > area.top && fgui::detail::m_mouse_position.x < area.left + area.right &&fgui::detail:: m_mouse_position.y < area.top + area.bottom);
        }

        inline const fgui::state mouse_in_area(const int &x, const int &y, const int &w, const int &h) noexcept {
            return (fgui::detail::m_mouse_position.x > x && fgui::detail::m_mouse_position.y > y && fgui::detail::m_mouse_position.x < x + w && fgui::detail::m_mouse_position.y < y + h);
        }

        // get scroll message delta (up, down)
        inline const fgui::delta scroll_delta() noexcept {

            return fgui::detail::m_scroll_wheel_delta;
        }

        // get cursor position
        inline const fgui::point mouse_position() noexcept {

            return fgui::detail::m_mouse_position;
        }

        // get cursor position delta
        inline const fgui::point mouse_position_delta() noexcept {
            
            return fgui::detail::m_mouse_position_delta;
        }
    };
}