//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_DEFINITIONS_HH
#define FGUI_DEFINITIONS_HH

// includes
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif
#include <cmath>
#include <string>
#include <stdint.h>
#include <algorithm>

namespace FGUI
{

using FONT = unsigned long;

using POINT = struct SPoint_t
{
  int m_iX, m_iY;
};

using PRECISION = struct SPrecisionPoint_t
{
  float m_flX, m_flY;
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

  static SColor_t Interpolate(const SColor_t &color1, const SColor_t &color2, float ttt)
  {
    float flRed = (std::clamp<int>(color1.m_ucRed, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_ucRed, 0, 255) * ttt);
    float flGreen = (std::clamp<int>(color1.m_ucGreen, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_ucGreen, 0, 255) * ttt);
    float flBlue = (std::clamp<int>(color1.m_ucBlue, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_ucBlue, 0, 255) * ttt);
    float flAlpha = (std::clamp<int>(color1.m_ucAlpha, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_ucAlpha, 0, 255) * ttt);

    return SColor_t(flRed, flGreen, flBlue, flAlpha);
  }

  static SColor_t HSBToRGB(float hue, float saturation, float brightness, std::uint8_t alpha = 255)
  {
    hue = std::clamp(hue, 0.f, 1.f);
    saturation = std::clamp(saturation, 0.f, 1.f);
    brightness = std::clamp(brightness, 0.f, 1.f);

    float flHue = (hue == 1.f) ? 0.f : (hue * 6.f);
    float flF = flHue - static_cast<int>(flHue);
    float flP = brightness * (1.f - saturation);
    float flQ = brightness * (1.f - saturation * flF);
    float flT = brightness * (1.f - (saturation * (1.f - flF)));

    if (flHue < 1)
    {
      return SColor_t((brightness * 255), (flT * 255), (flP * 255), alpha);
    }
    else if (flHue < 2)
    {
      return SColor_t((flQ * 255), (brightness * 255), (flP * 255), alpha);
    }
    else if (flHue < 3)
    {
      return SColor_t((flP * 255), (brightness * 255), (flT * 255), alpha);
    }
    else if (flHue < 4)
    {
      return SColor_t((flP * 255), (flQ * 255), (brightness * 255), alpha);
    }
    else if (flHue < 5)
    {
      return SColor_t((flT * 255), (flP * 255), (brightness * 255), alpha);
    }
    else
    {
      return SColor_t((brightness * 255), (flP * 255), (flQ * 255), alpha);
    }
  }

  static float GetHue(const SColor_t &color)
  {
    float flRed = (std::clamp<int>(color.m_ucRed, 0, 255) / 255.f);
    float flGreen = (std::clamp<int>(color.m_ucGreen, 0, 255) / 255.f);
    float flBlue = (std::clamp<int>(color.m_ucBlue, 0, 255) / 255.f);

    float flMax = std::fmaxf(std::max(flRed, flGreen), flBlue);
    float flMin = std::fminf(std::min(flRed, flGreen), flBlue);
    float flDelta = (flMax - flMin);

    if (flDelta != 0.f)
    {
      float flHue = 0.f;

      if (flRed == flMax)
      {
        flHue = (flGreen - flBlue) / flDelta;
      }

      else
      {
        if (flGreen == flMax)
        {
          flHue = 2.f + (flBlue - flRed) / flDelta;
        }
        else
        {
          flHue = 4.f + (flRed - flGreen) / flDelta;
        }
      }

      flHue *= 60.f;

      if (flHue < 0.f)
      {
        flHue += 360.f;
      }

      return (flHue / 360.f);
    }

    else
    {
      return 0.f;
    }
  }

  std::uint8_t m_ucRed, m_ucGreen, m_ucBlue, m_ucAlpha;
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
  TEXTBOX,
  COLORLIST,
  COLORPICKER
};

using WIDGET_FLAG = enum struct ESWidgetFlag_t : int {
  DRAWABLE = 0x1,
  CLICKABLE = 0x2,
  FOCUSABLE = 0x4,
};

} // namespace FGUI

#endif // FGUI_DEFINITIONS_HH