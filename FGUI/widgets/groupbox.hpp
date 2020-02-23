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
  void AddWidget(const std::shared_ptr<FGUI::CWidgets> &widget, const std::shared_ptr<FGUI::CTabs> &tab, bool padding = true);

  // @brief: populate widget geometry (draw widget)
  void Geometry() override;

  // @brief: handle update operations on the widget
  void Update() override;

  // @brief: handle input inside the widget
  void Input() override;
};
} // namespace FGUI

#endif // FGUI_GROUPBOX_HH