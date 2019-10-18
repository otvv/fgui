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

//---------------------------------------------------------
bool fgui::element::unlocked() {

	if (!m_controller || m_page_index == -1)
		return true;

	switch (m_controller->m_type) {

		case  static_cast<int>(fgui::detail::element_type::COMBOBOX):
			return std::reinterpret_pointer_cast<fgui::combobox>(m_controller)->get_index() == m_page_index;
		
		case  static_cast<int>(fgui::detail::element_type::CHECKBOX):
			return std::reinterpret_pointer_cast<fgui::checkbox>(m_controller)->get_bool() == m_page_index;

		case  static_cast<int>(fgui::detail::element_type::LISTBOX):
			return std::reinterpret_pointer_cast<fgui::listbox>(m_controller)->get_index() == m_page_index;
		
		case  static_cast<int>(fgui::detail::element_type::MULTIBOX):
			return std::reinterpret_pointer_cast<fgui::multibox>(m_controller)->get_selected(m_page_index);
		
		case  static_cast<int>(fgui::detail::element_type::TAB):
			return std::reinterpret_pointer_cast<fgui::tabs>(m_controller)->get_index() == static_cast<std::size_t>(m_page_index);
	}
	
	return false;
}

//---------------------------------------------------------
std::shared_ptr<fgui::element> fgui::element::get_window() {

	std::shared_ptr<fgui::element> current_container = shared_from_this();

	while (current_container->m_parent_element)
		current_container = current_container->m_parent_element;

	return current_container;
}

//---------------------------------------------------------
std::shared_ptr<fgui::element> fgui::element::get_first_container() {
	
	std::shared_ptr<fgui::element> first_container = shared_from_this();

	while (!first_container->get_family(fgui::detail::element_type::CONTAINER))
		first_container = first_container->m_parent_element;

	return first_container;
}

//---------------------------------------------------------
fgui::point fgui::element::get_absolute_position() {

	m_absolute_position = { 0, 0 };

	//
	// this is the size of the window header bar in pixels
	//
	constexpr int header_bar_size = 25;

	if (!m_parent_element)
		return { get_position().x, get_position().y };

	fgui::point position = m_parent_element->get_absolute_position();

	m_absolute_position.x = m_x + position.x;
	m_absolute_position.y = m_y + position.y;
	
	if (m_parent_element->get_family(fgui::detail::element_type::CONTAINER) && std::reinterpret_pointer_cast<fgui::container>(m_parent_element)->get_scrollbar_state())
		m_absolute_position.y -= std::reinterpret_pointer_cast<fgui::container>(m_parent_element)->get_scroll_offset();

	// element usable area 
	if (m_parent_element == get_window())
		m_absolute_position.y += header_bar_size;
	
	else if (m_parent_element != get_window())
		m_absolute_position.y += 1;

	return m_absolute_position;
}