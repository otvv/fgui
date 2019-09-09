/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
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

	 // win api (some keys might be missing)
	constexpr std::string_view m_winapi[] = { "", "MOUSE1", "MOUSE2", "BREAK", "MOUSE3", "MOUSE4", "MOUSE5",
				"", "BACKSPACE", "TAB", "", "", "", "ENTER", "", "", "SHIFT",
				"CTRL", "ALT", "PAUSE", "CAPSLOCK", "", "", "", "", "", "",
				"", "", "", "", "", "SPACE", "PG UP", "PG DOWN", "END", "HOME", "LEFT",
				"UP", "RIGHT", "DOWN", "", "", "", "PRT SCR", "INSERT", "DELETE", "", "0", "1",
				"2", "3", "4", "5", "6", "7", "8", "9", "", "", "", "", "", "",
				"", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
				"M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y",
				"Z", "LWIN", "RWIN", "", "", "", "NUM 0", "NUM 1", "NUM 2", "NUM 3",
				"NUM 4", "NUM 5", "NUM 6", "NUM 7", "NUM 8", "NUM 9", "*", "+", "_",
				"-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9",
				"F10", "F11", "F12",  "F13", "F14", "F15", "F16", "F17", "F18", "F19",
				"F20", "F21", "F22", "F23", "F24", "", "", "", "", "", "", "", "",
				"NUM LOCK", "SCROLL LOCK", "", "", "", "", "", "", "", "", "", "",
				"", "", "", "", "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU",
				"RMENU", "", "", "", "", "", "", "", "", "", "", "NEXT TRACK", "PREVIOUS TRACK",
				"STOP", "PLAY/PAUSE", "", "", "", "", "", "", ";", "+", ",", "-", ".",
				"/?", "~", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
				"", "", "", "", "", "", "", "", "", "", "", "[{", "\\|", "}]", "'\"",
				"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
				"", "", "", "", "", "", "", "", "", "", "", ""
	};

	// input system
	constexpr std::string_view m_input_system[] = { "'", "0", "1", "2", "3", "4", "5", "6", "7",
				"8", "9", "A", "B", "C", "D", "E", "F", "G", "H",
				"I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
				"S", "T", "U", "V", "W", "X", "Y", "Z", "NUM0",
				"NUM1", "NUM2", "NUM3", "NUM4", "NUM5", "NUM6", "NUM7",
				"NUM8", "NUM9", "/", "*", "-", "+", "ENTER", ",", ".",
				"[", "Ç", "~", "´", ",", ".", ";", "]", "-", "=",
				"ENTER", "SPACE", "BACKSPACE", "TAB", "CAPSLOCK", "NUMLCK", "",
				"SCROLL LOCK", "INSERT", "DELETE", "HOME", "END", "PG UP", "PG DOWN",
				"PAUSE", "LSHIFT", "RSHIFT", "ALT", "RALT", "LCONTROL",
				"RCONTROL", "LWIN", "RWIN", "APP", "UP", "LEFT", "DOWN",
				"RIGHT", "F1", "F2", "F3", "F4", "F5", "F6", "F7",
				"F8", "F9", "F10", "F11", "F12", "", "", "",
				"MOUSE1", "MOUSE2", "MOUSE3", "MOUSE4", "MOUSE5", "", ""
	};

	class keybinder : public fgui::element {
	public:
		keybinder();

		// draw the element
		void draw();

		// get the current key
		fgui::key get_key();

		// set a custom key
		void set_key(fgui::key key);

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

		fgui::key m_key;
		bool m_is_getting_key;
		std::string m_status;
	};
}