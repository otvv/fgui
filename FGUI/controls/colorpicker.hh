/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// framework includes
#include "element.hh"
#include "../dependencies/color.hh"

namespace fgui {

	class colorpicker final : public fgui::element {
	public:
		colorpicker();

		// draw the element
		void draw() override final;

		// set a custom color for the color picker
		inline void set_color(const int &red, const int &green, const int &blue, const int &alpha = 255) noexcept {

			m_color = { red, green, blue, alpha };
		}

		inline void set_color(const fgui::color &color) noexcept {

			m_color = color;
		}

		// returns the current selected color
		inline fgui::color get_color() const noexcept {

			return m_color;
		}

		// sets a custom state for the color picker (if the color pallet is opened or not)
		inline void set_state(const fgui::state &state) noexcept {

			m_opened = state;
		}

		// returns the current state of the color picker (if the color pallet is opened or not)
		inline fgui::state get_state() const noexcept {

			return m_opened;
		}

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
		fgui::state m_opened;
		fgui::color m_color = { 0, 0, 0 };
	};
}