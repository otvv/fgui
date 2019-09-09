/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

// includes
#include "container.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

/*
 * TODOs:
 *  
 * 1 - Create a "add_function" method for the container, so users can add their own stuff into a specific window 
 * (example: Draw a specific text, textures/images, etc)
 *
 */

fgui::container::container() {

	fgui::container::m_title = "container";
	fgui::container::m_opened = false;
	fgui::container::m_scroll_offset = 0;
	fgui::container::m_width = 235;
	fgui::container::m_height = 275;
	fgui::container::m_original_width = fgui::container::m_width;
	fgui::container::m_original_height = fgui::container::m_height;
	fgui::container::m_resizeable = false;
	fgui::container::m_size_changing = false;
	fgui::container::m_bottom_element_pos = 0;
	fgui::container::m_parent_element = nullptr;
	fgui::container::m_scrollbar_state = false;
	fgui::container::m_dragging_container = false;
	fgui::container::m_font = fgui::element::m_font;
	fgui::container::m_family = fgui::element_family::CONTAINER_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE;
}

//---------------------------------------------------------
void fgui::container::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	int text_width, text_height;
	fgui::render.get_text_size(fgui::container::get_font(), m_title, text_width, text_height);

	// if the container is not bound to another element it will behave like a window
	if (!m_parent_element) {

		// container window header
		fgui::render.outline(a.x, a.y, m_width, m_height, fgui::color(style.window.at(0), 150));
		fgui::render.outline(a.x + 1, a.y + 1, m_width - 2, m_height - 2, fgui::color(style.window.at(2)));
		fgui::render.colored_gradient(a.x + 2, a.y + 2, m_width - 4, 25, fgui::color(style.window.at(3)), fgui::color(style.window.at(4)), fgui::gradient_type::VERTICAL);
		fgui::render.rect(a.x + 2, (a.y + 2) + 25, m_width - 4, (m_height - 25) - 4, fgui::color(style.window.at(4)));
		fgui::render.text(a.x + 10, a.y + (text_height / 2), fgui::color(style.text.at(3)), fgui::container::get_font(), m_title);

		// container window background
		fgui::render.outline(a.x + 5, a.y + 25, m_width - 10, (m_height - 25) - 5, fgui::color(style.window.at(2), 150));
		fgui::render.rect((a.x + 5) + 1, (a.y + 25) + 1, (m_width - 10) - 2, (m_height - 25 - 5) - 2, fgui::color(style.window.at(1)));
	}

	// if the container is bound to a parent element it will behave like a groupbox
	else if (m_parent_element) {

		// condition color
		fgui::color conditional_color = { 0, 0, 0 };

		if (m_size_changing)
			conditional_color = fgui::color(style.container.at(2), 150);
		else
			conditional_color = fgui::color(style.container.at(0));

		// container body
		fgui::render.line(a.x - 1, a.y, a.x + 5, a.y, fgui::color(conditional_color));
		fgui::render.line(a.x + 5 + (text_width + 10), a.y, a.x + m_width, a.y, fgui::color(conditional_color));
		fgui::render.line(a.x + m_width, a.y, a.x + m_width, a.y + m_height, fgui::color(conditional_color));
		fgui::render.line(a.x, a.y + m_height, a.x + m_width, a.y + m_height, fgui::color(conditional_color)); 
		fgui::render.line(a.x - 1, a.y, a.x - 1, a.y + m_height, fgui::color(conditional_color));

		// container background
		fgui::render.rect(a.x, a.y + 1, m_width, m_height - 1, fgui::color(style.container.at(1)));

		// container label
		fgui::render.text(a.x + 10, a.y - (text_height / 2), fgui::color(style.text.at(0)), fgui::container::get_font(), m_title);

		// if the groupbox is resizeable
		if (m_resizeable) {
			render.rect(a.x + m_width - 5, a.y + m_height - 1, 5, 1, fgui::color(conditional_color));
			render.rect(a.x + m_width - 4, a.y + m_height - 2, 4, 1, fgui::color(conditional_color));
			render.rect(a.x + m_width - 3, a.y + m_height - 3, 3, 1, fgui::color(conditional_color));
			render.rect(a.x + m_width - 2, a.y + m_height - 4, 2, 1, fgui::color(conditional_color));
			render.rect(a.x + m_width - 1, a.y + m_height - 5, 1, 1, fgui::color(conditional_color));
		}

		if (!m_focused_element) {

			// parent current position
        	fgui::point pa = m_parent_element->get_absolute_position();

			// get the container clipping area (groupbox)
			fgui::rect parent_area = { std::max(a.x, pa.x), std::max(a.y, pa.y), std::min(m_width, m_parent_element->m_width), std::min(m_height, m_parent_element->m_height) };

			fgui::render.clip_rect(parent_area.left, parent_area.top + 1, parent_area.right, parent_area.bottom - 1);
		}
	}

	for (auto element : m_elements) {

		// check if the element can be drawned
		if (element && element->unlocked() && element->get_flag(fgui::element_flag::DRAWABLE)) {

			// lets not draw the focused element here
			if (element == m_focused_element)
				continue;

			// get the current position of the window
			fgui::point a = element->get_absolute_position();

			if (m_scrollbar_state) {
			
				/* 
			 	 *
			 	 * You can adjust the elements positions here in case your scrolling is wrong
				 *
			 	 */

				// check if the elements are inside the container
				if (a.y <= get_absolute_position().y + m_height && a.y + element->get_size().height >= get_absolute_position().y) {

					// draw the element
					element->draw();

					// element tooltip
					element->tooltip();
				}
			}

			else if (!m_scrollbar_state) {

				// draw the element
				element->draw();

				// element tooltip
				element->tooltip();
			}
		}
	}

	//
	// clipping
	//
	if (m_parent_element) {
		
		// get the current position of the window
		fgui::point a = get_window()->get_absolute_position();

		fgui::render.clip_rect(a.x, a.y, get_window()->m_width, get_window()->m_height);
	}

	else if (!m_parent_element) {
		
		// get the current position of the window
		fgui::point a = get_window()->get_absolute_position();

		// screen size
		int screen_width, screen_height;
		fgui::render.get_screen_size(screen_width, screen_height);

		fgui::render.clip_rect(0, 0, screen_width, screen_height);
	}

	// draw the skipped element (focused) after all other elements
	if (get_window() == shared_from_this() && m_focused_element && m_focused_element->unlocked() && m_focused_element->get_flag(fgui::element_flag::DRAWABLE)) {

		// get the current position of the window
		fgui::point a = m_focused_element->get_absolute_position();

		if (m_scrollbar_state) {

			/* 
			 *
			 * You can adjust the elements positions here in case your scrolling is wrong
			 *
			 */

			// check if the elements are inside the container
			if (a.y <= get_absolute_position().y + m_height && a.y + m_focused_element->get_size().height >= get_absolute_position().y) {

				// draw the element
				m_focused_element->draw();

				// element tooltip
				m_focused_element->tooltip();
			}
		}

		else if (!m_scrollbar_state) {

			// draw the element
			m_focused_element->draw();

			// element tooltip
			m_focused_element->tooltip();
		}
	}

	// draw the scrollbar
	if (m_scrollbar_state) {

		// disable resizing if the groupbox has scrollbars enabled
		m_resizeable = false;

		// calculate the scrollbar slider size
		float calculated_size = (m_height / static_cast<float>(m_bottom_element_pos)) * static_cast<float>(m_height);

		// calculate the scrollbar slider position
		float calculated_position = (m_height - calculated_size) * static_cast<float>(m_scroll_offset / static_cast<float>(m_bottom_element_pos - m_height));

		// scrollbar body
		fgui::render.rect((a.x + m_width) - 8, a.y + 1, 8, m_height - 1, fgui::color(style.container.at(1)));

		// scrollbar slider
		if (m_elements.size() > 75)
			fgui::render.rect((a.x + m_width) - 8 + (8 / 2) - (5 / 2), (a.y + 5) + calculated_position + 4, 5, 10, fgui::color(style.container.at(2)));
		else
			fgui::render.rect((a.x + m_width) - 8 + (8 / 2) - (5 / 2), (a.y + 5) + calculated_position + 4, 5, calculated_size - 27, fgui::color(style.container.at(2)));

		// up button
		fgui::render.rect((a.x + m_width) - 8 + (8 / 2) - (5 / 2), (a.y + 2), 5, 5, fgui::color(style.container.at(2)));

		// down button
		fgui::render.rect((a.x + m_width) - 8 + (8 / 2) - (5 / 2), (a.y + 2) + (m_height - 8), 5, 5, fgui::color(style.container.at(2)));
	}
}

//---------------------------------------------------------
void fgui::container::set_state(bool state) {

	m_opened = state;
}

//---------------------------------------------------------
bool fgui::container::get_state() {

	return m_opened;
}

//---------------------------------------------------------
void fgui::container::save_config(const std::string& file_name) {

	static nlohmann::json json_module;

	// check if the container have elements
	if (m_elements.empty())
		return;

	for (auto element : m_elements) {

		// save the element state
		element->save(file_name, json_module);
	}
	
	std::ofstream file_to_save(file_name);
	
	// write the file
	file_to_save << std::setw(4) << json_module << std::endl;
}

//---------------------------------------------------------
void fgui::container::add_control(std::shared_ptr<fgui::element> control, int page_index, bool manual_size) {

	control->m_parent_element = shared_from_this();
	control->m_page_index = page_index;

	// padding
	if (!manual_size) {

		static int scrollbar_width = 8;
		
		if (m_scrollbar_state)
			control->set_size(m_width - (control->get_position().x * 2) - scrollbar_width, control->get_size().height);
		else
			control->set_size(m_width - (control->get_position().x * 2), control->get_size().height);
	}

	// this might look a bit off due to the fact that pixels are counted from the top
	if (m_bottom_element_pos < control->m_y + control->m_height)
		m_bottom_element_pos = control->m_y + control->m_height;

	m_elements.push_back(control);
}

//---------------------------------------------------------
bool fgui::container::hovering() {

    if (shared_from_this() == get_window()) {

        if (m_focused_element) {

            fgui::point a = m_focused_element->get_absolute_position();

			// focused element region
			fgui::rect focused_control_region = { a.x, a.y, m_focused_element->m_width, m_focused_element->m_height };
            
			if (fgui::input.is_mouse_in_region(focused_control_region))
                return true;
        }

		// container region
		fgui::rect container_region = { m_x, m_y, m_width, m_height };

        return fgui::input.is_mouse_in_region(container_region);
    }
	
    fgui::point a = m_focused_element->get_absolute_position();

	// focused window region
	fgui::rect focused_window_region = { a.x, a.y, m_width, m_height };

    return fgui::input.is_mouse_in_region(focused_window_region);
}

//---------------------------------------------------------
void fgui::container::set_scrollbar_state(bool state) {

	m_scrollbar_state = state;
}

//---------------------------------------------------------
void fgui::container::set_resize_state(bool state) {

	m_resizeable = state;
}

//---------------------------------------------------------
bool fgui::container::get_scrollbar_state() {

	return m_scrollbar_state;
}

//---------------------------------------------------------
int fgui::container::get_scroll_offset() {

	return m_scroll_offset;
}

//---------------------------------------------------------
void fgui::container::handle_input() {}

//---------------------------------------------------------
void fgui::container::update() {

	static bool focused_element_clicked = false;

	// if it has no parent element it should be treated as a window
	if (!m_parent_element) {

		/*
		 *
		 *  Here you can edit the draggable area of the container
		 *
		 */
		
		// container draggable area
		fgui::rect draggable_area = { m_x, m_y, m_width, 25 };

		if (fgui::input.get_key_press(MOUSE_LEFT) && fgui::input.is_mouse_in_region(draggable_area))
			m_dragging_container = true;

		if (!fgui::input.get_key_state(MOUSE_LEFT)) {
			m_dragging_container = false;

			// set cursor
			handler::set_cursor(fgui::cursor_type::ARROW);
		}

		if (m_dragging_container) {

			// change cursor
			handler::set_cursor(fgui::cursor_type::MOVE);

			int drag_x = fgui::input.get_mouse_delta().x;
			int drag_y = fgui::input.get_mouse_delta().y;

			// move container
			m_x += drag_x;
			m_y += drag_y;

			// loose focus 
			if (m_focused_element)
				m_focused_element.reset();
		}

		// don't check for clicks
		focused_element_clicked = false;
	}

	// focused element
	if (m_focused_element && m_focused_element->unlocked()) {

		// get window current position
		fgui::point a = m_focused_element->get_absolute_position();

		// focused element area
		fgui::rect focused_control_area = {a.x, a.y, m_focused_element->m_width, m_focused_element->m_height};

		// update the element
		m_focused_element->update();

		// if the element can receive input
		if (m_focused_element->get_flag(fgui::element_flag::CLICKABLE) && fgui::input.is_mouse_in_region(focused_control_area) && fgui::input.get_key_press(MOUSE_LEFT)) {

			if (m_scrollbar_state) {

				if (m_focused_element->get_absolute_position().y + m_focused_element->get_size().height <= get_absolute_position().y + get_size().height && m_focused_element->get_absolute_position().y >= get_absolute_position().y) {

					// handle input
					m_focused_element->handle_input();

					// tell the container that we just clicked on a focused element
					focused_element_clicked = true;
				}
			}

			else if (!m_scrollbar_state) {

				// handle input
				m_focused_element->handle_input();

				// tell the container that we just clicked on a focused element
				focused_element_clicked = true;
			}
		}

		// update the cursor if the element is clickable
		if (m_focused_element && m_focused_element->get_flag(fgui::element_flag::CLICKABLE) && fgui::input.is_mouse_in_region(focused_control_area))
			handler::set_cursor(fgui::cursor_type::HAND);
		//else
		//	handler::set_cursor(fgui::cursor_type::ARROW);
	}

	// iterate over the rest of the elements
	for (auto element : m_elements) {
		
		if (element->unlocked()) {

			// get window current position
			fgui::point a = element->get_absolute_position();

			// element area
			fgui::rect control_area = {a.x, a.y, element->m_width, element->m_height};

			// update the element
			element->update();

			// if the element can receive input
			if (element->get_flag(fgui::element_flag::CLICKABLE) && fgui::input.is_mouse_in_region(control_area) && fgui::input.get_key_press(MOUSE_LEFT) && !focused_element_clicked) {

				if (m_scrollbar_state) {

					if (element->get_absolute_position().y + element->get_size().height <= get_absolute_position().y + get_size().height && element->get_absolute_position().y >= get_absolute_position().y) {

						// handle input
						element->handle_input();

						if (element->get_flag(fgui::element_flag::FOCUSABLE))
							m_focused_element = element;
						else
							m_focused_element.reset();
					}
				}

				else if (!m_scrollbar_state) {

					// handle input
					element->handle_input();

					if (element->get_flag(fgui::element_flag::FOCUSABLE))
						m_focused_element = element;
					else
						m_focused_element.reset();
				}

				// tell the menu that we clicked on a normal element
				//focused_element_clicked = false;
			}

			// update the cursor if the element is clickable
			if (element && element->get_flag(fgui::element_flag::CLICKABLE) && fgui::input.is_mouse_in_region(control_area))
				handler::set_cursor(fgui::cursor_type::HAND);
			//else
			//	handler::set_cursor(fgui::cursor_type::ARROW);
		}
	}

	// handle scrollbar input
	if (m_scrollbar_state) {

		// get window current position
		fgui::point a = fgui::element::get_absolute_position();

		// scrollbar area
		fgui::rect scrollbar_area = {a.x + m_width - 8, a.y + 1, 8, m_height - 1};

		// container area
		fgui::rect container_area = {a.x, a.y, m_width, m_height};

		if (fgui::input.is_mouse_in_region(container_area)) {
			
			if (!fgui::input.get_key_state(MOUSE_LEFT))	{

				// scroll wheel movement
				m_scroll_offset -= fgui::input.get_scroll_delta() * 5.f;

				// block clicks on the scrollbar slider
				m_dragging_scrollbar = false;
			}
		}

		if (fgui::input.is_mouse_in_region(scrollbar_area)) {

			// change cursor
			handler::set_cursor(fgui::cursor_type::HAND);

			if (fgui::input.get_key_press(MOUSE_LEFT))
				m_dragging_scrollbar = true;
		}

		if (m_dragging_scrollbar) {

			if (fgui::input.get_key_state(MOUSE_LEFT))
				m_scroll_offset += fgui::input.get_mouse_delta().y;
			else
				m_dragging_scrollbar = false;

			// don't check for clicks
			focused_element_clicked = false;
		}

		m_scroll_offset = std::clamp(m_scroll_offset, 0, std::max<int>(0, m_bottom_element_pos - (m_height - 15)));
	}

	// check if the container can be resized
	if (m_resizeable) {

		// get the current position of the window
		fgui::point a = fgui::element::get_absolute_position();

		// backup original size for clamping
		static int old_w = m_original_width;
		static int old_h = m_original_height;

		// container resizeable area
		fgui::rect resizeable_area = { a.x + m_width - 10, a.y + m_height - 10, 15, 15 };

		if (fgui::input.get_key_press(MOUSE_LEFT) && fgui::input.is_mouse_in_region(resizeable_area))
			m_size_changing = true;

		if (!fgui::input.get_key_state(MOUSE_LEFT)) {
			m_size_changing = false;

			// change cursor
			handler::set_cursor(fgui::cursor_type::ARROW);
		}

		// change cursor
		if (fgui::input.is_mouse_in_region(resizeable_area))
			handler::set_cursor(fgui::cursor_type::RESIZE);
		
		if (m_size_changing) {

			int drag_x = fgui::input.get_mouse_delta().x;
			int drag_y = fgui::input.get_mouse_delta().y;

			m_width += drag_x;
			m_height += drag_y;

			if (m_width < old_w) {
				m_width = old_w;
				m_size_changing = false;
			}

			if (m_height < old_h) {
				m_height = old_h;
				m_size_changing = false;
			}

			// don't check for clicks
			focused_element_clicked = false;
		}
	}
}

//---------------------------------------------------------
void fgui::container::tooltip() {}

//---------------------------------------------------------
void fgui::container::save(const std::string &file_name, nlohmann::json &json_module) {

	// check if the container have elements first
	if (m_elements.empty())
		return;

	for (auto element : m_elements) {

		if (element->m_family == fgui::element_family::CONTAINER_FAMILY)
			element->save(file_name, json_module);

		// check if the element can be saved
		else if (element->get_flag(fgui::element_flag::SAVABLE))
			element->save(file_name, json_module);
	}
}

//---------------------------------------------------------
void fgui::container::load(const std::string& file_name) {

	// check if the container have elements first
	if (m_elements.empty())
		return;

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good() || file_name.empty())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	for (auto element : m_elements) {

		if (element->get_family(fgui::element_family::CONTAINER_FAMILY))
			element->load(file_name);

		// check if the element can be loaded
		else if (element->get_flag(fgui::element_flag::SAVABLE))
			element->load(file_name);
	}
}