/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>
#include <string_view>

// framework includes
#include "element.hh"

namespace fgui {

	namespace detail {

		/*
	 	* NOTE 1: If you don't want to use winapi keycodes, you will need to manually map your keys here.
	 	*
	 	*
	 	* NOTE 2: By default the framework comes with 2 "maps". One for the IInputSystem (Source Engine) and
	 	* another for the Windows Virtual Keycodes (GetAsyncKeyState).
	 	*
	 	* (If you don't plan on using anything other than "VK keys", you should be fine.)
	 	*/

	 	// win api
		constexpr std::string_view m_winapi_text[] = { "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", " ", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "", "0", "1",
					"2", "3", "4", "5", "6", "7", "8", "9", "", "", "", "", "", "",
					"", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
					"m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y",
					"z", "", "", "", "", "", "0", "1", "2", "3",
					"4", "5", "6", "7", "8", "9", "*", "+", "_",
					"-", ".", "/", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", ";", "+", ",", "-", ".",
					"/?", "~", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "", "", "[{", "\\|", "}]", "'\"",
					"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "", "", "", "", ""
		};

			// iinput system
			constexpr std::string_view m_iinput_system_text[] = { "'", "0", "1", "2", "3", "4", "5", "6", "7",
					"8", "9", "a", "b", "c", "d", "e", "f", "g", "h",
					"i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
					"s", "t", "u", "v", "w", "x", "y", "z", "0",
					"1", "2", "3", "4", "5", "6", "7",
					"8", "9", "/", "*", "-", "+", "", ",", ".",
					"[", "ç", "~", "´", ",", ".", ";", "]", "-", "=",
					"", " ", "", "", "", "", "",
					"", "", "", "", "", "", "",
					"", "", "", "", "", "",
					"", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "",
					"", "", "", "", "", "", "", "",
					"", "", "", "", "", "", ""
		};
	}

	class textbox final : public fgui::element {
	public:
		textbox();

		// draw the element
		void draw() override final;

		// set a custom text
		inline void set_text(const std::string_view text) noexcept {

			m_text = text;
		}

		// get the state of the textbox (if the user is typing or not)
		inline fgui::state get_state() const noexcept {

			return m_is_getting_key;
		}

		// set the text flag (type)
		void set_text_flag(const fgui::text_flags &flags) noexcept {

			m_text_flag |= static_cast<int>(flags);
		}

		// get text flags
		inline bool get_text_flag(const fgui::text_flags &flags) const noexcept {

			if (m_text_flag & static_cast<int>(flags))
				return true;

			return false;
		}

		// set the max text length
		inline void set_length(const int &text_length) noexcept {
			
			m_text_length = text_length;
		}

		// get the current text typed on the textbox
		inline std::string get_text() const noexcept {

			return m_text;
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

		int m_text_flag;
		std::string::size_type m_text_length;
		std::string m_text;
		int m_holding_ticks;
		std::string::size_type m_text_input_pos;
		bool m_text_selected;
		fgui::state m_is_getting_key;
	};
}