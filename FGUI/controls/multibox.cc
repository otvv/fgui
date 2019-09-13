/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "multibox.hh"
#include "container.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::multibox::multibox() {

	fgui::multibox::m_width = 150;
	fgui::multibox::m_height = 20;
	fgui::multibox::m_opened = false;
	fgui::multibox::m_item_height = 20;
	fgui::multibox::m_title = "multibox";
	fgui::multibox::m_font = fgui::element::m_font;
	fgui::multibox::m_original_height = fgui::multibox::m_height;
	fgui::multibox::m_family = fgui::element_family::MULTIBOX_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE | fgui::element_flag::FOCUSABLE | fgui::element_flag::SAVABLE;
}

void fgui::multibox::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_original_height };

	int text_width, text_height;
	fgui::render.get_text_size(fgui::multibox::get_font(), m_title, text_width, text_height);

	// multibox body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.multibox.at(0)));

	if (fgui::input.is_mouse_in_region(area))
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.multibox.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.multibox.at(2)));

	fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.multibox.at(1)), fgui::color(style.multibox.at(2)), fgui::gradient_type::VERTICAL);

	// lines
	fgui::render.rect(area.left + (area.right - 20), (area.top + (area.bottom / 2) - 3) + 1, 10, 1, fgui::color(style.text.at(0)));
	fgui::render.rect(area.left + (area.right - 20), (area.top + (area.bottom / 2) - 3) + 3, 10, 1, fgui::color(style.text.at(0)));
	fgui::render.rect(area.left + (area.right - 20), (area.top + (area.bottom / 2) - 3) + 5, 10, 1, fgui::color(style.text.at(0)));

	// multibox label
	fgui::render.text(area.left, (area.top - text_height) - 2, fgui::color(style.text.at(0)), fgui::multibox::get_font(), m_title);

	// this needs to be initialized as a empty string
	std::string format = "";

	for (std::size_t i = 0; i < m_info.size(); ++i) {

		bool format_length = format.length() < 20;
		bool first_item = format.length() <= 0;

		if (m_info[i].m_checked && format_length) {

			if (!m_info[i].m_item.empty()) {

				if (!first_item)
					format.append(", ");

				format.append(m_info[i].m_item);
			}
		}

		else if (!format_length) {
			format.append(" ...");
			break;
		}
	}

	if (format.length() <= 0)
		format += "None";

	// draw the current selected items
	fgui::render.text(area.left + 5, area.top + (area.bottom / 2) - (text_height / 2), fgui::color(style.text.at(0)), fgui::multibox::get_font(), format);

	// if the drop down list is opened
	if (m_opened) {

		// draw the item list
		fgui::render.outline(area.left - 1, (area.top + 23) - 1, area.right + 2, (m_item_height * m_info.size()) + 2, fgui::color(style.multibox.at(3)));
		fgui::render.rect(area.left, area.top + 23, area.right, (m_item_height * m_info.size()), fgui::color(style.multibox.at(1)));

		for (std::size_t i = 0; i < m_info.size(); i++) {

			// get the item area on the drop down list
			fgui::rect item_area = { a.x, a.y + 23 + (m_item_height * i), m_width, m_item_height };

			// if the user starts hovering a item or selects one
			if (fgui::input.is_mouse_in_region(item_area) || m_info[i].m_checked) {

				if (m_info[i].m_item.length() > 20)
					fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.multibox.at(3)), fgui::multibox::get_font(), m_info[i].m_item.replace(m_info[i].m_item.begin() + 20, m_info[i].m_item.end(), "..."));
				else
					fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.multibox.at(3)), fgui::multibox::get_font(), m_info[i].m_item);
			}

			else if (!fgui::input.is_mouse_in_region(item_area) || !m_info[i].m_checked) {

				if (m_info[i].m_item.length() > 20)
					fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.text.at(0)), fgui::multibox::get_font(), m_info[i].m_item.replace(m_info[i].m_item.begin() + 20, m_info[i].m_item.end(), "..."));
				else
					fgui::render.text(item_area.left + 5, item_area.top + 5, fgui::color(style.text.at(0)), fgui::multibox::get_font(), m_info[i].m_item);
			}
		}
	}
}

//---------------------------------------------------------
void fgui::multibox::add_item(std::string item, bool state) {

	m_info.push_back({item, state});
}

//---------------------------------------------------------
void fgui::multibox::set_selected(int index, bool state) {

	m_info[index].m_checked = state;
}

//---------------------------------------------------------
bool fgui::multibox::get_selected(int index) {

	return m_info[index].m_checked;
}

//---------------------------------------------------------
void fgui::multibox::set_state(fgui::state state) {

	m_opened = state;
}

//---------------------------------------------------------
fgui::state fgui::multibox::get_state() {

	return m_opened;
}

//---------------------------------------------------------
void fgui::multibox::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_original_height };

	// open the drop down list
	if (fgui::input.is_mouse_in_region(area))
		m_opened = !m_opened;

	// if the dropdown list is opened
	if (m_opened) {

		if (!fgui::input.is_mouse_in_region(area)) {

			if (m_info.size() > 0) {

				for (std::size_t i = 0; i < m_info.size(); i++) {

					// item area
					fgui::rect item_area = { a.x, a.y + 23 + (m_item_height * i), m_width, m_item_height };

					// select an item
					if (fgui::input.is_mouse_in_region(item_area))
						m_info[i].m_checked = !m_info[i].m_checked;
				}
			}
		}
	}
}

//---------------------------------------------------------
void fgui::multibox::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();
		
	// get the control opened area
	fgui::rect opened_area = { a.x, (a.y + 23), m_width, m_height };

	if (m_opened) {
		m_height = opened_area.top + (m_item_height * m_info.size());

		if (!fgui::input.is_mouse_in_region(opened_area)) {

			if (fgui::input.get_key_press(MOUSE_LEFT))
				m_opened = false;
		}
	}

	else if (!m_opened)	{
		
		// restore height
		m_height = m_original_height;
	}
}

//---------------------------------------------------------
void fgui::multibox::tooltip() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_original_height };

	if (m_tooltip.length() > 0) {

		// tooltip text size
		int tooltip_text_width, tooltip_text_height;
		fgui::render.get_text_size(fgui::element::get_font(), m_tooltip, tooltip_text_width, tooltip_text_height);

		fgui::point cursor = { 0, 0 };
		fgui::input.get_mouse_position(cursor.x, cursor.y);

		if (fgui::input.is_mouse_in_region(area)) {
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_width + 10, 20, fgui::color(style.multibox.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_width + 10) / 2) - (tooltip_text_width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::multibox::save(const std::string& file_name, nlohmann::json& json_module) {

	for (std::size_t i = 0; i < m_info.size(); i++)
		json_module[m_identificator][m_info[i].m_item] = m_info[i].m_checked;
}

//---------------------------------------------------------
void fgui::multibox::load(const std::string& file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	for (std::size_t i = 0; i < m_info.size(); i++)
		set_selected(i, json_module[m_identificator][m_info[i].m_item]);
}