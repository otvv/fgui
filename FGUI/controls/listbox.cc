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
	fgui::listbox::m_family = fgui::element_family::LISTBOX_FAMILY;
	fgui::element::m_flags = fgui::element_flag::DRAWABLE | fgui::element_flag::CLICKABLE | fgui::element_flag::SAVABLE;
}

//---------------------------------------------------------
void fgui::listbox::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	auto style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, m_width, m_height };

	// get the number of displayed items
	unsigned int item_displayed = 0;

	// calculate the quantity of entries that will be drawned on the listbox
	int calculated_items = m_height / m_item_height;

	// listbox body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.listbox.at(0)));

	if (fgui::input.is_mouse_in_region(area) || m_dragging)
		fgui::render.outline(area.left + 2, area.top + 2, (area.right - 14) - 4, area.bottom - 4, fgui::color(style.listbox.at(3)));
	else
		fgui::render.outline(area.left + 1, area.top + 1, area.right - 2, area.bottom - 2, fgui::color(style.listbox.at(1)));

	fgui::render.rect(area.left + 3, area.top + 3, (area.right - 14) - 6, area.bottom - 6, fgui::color(style.listbox.at(2)));

	// listbox label
	fgui::render.text(area.left, area.top - 15, fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_title);

	if (m_items.empty())
		return;

	for (std::size_t i = m_slider_top; (i < m_items.size() && item_displayed < calculated_items); i++) {

		// get the item region
		fgui::rect item_area = { a.x, a.y + (m_item_height * item_displayed), (m_width - 15), m_item_height };
		
		int item_text_width, item_text_height;
		fgui::render.get_text_size(fgui::listbox::get_font(), m_items[i].first, item_text_width, item_text_height);

		// if the user is hovering an item on the list
		if (fgui::input.is_mouse_in_region(item_area) || m_index == i) {

			fgui::render.rect(item_area.left + 2, item_area.top + 2, item_area.right - 4, item_area.bottom - 4, fgui::color(style.listbox.at(3)));

			if (fgui::listbox::m_items[i].first.length() > 20)
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_height / 2), fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_items[i].first.replace(m_items[i].first.begin() + 20, m_items[i].first.end(), "..."));
			else
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_height / 2), fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_items[i].first);
		}

		else if (!fgui::input.is_mouse_in_region(item_area)) {

			if (fgui::listbox::m_items[i].first.length() > 20)
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_height / 2), fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_items[i].first.replace(m_items[i].first.begin() + 20, m_items[i].first.end(), "..."));
			else
				fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (item_text_height / 2), fgui::color(style.text.at(0)), fgui::listbox::get_font(), m_items[i].first);
		}

		item_displayed++;
	}

	// calculate the slider position
	float calculated_position = static_cast<float>(m_slider_top) / static_cast<float>(m_items.size());

	if (calculated_position >= 1.f)
		calculated_position = 1.f;

	calculated_position *= m_height;

	// calculate the slider size
	float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_items.size());

	if (calculated_size > 1.f)
		calculated_size = 1.f;

	calculated_size *= m_height;
	
	// scrollbar area
	fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

	// scrollbar body
	fgui::render.outline(scrollbar_area.left + 1, scrollbar_area.top + 1, scrollbar_area.right - 2, scrollbar_area.bottom - 2, fgui::color(style.listbox.at(0)));
	fgui::render.rect(scrollbar_area.left, scrollbar_area.top, scrollbar_area.right, scrollbar_area.bottom, fgui::color(style.listbox.at(1)));
	fgui::render.outline(scrollbar_area.left + 1, (scrollbar_area.top + calculated_position) + 1, scrollbar_area.right - 2, (calculated_size - 2) - 4, fgui::color(style.listbox.at(3)));

	if (m_items.size() > 100)
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.listbox.at(1)), fgui::color(style.listbox.at(2)), fgui::gradient_type::VERTICAL);
	else
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.listbox.at(1)), fgui::color(style.listbox.at(2)), fgui::gradient_type::VERTICAL);

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
void fgui::listbox::add_item(std::string item, int value) {

	m_items.emplace_back(item, value);
}

//---------------------------------------------------------
std::string fgui::listbox::get_item() {

	return m_items[m_index].first;
}

//---------------------------------------------------------
int fgui::listbox::get_index() {

	return m_index;
}

//---------------------------------------------------------
int fgui::listbox::get_value() {

	return m_items[m_index].second;
}

//---------------------------------------------------------
void fgui::listbox::set_index(int index) {

	m_index = index;
}

//---------------------------------------------------------
void fgui::listbox::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	if (m_items.size() > 0) {

		// get the control area
		fgui::rect area = { a.x, a.y, m_width , m_height };

		// scrollbar area
		fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

		if (fgui::input.is_mouse_in_region(scrollbar_area)) {
					
			if (fgui::input.get_key_state(MOUSE_LEFT)) 
				m_dragging = true;
		}

		// calculate the amount of items to be drawned
		int calculated_items = m_height / m_item_height;

		// get the number of displayed items
		unsigned int item_displayed = 0;

		for (std::size_t i = m_slider_top; (i < m_items.size() && item_displayed < calculated_items); i++) {

			// get the item area of the list box
			fgui::rect item_region = { a.x, a.y + (item_displayed * m_item_height), m_width - 15, m_item_height };

			if (fgui::input.is_mouse_in_region(item_region)) {

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
	int calculated_items = m_height / m_item_height;

	if (m_dragging) {

		if (fgui::input.get_key_state(MOUSE_LEFT)) {

			// get the cursor position
			fgui::point cursor;
			fgui::input.get_mouse_position(cursor.x, cursor.y);

			// move the slider vertically
			cursor.y -= a.y + 2;

			// ratio of how many visible to how many are hidden
			float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_items.size());
			calculated_size *= m_height;

			// height delta
			float height_delta = (cursor.y + calculated_size) - m_height;

			if (height_delta >= 0)
				cursor.y -= height_delta;

			float new_position_ratio = static_cast<float>(cursor.y) / static_cast<float>(m_height);
			m_slider_top = new_position_ratio * m_items.size();

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
void fgui::listbox::save(const std::string& file_name, nlohmann::json& json_module) {

	json_module[m_identificator] = m_index;
}

//---------------------------------------------------------
void fgui::listbox::load(const std::string& file_name) {
	
	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name, std::ifstream::binary);

	if (!file_to_load.good())
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	m_index = json_module[m_identificator];
}