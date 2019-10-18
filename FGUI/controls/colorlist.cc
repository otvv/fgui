/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

 // includes
#include "colorlist.hh"
#include "../handler/handler.hh"
#include "../dependencies/color.hh"

fgui::colorlist::colorlist() {

	fgui::colorlist::m_width = 350;
	fgui::colorlist::m_height = 200;
	fgui::colorlist::m_selected = 0;
	fgui::colorlist::m_slider_top = 0;
	fgui::colorlist::m_title = "colorlist";
	fgui::colorlist::m_item_height = 20;
	fgui::colorlist::m_font = fgui::element::m_font;
	fgui::colorlist::m_type =  static_cast<int>(fgui::detail::element_type::COLORLIST);
	fgui::element::m_flags =  static_cast<int>(fgui::detail::element_flags::DRAWABLE) |  static_cast<int>(fgui::detail::element_flags::CLICKABLE) |  static_cast<int>(fgui::detail::element_flags::SAVABLE);
}

//---------------------------------------------------------
void fgui::colorlist::draw() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the window style
	fgui::style style = handler::get_style();

	// get the control area
	fgui::rect area = { a.x, a.y, (m_width - 250) - 15, m_height };
				
	// get the number of displayed items
	unsigned int items_displayed = 0;

	// calculate the amount of items to be displayed
	unsigned int calculated_items = (m_height - 20) / m_item_height;

	// color list body
	fgui::render.outline(area.left, area.top, area.right, area.bottom, fgui::color(style.colorlist.at(0)));

	if (fgui::input_system::mouse_in_area(area))
		fgui::render.outline(area.left + 2, area.top + 2, (area.right - 15) - 4, area.bottom - 4, fgui::color(style.colorlist.at(3)));
	else
		fgui::render.outline(area.left + 2, area.top + 2, area.right - 4, area.bottom - 4, fgui::color(style.colorlist.at(1)));
	
	fgui::render.rect(area.left + 3, area.top + 3, (area.right - 15) - 6, area.bottom - 6, fgui::color(style.colorlist.at(2)));
	
	if (m_color_list.empty())
		return;

	for (std::size_t i = m_slider_top; (i < m_color_list.size() && items_displayed < calculated_items); i++) {

		// color identificator text size
		fgui::dimension identificator_text_size = fgui::render.get_text_size(fgui::colorlist::get_font(), m_color_list[i].identificator);

		// get the item area
		fgui::rect item_area = { a.x, a.y + (m_item_height * static_cast<int>(items_displayed)), (m_width - 250) - 15, m_item_height };

		// color identificator
		if (m_color_list[i].identificator.length() > 30)
			fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (identificator_text_size.height / 2), fgui::color(style.text.at(0)), fgui::colorlist::get_font(), m_color_list[i].identificator.replace(m_color_list[i].identificator.begin() + 30, m_color_list[i].identificator.end(), "..."));
		else
			fgui::render.text(item_area.left + 5, item_area.top + (item_area.bottom / 2) - (identificator_text_size.height / 2), fgui::color(style.text.at(0)), fgui::colorlist::get_font(), m_color_list[i].identificator);

		// color button body
		fgui::render.outline((item_area.left + 150), item_area.top + 4, 20, 16, fgui::color(style.colorlist.at(0)));
		
		if (fgui::input_system::mouse_in_area(item_area) || m_selected == i)
			fgui::render.outline((item_area.left + 150) + 2, (item_area.top + 2) + 4, 20 - 4, 16 - 4, fgui::color(style.colorlist.at(3)));
		else
			fgui::render.outline((item_area.left + 150) + 1, (item_area.top + 1) + 4, 20 - 2, 16 - 2, fgui::color(style.colorlist.at(2)));

		fgui::render.rect((item_area.left + 150) + 3, (item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(style.colorlist.at(1)));
		fgui::render.colored_gradient((item_area.left + 150) + 3, (item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(m_color_list[i].first_color), fgui::color(style.colorlist.at(2), m_color_list[i].first_color.m_alpha), false);

		// separator line
		fgui::render.line(item_area.left, item_area.top + item_area.bottom + 2, item_area.left + (item_area.right - 15) - 5, item_area.top + item_area.bottom + 2, fgui::color(style.colorlist.at(0)));

		if (m_color_list[i].second_color_added) {
			
			fgui::rect second_item_area = { a.x + 150, a.y + (m_item_height * static_cast<int>(items_displayed)), (m_width - 15) - 250, m_item_height };

			// second color button body
			fgui::render.outline((second_item_area.left + 25), second_item_area.top + 4, 20, 16, fgui::color(style.colorlist.at(0)));
		
			if (fgui::input_system::mouse_in_area(second_item_area) || m_selected == i)
				fgui::render.outline((second_item_area.left + 25) + 2, (second_item_area.top + 2) + 4, 20 - 4, 16 - 4, fgui::color(style.colorlist.at(3)));
			else
				fgui::render.outline((second_item_area.left + 25) + 1, (second_item_area.top + 1) + 4, 20 - 2, 16 - 2, fgui::color(style.colorlist.at(2)));

			fgui::render.rect((second_item_area.left + 25) + 3, (second_item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(style.colorlist.at(1)));
			fgui::render.colored_gradient((second_item_area.left + 25) + 3, (second_item_area.top + 3) + 4, 20 - 6, 16 - 6, fgui::color(m_color_list[i].second_color), fgui::color(style.colorlist.at(2), m_color_list[i].second_color.m_alpha), false);
		}

		items_displayed++;
	}

	// picker area
	fgui::rect picker_area = {a.x + (m_width - 240), a.y, 150, 150};

	// color picker pixelation value
	constexpr int pixelation = 3;

	// alpha background
	// NOTE: (If you are crashing here, you probably don't have the "alpha" function, just remove this line or replace with a rectangle)
	fgui::render.alpha(picker_area.left, picker_area.top, picker_area.right, picker_area.bottom);

	for (std::size_t i = 0; i < static_cast<float>(picker_area.bottom); i += pixelation) {

		// color
		fgui::color hue_color = fgui::color::hsb_to_rgb(i / 150.f, 1, 1);
		
		// hue
		fgui::render.rect(picker_area.left + picker_area.right + 10, picker_area.top + i, 15, pixelation, fgui::color(hue_color));

		for (std::size_t j = 0; j < (static_cast<float>(picker_area.right)); j += pixelation) {

			// color
			fgui::color hsb_color = fgui::color::hsb_to_rgb(fgui::color::get_hue(m_color_list[m_selected].first_color), j / static_cast<float>(picker_area.right), i / static_cast<float>(picker_area.bottom), m_color_list[m_selected].first_color.m_alpha);
			
			// hsb
			fgui::render.rect(picker_area.left + j, picker_area.top + i, pixelation, pixelation, fgui::color(hsb_color));
		}
	}

	// color hsb body
	fgui::render.outline(picker_area.left - 1, picker_area.top - 1, picker_area.right + 2, picker_area.bottom + 2, fgui::color(style.colorlist.at(0)));

	// hue bar body
	fgui::render.outline(picker_area.left + (picker_area.right + 10) - 1, picker_area.top - 1, 15 + 2, picker_area.bottom + 2, fgui::color(style.colorlist.at(0)));
	fgui::render.rect(picker_area.left + picker_area.right + 5, picker_area.top + picker_area.bottom * fgui::color::get_hue(m_color_list[m_selected].first_color), 3, 3, fgui::color(style.colorlist.at(3)));

	// alpha slider
	m_color_list[m_selected].alpha_slider->set_position(picker_area.left, picker_area.top + (picker_area.bottom + 20));
	m_color_list[m_selected].alpha_slider->draw();
	m_color_list[m_selected].alpha_slider->tooltip();

	// plus button
	m_color_list[m_selected].plus_button->set_position(picker_area.left, picker_area.top + (picker_area.bottom) + 40);
	m_color_list[m_selected].plus_button->draw();
	m_color_list[m_selected].plus_button->tooltip();

	// minus button
	m_color_list[m_selected].minus_button->set_position(picker_area.left + 20, picker_area.top + (picker_area.bottom) + 40);
	m_color_list[m_selected].minus_button->draw();
	m_color_list[m_selected].minus_button->tooltip();

	// gradient checkbox
	m_color_list[m_selected].gradient_checkbox->set_position(picker_area.left + 50, picker_area.top + (picker_area.bottom) + 40);
	m_color_list[m_selected].gradient_checkbox->draw();
	m_color_list[m_selected].gradient_checkbox->tooltip();

	// calculate the slider position
	float calculated_position = static_cast<float>(m_slider_top) / static_cast<float>(m_color_list.size());

	if (calculated_position >= 1.f)
		calculated_position = 1.f;

	calculated_position *= m_height;

	// calculate the slider size
	float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_color_list.size());

	if (calculated_size > 1.f)
		calculated_size = 1.f;

	calculated_size *= m_height;

	// scrollbar area
	fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

	// scrollbar body
	fgui::render.outline(scrollbar_area.left + 1, scrollbar_area.top + 1, scrollbar_area.right - 2, scrollbar_area.bottom - 2, fgui::color(style.colorlist.at(0)));
	fgui::render.rect(scrollbar_area.left, scrollbar_area.top, scrollbar_area.right, scrollbar_area.bottom, fgui::color(style.colorlist.at(1)));
	fgui::render.outline(scrollbar_area.left + 1, (scrollbar_area.top + calculated_position) + 1, scrollbar_area.right - 2, (calculated_size - 2) - 4, fgui::color(style.colorlist.at(3)));

	if (m_color_list.size() > 50)
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.colorlist.at(1)), fgui::color(style.colorlist.at(2)), false);
	else
		fgui::render.colored_gradient(scrollbar_area.left + 2, (scrollbar_area.top + calculated_position) + 2, scrollbar_area.right - 4, (calculated_size - 4) - 4, fgui::color(style.colorlist.at(1)), fgui::color(style.colorlist.at(2)), false);

	// dots
	if (m_dragging) {
		
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 1, 1, 1, fgui::color(style.colorlist.at(3)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 3, 1, 1, fgui::color(style.colorlist.at(3)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 5, 1, 1, fgui::color(style.colorlist.at(3)));
	}

	else if (!m_dragging) {
		
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 1, 1, 1, fgui::color(style.text.at(0)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 3, 1, 1, fgui::color(style.text.at(0)));
		fgui::render.rect(scrollbar_area.left + 5, (scrollbar_area.top + calculated_position) + 2 + (calculated_size / 2) - 5, 1, 1, fgui::color(style.text.at(0)));
	}
}

//---------------------------------------------------------
fgui::color fgui::colorlist::get_color(int index) {

	if (m_color_list[index].gradient_checkbox->get_bool()) {

		static float ttt1 = 0.f;

		ttt1 = std::fminf(ttt1 + 0.0005f, 1.f);

		if (ttt1 >= 1.f) {

			static float ttt2 = 0.f;

			// ghetto way to return back to the first color
			ttt2 = std::fminf(ttt2 + 0.0005f, 1.f);

			if (ttt2 >= 1.f) {
				ttt2 = 0.f;
				ttt1 = 0.f;
			}

			return fgui::color::interpolate(m_color_list[index].second_color, m_color_list[index].first_color, ttt2);
		}

		return fgui::color::interpolate(m_color_list[index].first_color, m_color_list[index].second_color, ttt1);
	}

	return m_color_list[index].first_color;
}

//---------------------------------------------------------
void fgui::colorlist::handle_input() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the control area
	fgui::rect area = { a.x, a.y, (m_width - 250) - 15, m_height };

	// scrollbar slider area
	fgui::rect scrollbar_area = { (area.left + 2) + (area.right - 15), area.top + 2, 15 - 4, area.bottom - 4 };

		if (fgui::input_system::mouse_in_area(scrollbar_area)) {
					
			if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) 
				m_dragging = true;
	}

	if (m_color_list.size() > 0) {
		
		// color picker area
		fgui::rect picker_area = { a.x + (m_width - 240), a.y, 150, 150 };

		// handle input
		m_color_list[m_selected].gradient_checkbox->handle_input();
		m_color_list[m_selected].alpha_slider->handle_input();
		
		// plus button area
		fgui::rect plus_button_area = { picker_area.left, (picker_area.top + picker_area.bottom) + 40, m_color_list[m_selected].plus_button->get_size().width, m_color_list[m_selected].plus_button->get_size().height };

		if (fgui::input_system::mouse_in_area(plus_button_area)) {

			// check if we don't have a second color added
			if (!m_color_list[m_selected].second_color_added) {

				m_color_list[m_selected].second_color_added = true;

				m_color_list[m_selected].backup_color = m_color_list[m_selected].first_color; 
				m_color_list[m_selected].second_color = m_color_list[m_selected].first_color;
			}
		}

		// minus button area
		fgui::rect minus_button_area = { picker_area.left + 20, (picker_area.top + picker_area.bottom) + 40, m_color_list[m_selected].minus_button->get_size().width, m_color_list[m_selected].minus_button->get_size().height };

		if (fgui::input_system::mouse_in_area(minus_button_area)) {

			// check if we have something to remove
			if (m_color_list[m_selected].second_color_added) {

				m_color_list[m_selected].second_color_added = false;

				m_color_list[m_selected].first_color = m_color_list[m_selected].backup_color;
				m_color_list[m_selected].second_color = fgui::color(0, 0, 0);

				m_color_list[m_selected].gradient_checkbox->set_bool(false);
			}
		}

		// get the number of displayed items
		static int item_displayed = 0;

		// calculate the amount of items to be drawned
		static int calculated_items = (m_height - 20) / m_item_height;

		for (std::size_t i = m_slider_top; (i < m_color_list.size() && item_displayed < calculated_items); i++) {

			// get the item area of the colorlist
			fgui::rect item_area = { a.x, a.y + (m_item_height * item_displayed), (m_width - 250) - 15, m_item_height };

			if (fgui::input_system::mouse_in_area(item_area)) {

				// select a color picker
				m_selected = i;
			}

			item_displayed++;
		}
	}
}

//---------------------------------------------------------
void fgui::colorlist::update() {

	// get the current position of the window
	fgui::point a = fgui::element::get_absolute_position();

	// get the number of displayed items
	static int item_displayed = 0;

	// calculate the amount of items to be drawned
	static int calculated_items = (m_height - 20) / m_item_height;

	if (m_dragging) {

		if (fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) {

			// get the cursor position
			fgui::point cursor = fgui::input_system::mouse_position();

			// move the scrollbar UP and DOWN according to the cursors position
			cursor.y -= a.y + 2;

			// ratio of how many visible to how many are hidden
			float calculated_size = static_cast<float>(calculated_items) / static_cast<float>(m_color_list.size());
			calculated_size *= m_height;

			// height delta
			float height_delta = (cursor.y + calculated_size) - m_height;

			if (height_delta >= 0)
				cursor.y -= height_delta;

			float new_position_ratio = static_cast<float>(cursor.y) / static_cast<float>(m_height);
			m_slider_top = new_position_ratio * m_color_list.size();

			if (m_slider_top <= 0)
				m_slider_top = 0;
		}

		else
			m_dragging = false;
	}

	if (m_color_list.size() > 0) {
		
		// update elements
		m_color_list[m_selected].alpha_slider->update();
		m_color_list[m_selected].minus_button->update();
		m_color_list[m_selected].plus_button->update();
		m_color_list[m_selected].gradient_checkbox->update();

		for (std::size_t i = m_slider_top; (i < m_color_list.size() && item_displayed < calculated_items); i++) {

			if (m_selected == i) {

				// color picker area
				fgui::rect picker_area = { a.x + (m_width - 240), a.y, 150, 150 };

				fgui::rect hsb_area = { picker_area.left, picker_area.top, picker_area.right, picker_area.bottom };
				fgui::rect hue_area = { picker_area.left + picker_area.right + 10, picker_area.top, 15, picker_area.bottom };

				static bool hue_selected = false;
				static bool hsb_selected = false;

				// get the cursor position
				fgui::point cursor = fgui::input_system::mouse_position();

				if (fgui::input_system::key_press(fgui::external::MOUSE_LEFT)) {

					hue_selected = fgui::input_system::mouse_in_area(hue_area);
					hsb_selected = fgui::input_system::mouse_in_area(hsb_area);
				}

				else if (!fgui::input_system::key_held(fgui::external::MOUSE_LEFT)) {

					hue_selected = false;
					hsb_selected = false;
				}

				if (hsb_selected) {

					fgui::precision_point relative_pos = { cursor.x - static_cast<float>(hsb_area.left), cursor.y - static_cast<float>(hsb_area.top) };
					m_color_list[i].first_color = fgui::color::hsb_to_rgb(fgui::color::get_hue(m_color_list[i].first_color), relative_pos.x / picker_area.right, relative_pos.y / picker_area.bottom, m_color_list[i].first_color.m_alpha);
				}

				if (hue_selected) {

					float hue = (cursor.y - hue_area.top) / 150.f;
					
					m_color_list[i].first_color = fgui::color::hsb_to_rgb(std::clamp(hue, 0.f, 1.f), 1, 1);
				}

				// color alpha
				m_color_list[i].first_color.m_alpha = (m_color_list[i].alpha_slider->get_value() * 2.55f);
			}
		}
	}
}

//---------------------------------------------------------
void fgui::colorlist::tooltip() {}

//---------------------------------------------------------
void fgui::colorlist::save(nlohmann::json& json_module) {

	for (std::size_t i = 0; i < m_color_list.size(); i++) {

		// main color
		json_module[m_identificator.data()][m_color_list[i].identificator]["primary_red"] = m_color_list[i].first_color.m_red;
		json_module[m_identificator.data()][m_color_list[i].identificator]["primary_green"] = m_color_list[i].first_color.m_green;
		json_module[m_identificator.data()][m_color_list[i].identificator]["primary_blue"] = m_color_list[i].first_color.m_blue;
		json_module[m_identificator.data()][m_color_list[i].identificator]["primary_alpha"] = m_color_list[i].first_color.m_alpha;

		if (m_color_list[i].second_color_added) {

			// secondary color
			json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_red"] = m_color_list[i].second_color.m_red;
			json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_green"] = m_color_list[i].second_color.m_green;
			json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_blue"] = m_color_list[i].second_color.m_blue;
			json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_alpha"] = m_color_list[i].second_color.m_alpha;
		}

		// gradient
		json_module[m_identificator.data()][m_color_list[i].identificator]["color_interpolation"] = m_color_list[i].gradient_checkbox->get_bool();
	}
}

//---------------------------------------------------------
void fgui::colorlist::load(const std::string_view file_name) {

	nlohmann::json json_module;

	// open the file
	std::ifstream file_to_load(file_name.data(), std::ifstream::binary);

	if (file_to_load.fail()) // todo: make an exception handler
		return;

	// read config file
	json_module = nlohmann::json::parse(file_to_load);

	// change the element state to match the one stored on file
	for (std::size_t i = 0; i < m_color_list.size(); i++) {

		// primary color
		m_color_list[i].first_color.m_red = json_module[m_identificator.data()][m_color_list[i].identificator]["primary_red"];
		m_color_list[i].first_color.m_green = json_module[m_identificator.data()][m_color_list[i].identificator]["primary_green"];
		m_color_list[i].first_color.m_blue = json_module[m_identificator.data()][m_color_list[i].identificator]["primary_blue"];
		m_color_list[i].first_color.m_alpha = json_module[m_identificator.data()][m_color_list[i].identificator]["primary_alpha"];

		if (m_color_list[i].second_color_added) {

			// secondary color
			m_color_list[i].second_color.m_red = json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_red"];
			m_color_list[i].second_color.m_green = json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_green"];
			m_color_list[i].second_color.m_blue = json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_blue"];
			m_color_list[i].second_color.m_alpha = json_module[m_identificator.data()][m_color_list[i].identificator]["secondary_alpha"];
		}

		// gradient
		m_color_list[i].gradient_checkbox->set_bool(json_module[m_identificator.data()][m_color_list[i].identificator]["color_interpolation"]);
	}
}