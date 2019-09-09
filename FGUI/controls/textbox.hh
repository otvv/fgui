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

	// input system
	constexpr std::string_view m_input_system_text[] = { "'", "0", "1", "2", "3", "4", "5", "6", "7",
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

	class textbox : public fgui::element {
	public:
		textbox();

		// draw the element
		void draw();

		// get the state of the textbox (if the user is typing or not)
		bool get_state();

		// set a custom text
		void set_text(std::string text);

		// set the max text length
		void set_length(int length);

		// get the current typed text
		std::string get_text();

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

		std::string m_text;
		int m_text_input_pos;
		int m_text_length;
		bool m_is_getting_key;
		bool m_text_selected;
	};
}