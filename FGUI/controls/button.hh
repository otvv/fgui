/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>
#include <vector>
#include <functional>

// framework includes
#include "element.hh"

namespace fgui {

	class button final : public fgui::element {
	public:
		button();

		// draw the element
		void draw() override final;

		// set the function that the button will call when clicked
		inline void set_function(const std::function<void()> &callback) noexcept {

			m_callback = callback; 
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
		std::function<void()> m_callback;
	};
}