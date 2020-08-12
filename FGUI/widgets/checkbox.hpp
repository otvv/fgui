//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_CHECKBOX_HH
#define FGUI_CHECKBOX_HH

// includes
#include <functional>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CCheckBox : public FGUI::CWidgets
  {
  public:
    CCheckBox();

    // @brief: set the checkbox state (toggle on/off)
    // @params: bool onoff = checkbox state
    void SetState(bool onoff);

    // @brief: get the checkbox state (toggled or not)
    bool GetState();

    // @brief: adds a function callback for the checkbox (it will call the function whenever the user check the checkbox)
    // @params: std::function<void()> callback = function instance
    void AddCallback(std::function<void()> callback);

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
    bool m_bIsChecked;
    std::function<void()> m_fnctCallback;
  };
} // namespace FGUI

#endif // FGUI_CHECKBOX_HH