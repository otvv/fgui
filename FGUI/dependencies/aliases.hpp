//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_ALIASES_HH
#define FGUI_ALIASES_HH

// includes
#include <functional>

// library includes
#include "definitions.hpp"

namespace FGUI
{

namespace DETAIL
{

// drawing functions pointers
using pCreateFont = std::add_pointer_t<void(FGUI::FONT &, const std::string &, int, int, bool)>;
using pGetScreenSize = std::add_pointer_t<const FGUI::DIMENSION &()>;
using pGetTextSize = std::add_pointer_t<const FGUI::DIMENSION &(const FGUI::FONT &, const std::string &)>;
using pDrawRectangle = std::add_pointer_t<void(int, int, int, int, const FGUI::COLOR &)>;
using pDrawOutline = std::add_pointer_t<void(int, int, int, int, const FGUI::COLOR &)>;
using pDrawGradient = std::add_pointer_t<void(int, int, int, int, std::size_t, std::size_t, const FGUI::COLOR &, bool)>;
using pDrawLine = std::add_pointer_t<void(int, int, int, int, const FGUI::COLOR &)>;
using pDrawText = std::add_pointer_t<void(int, int, const FGUI::FONT &, const FGUI::COLOR &, const std::string &)>;

// input functions pointers
using pPullInput = std::add_pointer_t<void()>;
using pGetKeyState = std::add_pointer_t<bool(int)>;
using pGetKeyPress = std::add_pointer_t<bool(int)>;
using pGetKeyRelease = std::add_pointer_t<bool(int)>;
using pGetCursorPos = std::add_pointer_t<const FGUI::POINT &()>;
using pGetCursorPosDelta = std::add_pointer_t<const FGUI::POINT &()>;
using pGetCursorWheelDelta = std::add_pointer_t<int()>;
using pIsCursorInArea = std::add_pointer_t<bool(const FGUI::AREA &)>;

} // namespace DETAIL

using RENDER_MANAGER = struct SRenderManager_t
{
  DETAIL::pCreateFont CreateFont;
  DETAIL::pGetScreenSize GetScreenSize;
  DETAIL::pGetTextSize GetTextSize;
  DETAIL::pDrawRectangle Rectangle;
  DETAIL::pDrawOutline Outline;
  DETAIL::pDrawGradient Gradient;
  DETAIL::pDrawLine Line;
  DETAIL::pDrawText Text;
};

using INPUT_SYTEM = struct SInputSystem_t
{
  DETAIL::pPullInput PullInput;
  DETAIL::pGetKeyState GetKeyState;
  DETAIL::pGetKeyRelease GetKeyRelease;
  DETAIL::pGetKeyPress GetKeyPress;
  DETAIL::pGetCursorPos GetCursorPos;
  DETAIL::pGetCursorPosDelta GetCursorPosDelta;
  DETAIL::pGetCursorWheelDelta GetCursorWheelDelta;
  DETAIL::pIsCursorInArea IsCursorInArea;
};

// declarations
inline RENDER_MANAGER RENDER;
inline INPUT_SYTEM INPUT;

} // namespace FGUI

#endif // FGUI_ALIASES_HH