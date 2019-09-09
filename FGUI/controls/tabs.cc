/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

// includes
#include "tabs.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::tabs::tabs() {

	fgui::tabs::m_width = 150;
	fgui::tabs::m_height = 30;
	fgui::tabs::m_title = "tab";
	fgui::tabs::m_selected_tab = 0;
	fgui::tabs::m_font = fgui::element::m_font;
	fgui::tabs::m_family = fgui::element_family::TAB_FAMILY;
	fgui::tabs::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE;
}

//---------------------------------------------------------
void fgui::tabs::draw() {
	
	if (m_info.empty())
		return;
	
	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();
	
	// calculate the size of the tab buttons
	static int tab_button_size = 0;
	if (m_parent_element)
	 	tab_button_size = (m_parent_element->get_size().width - 12) / m_info.size();
	else
		tab_button_size = m_width / m_info.size();

	// get the window style
	auto style = handler::get_style();


	for (std::size_t i = 0; i < m_info.size(); i++) {

		int text_width, text_height;
		fgui::render.get_text_size(fgui::tabs::get_font(), m_info[i].m_item, text_width, text_height);

		// tab area
		fgui::rect area = { a.x + (i * tab_button_size), a.y, (tab_button_size + 1), m_height };

		// get the window style
		auto style = handler::get_style();

		// tab button body
		fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.tabs.at(1)));
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.tabs.at(0), 200));
		
		if (m_selected_tab == i)
			fgui::render.colored_gradient(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.tabs.at(3)), fgui::color(style.tabs.at(4)), fgui::gradient_type::VERTICAL);
		else
			fgui::render.colored_gradient(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.tabs.at(2)), fgui::color(style.tabs.at(1)), fgui::gradient_type::VERTICAL);

		// tab button label
		fgui::render.text(area.left + (area.right / 2) - (text_width / 2), area.top + (area.bottom / 2) - (text_height / 2), fgui::color(style.text.at(3)), fgui::tabs::get_font(), m_info[i].m_item);
	}
}

//---------------------------------------------------------
int fgui::tabs::get_index() {

	return m_selected_tab;
}

//---------------------------------------------------------
void fgui::tabs::add_tab(std::string tab) {

	m_info.push_back(fgui::item_info(tab));
}

//---------------------------------------------------------
void fgui::tabs::handle_input() {}

//---------------------------------------------------------
void fgui::tabs::update() {

	if (m_info.empty())
		return;

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// calculate the size of the tab buttons
	int tab_button_size = 0;
	if (m_parent_element)
	 	tab_button_size = (m_parent_element->get_size().width - 10) / m_info.size();
	else
		tab_button_size = m_width / m_info.size();

	for (std::size_t i = 0; i < m_info.size(); i++) {

		int text_width, text_height;
		fgui::render.get_text_size(fgui::tabs::get_font(), m_info[i].m_item, text_width, text_height);

		// tab area
		fgui::rect area = { a.x + (i * tab_button_size), a.y, tab_button_size, m_height };

		// select the tab
		if (fgui::input.is_mouse_in_region(area)) {
			
			if (fgui::input.get_key_press(MOUSE_LEFT))
				m_selected_tab = i;
		}
	}
}

//---------------------------------------------------------
void fgui::tabs::tooltip() {}

//---------------------------------------------------------
void fgui::tabs::save(const std::string& file_name, nlohmann::json& json_module) {}

//---------------------------------------------------------
void fgui::tabs::load(const std::string& file_name) {}