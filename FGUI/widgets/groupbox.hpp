//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_GROUPBOX_HH
#define FGUI_GROUPBOX_HH

// includes
#include <memory>

// library includes
#include "widgets.hpp"

namespace FGUI
{

class CTabs;

class CGroupBox : public FGUI::CWidgets
{
public:
  CGroupBox();

  // @brief: add a new widget inside the groupbox
  // @params: std::shared_ptr<FGUI::CWidgets> widget = widget
  // std::shared_ptr<FGUI::CTabs> tab = tab that the widget will be added
  // bool padding = enable/disable padding
  void AddWidget(std::shared_ptr<FGUI::CWidgets> widget, std::shared_ptr<FGUI::CTabs> tab, bool padding = true);

  // @brief: enables/disabled groupbox scrollbar
  // @params: bool state = scrollbar state (on/off)
  void SetScrollbarState(bool state);

  // @brief: gets the state of the scrollbar, if it's enabled or not
  bool GetScrollbarState();

  // @brief: get the scrolling offset
  int GetScrollOffset();

  // @brief: populate widget geometry (draw widget)
  void Geometry() override;

  // @brief: handle update operations on the widget
  void Update() override;

  // @brief: handle input inside the widget
  void Input() override;

private:
  int m_iWidgetPositionOffset;
  bool m_bScrollBarState;
  std::vector<std::shared_ptr<FGUI::CWidgets>> m_prgpGroupBoxWidgets;
};
} // namespace FGUI

#endif // FGUI_GROUPBOX_HH