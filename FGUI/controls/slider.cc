/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "slider.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::slider::slider() {

	fgui::slider::m_width = 150;
	fgui::slider::m_height = 10;
	fgui::slider::m_value = 0.f;
	fgui::slider::m_dragging = false;
	fgui::slider::m_min_text = "";
	fgui::slider::m_max_text = "";
	fgui::slider::m_title = "slider";
	fgui::slider::m_font = fgui::element::m_font;
	fgui::slider::m_family = fgui::element_family::SLIDER_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE | fgui::element_flag::SAVABLE;
}

//---------------------------------------------------------
void fgui::slider::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// ratio
	float ratio = (m_value - m_min) / (m_max - m_min);
	float location = ratio * m_width;

	// custom value
	static std::string custom_value = "";

	// slider label text size
	int title_width, title_height;
	fgui::render.get_text_size(fgui::slider::get_font(), m_min_text, title_width, title_height);

	// slider body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.slider.at(0)));
	fgui::render.colored_gradient(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.slider.at(1)), fgui::color(style.slider.at(2)), fgui::gradient_type::VERTICAL);

	if (fgui::input.is_mouse_in_region(area) || m_dragging)
		fgui::render.outline(area.left + 1, area.top + 1, location - 2, area.bottom - 2, fgui::color(style.slider.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.slider.at(2), 150));

	fgui::render.colored_gradient(area.left + 2, area.top + 2, location - 4, area.bottom - 4, fgui::color(style.slider.at(3)), fgui::color(style.slider.at(4)), fgui::gradient_type::VERTICAL);
	
	// slider label
	fgui::render.text(area.left, (area.top - title_height) - 2, fgui::color(style.text.at(0)), fgui::slider::get_font(), m_title);

	// value text size
	int value_width, value_height;
	fgui::render.get_text_size(fgui::slider::get_font(), custom_value, value_width, value_height);

	// slider custom value
	if (!m_min_text.empty()) {

		if (m_value <= m_min)
			custom_value = m_min_text;
	}

	else
		custom_value = std::to_string(static_cast<int>(m_value));

	if (!m_max_text.empty()) {
		
		if (m_value >= m_max)
			custom_value = m_max_text;
	}

	else
		custom_value = std::to_string(static_cast<int>(m_value));

	if (m_value != m_min && m_value != m_max)
		custom_value = std::to_string(static_cast<int>(m_value));
	
	// slider value
	fgui::render.text((area.left + area.right) - value_width, (area.top - title_height) - 2, fgui::color(style.text.at(0)), fgui::slider::get_font(), custom_value);
}

//---------------------------------------------------------
void fgui::slider::set_value(float value) {

	m_value = value;
}

//---------------------------------------------------------
float fgui::slider::get_value() {

	return m_value;
}

//---------------------------------------------------------
void fgui::slider::set_boundaries(float min, float max) {

	m_min = min;
	m_max = max;
}

//---------------------------------------------------------
void fgui::slider::set_boundaries_text(std::string min_text, std::string max_text) {

	m_min_text = min_text;
	m_max_text = max_text;
}

//---------------------------------------------------------
void fgui::slider::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// enable the drag state if the user is clicking inside the scrollbar area
	if (fgui::input.is_mouse_in_region(area))
		m_dragging = true;
}

//---------------------------------------------------------
void fgui::slider::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (m_dragging) {

		if (fgui::input.get_key_state(MOUSE_LEFT)) {

			// get the cursor position
			fgui::point cursor;
			fgui::input.get_mouse_position(cursor.x, cursor.y);

			float new_x = 0.f;
			float ratio = 0.f;

			new_x = cursor.x - a.x - 1.f;
			
			if (new_x <= m_min)
				new_x = m_min;

			else if (new_x >= m_width)
				new_x = m_width;

			ratio = new_x / float(m_width);

			m_value = m_min + (m_max - m_min) * ratio;
		}

		else
			m_dragging = false;
	}

	// check if the mouse is on the control area
	if (fgui::input.is_mouse_in_region(area)) {

		// now check if we are holding one of these keys
		if (fgui::input.get_key_state(KEY_RIGHT) || fgui::input.get_key_state(KEY_UP)) {
			m_value += 1.f;

			if (m_value >= m_max)
				m_value = m_max;

			else if (m_value <= m_min)
				m_value = m_min;
		}

		else if (fgui::input.get_key_state(KEY_LEFT) || fgui::input.get_key_state(KEY_DOWN)) {
			m_value -= 1.f;
			
			if (m_value >= m_max)
				m_value = m_max;

			else if (m_value <= m_min)
				m_value = m_min;
		}

	}
}

//---------------------------------------------------------
void fgui::slider::tooltip() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height + 3 };

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
void fgui::slider::save(const std::string& file_name, nlohmann::json& json_module) {

	json_module[m_identificator] = m_value;
}

//---------------------------------------------------------
void fgui::slider::load(const std::string& file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	m_value = json_module[m_identificator];
}