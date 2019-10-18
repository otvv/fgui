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
	fgui::element::m_type =  static_cast<int>(fgui::detail::element_type::LABEL);
	fgui::element::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE);
}

//---------------------------------------------------------
void fgui::label::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// label size
	fgui::dimension text_size = fgui::render.get_text_size(fgui::label::get_font(), m_text.data());

	// label types
	switch (m_type) {

	case fgui::label_type::TEXT: {
		fgui::render.text(a.x, a.y, fgui::color(style.label.at(3)), fgui::label::get_font(), m_text.data());
		break;
	}

	case fgui::label_type::LINK: {
		fgui::render.text(a.x, a.y, fgui::color(style.label.at(5)), fgui::label::get_font(), m_text.data());
		fgui::render.rect(a.x, a.y + text_size.height, text_size.width, 1, fgui::color(style.label.at(5)));
		break;
	}

	case fgui::label_type::BANNER: {

		if (m_parent_element)
			m_width = m_parent_element->get_size().width - (m_x * 2);
		else
			m_width = text_size.width;

		// banner area
		fgui::rect banner_area = {a.x, a.y, m_width, 30};

		// banner body
		fgui::render.outline(banner_area.left, banner_area.top, banner_area.right, banner_area.bottom, fgui::color(style.label.at(0)));
		fgui::render.outline(banner_area.left + 2, banner_area.top + 2, banner_area.right - 4, banner_area.bottom - 4, fgui::color(style.label.at(4)));
		fgui::render.rect(banner_area.left + 3, banner_area.top + 3, banner_area.right - 6, banner_area.bottom - 6, fgui::color(style.label.at(1)));

		// banner label
		if (m_parent_element)
			fgui::render.text(banner_area.left + (banner_area.right / 2) - (text_size.width / 2), banner_area.top + (banner_area.bottom / 2) - (text_size.height / 2), fgui::color(style.label.at(3)), fgui::label::get_font(), m_text.data());
		else
			fgui::render.text(banner_area.left + 10, banner_area.top + (banner_area.bottom / 2) - (text_size.height / 2), fgui::color(style.label.at(3)), fgui::label::get_font(), m_text.data());

		break;
	}

	case fgui::label_type::COLORED: {
		fgui::render.text(a.x, a.y, fgui::color(style.label.at(4)), fgui::label::get_font(), m_text.data());
		break;
	}

	case fgui::label_type::SEPARATOR: {
		// TODO: Handle this case.
		break;
	}

	}
}

//---------------------------------------------------------
void fgui::label::handle_input() {

	if (m_type == fgui::label_type::LINK) {

		// get the current position of the window
		fgui::point a = fgui::element::get_absolute_position();

		// label size
		fgui::dimension text_size = fgui::render.get_text_size(fgui::label::get_font(), m_text.data());

		// get the label area
		fgui::rect area = { a.x, a.y, text_size.width, text_size.height };

		if (fgui::input_system::mouse_in_area(area)) {

			if (fgui::input_system::key_press(fgui::external::MOUSE_LEFT)) {

				// TODO: figure out a way to open links.
			}
		}
	}
}

//---------------------------------------------------------
void fgui::label::update() {

	if (m_type == fgui::label_type::TEXT || m_type == fgui::label_type::COLORED || m_type == fgui::label_type::BANNER)
		fgui::label::m_flags = static_cast<int>(fgui::detail::element_flags::DRAWABLE);

	// make the element clickable if the label is a link
	else if (m_type == fgui::label_type::LINK)
		fgui::label::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE) |  static_cast<int>(fgui::detail::element_flags::CLICKABLE);
}

//---------------------------------------------------------
void fgui::label::tooltip() {

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
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_size.width + 10, 20, fgui::color(style.label.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_size.width + 10) / 2) - (tooltip_text_size.width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_size.height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::label::save(nlohmann::json& json_module) {}

//---------------------------------------------------------
void fgui::label::load(const std::string_view file_name) {}