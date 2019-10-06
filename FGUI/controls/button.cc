/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "button.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"

fgui::button::button() {

	fgui::button::m_width = 150;
	fgui::button::m_height = 20;
	fgui::button::m_title = "button";
	fgui::button::m_callback = nullptr;
	fgui::button::m_font = fgui::element::m_font;
	fgui::button::m_type =  static_cast<int>(fgui::detail::element_type::BUTTON);
	fgui::element::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE) |  static_cast<int>(fgui::detail::element_flags::CLICKABLE);
}

//---------------------------------------------------------
void fgui::button::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// button title text size
	fgui::dimension text_size = fgui::render.get_text_size(fgui::button::get_font(), m_title);

	// button body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.button.at(0)));
	
	if (fgui::input_system::mouse_in_area(area))
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.button.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.button.at(1)));

	fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.button.at(2)), fgui::color(style.button.at(1)), false);
	
	// button label
	fgui::render.text(area.left + (area.right / 2) - (text_size.width / 2), area.top + (area.bottom / 2) - (text_size.height / 2), fgui::color(style.text.at(0)), fgui::button::get_font(), m_title);
}

//---------------------------------------------------------
void fgui::button::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (fgui::input_system::mouse_in_area(area)) {

		// call the custom function
		if (m_callback)
			m_callback();
	}
}

//---------------------------------------------------------
void fgui::button::update() {}

//---------------------------------------------------------
void fgui::button::tooltip() {

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
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_size.width + 10, 20, fgui::color(style.button.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_size.width + 10) / 2) - (tooltip_text_size.width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_size.height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::button::save(nlohmann::json& json_module) {}

//---------------------------------------------------------
void fgui::button::load(const std::string_view file_name) {}