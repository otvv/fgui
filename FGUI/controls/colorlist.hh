/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>
#include <vector>
#include <algorithm>

// framework includes
#include "button.hh"
#include "slider.hh"
#include "element.hh"
#include "checkbox.hh"
#include "../dependencies/color.hh"

namespace fgui {

	struct color_info {
		color_info(std::string identificator, fgui::color color, bool gradient = false) {
			
			m_alpha_slider = std::make_shared<fgui::slider>();
			m_alpha_slider->set_title("alpha");
			m_alpha_slider->set_value(m_first_color.m_alpha / 2.55f);
			m_alpha_slider->set_boundaries(0, (255 / 2.55f));
			m_alpha_slider->set_tooltip("Change the color alpha percentage");
			m_alpha_slider->set_font("Tahoma", 12, fgui::font_flags::ANTIALIAS, false);
			m_alpha_slider->set_boundaries_text("transparent", "opaque");

			m_plus_button = std::make_shared<fgui::button>();
			m_plus_button->set_title("+");
			m_plus_button->set_size(16, 16);
			m_plus_button->set_tooltip("Add a new color into the sequence");
			m_plus_button->set_font("Tahoma", 11, fgui::font_flags::ANTIALIAS, true);

			m_minus_button = std::make_shared<fgui::button>();
			m_minus_button->set_title("-");
			m_minus_button->set_size(16, 16);
			m_minus_button->set_tooltip("Remove the last added color of the sequence");
			m_minus_button->set_font("Tahoma", 11, fgui::font_flags::ANTIALIAS, true);

			m_gradient_checkbox = std::make_shared<fgui::checkbox>();
			m_gradient_checkbox->set_title("Gradient");
			m_gradient_checkbox->set_tooltip("Enable the color interpolation");
			m_gradient_checkbox->set_font("Tahoma", 12, fgui::font_flags::ANTIALIAS, false);

			m_second_color_added = false;
			m_identificator = identificator;
			m_first_color = color;
			m_backup_color = m_first_color;
			m_gradient_checkbox->set_bool(gradient);
		}

		std::string m_identificator;
		fgui::color	m_first_color = { 0, 0, 0 };
		fgui::color	m_second_color = { 0, 0, 0 };
		fgui::color	m_backup_color = { 0, 0, 0 };
		std::shared_ptr<fgui::slider> m_alpha_slider;
		std::shared_ptr<fgui::button> m_plus_button, m_minus_button;
		std::shared_ptr<fgui::checkbox> m_gradient_checkbox;
		bool m_second_color_added = false;
	};

	class colorlist : public fgui::element {
	public:
		colorlist();

		// draw the element
		void draw();

		// add a new color to the list
		void add_color(std::string identificator, fgui::color color, bool gradient = false);

		// set the color of a specific element on the list
		void set_color(int index, fgui::color color);

		// set the gradient state for a specific color on the list
		void set_gradient(int index, bool gradient);

		// get info the color of a specified color picker index
		fgui::color get_color(int index);

		// handle keyboard and mouse input
		void handle_input();

		// handle the element updates
		void update();

		// element tooltip
		void tooltip();

		// save the element state
		void save(const std::string& file_name, nlohmann::json& json_module);

		// load the element state
		void load(const std::string& file_name);
	private:

		int m_selected;
		bool m_dragging;
		int m_slider_top;
		int m_item_height;
		std::vector<fgui::color_info> m_color_list;
	};
}