/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

// includes
#include "container.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"

fgui::container::container() {

	fgui::container::m_title = "container";
	fgui::container::m_opened = false;
	fgui::container::m_scroll_offset = 0;
	fgui::container::m_width = 50;
	fgui::container::m_height = 50;
	fgui::container::m_original_width = fgui::container::m_width;
	fgui::container::m_original_height = fgui::container::m_height;
	fgui::container::m_resizeable = false;
	fgui::container::m_size_changing = false;
	fgui::container::m_bottom_element_pos = 0;
	fgui::container::m_parent_element = nullptr;
	fgui::container::m_scrollable = false;
	fgui::container::m_hideable = false;
	fgui::container::m_dragging_container = false;
	fgui::container::m_font = fgui::element::m_font;
	fgui::container::m_type =  static_cast<int>(fgui::detail::element_type::CONTAINER);
	fgui::element::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE);
}

//---------------------------------------------------------
void fgui::container::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// container title text size
	fgui::dimension text_size = fgui::render.get_text_size(fgui::container::get_font(), m_title);

	// if the container is not bound to another element it will behave like a window
	if (!m_parent_element) {

		// container window header
		fgui::render.outline(a.x, a.y, m_width, m_height, fgui::color(style.window.at(0), 150));
		fgui::render.outline(a.x + 1, a.y + 1, m_width - 2, m_height - 2, fgui::color(style.window.at(2)));
		fgui::render.colored_gradient(a.x + 2, a.y + 2, m_width - 4, 25, fgui::color(style.window.at(3), 150), fgui::color(style.window.at(4), 150), false);
		fgui::render.rect(a.x + 2, (a.y + 2) + 25, m_width - 4, (m_height - 25) - 4, fgui::color(style.window.at(4), 235));
		fgui::render.text(a.x + 10, a.y + (text_size.height / 2), fgui::color(style.text.at(3)), fgui::container::get_font(), m_title);

		// container window background
		fgui::render.outline(a.x + 5, a.y + 25, m_width - 10, (m_height - 25) - 5, fgui::color(style.window.at(2), 150));
		fgui::render.rect((a.x + 5) + 1, (a.y + 25) + 1, (m_width - 10) - 2, (m_height - 25 - 5) - 2, fgui::color(style.window.at(1)));

		// if the window has a function
		if (m_callback) {
		
			// disable cursor
			handler::set_cursor(fgui::cursor_type::NONE);

			// invoke function
			m_callback();
		}
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
		fgui::render.line(a.x + 5 + (text_size.width + 10), a.y, a.x + m_width, a.y, fgui::color(conditional_color));
		fgui::render.line(a.x + m_width, a.y, a.x + m_width, a.y + m_height, fgui::color(conditional_color));
		fgui::render.line(a.x, a.y + m_height, a.x + m_width, a.y + m_height, fgui::color(conditional_color)); 
		fgui::render.line(a.x - 1, a.y, a.x - 1, a.y + m_height, fgui::color(conditional_color));

		// container background
		fgui::render.rect(a.x, a.y + 1, m_width, m_height - 1, fgui::color(style.container.at(1)));

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

	for (std::shared_ptr<fgui::element> element : m_elements) {

		// check if the element can be drawned
		if (element && element->unlocked() && element->get_flag(fgui::detail::element_flags::DRAWABLE)) {

			// lets not draw the focused element here
			if (element == m_focused_element)
				continue;

			// get the current position of the window
			fgui::point a = element->get_absolute_position();

			if (m_scrollable) {
			
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

			else if (!m_scrollable) {

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

		// screen size
		int screen_width, screen_height;
		fgui::render.get_screen_size(screen_width, screen_height);

		fgui::render.clip_rect(0, 0, screen_width, screen_height);
	}

	// draw the skipped (focused) element after all other elements
	if (get_window() == shared_from_this() && m_focused_element && m_focused_element->unlocked() && m_focused_element->get_flag(fgui::detail::element_flags::DRAWABLE)) {

		// get the current position of the window
		fgui::point a = m_focused_element->get_absolute_position();

		if (m_scrollable) {

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

		else if (!m_scrollable) {

			// draw the element
			m_focused_element->draw();

			// element tooltip
			m_focused_element->tooltip();
		}
	}

	// draw the scrollbar
	if (m_scrollable) {

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

	if (m_parent_element && m_hideable) {

		// 'hidden' text size
		fgui::dimension hidden_text_size = fgui::render.get_text_size(fgui::container::get_font(), "Hidden");

		// container area
		fgui::rect container_area = {a.x, a.y, m_width, m_height};

		if (!fgui::input_system::mouse_in_area(container_area)) {
			
			// don't draw the skipped element
			if (m_focused_element)
				m_focused_element.reset();

			// 'hidden' body
			fgui::render.outline(a.x, a.y, m_width, m_height, fgui::color(style.container.at(0)));
			fgui::render.outline(a.x + 2, a.y + 2, m_width - 4, m_height - 4, fgui::color(style.container.at(2)));
			fgui::render.rect(a.x + 3, a.y + 3, m_width - 6, m_height - 6, fgui::color(style.container.at(1)));

			// 'hidden' label
			fgui::render.text(a.x + (m_width / 2) - (hidden_text_size.width / 2), a.y + (m_height / 2) - (hidden_text_size.height / 2), fgui::color(style.text.at(0)), fgui::container::get_font(), "Hidden");
		}
	}

	if (m_parent_element) {

    	// container label
    	fgui::render.text(a.x + 10, a.y - (text_size.height / 2), fgui::color(style.text.at(0)), fgui::container::get_font(), m_title);
  	}
}

//---------------------------------------------------------
void fgui::container::save_config(const std::string_view file_name) {

	static nlohmann::json json_module;

	// check if the container have elements
	if (m_elements.empty())
		return;

	for (std::shared_ptr<fgui::element> element : m_elements) {

		// save the element state
		element->save(json_module);
	}
	
	std::ofstream file_to_save(file_name.data());

	if (file_to_save.fail()) // todo: make an exception handler 
		return;
	
	// write the file
	file_to_save << std::setw(4) << json_module << std::endl;
}

//---------------------------------------------------------
void fgui::container::add_control(const std::shared_ptr<fgui::element> &control, int page_index, bool manual_size) {

	control->m_parent_element = shared_from_this();
	control->m_page_index = page_index;

	// padding
	if (!manual_size) {

		constexpr int scrollbar_width = 8;
		
		if (m_scrollable)
			control->set_size(m_width - (control->get_position().x * 2) - scrollbar_width, control->get_size().height);
		else
			control->set_size(m_width - (control->get_position().x * 2), control->get_size().height);
	}

	// this might look a bit off due to the fact that pixels are counted from the top
	if (m_bottom_element_pos < control->get_position().y + control->get_size().height)
		m_bottom_element_pos = control->get_position().y + control->get_size().height;

	m_elements.push_back(control);
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
		fgui::rect draggable_area = { m_x, m_y, m_width, 25 }; // 25 being the height in pixels of the draggable area

		if (fgui::input_system::mouse_in_area(draggable_area)) {
		
			if  (fgui::input_system::key_press(fgui::external::MOUSE_LEFT))
				m_dragging_container = true;
		}

		if (!fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) {
			m_dragging_container = false;

			// set cursor
			handler::set_cursor(fgui::cursor_type::ARROW);
		}

		if (m_dragging_container) {

			// change cursor
			handler::set_cursor(fgui::cursor_type::MOVE);

			// mouse position delta
			fgui::point position_delta = fgui::input_system::mouse_position_delta();

			// move container
			m_x += position_delta.x;
			m_y += position_delta.y;

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
		if (m_focused_element->get_flag(fgui::detail::element_flags::CLICKABLE) && fgui::input_system::mouse_in_area(focused_control_area) && fgui::input_system::key_press(fgui::external::MOUSE_LEFT)) {

			if (m_scrollable) {

				if (m_focused_element->get_absolute_position().y + m_focused_element->get_size().height <= get_absolute_position().y + get_size().height && m_focused_element->get_absolute_position().y >= get_absolute_position().y) {

					// handle input
					m_focused_element->handle_input();

					// tell the container that we just clicked on a focused element
					focused_element_clicked = true;
				}
			}

			else if (!m_scrollable) {

				// handle input
				m_focused_element->handle_input();

				// tell the container that we just clicked on a focused element
				focused_element_clicked = true;
			}
		}

		// update the cursor if the element is clickable
		if (m_focused_element && m_focused_element->get_flag(fgui::detail::element_flags::CLICKABLE) && fgui::input_system::mouse_in_area(focused_control_area))
			handler::set_cursor(fgui::cursor_type::HAND);
		//else
		//	handler::set_cursor(fgui::cursor_type::ARROW);
	}

	// iterate over the rest of the elements
	for (std::shared_ptr<fgui::element> element : m_elements) {
		
		if (element->unlocked()) {

			// get window current position
			fgui::point a = element->get_absolute_position();

			// element area
			fgui::rect control_area = {a.x, a.y, element->m_width, element->m_height};

			// update the element
			element->update();

			// if the element can receive input
			if (element->get_flag(fgui::detail::element_flags::CLICKABLE) && fgui::input_system::mouse_in_area(control_area) && fgui::input_system::key_press(fgui::external::MOUSE_LEFT) && !focused_element_clicked) {

				if (m_scrollable) {

					if (element->get_absolute_position().y + element->get_size().height <= get_absolute_position().y + get_size().height && element->get_absolute_position().y >= get_absolute_position().y) {

						// handle input
						element->handle_input();

						if (element->get_flag(fgui::detail::element_flags::FOCUSABLE))
							m_focused_element = element;
						else
							m_focused_element.reset();
					}
				}

				else if (!m_scrollable) {

					// handle input
					element->handle_input();

					if (element->get_flag(fgui::detail::element_flags::FOCUSABLE))
						m_focused_element = element;
					else
						m_focused_element.reset();
				}

				// tell the menu that we clicked on a normal element
				//focused_element_clicked = false;
			}

			// update the cursor if the element is clickable
			if (element && element->get_flag(fgui::detail::element_flags::CLICKABLE) && fgui::input_system::mouse_in_area(control_area))
				handler::set_cursor(fgui::cursor_type::HAND);
			//else
			//	handler::set_cursor(fgui::cursor_type::ARROW);
		}
	}

	// handle scrollbar input
	if (m_scrollable) {

		// get window current position
		fgui::point a = fgui::element::get_absolute_position();

		// scrollbar area
		fgui::rect scrollbar_area = {a.x + m_width - 8, a.y + 1, 8, m_height - 1};

		// container area
		fgui::rect container_area = {a.x, a.y, m_width, m_height};

		if (fgui::input_system::mouse_in_area(container_area)) {

			// lines to scroll
			constexpr int lines_to_scroll = 4;
			
			if (!fgui::input_system::key_held(fgui::external::MOUSE_LEFT))	{

				// scroll wheel movement
				m_scroll_offset -= fgui::input_system::scroll_delta() * lines_to_scroll;

				// block clicks on the scrollbar slider
				m_dragging_scrollbar = false;
			}
		}

		if (fgui::input_system::mouse_in_area(scrollbar_area)) {

			// change cursor
			handler::set_cursor(fgui::cursor_type::HAND);

			if (fgui::input_system::key_press(fgui::external::MOUSE_LEFT))
				m_dragging_scrollbar = true;
		}

		if (m_dragging_scrollbar) {

			// mouse position delta
			fgui::point position_delta = fgui::input_system::mouse_position_delta();

			if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT))
				m_scroll_offset += position_delta.y;
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

		if (fgui::input_system::mouse_in_area(resizeable_area)) {
		
			if  (fgui::input_system::key_press(fgui::external::MOUSE_LEFT))
				m_size_changing = true;
		}

		if (!fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) {
			m_size_changing = false;

			// change cursor
			handler::set_cursor(fgui::cursor_type::ARROW);
		}

		// change cursor
		if (fgui::input_system::mouse_in_area(resizeable_area))
			handler::set_cursor(fgui::cursor_type::RESIZE);
		
		if (m_size_changing) {

			// mouse position delta
			fgui::point position_delta = fgui::input_system::mouse_position_delta();

			m_width += position_delta.x;
			m_height += position_delta.y;

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
void fgui::container::save(nlohmann::json &json_module) {

	// check if the container have elements first
	if (m_elements.empty())
		return;

	for (std::shared_ptr<fgui::element> element : m_elements) {

		if (element->get_family(fgui::detail::element_type::CONTAINER))
			element->save(json_module);

		// check if the element can be saved
		else if (element->get_flag(fgui::detail::element_flags::SAVABLE))
			element->save(json_module);
	}
}

//---------------------------------------------------------
void fgui::container::load(const std::string_view file_name) {

	// check if the container have elements first
	if (m_elements.empty())
		return;

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name.data(), std::ifstream::binary);

	if (file_to_load.fail()) // todo: make an exception handler 
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	for (std::shared_ptr<fgui::element> element : m_elements) {

		if (element->get_family(fgui::detail::element_type::CONTAINER))
			element->load(file_name);

		// check if the element can be loaded
		else if (element->get_flag(fgui::detail::element_flags::SAVABLE))
			element->load(file_name);
	}
}