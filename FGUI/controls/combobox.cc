/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "combobox.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"

fgui::combobox::combobox() {

	fgui::combobox::m_width = 150;
	fgui::combobox::m_height = 20;
	fgui::combobox::m_index = 0;
	fgui::combobox::m_opened = false;
	fgui::combobox::m_item_height = 20;
	fgui::combobox::m_slider_top = 0;
	fgui::combobox::m_title = "combobox";
	fgui::combobox::m_font = fgui::element::m_font;
	fgui::combobox::m_original_height = fgui::combobox::m_height;
	fgui::combobox::m_type =  static_cast<int>(fgui::detail::element_type::COMBOBOX);
	fgui::element::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE) |  static_cast<int>(fgui::detail::element_flags::FOCUSABLE) |  static_cast<int>(fgui::detail::element_flags::CLICKABLE) |  static_cast<int>(fgui::detail::element_flags::SAVABLE);
}

//---------------------------------------------------------
void fgui::combobox::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_original_height };

	// combobox title text size
	fgui::dimension text_size = fgui::render.get_text_size(fgui::combobox::get_font(), m_title);

	// combobox body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.combobox.at(0)));

	if (fgui::input_system::mouse_in_area(area) || m_opened)
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.combobox.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.combobox.at(2)));

	fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.combobox.at(1)), fgui::color(style.combobox.at(2)), false);

	// dropdown arrow
	fgui::render.rect((area.left + area.right - 10) - 5, (area.top + (area.bottom / 2) - 3) + 1, 5, 1, fgui::color(style.text.at(0)));
	fgui::render.rect((area.left + area.right - 10) - 4, (area.top + (area.bottom / 2) - 3) + 2, 3, 1, fgui::color(style.text.at(0)));
	fgui::render.rect((area.left + area.right - 10) - 3, (area.top + (area.bottom / 2) - 3) + 3, 1, 1, fgui::color(style.text.at(0)));

	// combobox label
	fgui::render.text(area.left, (area.top - text_size.height) - 2, fgui::color(style.text.at(0)), fgui::combobox::get_font(), m_title);

	if (m_info.empty())
		return;

	// current item text size
	fgui::dimension current_item_text_size = fgui::render.get_text_size(fgui::combobox::get_font(), m_info[m_index].item);

	// draw the current item
	fgui::render.text(a.x + (area.right / 2) - (current_item_text_size.width / 2), a.y + (area.bottom / 2) - (current_item_text_size.height / 2), fgui::color(style.text.at(0)), fgui::combobox::get_font(), m_info[m_index].item);

	if (m_opened) {

		if (m_info.size() > 15) {

			// item list
			fgui::render.outline(area.left - 1, (area.top + 23) - 1, area.right + 2, (m_item_height * 10 /* <- make a function to this later */) + 2, fgui::color(style.combobox.at(3)));
			fgui::render.rect(area.left, area.top + 23, area.right, (m_item_height * 10), fgui::color(style.combobox.at(1)));

			// get the number of displayed items
			unsigned int item_displayed = 0;

			// calculate the amount of items to be displayed
			static int calculated_items = (m_height - m_item_height) / m_item_height;

			for (std::size_t i = m_slider_top; (i < m_info.size() && item_displayed < calculated_items); i++) {

				// get the item area on the drop down list
				fgui::rect item_area = {a.x, a.y + 23 + (m_item_height * item_displayed), (m_width - 8), m_item_height };

				// if the user starts hovering a item or selects one
				if (fgui::input_system::mouse_in_area(item_area) || m_index == i) {

					// this will check if the item text is too large for the combobox, if so the last three characters will be replaced with "..."
					if (m_info[i].item.length() > 20)
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.combobox.at(3)), fgui::combobox::get_font(), m_info[i].item.replace(m_info[i].item.begin() + 20, m_info[i].item.end(), "..."));
					else
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.combobox.at(3)), fgui::combobox::get_font(), m_info[i].item);
				}

				else if (!fgui::input_system::mouse_in_area(item_area)) {

					// this will check if the item text is too large for the combobox, if so the last three characters will be replaced with "..."
					if (m_info[i].item.length() > 20)
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.text.at(0)), fgui::combobox::get_font(), m_info[i].item.replace(m_info[i].item.begin() + 20, m_info[i].item.end(), "..."));
					else
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.text.at(0)), fgui::combobox::get_font(), m_info[i].item);
				}

				item_displayed++;
			}

			// calculate the slider position
			float calculated_position = static_cast<float>(m_slider_top) / static_cast<float>(m_info.size());

			if (calculated_position >= 1.f)
				calculated_position = 1.f;

			calculated_position *= m_height - m_item_height;

			// calculate the slider size
			float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_info.size());

			if (calculated_size > 1.f)
				calculated_size = 1.f;

			calculated_size *= m_height - m_item_height;

			// scrollbar body
			fgui::render.rect(area.left + (area.right - 8), area.top + 23, 8, (m_height - m_item_height) - 1, fgui::color(style.combobox.at(2)));

			if (m_info.size() > 75)
				fgui::render.rect((area.left + area.right) - 8 + (8 / 2) - (5 / 2), (area.top + 23) + 5 + calculated_position + 4, 5, 10, fgui::color(style.combobox.at(3)));
			else
				fgui::render.rect((area.left + area.right) - 8 + (8 / 2) - (5 / 2), (area.top + 23) + 5 + calculated_position + 4, 5, calculated_size - 18, fgui::color(style.combobox.at(3)));

			// up button
			fgui::render.rect((area.left + area.right) - 8 + (8 / 2) - (5 / 2), (area.top + 24) + 1, 5, 5, fgui::color(style.combobox.at(3)));

			// down button
			fgui::render.rect((area.left + area.right) - 8 + (8 / 2) - (5 / 2), (area.top + 24) + (m_height - m_item_height) - 8, 5, 5, fgui::color(style.combobox.at(3)));
		}

		else if (m_info.size() <= 15) {

			// item list
			fgui::render.outline(area.left - 1, (area.top + 23) - 1, area.right + 2, (m_item_height * m_info.size()) + 2, fgui::color(style.combobox.at(3)));
			fgui::render.rect(area.left, area.top + 23, area.right, (m_item_height * m_info.size()), fgui::color(style.combobox.at(1)));

			for (std::size_t i = 0; i < m_info.size(); i++) {

				// get the item area on the drop down list
				fgui::rect item_area = {a.x, a.y + 23 + (m_item_height * static_cast<int>(i)), m_width, m_item_height};

				// if the user starts hovering a item or selects one
				if (fgui::input_system::mouse_in_area(item_area) || m_index == i) {

					if (m_info[i].item.length() > 20)
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.combobox.at(3)), fgui::combobox::get_font(), m_info[i].item.replace(m_info[i].item.begin() + 20, m_info[i].item.end(), "..."));
					else
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.combobox.at(3)), fgui::combobox::get_font(), m_info[i].item);
				}

				else if (!fgui::input_system::mouse_in_area(item_area)) {

					if (m_info[i].item.length() > 20)
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.text.at(0)), fgui::combobox::get_font(), m_info[i].item.replace(m_info[i].item.begin() + 20, m_info[i].item.end(), "..."));
					else
						fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.text.at(0)), fgui::combobox::get_font(), m_info[i].item);
				}
			}
		}
	}
}

//---------------------------------------------------------
void fgui::combobox::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_original_height };

	// open the drop down list
	if (fgui::input_system::mouse_in_area(area))
		m_opened = !m_opened;

	if (m_opened) {
		
		// scrollbar slider area
		fgui::rect scrollbar_slider_area = { a.x + (m_width - 8), a.y + 23, 8, m_height };

		if (fgui::input_system::mouse_in_area(scrollbar_slider_area)) {
					
			if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) 
				m_dragging = true;
		}

		// check if the cursor is on the right place
		if (!fgui::input_system::mouse_in_area(area)) {
			
			if (m_info.size() > 15) {
				
				// get the number of displayed items
				unsigned int items_displayed = 0;

				// calculate the amount of items to be drawned
				static int calculated_items = m_height / m_item_height;

				for (std::size_t i = m_slider_top; (i < m_info.size() && items_displayed < calculated_items); i++) {

					// get the item area on the drop down list
					fgui::rect item_area = { a.x, a.y + 23 + (m_item_height * items_displayed), (m_width - 8), m_item_height };

					if (fgui::input_system::mouse_in_area(item_area)) {

						// select an item
						m_index = i;

						if (m_index == i) {
						
							if (m_callback)
								m_callback();

							// close dropdown when a item is selected
							m_opened = false;
						}
					}

					items_displayed++;
				}
			}

			else if (m_info.size() <= 15) {

				for (std::size_t i = 0; (i < m_info.size()); i++) {

					// get the item area on the drop down list
					fgui::rect item_area = { a.x, a.y + 23 + (m_item_height * static_cast<int>(i)), (m_width - 8), m_item_height };

					if (fgui::input_system::mouse_in_area(item_area)) {

						// select an item
						m_index = i;

						if (m_index == i) {
						
							if (m_callback)
								m_callback();
						}
					}
				}
			}
		}
	}
}

//---------------------------------------------------------
void fgui::combobox::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	if (m_opened) {

		// get the control opened area
		fgui::rect opened_area = { a.x, (a.y + 23), m_width, m_height };

		if (m_info.size() > 15)
			m_height = (m_item_height * 10) + m_item_height;

		else if (m_info.size() <= 15)
			m_height = opened_area.top + (m_item_height * m_info.size());

		if (!fgui::input_system::mouse_in_area(opened_area)) {

			if (fgui::input_system::key_press(fgui::external::MOUSE_LEFT))
				m_opened = false;
		}
	}

	else if (!m_opened) {

		// restore height
		m_height = m_original_height;
	}

	if (m_info.size() > 15) {

		// scrollbar slider area
		fgui::rect scrollbar_slider_area = { a.x + (m_width - 8), a.y + 23, 8, m_height };

		// calculate the amount of items to be drawned
		static int calculated_items = (m_height - m_item_height) / m_item_height;
		
		if (m_dragging) {

			if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) {
			
				// cursor position
				fgui::point cursor = fgui::input_system::mouse_position();

				// move the slider vertically
				cursor.y -= (a.y + 23);

				// ratio of how many visible to how many are hidden
				float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_info.size());
				calculated_size *= m_height - m_item_height;

				// height delta
				float height_delta = (cursor.y + calculated_size) - m_height;

				if (height_delta >= 0)
					cursor.y -= height_delta;

				float new_position_ratio = static_cast<float>(cursor.y) / static_cast<float>(m_height);
				m_slider_top = new_position_ratio * m_info.size();

				if (m_slider_top <= 0)
					m_slider_top = 0;
			}
			
			else
				m_dragging = false;
		}

		if (fgui::input_system::mouse_in_area(scrollbar_slider_area)) {

			if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT))
				m_opened = true;
		}
	}
}

//---------------------------------------------------------
void fgui::combobox::tooltip() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (m_tooltip.length() > 0) {

		// tooltip text size
		fgui::dimension tooltip_text_size = fgui::render.get_text_size(fgui::element::get_font(), m_tooltip);

		// cursor position
		fgui::point cursor = fgui::input_system::mouse_position();

		if (fgui::input_system::mouse_in_area(area)) {
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_size.width + 10, 20, fgui::color(style.combobox.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_size.width + 10) / 2) - (tooltip_text_size.width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_size.height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::combobox::save(nlohmann::json& json_module) {

	json_module[m_identificator.data()] = m_index;
}

//---------------------------------------------------------
void fgui::combobox::load(const std::string_view file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name.data(), std::ifstream::binary);

	if (file_to_load.fail()) // todo: make an exception handler
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element value to match the one stored on file
	m_index = json_module[m_identificator.data()];
}
