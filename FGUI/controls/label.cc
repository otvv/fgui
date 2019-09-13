/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "label.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::label::label() {

	fgui::element::m_height = 14;
	fgui::label::m_text = "sample text";
	fgui::label::m_font = fgui::element::m_font;
	fgui::label::m_type = fgui::label_type::TEXT;
	fgui::element::m_family = fgui::element_family::LABEL_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE;
}

//---------------------------------------------------------
void fgui::label::set_text(std::string text) {

	m_text = text;
}

//---------------------------------------------------------
void fgui::label::set_type(fgui::label_type type) {

	m_type = type;
}

//---------------------------------------------------------
void fgui::label::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	int text_width, text_height;
	fgui::render.get_text_size(fgui::label::get_font(), fgui::label::m_text, text_width, text_height);

	// label types
	if (m_type == fgui::label_type::TEXT)
		fgui::render.text(a.x, a.y, fgui::color(style.label.at(3)), fgui::label::get_font(), m_text);

	else if (m_type == fgui::label_type::LINK) {
		fgui::render.text(a.x, a.y, fgui::color(style.label.at(5)), fgui::label::get_font(), m_text);
		fgui::render.rect(a.x, a.y + text_height, text_width, 1, fgui::color(style.label.at(5)));
	}

	else if (m_type == fgui::label_type::BANNER) {
		
		if (m_parent_element)
			m_width = m_parent_element->get_size().width - (m_x * 2);
		else
			m_width = text_width;

		// banner area
		fgui::rect banner_area = { a.x, a.y, m_width, 30 };

		// banner body
		fgui::render.outline(banner_area.left, banner_area.top, banner_area.right, banner_area.bottom, fgui::color(style.label.at(0)));
		fgui::render.outline(banner_area.left + 2, banner_area.top + 2, banner_area.right - 4, banner_area.bottom - 4, fgui::color(style.label.at(4)));
		fgui::render.rect(banner_area.left + 3, banner_area.top + 3, banner_area.right - 6, banner_area.bottom - 6, fgui::color(style.label.at(1)));

		// banner label
		if (m_parent_element)
			fgui::render.text(banner_area.left + (banner_area.right / 2) - (text_width / 2), banner_area.top + (banner_area.bottom / 2) - (text_height / 2), fgui::color(style.label.at(3)), fgui::label::get_font(), m_text);
		else
			fgui::render.text(banner_area.left + 10, banner_area.top + (banner_area.bottom / 2) - (text_height / 2), fgui::color(style.label.at(3)), fgui::label::get_font(), m_text);
	}

	else if (m_type == fgui::label_type::COLORED_TEXT)
		fgui::render.text(a.x, a.y, fgui::color(style.label.at(4)), fgui::label::get_font(), m_text);
}

//---------------------------------------------------------
void fgui::label::handle_input() {

	if (m_type == fgui::label_type::LINK) {

		// get the current position of the window
		fgui::point a = fgui::element::get_absolute_position();

		// label text size
		int text_width, text_height;
		fgui::render.get_text_size(fgui::label::get_font(), m_text, text_width, text_height);

		// get the label area
		fgui::rect area = { a.x, a.y, text_width, text_height };

		if (fgui::input.is_mouse_in_region(area)) {

			if (fgui::input.get_key_press(MOUSE_LEFT)) {

				// TODO: Figure out a way to open links.
			}
		}
	}
}

//---------------------------------------------------------
void fgui::label::update() {

	if (m_type == fgui::label_type::TEXT || m_type == fgui::label_type::COLORED_TEXT || m_type == fgui::label_type::BANNER)
		fgui::label::m_flags = fgui::element_flag::DRAWABLE;

	// make the element clickable if its a link
	else if (m_type == fgui::label_type::LINK)
		fgui::label::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE;
}

//---------------------------------------------------------
void fgui::label::tooltip() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (m_tooltip.length() > 0) {

		// tooltip text size
		int tooltip_text_width, tooltip_text_height;
		fgui::render.get_text_size(fgui::element::get_font(), m_tooltip, tooltip_text_width, tooltip_text_height);

		if (fgui::input.is_mouse_in_region(area)) {

			fgui::point cursor = { 0, 0 };
			fgui::input.get_mouse_position(cursor.x, cursor.y);

			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_width + 10, 20, fgui::color(225, 100, 85));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_width + 10) / 2) - (tooltip_text_width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_height / 2), fgui::color(255, 255, 255), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::label::save(const std::string& file_name, nlohmann::json& json_module) {}

//---------------------------------------------------------
void fgui::label::load(const std::string& file_name) {}