//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_ALIASES_HH
#define FGUI_ALIASES_HH

// includes
#include <functional>

// library includes
#include "definitions.hpp"
#include "helpers.hpp"

namespace FGUI
{
  namespace DETAIL
  {
    // drawing functions pointers
    using pCreateFont = std::add_pointer_t<void(FGUI::FONT &, std::string, int, int, bool)>;
    using pGetScreenSize = std::add_pointer_t<FGUI::DIMENSION()>;
    using pGetTextSize = std::add_pointer_t<FGUI::DIMENSION(FGUI::FONT, std::string)>;
    using pDrawRectangle = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR)>;
    using pDrawOutline = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR)>;
    using pDrawGradient = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR, FGUI::COLOR, bool)>;
    using pDrawLine = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR)>;
    using pDrawText = std::add_pointer_t<void(int, int, FGUI::FONT, FGUI::COLOR, std::string)>;

    // input functions pointers
    using pPullInput = std::add_pointer_t<void()>;
    using pIsKeyHeld = std::add_pointer_t<bool(unsigned int)>;
    using pIsKeyReleased = std::add_pointer_t<bool(unsigned int)>;
    using pIsKeyPressed = std::add_pointer_t<bool(unsigned int)>;
    using pGetCursorPos = std::add_pointer_t<FGUI::POINT()>;
    using pGetCursorPosDelta = std::add_pointer_t<FGUI::POINT()>;
    using pGetCursorWheelDelta = std::add_pointer_t<int()>;
    using pIsCursorInArea = std::add_pointer_t<bool(FGUI::AREA)>;

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
    DETAIL::pIsKeyHeld IsKeyHeld;
    DETAIL::pIsKeyReleased IsKeyReleased;
    DETAIL::pIsKeyPressed IsKeyPressed;
    DETAIL::pGetCursorPos GetCursorPos;
    DETAIL::pGetCursorPosDelta GetCursorPosDelta;
    DETAIL::pGetCursorWheelDelta GetCursorWheelDelta;
    DETAIL::pIsCursorInArea IsCursorInArea;
  };

  inline RENDER_MANAGER RENDER;
  inline INPUT_SYTEM INPUT;

} // namespace FGUI

#endif // FGUI_ALIASES_HH