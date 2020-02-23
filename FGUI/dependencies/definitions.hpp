//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_DEFINITIONS_HH
#define FGUI_DEFINITIONS_HH

// includes
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif
#include <string>
#include <stdint.h>

namespace FGUI
{

using FONT = unsigned long;

using POINT = struct SPoint_t
{
  int m_iX, m_iY;
};

using DIMENSION = struct SDimension_t
{
  int m_iWidth, m_iHeight;
};

using AREA = struct SArea_t
{
  int m_iLeft, m_iTop, m_iRight, m_iBottom;
};

using RANGE = struct SRange_t
{
  float m_flMin, m_flMax;
};

using COLOR = struct SColor_t
{
  SColor_t() = default;

  constexpr SColor_t(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255) : m_ucRed(red), m_ucGreen(green), m_ucBlue(blue), m_ucAlpha(alpha) {}
  constexpr SColor_t(const SColor_t &color, std::uint8_t alpha) : m_ucRed(color.m_ucRed), m_ucGreen(color.m_ucGreen), m_ucBlue(color.m_ucBlue), m_ucAlpha(alpha) {}

  unsigned char m_ucRed, m_ucGreen, m_ucBlue, m_ucAlpha;
};

using WIDGET_FONT = struct SWidgetFont_t
{
  std::string m_strFamily;
  int m_iSize;
  bool m_bBold;
  int m_iFlags;
};

using KEY_CODES = struct SKeyCodes_t
{ 
  // Valve's IInputSystem
  const std::string_view m_strInputSystem[117] = {"'", "0", "1", "2", "3", "4", "5", "6", "7",
                                          "8", "9", "A", "B", "C", "D", "E", "F", "G", "H",
                                          "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                                          "S", "T", "U", "V", "W", "X", "Y", "Z", "NUM0",
                                          "NUM1", "NUM2", "NUM3", "NUM4", "NUM5", "NUM6", "NUM7",
                                          "NUM8", "NUM9", "/", "*", "-", "+", "NUMENTER", ",", "[",
                                          "]", "Ç", "'", "´", ",", ".", "/", "\\", "-", "=",
                                          "ENTER", "SPACE", "BACKSPACE", "TAB", "CAPSLOCK", "NUMLCK", "ESCAPE",
                                          "SCRLK", "INSERT", "DELETE", "HOME", "END", "PAGE UP", "PAGE DOWN",
                                          "PAUSE", "LSHIFT", "RSHIFT", "ALT", "RALT", "LCONTROL",
                                          "RCONTROL", "LWIN", "RWIN", "APP", "UP", "LEFT", "DOWN",
                                          "RIGHT", "F1", "F2", "F3", "F4", "F5", "F6", "F7",
                                          "F8", "F9", "F10", "F11", "F12", "", "", "",
                                          "MOUSE1", "MOUSE2", "MOUSE3", "MOUSE4", "MOUSE5", "", ""};

  // Windows Virtual Key Codes (VK)
  const std::string_view m_strVirtualKeyCodes[222] = {"MOUSE1", "MOUSE2", "", "MOUSE3", "MOUSE4", "MOUSE5", "", 
                                    "BACKSPACE", "TAB", "", "", "", "ENTER", "", "", "SHIFT", "CONTROL", "ALT", 
                                    "PAUSE", "CAPSLOCK", "", "", "", "", "", "", "ESC", "", "", "", "",
                                    "SPACE", "PAGE UP", "PAGE DOWN", "END", "HOME", "LEFT", "UP", "RIGHT",
                                    "DOWN", "", "", "", "", "INS", "DEL", "", "0", "1", "2", "3",
                                    "4", "5", "6", "7", "8", "9", "", "", "", "", "", "", "", "A",
                                    "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
                                    "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "LWIN",
                                    "RWIN", "", "", "", "NUM0", "NUM1", "NUM2", "NUM3", "NUM4", "NUM5",
                                    "NUM6", "NUM7", "NUM8", "NUM9", "*", "+", "_", "-", ".", "/", "F1",
                                    "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                                    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "SCROLL LOCK", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "", "",
                                    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", ";", "+", ",", "-", ".", "/?", "~", "", "", "", "", "",
                                    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "{", "\\", "}", "/"};
};

using KEY_STRINGS = struct SKeyStrings_t
{
    // Valve's IInputSystem
  const std::string_view m_strInputSystem[117] = {"'", "0", "1", "2", "3", "4", "5", "6", "7",
                                          "8", "9", "a", "b", "c", "d", "e", "f", "g", "h",
                                          "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                          "s", "t", "u", "v", "w", "x", "y", "z", "",
                                          "", "", "", "", "", "", "",
                                          "", "", "/", "*", "-", "+", "", ",", "[",
                                          "]", "Ç", "'", "´", ",", ".", "/", "\\", "-", "=",
                                          "", " ", "", "", "", "", "",
                                          "", "", "", "", "", "", "",
                                          "", "", "", "", "", "",
                                          "", "", "", "", "", "", "",
                                          "", "", "", "", "", "", "", "",
                                          "", "", "", "", "", "", "", "",
                                          "", "", "", "", "", "", ""};

  // Windows Virtual Key Codes (VK)
  const std::string_view m_strVirtualKeyCodes[222] = {"", "", "", "", "", "", "", 
                                    "", "", "", "", "", "", "", "", "", "", "", 
                                    "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    " ", "", "", "", "", "", "", "",
                                    "", "", "", "", "", "", "", "", "0", "1", "2", "3",
                                    "4", "5", "6", "7", "8", "9", "", "", "", "", "", "", "", "A",
                                    "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
                                    "q", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "",
                                    "", "", "", "", "0", "1", "2", "3", "4", "5",
                                    "6", "7", "8", "9", "*", "+", "_", "-", ".", "/", "",
                                    "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", ";", "+", ",", "-", ".", "/?", "~", "", "", "", "", "",
                                    "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "", "", "", "", "{", "\\", "}", "/"};
};

using WIDGET_TYPE = enum struct ESWidgetType_t : int {
  BUTTON = 0,
  CHECKBOX,
  GROUPBOX,
  MULTIBOX,
  SLIDER,
  KEYBINDER,
  LISTBOX,
  LABEL,
  TEXTBOX
};

using WIDGET_FLAG = enum struct ESWidgetFlag_t : int {
  DRAWABLE = 0x1,
  CLICKABLE = 0x2,
  FOCUSABLE = 0x4,
  DRAW_FIRST = 0x8,
};

} // namespace FGUI

#endif // FGUI_DEFINITIONS_HH