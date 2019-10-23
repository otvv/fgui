/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "listbox.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"
#include "../dependencies/aliases.hh"

fgui::listbox::listbox() {

	fgui::listbox::m_index = 0;
	fgui::listbox::m_title = "listbox";
	fgui::listbox::m_slider_top = 0;
	fgui::listbox::m_item_height = 20;
	fgui::listbox::m_font = fgui::element::m_font;
	fgui::listbox::m_type =  static_cast<int>(fgui::detail::element_type::LISTBOX);
	fgui::element::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE) |  static_cast<int>(fgui::detail::element_flags::CLICKABLE) |  static_cast<int>(fgui::detail::element_flags::SAVABLE);
}

//---------------------------------------------------------
void fgui::listbox::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// get the number of displayed items
	unsigned int item_displayed = 0;

	// calculate the quantity of entries that will be drawned on the listbox
	static int calculated_items = m_height / m_item_height;

	// listbox body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.listbox.at(0)));

	if (fgui::input_system::mouse_in_area(area) || m_dragging)
		fgui::render.outline(area.left + 2, area.top + 2, (area.right - 14) - 4, area.bottom - 4, fgui::color(style.listbox.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.listbox.at(1)));

	fgui::render.rect(area.left + 3, area.top + 3, (area.right - 14) - 6, area.bottom - 6, fgui::color(style.listbox.at(2)));

	// listbox label
	fgui::render.text(area.left, area.top - 15, fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_title);

	if (m_info.empty())
		return;

	for (std::size_t i = m_slider_top; (i < m_info.size() && item_displayed < calculated_items); i++) {

		// get the item region
		fgui::rect item_area = { a.x, a.y + (m_item_height * item_displayed), (m_width - 15), m_item_height };

		// item text size		
		fgui::dimension item_text_size = fgui::render.get_text_size(fgui::listbox::get_font(), m_info[i].item);

		// if the user is hovering an item on the list
		if (fgui::input_system::mouse_in_area(item_area) || m_index == i) {

			fgui::render.rect(item_area.left + 2, item_area.top + 2, item_area.right - 4, item_area.bottom - 4, fgui::color(style.listbox.at(3)));

			if (m_info[i].item.length() > 20)
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_size.height / 2), fgui::color(style.text.at(3)), fgui::listbox::get_font(), m_info[i].item.replace(m_info[i].item.begin() + 20, m_info[i].item.end(), "..."));
			else
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_size.height / 2), fgui::color(style.text.at(3)), fgui::listbox::get_font(), m_info[i].item);
		}

		else if (!fgui::input_system::mouse_in_area(item_area)) {

			if (m_info[i].item.length() > 20)
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_size.height / 2), fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_info[i].item.replace(m_info[i].item.begin() + 20, m_info[i].item.end(), "..."));
			else
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_size.height / 2), fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_info[i].item);
		}

		item_displayed++;
	}

	// calculate the slider position
	float calculated_position = static_cast<float>(m_slider_top) / static_cast<float>(m_info.size());

	if (calculated_position >= 1.f)
		calculated_position = 1.f;

	calculated_position *= m_height;

	// calculate the slider size
	float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_info.size());

	if (calculated_size > 1.f)
		calculated_size = 1.f;

	calculated_size *= m_height;
	
	// scrollbar area
	fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

	// scrollbar body
	fgui::render.outline(scrollbar_area.left + 1, scrollbar_area.top + 1, scrollbar_area.right - 2, scrollbar_area.bottom - 2, fgui::color(style.listbox.at(0)));
	fgui::render.rect(scrollbar_area.left, scrollbar_area.top, scrollbar_area.right, scrollbar_area.bottom, fgui::color(style.listbox.at(1)));
	fgui::render.outline(scrollbar_area.left + 1, (scrollbar_area.top + calculated_position) + 1, scrollbar_area.right - 2, (calculated_size - 2) - 4, fgui::color(style.listbox.at(3)));

	if (m_info.size() > 100)
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.listbox.at(1)), fgui::color(style.listbox.at(2)), false);
	else
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.listbox.at(1)), fgui::color(style.listbox.at(2)), false);

	// dots
	if (m_dragging) {
		
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 1, 1, 1, fgui::color(style.listbox.at(3)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 3, 1, 1, fgui::color(style.listbox.at(3)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 5, 1, 1, fgui::color(style.listbox.at(3)));
	}

	else if (!m_dragging) {
		
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 1, 1, 1, fgui::color(style.text.at(0)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 3, 1, 1, fgui::color(style.text.at(0)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 5, 1, 1, fgui::color(style.text.at(0)));
	}
}

//---------------------------------------------------------
void fgui::listbox::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	if (m_info.size() > 0) {

		// get the control area
		fgui::rect area = { a.x, a.y, m_width , m_height };

		// scrollbar area
		fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

		if (fgui::input_system::mouse_in_area(scrollbar_area)) {
					
			if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) 
				m_dragging = true;
		}

		// get the number of displayed items
		unsigned int item_displayed = 0;

		// calculate the amount of items to be drawned
		static int calculated_items = m_height / m_item_height;

		for (std::size_t i = m_slider_top; (i < m_info.size() && item_displayed < calculated_items); i++) {

			// get the item area of the list box
			fgui::rect item_region = { a.x, a.y + (item_displayed * m_item_height), m_width - 15, m_item_height };

			if (fgui::input_system::mouse_in_area(item_region)) {

				// select a item
				m_index = i;
			}

			item_displayed++;
		}
	}
}

//---------------------------------------------------------
void fgui::listbox::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// calculate the amount of items to be drawned
	static int calculated_items = m_height / m_item_height;

	if (m_dragging) {

		if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) {

			// cursor position
			fgui::point cursor = fgui::input_system::mouse_position();

			// move the slider vertically
			cursor.y -= a.y + 2;

			// ratio of how many visible to how many are hidden
			float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_info.size());
			calculated_size *= m_height;

			// height delta
			float height_delta = (cursor.y + calculated_size) - m_height;

			if (height_delta >= 0)
				cursor.y -= height_delta;

			float new_position_ratio = static_cast<float>(cursor.y) / static_cast<float>(m_height);
			m_slider_top = new_position_ratio * m_info.size();

			if (m_slider_top <= 0)
				m_slider_top = 0;
		}

		else
			m_dragging = false;
	}
}

//---------------------------------------------------------
void fgui::listbox::tooltip() {

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
			fgui::render.rect(cursor.x + 10, cursor.y + 20, tooltip_text_size.width + 10, 20, fgui::color(style.listbox.at(3)));
			fgui::render.text(cursor.x + 10 + ((tooltip_text_size.width + 10) / 2) - (tooltip_text_size.width / 2), cursor.y + 20 + (20 / 2) - (tooltip_text_size.height / 2), fgui::color(style.text.at(3)), fgui::element::get_font(), m_tooltip);
		}
	}
}

//---------------------------------------------------------
void fgui::listbox::save(nlohmann::json& json_module) {

	json_module[m_identificator.data()] = m_index;
}

//---------------------------------------------------------
void fgui::listbox::load(const std::string_view file_name) {
	
	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name.data(), std::ifstream::binary);

	if (file_to_load.fail()) // todo: make an exception handler
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	m_index = json_module[m_identificator.data()];
}
