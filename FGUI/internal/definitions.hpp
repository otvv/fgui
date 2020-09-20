//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_DEFINITIONS_HH
#define FGUI_DEFINITIONS_HH

// includes
#include <cmath>
#include <string>
#include <stdint.h>
#include <algorithm>

namespace FGUI
{

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

  using VERTEX = struct SVertex_t
  {
    float m_flX, m_flY, m_flZ, m_flW;
    unsigned long m_ulColor;
  };

  using COLOR = struct SColor_t
  {
    SColor_t() = default;

    SColor_t(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255) : m_ucRed(red), m_ucGreen(green), m_ucBlue(blue), m_ucAlpha(alpha) {}
    SColor_t(SColor_t color, std::uint8_t alpha) : m_ucRed(color.m_ucRed), m_ucGreen(color.m_ucGreen), m_ucBlue(color.m_ucBlue), m_ucAlpha(alpha) {}

    static SColor_t Interpolate(SColor_t color1, SColor_t color2, float ttt)
    {
      float flRed = color1.m_ucRed * (1.f - ttt) + (color2.m_ucRed * ttt);
      float flGreen = color1.m_ucGreen * (1.f - ttt) + (color2.m_ucGreen * ttt);
      float flBlue = color1.m_ucBlue * (1.f - ttt) + (color2.m_ucBlue * ttt);
      float flAlpha = color1.m_ucAlpha * (1.f - ttt) + (color2.m_ucAlpha * ttt);

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

      if (flHue < 1.f)
      {
        return SColor_t((brightness * 255), (flT * 255), (flP * 255), alpha);
      }
      else if (flHue < 2.f)
      {
        return SColor_t((flQ * 255), (brightness * 255), (flP * 255), alpha);
      }
      else if (flHue < 3.f)
      {
        return SColor_t((flP * 255), (brightness * 255), (flT * 255), alpha);
      }
      else if (flHue < 4.f)
      {
        return SColor_t((flP * 255), (flQ * 255), (brightness * 255), alpha);
      }
      else if (flHue < 5.f)
      {
        return SColor_t((flT * 255), (flP * 255), (brightness * 255), alpha);
      }
      else
      {
        return SColor_t((brightness * 255), (flP * 255), (flQ * 255), alpha);
      }
    }

    static float GetHue(SColor_t color)
    {
      float flRed = (color.m_ucRed / 255.f);
      float flGreen = (color.m_ucGreen / 255.f);
      float flBlue = (color.m_ucBlue / 255.f);

      float flMax = std::fmaxf(std::fmaxf(flRed, flGreen), flBlue);
      float flMin = std::fminf(std::fminf(flRed, flGreen), flBlue);

      float flDelta = (flMax - flMin);

      if (flDelta != 0.f)
      {
        static float flHue = 0.f;

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
    int m_nFlags;
  };

  using KEY_CODES = struct SKeyCodes_t
  {
    // Valve's IInputSystem
    const std::string_view m_strInputSystem[117] = { "'", "0", "1", "2", "3", "4", "5", "6", "7",
                                                    "8", "9", "A", "B", "C", "D", "E", "F", "G", "H",
                                                    "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                                                    "S", "T", "U", "V", "W", "X", "Y", "Z", "NUM0",
                                                    "NUM1", "NUM2", "NUM3", "NUM4", "NUM5", "NUM6", "NUM7",
                                                    "NUM8", "NUM9", "/", "*", "-", "+", "NUMENTER", ",", "[",
                                                    "]", "; (Ç)", "'", "´", ",", ".", "/", "\\", "-", "=",
                                                    "ENTER", "SPACE", "BACKSPACE", "TAB", "CAPSLOCK", "NUMLOCK", "ESCAPE",
                                                    "SCROLL", "INSERT", "DELETE", "HOME", "END", "PAGEUP", "PAGEDOWN",
                                                    "PAUSE", "LSHIFT", "RSHIFT", "ALT", "RALT", "LCONTROL",
                                                    "RCONTROL", "LWIN", "RWIN", "APP", "UP", "LEFT", "DOWN",
                                                    "RIGHT", "F1", "F2", "F3", "F4", "F5", "F6", "F7",
                                                    "F8", "F9", "F10", "F11", "F12", "", "", "",
                                                    "MOUSE1", "MOUSE2", "MOUSE3", "MOUSE4", "MOUSE5", "", "" };

    // Windows Virtual Key Codes (VK)
    const std::string_view m_strVirtualKeyCodes[223] = { "INVALID", "MOUSE1", "MOUSE2", "", "MOUSE3", "MOUSE4", "MOUSE5", "",
                                                        "BACKSPACE", "TAB", "", "", "", "ENTER", "", "", "SHIFT", "CONTROL", "ALT",
                                                        "PAUSE", "CAPSLOCK", "", "", "", "", "", "", "ESC", "", "", "", "",
                                                        "SPACE", "PAGEUP", "PAGEDOWN", "END", "HOME", "LEFT", "UP", "RIGHT",
                                                        "DOWN", "", "", "", "", "INS", "DEL", "", "0", "1", "2", "3",
                                                        "4", "5", "6", "7", "8", "9", "", "", "", "", "", "", "", "A",
                                                        "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
                                                        "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "LWIN",
                                                        "RWIN", "", "", "", "NUM0", "NUM1", "NUM2", "NUM3", "NUM4", "NUM5",
                                                        "NUM6", "NUM7", "NUM8", "NUM9", "*", "+", "_", "-", ".", "/", "F1",
                                                        "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "SCROLL", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", ";", "+", ",", "-", ".", "/?", "~", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "{", "\\", "}", "/" };

    // Custom Key Codes
    const std::string_view m_strCustomKeyCodes[256] = { "MAP YOUR KEYS HERE", "MAP YOUR KEYS HERE" };
  };

  using KEY_STRINGS = struct SKeyStrings_t
  {
    // Valve's IInputSystem
    const std::string_view m_strInputSystem[117] = { "'", "0", "1", "2", "3", "4", "5", "6", "7",
                                                    "8", "9", "a", "b", "c", "d", "e", "f", "g", "h",
                                                    "i", "j", "k", "l", "m", "n", "o", "p", "q", "r",
                                                    "s", "t", "u", "v", "w", "x", "y", "z", "",
                                                    "", "", "", "", "", "", "",
                                                    "", "", "/", "*", "-", "+", "", ",", "[",
                                                    "]", "Ç", "'", "´", ",", ".", "/", "\\", "-", "=",
                                                    "", "", "", "", "", "", "",
                                                    "", "", "", "", "", "", "",
                                                    "", "", "", "", "", "",
                                                    "", "", "", "", "", "", "",
                                                    "", "", "", "", "", "", "", "",
                                                    "", "", "", "", "", "", "", "",
                                                    "", "", "", "", "", "", "" };

    // Windows Virtual Key Codes (VK)
    const std::string_view m_strVirtualKeyCodes[223] = { "INVALID", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "0", "1", "2", "3",
                                                        "4", "5", "6", "7", "8", "9", "", "", "", "", "", "", "", "a",
                                                        "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
                                                        "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "",
                                                        "", "", "", "", "0", "1", "2", "3", "4", "5",
                                                        "6", "7", "8", "9", "*", "+", "_", "-", ".", "/", "",
                                                        "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", ";", "+", ",", "-", ".", "/?", "~", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "{", "\\", "}", "/" };

    // Custom Key Codes
    const std::string_view m_strCustomKeyCodes[256] = { "MAP YOUR KEYS HERE", "MAP YOUR KEYS HERE" };
  };

  using WIDGET_TYPE = enum struct ESWidgetType_t : int {
    BUTTON = 0,
    CHECKBOX,
    COLORPICKER,
    COMBOBOX,
    CONTAINER,
    ITEMSELECTOR,
    KEYBINDER,
    LABEL,
    LISTBOX,
    MULTIBOX,
    SLIDER,
    TABPANEL,
    TEXTBOX
  };

  using WIDGET_FLAG = enum struct ESWidgetFlag_t : int {
    DRAW_FIRST = 0x1,
    DRAWABLE = 0x2,
    CLICKABLE = 0x4,
    SAVABLE = 0x8,
    FOCUSABLE = 0x10,

    FULLSCREEN = 0x20, // this is exclusively for window Containers
    LIMIT = 0x40 // this is exclusively for window Containers
  };

  using WIDGET_STATUS = enum struct ESWidgetState_t : int {
    NONE = 0,
    HOVERED

    // TODO: add more status flags
  };

} // namespace FGUI

#endif // FGUI_DEFINITIONS_HH
