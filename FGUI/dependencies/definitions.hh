/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

namespace fgui {

	// handlers
	typedef int key;
	typedef bool state;
	typedef unsigned long font;

	enum key_code {
		KEY_0 = 0x1,
		KEY_1 = 0x2,
		KEY_2 = 0x3,
		KEY_3 = 0x4,
		KEY_4 = 0x5,
		KEY_5 = 0x6,
		KEY_6 = 0x7,
		KEY_7 = 0x8,
		KEY_8 = 0x9,
		KEY_9 = 0xA,
		KEY_A = 0xB,
		KEY_B = 0xC,
		KEY_C = 0xD,
		KEY_D = 0xE,
		KEY_E = 0xF,
		KEY_F = 0x10,
		KEY_G = 0x11,
		KEY_H = 0x12,
		KEY_I = 0x13,
		KEY_J = 0x14,
		KEY_K = 0x15,
		KEY_L = 0x16,
		KEY_M = 0x17,
		KEY_N = 0x18,
		KEY_O = 0x19,
		KEY_P = 0x1A,
		KEY_Q = 0x1B,
		KEY_R = 0x1C,
		KEY_S = 0x1D,
		KEY_T = 0x1E,
		KEY_U = 0x1F,
		KEY_V = 0x20,
		KEY_W = 0x21,
		KEY_X = 0x22,
		KEY_Y = 0x23,
		KEY_Z = 0x24,
		KEY_PAD_0 = 0x25,
		KEY_PAD_1 = 0x26,
		KEY_PAD_2 = 0x27,
		KEY_PAD_3 = 0x28,
		KEY_PAD_4 = 0x29,
		KEY_PAD_5 = 0x2A,
		KEY_PAD_6 = 0x2B,
		KEY_PAD_7 = 0x2C,
		KEY_PAD_8 = 0x2D,
		KEY_PAD_9 = 0x2E,
		KEY_PAD_DIVIDE = 0x2F,
		KEY_PAD_MULTIPLY = 0x30,
		KEY_PAD_MINUS = 0x31,
		KEY_PAD_PLUS = 0x32,
		KEY_PAD_ENTER = 0x33,
		KEY_PAD_DECIMAL = 0x34,
		KEY_LBRACKET = 0x35,
		KEY_RBRACKET = 0x36,
		KEY_SEMICOLON = 0x37,
		KEY_APOSTROPHE = 0x38,
		KEY_BACKQUOTE = 0x39,
		KEY_COMMA = 0x3A,
		KEY_PERIOD = 0x3B,
		KEY_SLASH = 0x3C,
		KEY_BACKSLASH = 0x3D,
		KEY_MINUS = 0x3E,
		KEY_EQUAL = 0x3F,
		KEY_ENTER = 0x40,
		KEY_SPACE = 0x41,
		KEY_BACKSPACE = 0x42,
		KEY_TAB = 0x43,
		KEY_CAPSLOCK = 0x44,
		KEY_NUMLOCK = 0x45,
		KEY_ESCAPE = 0x46,
		KEY_SCROLLLOCK = 0x47,
		KEY_INSERT = 0x48,
		KEY_DELETE = 0x49,
		KEY_HOME = 0x4A,
		KEY_END = 0x4B,
		KEY_PAGEUP = 0x4C,
		KEY_PAGEDOWN = 0x4D,
		KEY_BREAK = 0x4E,
		KEY_LSHIFT = 0x4F,
		KEY_RSHIFT = 0x50,
		KEY_LALT = 0x51,
		KEY_RALT = 0x52,
		KEY_LCONTROL = 0x53,
		KEY_RCONTROL = 0x54,
		KEY_LWIN = 0x55,
		KEY_RWIN = 0x56,
		KEY_APP = 0x57,
		KEY_UP = 0x58,
		KEY_LEFT = 0x59,
		KEY_DOWN = 0x5A,
		KEY_RIGHT = 0x5B,
		KEY_F1 = 0x5C,
		KEY_F2 = 0x5D,
		KEY_F3 = 0x5E,
		KEY_F4 = 0x5F,
		KEY_F5 = 0x60,
		KEY_F6 = 0x61,
		KEY_F7 = 0x62,
		KEY_F8 = 0x63,
		KEY_F9 = 0x64,
		KEY_F10 = 0x65,
		KEY_F11 = 0x66,
		KEY_F12 = 0x67,
		KEY_CAPSLOCKTOGGLE = 0x68,
		KEY_NUMLOCKTOGGLE = 0x69,
		KEY_SCROLLLOCKTOGGLE = 0x6A,
		MOUSE_LEFT = 0x6B,
		MOUSE_RIGHT = 0x6C,
		MOUSE_MIDDLE = 0x6D,
		MOUSE_4 = 0x6E,
		MOUSE_5 = 0x6F,
	};

	enum gradient_type {
		VERTICAL = 1,
		HORIZONTAL
	};

	enum cursor_type {
		ARROW = 1,
		IBEAM,
		HAND,
		PIPETTE,
		RESIZE,
		MOVE
	};

	enum input_state {
		LOCKED = 1,
		UNLOCKED,
	};

	// this will only work if you're using ISurface (Source Engine)
	enum font_flags {
		ITALIC = 0x001,
		UNDERLINE = 0x002,
		STRIKEOUT = 0x004,
		SYMBOL = 0x008,
		ANTIALIAS = 0x010,
		GAUSSIANBLUR = 0x020,
		ROTARY = 0x040,
		SHADOW = 0x080,
		ADDITIVE = 0x100,
		OUTLINE = 0x200,
		CUSTOM = 0x400,
		BITMAP = 0x800,
	};

	enum label_type {
		TEXT = 1,
		LINK,
		BANNER,
		SEPARATOR,
		COLORED_TEXT,
	};

	enum text_flags {
		SECRET = (1 << 0),
		UPPERCASE = (1 << 1),
		NORMAL = (1 << 2)
	};

	enum key_status {
		KEY_INVALID = -1,
		KEY_FIRST = 0,
		KEY_MAX = 256
	};

	enum element_family {
		BUTTON_FAMILY = 1,
		CHECKBOX_FAMILY,
		COLORPICKER_FAMILY,
		COMBOBOX_FAMILY,
		KEYBINDER_FAMILY,
		LABEL_FAMILY,
		LISTBOX_FAMILY,
		MULTIBOX_FAMILY,
		SLIDER_FAMILY,
		TEXTBOX_FAMILY,
		COLORLIST_FAMILY,
		CONTAINER_FAMILY,
		TAB_FAMILY,
		SPINNER_FAMILY
	};

	enum element_flag {
		DRAWABLE = (1 << 0),
		CLICKABLE = (1 << 1),
		FOCUSABLE = (1 << 2),
		SAVABLE = (1 << 3)
	};

	typedef struct rectangle {
		int left;
		int top;
		int right;
		int bottom;
	} rect;

	typedef struct dimension {
		unsigned int width;
		unsigned int height;
	} dimension;

	typedef struct point_2d {
		int x, y;

		point_2d() = default;
		point_2d(int x1, int y1) : x(x1), y(y1) {}

		// operators
		point_2d operator+(const point_2d& rhs) {
			return point_2d(x + rhs.x, y + rhs.y);
		}
		
		point_2d operator-(const point_2d& rhs) {
			return point_2d(x - rhs.x, y - rhs.y);
		}

		point_2d operator/(const int& rhs) {
			return point_2d(x / rhs, y / rhs);
		}

		point_2d operator*(const int& rhs) {
			return point_2d(x * rhs, y * rhs);
		}

		int& operator[](std::size_t index) {
			return *reinterpret_cast<int*>(this + index);
		}

	} point;

	typedef struct precision_point_2d {
		float x, y;

		precision_point_2d() = default;
		precision_point_2d(float x1, float y1) : x(x1), y(y1) {}

		precision_point_2d operator+(const point_2d& rhs) {
			return precision_point_2d(x + rhs.x, y + rhs.y);
		}
		
		precision_point_2d operator-(const point_2d& rhs) {
			return precision_point_2d(x - rhs.x, y - rhs.y);
		}

		precision_point_2d operator/(const int& rhs) {
			return precision_point_2d(x / rhs, y / rhs);
		}

		precision_point_2d operator*(const int& rhs) {
			return precision_point_2d(x * rhs, y * rhs);
		}

		float& operator[](std::size_t index) {
			return *reinterpret_cast<float*>(this + index);
		}

	} precision_point;

	struct vertex {

		fgui::precision_point position;
		fgui::precision_point text_coord;

		vertex() = default;
		vertex(const fgui::precision_point& pos, const fgui::precision_point& coord = fgui::precision_point(0, 0)) {
			position = pos; text_coord = coord;
		}
	};

	struct item_info {
		item_info() { m_item = ""; m_checked = false; };
		item_info(std::string item, int value) : m_item(item), m_value(value) {}
		item_info(std::string item, bool state) : m_item(item), m_checked(state) {}
		item_info(std::string item) : m_item(item) {}
		item_info(std::vector<std::string> items) : m_items(items) {}

		std::string m_item = "";
		bool m_checked = false;
		int m_value = 0;
		std::vector<std::string> m_items;
	};
}