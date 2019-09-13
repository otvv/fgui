/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "textbox.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::textbox::textbox() {

	fgui::textbox::m_width = 150;
	fgui::textbox::m_height = 20;
	fgui::textbox::m_title = "textbox";
	fgui::textbox::m_text_input_pos = 0;
	fgui::textbox::m_text_length = 32;
	fgui::textbox::m_text = "sample text";
	fgui::textbox::m_is_getting_key = false;
	fgui::textbox::m_text_selected = false;
	fgui::textbox::m_holding_ticks = 0;
	fgui::textbox::m_font = fgui::element::m_font;
	fgui::textbox::m_family = fgui::element_family::TEXTBOX_FAMILY;
	fgui::textbox::m_text_flag = fgui::text_flags::UPPERCASE; 
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE | fgui::element_flag::SAVABLE;
}

//---------------------------------------------------------
void fgui::textbox::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	int text_width, text_height;
	fgui::render.get_text_size(fgui::textbox::get_font(), m_title, text_width, text_height);

	// textbox body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.textbox.at(0)));
	
	if (fgui::input.is_mouse_in_region(area) || m_is_getting_key)
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.textbox.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.textbox.at(2)));

	fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.textbox.at(1)), fgui::color(style.textbox.at(2)), fgui::gradient_type::VERTICAL);

	// textbox label
	fgui::render.text(area.left, (area.top - text_height) - 2, fgui::color(style.text.at(0)), fgui::textbox::get_font(), m_title);

	if (m_text.empty())
		return;

	int custom_text_width, custom_text_height;
	fgui::render.get_text_size(fgui::textbox::get_font(), m_text, custom_text_width, custom_text_height);

	// draw custom text
	if (m_text_flag & fgui::text_flags::SECRET)
		fgui::render.text(area.left + 5, area.top + (area.bottom / 2) - (custom_text_height / 2) - 1, fgui::color(style.text.at(0)), fgui::textbox::get_font(), std::string(m_text.length(), '*'));
	
	else if (m_text_flag & fgui::text_flags::UPPERCASE) {
		
		// transform the text into uppercase
		std::string upper_case_display = m_text;
		std::transform(upper_case_display.begin(), upper_case_display.end(),upper_case_display.begin(), ::toupper);

		fgui::render.text(area.left + 5, area.top + (area.bottom / 2) - (custom_text_height / 2) - 1, fgui::color(style.text.at(0)), fgui::textbox::get_font(), upper_case_display);
	}
	else
		fgui::render.text(area.left + 5, area.top + (area.bottom / 2) - (custom_text_height / 2) - 1, fgui::color(style.text.at(0)), fgui::textbox::get_font(), m_text);

	// if the textbox is ready to receive text
	if (m_is_getting_key) {

		// caret
		std::string caret = m_text;
		caret.erase(m_text_input_pos, caret.size());

		// get the caret position
		int caret_width, caret_height;
		fgui::render.get_text_size(fgui::textbox::get_font(), caret, caret_width, caret_height);

		// draw the caret
		fgui::render.line(area.left + caret_width + 7, area.top + 5, area.left + caret_width + 7, (area.top + area.bottom) - 5, fgui::color(style.text.at(0)));
	}

	// selected text rectangle
	if (m_text_selected)
		fgui::render.rect(area.left + 5, area.top + (area.bottom / 2) - (custom_text_height / 2) - 1, custom_text_width, custom_text_height, fgui::color(style.textbox.at(3), 100));
}

//---------------------------------------------------------
fgui::state fgui::textbox::get_state() {

	return m_is_getting_key;
}

//---------------------------------------------------------
void fgui::textbox::set_text(std::string text) {

	m_text = text;
}

//---------------------------------------------------------
void fgui::textbox::set_text_flag(fgui::text_flags flags) {

	m_text_flag |= flags;
}

//---------------------------------------------------------
bool fgui::textbox::get_text_flag(fgui::text_flags flags) {

	if (m_text_flag & flags)
		return true;

	return false;
} 

//---------------------------------------------------------
void fgui::textbox::set_length(int length) {

	m_text_length = length;
}

//---------------------------------------------------------
std::string fgui::textbox::get_text() {

	return m_text;
}

//---------------------------------------------------------
void fgui::textbox::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (fgui::input.is_mouse_in_region(area))
		m_is_getting_key = !m_is_getting_key;
}

//---------------------------------------------------------
void fgui::textbox::update() {

	if (m_is_getting_key) {

		for (std::size_t i = 0; i < fgui::key_status::KEY_MAX; i++) {

			if (!fgui::input.get_key_press(i))
				continue;

			// input 
			// NOTE: If your keys are wrong, you might want to check this.
			std::string input = m_input_system_text[i].data();

			// clear text if the user types something while the text is selected
			if (m_text_selected) {

				if (fgui::input.get_key_press(i)) {
					m_text.clear();
					m_text_input_pos = 0;
					m_text_selected = false;
				}
			}

			// if the user press ESC or ENTER, stop the control from receiving input
			if (i == KEY_ESCAPE || i == KEY_ENTER)
				m_is_getting_key = false;

			// make the text in upper case if shift is pressed
			if (fgui::input.get_key_state(KEY_LSHIFT) || fgui::input.get_key_state(KEY_RSHIFT) || m_text_flag & fgui::text_flags::UPPERCASE)
				std::transform(input.begin(), input.end(), input.begin(), ::toupper);

			if (input.length() == 1 && m_text.length() < m_text_length) {
				m_text.insert(m_text_input_pos, input);
				m_text_input_pos++;
			}
		}

		if (m_text.length() > 0) {

			// erase text if the user press backspace 
			if (fgui::input.get_key_press(KEY_BACKSPACE) && m_text_input_pos > 0 && !m_text_selected) {

				m_text_input_pos--;
				m_text.erase(m_text_input_pos, 1);

			}

			// erase text if the user holds backspace 
			else if (fgui::input.get_key_state(KEY_BACKSPACE) && m_text_input_pos > 0 && !m_text_selected) {
				
				m_holding_ticks += 1;

				if (m_holding_ticks > 64) {
					m_text_input_pos--;
					m_text.erase(m_text_input_pos, 1);
				}
			}

			else if (fgui::input.get_key_state(KEY_LCONTROL) && fgui::input.get_key_press(KEY_A)) {

				m_text_selected = true;

				if (m_text_selected) {

					if (fgui::input.get_key_press(KEY_BACKSPACE) && m_text_input_pos > 0) {
						m_text.clear();
						m_text_input_pos = 0;
						m_text_selected = false;
					}
				}
			}

			else if (fgui::input.get_key_press(KEY_DELETE)) {
				m_text.clear();
				m_text_input_pos = 0;
			}

			else // reset ticks
				m_holding_ticks = 0;

			// change the current input position
			if (fgui::input.get_key_press(KEY_LEFT) && m_text_input_pos > 0)
				m_text_input_pos--;

			if (fgui::input.get_key_press(KEY_RIGHT) && m_text_input_pos < m_text.length())
				m_text_input_pos++;
		}
	}
}

//---------------------------------------------------------
void fgui::textbox::tooltip() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	if (m_tooltip.length() > 0) {

		// tooltip text size
		int tooltip_text_width, tooltip_text_height;
		fgui::render.get_text_size(fgui::element::get_font(), m_tooltip, tooltip_text_width, tooltip_text_height);

		fgui::point cursor = { 0, 0 };
		fgui::input.get_mouse_position(cursor.x, cursor.y);

		if (fgui::input.is_mouse_in_region(area)) {
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_width + 10, 20, fgui::color(style.textbox.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_width + 10) / 2) - (tooltip_text_width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::textbox::save(const std::string& file_name, nlohmann::json& json_module) {

	json_module[m_identificator] = m_text;
}

//---------------------------------------------------------
void fgui::textbox::load(const std::string& file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	m_text = json_module[m_identificator];
}