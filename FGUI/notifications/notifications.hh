/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>
#include <vector>
#include <memory>

// framework includes
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"
#include "../dependencies/definitions.hh"

namespace fgui {

    struct notification_info {
        
        notification_info(const std::string_view _text, const fgui::animation_type &_animation_type) : tick(0), animation_progress(0.f), text(_text), state(true), animation_type(_animation_type) {}
        
        int tick;
        int animation_progress;
        std::string text;
        fgui::state state;
        fgui::animation_type animation_type;
    };
    
    class notification {
    public:
        notification();

        // draw notifications
        void draw();

        // creates a new notification
        inline void add_notification(const std::string_view _text, const fgui::animation_type &_animation_type) noexcept {
            
            m_info.push_back({_text, _animation_type});
        }

		// allows the user to change the font of the notification
		inline void set_font(const std::string_view font_family, int size, int flags = 0, bool bold = false) noexcept {

			fgui::render.create_font(m_font, font_family, size, flags, bold);
		}

		inline void set_font(const fgui::element_font &element_font) noexcept {

			fgui::render.create_font(m_font, element_font.family, element_font.size, element_font.flags, element_font.bold);
		}

        // set default notification position of the screen
        inline void set_position(const int &x, const int &y) noexcept {
            m_x = x;
            m_y = y;
        }

        inline void set_position(const fgui::point& position) noexcept {
            m_x = position.x;
            m_y = position.y;
        }

		// returns the font that the notification is currently using
		inline fgui::font get_font() const noexcept {

            return m_font;
        }

        // handle notification updates
        void update();

        // handle notification mouse and keyboard input
        void handle_input();

    private:
        int m_x, m_y;
        fgui::font m_font;
        int m_stay_time;
        int m_width, m_height;
        std::vector<fgui::notification_info> m_info;
    };
}