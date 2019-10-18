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
		color_info(const std::string_view _identificator, const fgui::color &_color, bool _gradient = false) {
			
			alpha_slider = std::make_shared<fgui::slider>();
			alpha_slider->set_title("alpha");
			alpha_slider->set_value(first_color.m_alpha / 2.55f);
			alpha_slider->set_boundaries(0, (255 / 2.55f));
			alpha_slider->set_tooltip("Change the color alpha percentage");
			alpha_slider->set_font("Tahoma", 12, 0x0 /* NONE */, false);
			alpha_slider->set_boundaries_text("transparent", "opaque");

			plus_button = std::make_shared<fgui::button>();
			plus_button->set_title("+");
			plus_button->set_size(16, 16);
			plus_button->set_tooltip("Add a new color into the sequence");
			plus_button->set_font("Tahoma", 11, 0x0 /* NONE */, true);

			minus_button = std::make_shared<fgui::button>();
			minus_button->set_title("-");
			minus_button->set_size(16, 16);
			minus_button->set_tooltip("Remove the last added color of the sequence");
			minus_button->set_font("Tahoma", 11, 0x0 /* NONE */, true);

			gradient_checkbox = std::make_shared<fgui::checkbox>();
			gradient_checkbox->set_title("Gradient");
			gradient_checkbox->set_tooltip("Enable color interpolation");
			gradient_checkbox->set_font("Tahoma", 12, 0x0 /* NONE */, false);

			second_color_added = false;
			identificator = _identificator;
			first_color = _color;
			backup_color = first_color;
			gradient_checkbox->set_bool(_gradient);
		}

		std::string identificator;
		fgui::color	first_color = { 0, 0, 0 };
		fgui::color	second_color = { 0, 0, 0 };
		fgui::color	backup_color = { 0, 0, 0 };
		std::shared_ptr<fgui::slider> alpha_slider;
		std::shared_ptr<fgui::button> plus_button, minus_button;
		std::shared_ptr<fgui::checkbox> gradient_checkbox;
		bool second_color_added = false;
	};

	class colorlist final : public fgui::element {
	public:
		colorlist();

		// draw the element
		void draw() override final;

		// add a new color to the list
		inline void add_color(const std::string_view identificator, const fgui::color &color, bool gradient_state = false) noexcept {
			
			m_color_list.push_back( {identificator, color, gradient_state});
		}

		// set the color and the gradient state of a specific color on the list
		inline void set_color(const int &index, const fgui::color &color, bool gradient_state = false) noexcept {

			m_color_list[index].first_color = color;

			m_color_list[index].gradient_checkbox->set_bool(gradient_state);
		}

		// get info the color of a specified color picker index
		fgui::color get_color(int index);

		// handle keyboard and mouse input
		void handle_input() override final;

		// handle the element updates
		void update() override final;

		// element tooltip
		void tooltip() override final;

		// save the element state
		void save(nlohmann::json& json_module) override final;

		// load the element state
		void load(const std::string_view file_name) override final;
	private:

		std::size_t m_selected;
		bool m_dragging;
		int m_slider_top;
		int m_item_height;
		std::vector<fgui::color_info> m_color_list;
	};
}