/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <functional>

// framework includes
#include "element.hh"

namespace fgui {

	class container final : public fgui::element {
	public:
		container();

		// draw the element
		void draw() override final;

		// set the container state (this will be used for windows)
		inline void set_state(const fgui::state &state) noexcept {

			m_opened = state;
		}

		// returns the state of the container
		inline fgui::state get_state() const noexcept {

			return m_opened;
		}

		// save all elements inside a config file
		void save_config(const std::string_view file_name);

		// add a new control in the container
		void add_control(const std::shared_ptr<fgui::element> &control, int page_index = -1, bool manual_size = false);

		// set whether or not the scrollbar should be used
		inline void set_scrollbar_state(const fgui::state &state) noexcept {

			m_scrollable = state;
		}

		// enable/disable the resizeable option of the container
		inline void set_resize_state(const fgui::state &state) noexcept {

			m_resizeable = state;
		}

		// enable/disable the hidden state of the container (hover to unhide)
		inline void set_hidden_state(const fgui::state &state) noexcept{

			m_hideable = state;
		}

		// returns true if the container has a scrollbar
		inline fgui::state get_scrollbar_state() const noexcept {

			return m_scrollable;
		}

		// get the amount that a element is suposed to move according with the scrollbar
		inline int get_scroll_offset() const noexcept {

			return m_scroll_offset;
		}

		// call a function when the window is opened
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

		int m_scroll_offset, m_bottom_element_pos;
		fgui::state m_opened, m_scrollable, m_resizeable, m_hideable;
		bool m_dragging_container, m_size_changing, m_dragging_scrollbar;
		std::vector<std::shared_ptr<fgui::element>> m_elements;
		std::function<void()> m_callback;
	};
}