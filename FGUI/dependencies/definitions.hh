/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

// includes
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace fgui {

	// handlers
	typedef int key;
	typedef int delta;
	typedef bool state;
	typedef unsigned long font;

	// you are not supposed to edit the contents of this namespace. but if you know what you are doing, go ahead.  
	namespace detail {

		enum struct  element_type : int {
			BUTTON = 1,
			CHECKBOX,
			COLORPICKER,
			COMBOBOX,
			KEYBINDER,
			LABEL,
			LISTBOX,
			MULTIBOX,
			SLIDER,
			TEXTBOX,
			COLORLIST,
			CONTAINER,
			TAB,
			SPINNER
		};

		enum struct element_flags : int {
			DRAWABLE = (1 << 0),
			CLICKABLE = (1 << 1),
			FOCUSABLE = (1 << 2),
			SAVABLE = (1 << 3)
		};

		struct item_info {

			item_info() { item = ""; checked = false; value = 0; };
			item_info(const std::string_view _item, int _value) : value(_value), item(_item) {}
			item_info(const std::string_view _item, bool _state) : checked(_state), item(_item) {}
			item_info(const std::string_view _item) : item(_item) {}

			int value = 0;
			bool checked = false;
			std::string item = "";
		};
	}
	
	// everything inside this namespace usually depends of an external library to work.
	namespace external {

		// this will only work if you are using IInputSystem (Source Engine)
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
	}

	// public enums 
	enum struct cursor_type : int {
		NONE = 0,
		ARROW,
		IBEAM,
		HAND,
		PIPETTE,
		RESIZE,
		MOVE
	};

	enum struct input_state : int {
		LOCKED = 1,
		UNLOCKED,
	};

	enum struct label_type : int {
		TEXT = 1,
		LINK,
		BANNER,
		SEPARATOR,
		COLORED,
	};

	enum struct text_flags : int {
		SECRET = (1 << 0),
		UPPERCASE = (1 << 1),
		NORMAL = (1 << 2)
	};

   	enum struct animation_type : int {
        LINEAR = 1,
        FADE
    };

	enum struct tab_layout : int {
		HORIZONTAL = 1,
		VERTICAL = 2
	};

	// public structs
	typedef struct element_area {
		int left;
		int top;
		int right;
		int bottom;
	} rect;

	typedef struct element_dimension {
		int width;
		int height;
	} dimension;

	typedef struct point_2d {
		int x = 0;
		int y = 0;

		point_2d() = default;
		point_2d(int _x, int _y) : x(_x), y(_y) {}

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
		float x = 0.f;
		float y = 0.f;

		precision_point_2d() = default;
		precision_point_2d(float _x, float _y) : x(_x), y(_y) {}

		// operators
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

	typedef struct vertex_2d {

		fgui::precision_point position = { 0.f, 0.f };
		fgui::precision_point text_coord = { 0.f, 0.f };

		vertex_2d() = default;
		vertex_2d(const fgui::precision_point& _position, const fgui::precision_point& _text_coord = { 0.f, 0.f }) : position(_position), text_coord(_text_coord) {}

	} vertex;

	typedef struct element_font_info {
		std::string_view family;
		int size;
		int flags;
		bool bold;
	} element_font;
}