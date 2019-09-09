/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "button.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::button::button() {

	fgui::button::m_width = 150;
	fgui::button::m_height = 20;
	fgui::button::m_title = "button";
	fgui::button::m_callback = nullptr;
	fgui::button::m_font = fgui::element::m_font;
	fgui::button::m_family = fgui::element_family::BUTTON_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE;
}

//---------------------------------------------------------
void fgui::button::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// get the button title text size
	int text_width, text_height;
	fgui::render.get_text_size(fgui::button::get_font(), m_title, text_width, text_height);

	// button body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.button.at(0)));
	
	if (fgui::input.is_mouse_in_region(area))
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.button.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.button.at(1)));

	fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.button.at(2)), fgui::color(style.button.at(1)), fgui::gradient_type::VERTICAL);
	
	// button label
	fgui::render.text(area.left + (area.right / 2) - (text_width / 2), area.top + (area.bottom / 2) - (text_height / 2), fgui::color(style.text.at(0)), fgui::button::get_font(), m_title);
}

//---------------------------------------------------------
void fgui::button::set_function(std::function<void()> callback) {

	m_callback = callback;
}

//---------------------------------------------------------
void fgui::button::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (fgui::input.is_mouse_in_region(area)) {

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
void fgui::button::save(const std::string& file_name, nlohmann::json& json_module) {}

//---------------------------------------------------------
void fgui::button::load(const std::string& file_name) {}