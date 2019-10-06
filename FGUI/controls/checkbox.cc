/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "checkbox.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"

fgui::checkbox::checkbox() {

	fgui::checkbox::m_width = 15;
	fgui::checkbox::m_height = 15;
	fgui::checkbox::m_original_width = fgui::checkbox::m_width;
	fgui::checkbox::m_checked = false;
	fgui::checkbox::m_title = "checkbox";
	fgui::checkbox::m_font = fgui::element::m_font;
	fgui::checkbox::m_original_width = fgui::checkbox::m_width;
	fgui::checkbox::m_type =  static_cast<int>(fgui::detail::element_type::CHECKBOX);
	fgui::element::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE) |  static_cast<int>(fgui::detail::element_flags::CLICKABLE) |  static_cast<int>(fgui::detail::element_flags::SAVABLE);
}

//---------------------------------------------------------
void fgui::checkbox::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// checkbox area
	fgui::rect area = { a.x, a.y, m_original_width, m_height };

	// checkbox body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.checkbox.at(0)));
	fgui::render.colored_gradient(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.checkbox.at(1)), fgui::color(style.checkbox.at(2)), false);

	if (fgui::input_system::mouse_in_area(area) || m_checked)
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.checkbox.at(3)));

	if (m_checked)
		fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.checkbox.at(3)), fgui::color(style.checkbox.at(4)), false);

	// checkbox label
	fgui::render.text(area.left + area.right + 5, area.top, fgui::color(style.text.at(0)), fgui::checkbox::get_font(), m_title);
}

//---------------------------------------------------------
void fgui::checkbox::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// control area
	fgui::rect area = { a.x, a.y, a.x + m_width, m_height };

	// switch
	if (fgui::input_system::mouse_in_area(area))
		m_checked = !m_checked;
}

//---------------------------------------------------------
void fgui::checkbox::update() {

	// get the label text size
	fgui::dimension text_size =	fgui::render.get_text_size(fgui::checkbox::get_font(), m_title);

	m_width = m_original_width + (5 + text_size.width);
}

//---------------------------------------------------------
void fgui::checkbox::tooltip() {

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
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_size.width + 10, 20, fgui::color(style.checkbox.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_size.width + 10) / 2) - (tooltip_text_size.width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_size.height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::checkbox::save(nlohmann::json& json_module) {
	
	json_module[m_identificator.data()] = m_checked;
}

//---------------------------------------------------------
void fgui::checkbox::load(const std::string_view file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name.data(), std::ifstream::binary);

	if (file_to_load.fail()) // todo: make an exception handler
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	m_checked = json_module[m_identificator.data()];
}