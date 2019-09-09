/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

// includes
#include "tabs.hh"
#include "listbox.hh"
#include "element.hh"
#include "combobox.hh"
#include "checkbox.hh"
#include "multibox.hh"
#include "container.hh"
#include "../dependencies/aliases.hh"

void fgui::element::set_position(int x, int y) {

	m_x = x;
	m_y = y;
}

//---------------------------------------------------------
void fgui::element::set_size(int width, int height) {

	m_width = width;
	m_height = height;
}

//---------------------------------------------------------
fgui::dimension fgui::element::get_size() {

	return { m_width, m_height };
}

//---------------------------------------------------------
bool fgui::element::unlocked() { // figure out a new name for this

	if (!m_controller || m_page_index == -1)
		return true;

	if (m_controller->get_family(fgui::element_family::COMBOBOX_FAMILY))
		return std::reinterpret_pointer_cast<fgui::combobox>(m_controller)->get_index() == m_page_index;
		
	else if (m_controller->get_family(fgui::element_family::CHECKBOX_FAMILY))
		return std::reinterpret_pointer_cast<fgui::checkbox>(m_controller)->get_bool() == m_page_index;

	else if (m_controller->get_family(fgui::element_family::LISTBOX_FAMILY))
		return std::reinterpret_pointer_cast<fgui::listbox>(m_controller)->get_index() == m_page_index;
		
	else if (m_controller->get_family(fgui::element_family::MULTIBOX_FAMILY))
		return std::reinterpret_pointer_cast<fgui::multibox>(m_controller)->get_selected(m_page_index);
		
	else if (m_controller->get_family(fgui::element_family::TAB_FAMILY))
		return std::reinterpret_pointer_cast<fgui::tabs>(m_controller)->get_index() == m_page_index;
	
	return false;
}

//---------------------------------------------------------
fgui::point fgui::element::get_position() {

	return { m_x, m_y };
}

//---------------------------------------------------------
void fgui::element::set_title(std::string title) {

	m_title = title;
}

//---------------------------------------------------------
std::string fgui::element::get_title() {

	return m_title;
}

//---------------------------------------------------------
void fgui::element::set_tooltip(std::string tooltip) {

	m_tooltip = tooltip;
}

//---------------------------------------------------------
std::shared_ptr<fgui::element> fgui::element::get_window() {

	auto current_container = shared_from_this();

	while (current_container->m_parent_element)
		current_container = current_container->m_parent_element;

	return current_container;
}

//---------------------------------------------------------
std::shared_ptr<fgui::element> fgui::element::get_first_container() {
	
	auto first_container = shared_from_this();

	while (!first_container->get_family(fgui::element_family::CONTAINER_FAMILY))
		first_container = first_container->m_parent_element;

	return first_container;
}

//---------------------------------------------------------
fgui::point fgui::element::get_absolute_position() {

	m_absolute_position = { 0, 0 };

	if (!m_parent_element)
		return { get_position().x, get_position().y };

	fgui::point position = m_parent_element->get_absolute_position();

	m_absolute_position.x = m_x + position.x;
	m_absolute_position.y = m_y + position.y;
	
	if (m_parent_element->get_family(fgui::element_family::CONTAINER_FAMILY) && std::reinterpret_pointer_cast<fgui::container>(m_parent_element)->get_scrollbar_state())
		m_absolute_position.y -= std::reinterpret_pointer_cast<fgui::container>(m_parent_element)->get_scroll_offset();

	// element area 
	if (m_parent_element == get_window())
		m_absolute_position.y += 25; // 25 being the size of the header bar
	
	else if (m_parent_element != get_window())
		m_absolute_position.y += 1;

	return m_absolute_position;
}

//---------------------------------------------------------
void fgui::element::set_flag(int flag) {

	m_flags |= flag;
}

//---------------------------------------------------------
bool fgui::element::get_flag(fgui::element_flag flag) {

	if (m_flags & flag)
		return true;

	return false;
}

//---------------------------------------------------------
void fgui::element::set_family(int family) {

	m_family = family;
}

//---------------------------------------------------------
bool fgui::element::get_family(fgui::element_family family) {

	if (m_family == family)
		return true;

	return false;
}

//---------------------------------------------------------
void fgui::element::set_controller(std::shared_ptr<fgui::element> controller) { 

	m_controller = controller;
}

//---------------------------------------------------------
void fgui::element::set_identificator(std::string identificator) {

	m_identificator = identificator;
}

//---------------------------------------------------------
std::string fgui::element::get_identificator() {

	return m_identificator;
}

//---------------------------------------------------------
void fgui::element::set_font(std::string font_family, int size, int flags, bool bold) {

	fgui::render.create_font(m_font, font_family, size, flags, bold);
}

//---------------------------------------------------------
void fgui::element::set_font(fgui::element_font element_font) {

	fgui::render.create_font(m_font, element_font.m_family, element_font.m_size, element_font.m_flags, element_font.m_bold);
}

//---------------------------------------------------------
fgui::font fgui::element::get_font() {

	return m_font;
}