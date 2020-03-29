//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_COLORLIST_HH
#define FGUI_COLORLIST_HH

// includes
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

// library includes
#include "widgets.hpp"

namespace FGUI
{

class CSlider;
class CButton;
class CCheckBox;

using COLOR_INFO = struct SColorInfo_t
{
  SColorInfo_t(const std::string &identificator, const FGUI::COLOR& color, bool gradient);

  std::string m_strIdentificator;
  FGUI::COLOR m_clrFirst;
  FGUI::COLOR m_clrSecond;
  bool m_bGradient;
  bool m_bIsSecondColorAdded;
};

class CColorList : public FGUI::CWidgets
{
public:
  CColorList();

  // @brief: adds a new color into the list
  // @params: std::string identificator = color identificator (label), FGUI::COLOR color = color, bool gradient = interpolation state (true by default or not)
  void AddColor(const std::string &identificator, const FGUI::COLOR &color, bool gradient = false);

  // @brief: set a custom color and the gradient state of an entry on the list
  // @params: std::size_t index = entry index, FGUI::COLOR color = color, bool gradient = gradient state (defaults to false)
  void SetColor(std::size_t index, const FGUI::COLOR &color, bool gradient = false);

  // @brief: returns the current color from a entry on the list
  // @params: std::size_t index = entry index (defaults to 0)
  const FGUI::COLOR GetColor(std::size_t index = 0);

  // @brief: get color info
  const std::vector<FGUI::COLOR_INFO> &GetColorInfo();

  // @brief: populate widget geometry (draw widget)
  void Geometry() override;

  // @brief: handle update operations on the widget
  void Update() override;

  // @brief: handle input inside the widget
  void Input() override;

private:
  std::size_t m_uiSelectedEntry;
  int m_iEntrySpacing;
  bool m_bIsDragging;
  int m_iScrollThumbPosition;
  std::vector<FGUI::COLOR_INFO> m_prgpColorInfo;
};

} // namespace FGUI

#endif // FGUI_COLORLIST_hH