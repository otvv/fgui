/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

// includes
#include "handler.hh"
#include "../dependencies/aliases.hh"

void fgui::handler::register_window(std::shared_ptr<fgui::container> window) {

	m_windows.emplace_back(window);
}

//---------------------------------------------------------
void fgui::handler::render_window() {

	bool overlaying_window_clicked = false;

	if (m_input_state == fgui::input_state::UNLOCKED) {

		// enable input
		fgui::input.poll_input();
	}

	// bindings
	for (auto &binded_key : m_binds) {

		// toggle the window on and off
		if (fgui::input.get_key_press(binded_key.first))
			binded_key.second->set_state(!binded_key.second->get_state());
	}

	for (std::size_t i = 0; i < m_windows.size(); i++) {

		// main window 
        auto main_window = m_windows.at(i);

		if (main_window->get_state()) {

			// draw and update
        	main_window->update();
       		main_window->draw();

			// draw cursors
			draw_cursors();
		}

		// other window
        auto other_window = m_windows.at(m_windows.size() - 1 - i);

        if (other_window && other_window->hovering()) {

            if (!overlaying_window_clicked && fgui::input.get_key_press(MOUSE_LEFT)) {

                overlaying_window_clicked = true;
                
				m_windows.erase(m_windows.end() - i - 1);    
				m_windows.push_back(other_window);
            }
        }
    }
}

//---------------------------------------------------------
void fgui::handler::set_key(fgui::key key, std::shared_ptr<fgui::container> window) {

	if (window)
		m_binds[key] = window;

	else if (!window)
		m_binds.erase(key);
}

//---------------------------------------------------------
void fgui::handler::set_cursor(fgui::cursor_type type) {

	m_cursor_type = type;
}

//---------------------------------------------------------
void fgui::handler::set_input_state(fgui::input_state state) {

	m_input_state = state;
}

//---------------------------------------------------------
fgui::style fgui::handler::get_style() {

	return m_window_style;
}

//---------------------------------------------------------
void fgui::handler::draw_cursors() {

	static fgui::point cursor = {0, 0};

	// get the window style
	auto style = get_style();

	if (m_input_state == fgui::input_state::UNLOCKED) {

		// get the cursor position
		fgui::input.get_mouse_position(cursor.x, cursor.y);
	}

	//
	// cursor types
	//

	if (m_cursor_type == fgui::cursor_type::ARROW) {

		fgui::render.rect(cursor.x + 1, cursor.y, 1, 17, fgui::color(style.cursor.at(1)));

		for (std::size_t i = 0; i < 11; i++)
			fgui::render.rect(cursor.x + 2 + i, cursor.y + 1 + i, 1, 1, fgui::color(style.cursor.at(1)));

		fgui::render.rect(cursor.x + 8, cursor.y + 12, 5, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 8, cursor.y + 13, 1, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 9, cursor.y + 14, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 10, cursor.y + 16, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 8, cursor.y + 18, 2, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 7, cursor.y + 16, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 6, cursor.y + 14, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 5, cursor.y + 13, 1, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 4, cursor.y + 14, 1, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 3, cursor.y + 15, 1, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 2, cursor.y + 16, 1, 1, fgui::color(style.cursor.at(1)));

		for (std::size_t i = 0; i < 4; i++)
			fgui::render.rect(cursor.x + 2 + i, cursor.y + 2 + i, 1, 14 - (i * 2), fgui::color(style.cursor.at(0)));

		fgui::render.rect(cursor.x + 6, cursor.y + 6, 1, 8, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x + 7, cursor.y + 7, 1, 9, fgui::color(style.cursor.at(0)));

		for (std::size_t i = 0; i < 4; i++)
			fgui::render.rect(cursor.x + 8 + i, cursor.y + 8 + i, 1, 4 - i, fgui::color(style.cursor.at(0)));

		fgui::render.rect(cursor.x + 8, cursor.y + 14, 1, 4, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x + 9, cursor.y + 16, 1, 2, fgui::color(style.cursor.at(0)));
	}

	else if (m_cursor_type == fgui::cursor_type::IBEAM) {

		fgui::render.rect(cursor.x - 1, cursor.y - 1, 6 + 2, 1 + 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x, cursor.y, 7, 1, fgui::color(style.cursor.at(0)));

		fgui::render.rect(cursor.x - 1 + 3, cursor.y - 1 + 1, 1 + 2, 9 + 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 3, cursor.y + 1, 1, 9, fgui::color(style.cursor.at(0)));

		fgui::render.rect(cursor.x - 1, cursor.y - 1 + 9, 6 + 2, 1 + 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x, cursor.y + 9, 7, 1, fgui::color(style.cursor.at(0)));
	}

	else if (m_cursor_type == fgui::cursor_type::HAND) {

		fgui::render.rect(cursor.x - 5 + 6, cursor.y + 5 + 5 + -5, 7, 9, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 5, cursor.y + 5 + 7 + -5, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 1, cursor.y + 5 + 6 + -5, 1, 1, fgui::color(style.cursor.at(1)));

		for (std::size_t i = 0; i < 3; ++i)
			fgui::render.rect(cursor.x - 5 + 2 + i, cursor.y + 5 + 6 + i + -5, 1, 1, fgui::color(style.cursor.at(1)));

		for (std::size_t i = 0; i < 4; ++i) {
			fgui::render.rect(cursor.x - 5 + 1 + i, cursor.y + 5 + 9 + i + -5, 1, 1, fgui::color(style.cursor.at(1)));
			fgui::render.rect(cursor.x - 5 + 1 + i, cursor.y + 5 + 7 + i + -5, 1, 1, fgui::color(style.cursor.at(0)));
			fgui::render.rect(cursor.x - 5 + 2 + i, cursor.y + 5 + 7 + i + -5, 1, 1, fgui::color(style.cursor.at(0)));
			fgui::render.rect(cursor.x - 5 + 1 + i, cursor.y + 5 + 8 + i + -5, 1, 1, fgui::color(style.cursor.at(0)));
			fgui::render.rect(cursor.x - 5 + 3 + i, cursor.y + 5 + 11 + i + -5, 1, 1, fgui::color(style.cursor.at(0)));
		}

		fgui::render.rect(cursor.x - 5 + 4, cursor.y + 5 + 1 + -5, 1, 7, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 5, cursor.y + 5 + 0 + -5, 2, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 5, cursor.y + 5 + 15 + -5, 5, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 7, cursor.y + 5 + 1 + -5, 1, 6, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 8, cursor.y + 5 + 4 + -5, 4, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 10, cursor.y + 5 + 5 + -5, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 12, cursor.y + 5 + 5 + -5, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 13, cursor.y + 5 + 5 + -5, 1, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 14, cursor.y + 5 + 6 + -5, 1, 5, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 13, cursor.y + 5 + 11 + -5, 1, 2, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x - 5 + 12, cursor.y + 5 + 13 + -5, 1, 3, fgui::color(style.cursor.at(1)));

		fgui::render.rect(cursor.x - 5 + 5, cursor.y + 5 + 1 + -5, 2, 13, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 5 + 7, cursor.y + 5 + 14 + -5, 3, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 5 + 13, cursor.y + 5 + 6 + -5, 1, 5, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 5 + 11, cursor.y + 5 + 14 + -5, 1, 1, fgui::color(style.cursor.at(0)));

		for (std::size_t i = 0; i < 2; ++i) {
			fgui::render.rect(cursor.x - 5 + 10 + i, cursor.y + 5 + 14 + i + -5, 1, 1, fgui::color(style.cursor.at(1)));
			fgui::render.rect(cursor.x - 5 + 4 + i, cursor.y + 5 + 13 + i + -5, 1, 1, fgui::color(style.cursor.at(1)));
		}
	}

	else if (m_cursor_type == fgui::cursor_type::PIPETTE) {

		fgui::render.rect(cursor.x, cursor.y + 14 + -15, 1, 1, fgui::color(style.cursor.at(1)));

		for (std::size_t i = 0; i < 2; ++i) {

			fgui::render.rect(cursor.x + i, cursor.y + 13 - i + -15, 1, 1, fgui::color(style.cursor.at(1)));
			fgui::render.rect(cursor.x + 1 + i, cursor.y + 14 - i + -15, 1, 1, fgui::color(style.cursor.at(1)));
		}

		for (std::size_t i = 0; i < 6; ++i) {

			fgui::render.rect(cursor.x + 1 + i, cursor.y + 11 - i + -15, 1, 1, fgui::color(style.cursor.at(1)));
			fgui::render.rect(cursor.x + 3 + i, cursor.y + 13 - i + -15, 1, 1, fgui::color(style.cursor.at(1)));

			fgui::render.rect(cursor.x + 2 + i, cursor.y + 11 - i + -15, 1, 1, fgui::color(style.cursor.at(0)));
			fgui::render.rect(cursor.x + 3 + i, cursor.y + 12 - i + -15, 1, 1, fgui::color(style.cursor.at(0)));
			fgui::render.rect(cursor.x + 2 + i, cursor.y + 12 - i + -15, 1, 1, fgui::color(style.cursor.at(0)));
		}

		fgui::render.rect(cursor.x + 8, cursor.y + 6 + -15, 1, 1, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 7, cursor.y + 3 + -15, 6, 3, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 9, cursor.y + 2 + -15, 3, 6, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 11, cursor.y + -15, 3, 5, fgui::color(style.cursor.at(1)));
		fgui::render.rect(cursor.x + 10, cursor.y + 1 + -15, 5, 3, fgui::color(style.cursor.at(1)));
	}

	else if (m_cursor_type == fgui::cursor_type::RESIZE) {
		
		// up arrow
		fgui::render.rect(cursor.x - 5, cursor.y - 1, 5, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 4, cursor.y - 2, 3, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 3, cursor.y - 3, 1, 1, fgui::color(style.cursor.at(0)));

		// middle
		fgui::render.rect(cursor.x - 3, cursor.y, 1, 12, fgui::color(style.cursor.at(0)));

		// down arrow
		fgui::render.rect(cursor.x - 5, cursor.y + 11, 5, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 4, cursor.y + 12, 3, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 3, cursor.y + 13, 1, 1, fgui::color(style.cursor.at(0)));
	}

	else if (m_cursor_type == fgui::cursor_type::MOVE) {
		
		// up arrow
		fgui::render.rect(cursor.x - 5, cursor.y - 1, 5, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 4, cursor.y - 2, 3, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 3, cursor.y - 3, 1, 1, fgui::color(style.cursor.at(0)));

		// left arrow
		fgui::render.rect(cursor.x - 3 - 7, cursor.y + 11 - 7, 1, 5, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 4 - 7, cursor.y + 12 - 7, 1, 3, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 5 - 7, cursor.y + 13 - 7, 1, 1, fgui::color(style.cursor.at(0)));

		// cross
		fgui::render.rect(cursor.x - 3 - (12 / 2), cursor.y + (12 / 2), 12, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 3, cursor.y, 1, 12, fgui::color(style.cursor.at(0)));

		// down arrow
		fgui::render.rect(cursor.x - 5, cursor.y + 12, 5, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 4, cursor.y + 13, 3, 1, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 3, cursor.y + 14, 1, 1, fgui::color(style.cursor.at(0)));

		// right arrow
		fgui::render.rect(cursor.x - 5 + 8, cursor.y + 11 - 7, 1, 5, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 4 + 8, cursor.y + 12 - 7, 1, 3, fgui::color(style.cursor.at(0)));
		fgui::render.rect(cursor.x - 3 + 8, cursor.y + 13 - 7, 1, 1, fgui::color(style.cursor.at(0)));
	}
}