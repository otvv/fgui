/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// framework includes
#include "element.hh"
#include "../dependencies/color.hh"

namespace fgui {

	class colorpicker : public fgui::element {
	public:
		colorpicker();

		// draw the element
		void draw();

		// set a custom color for the color picker
		void set_color(int red, int green, int blue, int alpha = 255);
		void set_color(fgui::color color);

		// returns the current selected color
		fgui::color get_color();

		// sets a custom state for the color picker (if the color pallet is opened or not)
		void set_state(bool state);

		// returns the current state of the color picker (if the color pallet is opened or not)
		bool get_state();

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

		bool m_opened;
		fgui::color m_color = { 0, 0, 0 };
	};
}