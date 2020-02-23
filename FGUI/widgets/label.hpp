//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_LABEL_HH
#define FGUI_LABEL_HH

// includes
#include <string>
#include <functional>

// library includes
#include "widgets.hpp"

namespace FGUI
{

class CLabel : public FGUI::CWidgets
{
public:
  CLabel();

  // @brief: adds a function callback for the label (it will call the function whenever the user clicks on the label)
  // @params: std::function<void()> callback = function instance
  void AddCallback(const std::function<void()> &callback);

  // @brief: populate widget geometry (draw widget)
  void Geometry() override;

  // @brief: handle update operations on the widget
  void Update() override;

  // @brief: handle input inside the widget
  void Input() override;

private:
  std::function<void()> m_fnctCallback;
};

} // namespace FGUI

#endif // FGUI_LABEL_HH