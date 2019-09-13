/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "keybinder.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::keybinder::keybinder() {

	fgui::keybinder::m_width = 100;
	fgui::keybinder::m_height = 20;
	fgui::keybinder::m_title = "keybinder";
	fgui::keybinder::m_font = fgui::element::m_font;
	fgui::keybinder::m_is_getting_key = false;
	fgui::keybinder::m_key = fgui::key_status::KEY_INVALID;
	fgui::keybinder::m_family = fgui::element_family::KEYBINDER_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE | fgui::element_flag::SAVABLE;
}

//---------------------------------------------------------
void fgui::keybinder::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	int text_width, text_height;
	fgui::render.get_text_size(fgui::keybinder::get_font(), m_title, text_width, text_height);
		
	// keybinder body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.keybinder.at(0)));

	if (fgui::input.is_mouse_in_region(area) || m_is_getting_key)
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.keybinder.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.keybinder.at(2)));

	fgui::render.colored_gradient(area.left + 3, area.top + 3, area.right - 6, area.bottom - 6, fgui::color(style.keybinder.at(1)), fgui::color(style.keybinder.at(2)), fgui::gradient_type::VERTICAL);

	// keybinder label
	fgui::render.text(area.left, (area.top - text_height) - 2, fgui::color(style.text.at(0)), fgui::keybinder::get_font(), m_title);

	int key_text_width, key_text_height;
	fgui::render.get_text_size(fgui::keybinder::get_font(), m_key > 0 ? m_input_system[m_key].data() : "Not Bound", key_text_width, key_text_height);

	// draw the current key
	fgui::render.text(area.left + (area.right / 2) - (key_text_width / 2), area.top + (area.bottom / 2) - (text_height / 2) - 1, fgui::color(style.text.at(0)), fgui::keybinder::get_font(), m_key > 0 ? m_input_system[m_key].data() : "Not Bound");
}

//---------------------------------------------------------
fgui::key fgui::keybinder::get_key() {

	return m_key;
}

//---------------------------------------------------------
void fgui::keybinder::set_key(fgui::key key) {

	m_key = key;
}

//---------------------------------------------------------
void fgui::keybinder::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// unlock the key binder
	if (fgui::input.is_mouse_in_region(area))
		m_is_getting_key = !m_is_getting_key;
}

//---------------------------------------------------------
void fgui::keybinder::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// if the key binder is unlocked
	if (m_is_getting_key) {

		for (std::size_t i = 0; i < fgui::key_status::KEY_MAX; i++) {

			// if the user has pressed a valid key
			if (fgui::input.get_key_press(i)) {

				// if the user hits escape, lock the keybinder
				if (i == KEY_ESCAPE) {

					// select the key
					m_key = fgui::key_status::KEY_INVALID;

					// change key binder status
					m_status = "Not Bound";

					// block the keybinder from receiving input
					m_is_getting_key = false;
				}

				else if (i != KEY_ESCAPE) {

					m_key = i;

					// display the current selected key
					fgui::m_input_system[m_key].data();

					// block the key binder from receiving input
					m_is_getting_key = false;
				}
			}
		}
	}
}

//---------------------------------------------------------
void fgui::keybinder::tooltip() {

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
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_width + 10, 20, fgui::color(style.keybinder.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_width + 10) / 2) - (tooltip_text_width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::keybinder::save(const std::string& file_name, nlohmann::json& json_module) {

	json_module[m_identificator]["key_code"] = m_key;
}

//---------------------------------------------------------
void fgui::keybinder::load(const std::string& file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	m_key = json_module[m_identificator]["key_code"];
}