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

  using LABEL_STYLE = enum struct ESLabelStyle_t : int {
    NORMAL = 1,
    COLORED,
    LINK,
    SEPARATOR
  };

  class CLabel : public FGUI::CWidgets
  {
  public:
    CLabel();

    // @brief: adds a function callback for the label (it will call the function whenever the user clicks on the label)
    // @params: std::function<void()> callback = function instance
    void AddCallback(std::function<void()> callback);

    // @brief: set the label style (NORMAL = it will draw a normal label; COLORED = it will draw a colored label; LINK = it will draw a clickable label)
    // @params: FGUI::LABEL_STYLE style = label style (type)
    void SetStyle(FGUI::LABEL_STYLE style);

    // @brief: set the label color (it only works for colored label type)
    // @params: FGUI::COLOR color = label custom color
    void SetColor(FGUI::COLOR color);

    // @brief: return the current color of the label
    FGUI::COLOR GetColor();

    // @brief: returns the current style of the label
    int GetStyle();

    // @brief: populate widget geometry (draw widget)
    void Geometry() override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

    // @brief: save the widget state
    // @params: nlohmann::json module = json module
    void Save(nlohmann::json& module) override;

    // @brief: load the widget state
    // @params: nlohmann::json module = json module
    void Load(nlohmann::json& module) override;

    // @brief: handle widget tooltips
    void Tooltip() override;

  private:
    int m_nStyle;
    FGUI::COLOR m_clrLabel;
    std::function<void()> m_fnctCallback;
  };

} // namespace FGUI

#endif // FGUI_LABEL_HH