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
	fgui::tabs::m_index = 0;
	fgui::tabs::m_font = fgui::element::m_font;
	fgui::tabs::m_tab_layout = fgui::tab_layout::HORIZONTAL;
	fgui::tabs::m_type =  static_cast<int>(fgui::detail::element_type::TAB);
	fgui::tabs::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE) |  static_cast<int>(fgui::detail::element_flags::CLICKABLE);
}

//---------------------------------------------------------
void fgui::tabs::draw() {
	
	if (m_info.empty())
		return;
	
	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();
	
	// calculate the size of the tab buttons
	static int tab_button_size = 0;
	
	if (m_parent_element) {
	 	
		if (m_tab_layout == fgui::tab_layout::HORIZONTAL) 
			tab_button_size = (m_parent_element->get_size().width - 12) / m_info.size();
		
		else if (m_tab_layout == fgui::tab_layout::VERTICAL)
			tab_button_size = (m_parent_element->get_size().height - 31) / m_info.size();
	}
	else
		tab_button_size = m_width / m_info.size();

	// get the window style
	fgui::style style = handler::get_style();

	for (std::size_t i = 0; i < m_info.size(); i++) {

		// tab title text size
		fgui::dimension text_size = fgui::render.get_text_size(fgui::tabs::get_font(), m_info[i].item);

		// tab area
		fgui::rect area = { 0, 0, 0, 0 };
		
		if (m_tab_layout == fgui::tab_layout::HORIZONTAL) 
			area = { a.x + (static_cast<int>(i) * tab_button_size), a.y, tab_button_size, m_height };
		
		else if (m_tab_layout == fgui::tab_layout::VERTICAL)
			area = { a.x, a.y + static_cast<int>(i) * tab_button_size, m_width, tab_button_size };

		// tab button body
		fgui::render.outline(area.left - 1, area.top - 1, area.right + 2, area.bottom + 2, fgui::color(style.tabs.at(1)));
		fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.tabs.at(0), 200));
		
		if (m_index == i)
			fgui::render.colored_gradient(area.left, area.top, area.right, area.bottom, fgui::color(style.tabs.at(3)), fgui::color(style.tabs.at(4)), false);
		else
			fgui::render.colored_gradient(area.left, area.top, area.right, area.bottom, fgui::color(style.tabs.at(2)), fgui::color(style.tabs.at(1)), false);

		// tab button label
		fgui::render.text(area.left + (area.right / 2) - (text_size.width / 2), area.top + (area.bottom / 2) - (text_size.height / 2), fgui::color(style.text.at(3)), fgui::tabs::get_font(), m_info[i].item);
	}
}

//---------------------------------------------------------
void fgui::tabs::handle_input() {}

//---------------------------------------------------------
void fgui::tabs::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// calculate the size of the tab buttons
	static int tab_button_size = 0;

	if (m_parent_element) {
		
		if (m_tab_layout == fgui::tab_layout::HORIZONTAL) 
			tab_button_size = (m_parent_element->get_size().width - 12) / m_info.size();
		
		else if (m_tab_layout == fgui::tab_layout::VERTICAL)
			tab_button_size = (m_parent_element->get_size().height - 12) / m_info.size();
	}
	else
		tab_button_size = m_width / m_info.size();

	for (std::size_t i = 0; i < m_info.size(); i++) {

		// tab area
		fgui::rect area = { 0, 0, 0, 0 };
		
		if (m_tab_layout == fgui::tab_layout::HORIZONTAL) 
			area = { a.x + (static_cast<int>(i) * tab_button_size), a.y, tab_button_size, m_height };
		
		else if (m_tab_layout == fgui::tab_layout::VERTICAL)
			area = { a.x, a.y + static_cast<int>(i) * tab_button_size, m_width, tab_button_size };

		// select the tab
		if (fgui::input_system::key_press(fgui::external::MOUSE_LEFT)) {

			if (fgui::input_system::mouse_in_area(area))
				m_index = i;
		}
	}
}

//---------------------------------------------------------
void fgui::tabs::tooltip() {}

//---------------------------------------------------------
void fgui::tabs::save(nlohmann::json& json_module) {}

//---------------------------------------------------------
void fgui::tabs::load(const std::string_view file_name) {}