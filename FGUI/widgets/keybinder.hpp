//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_KEYBINDER_HH
#define FGUI_KEYBINDER_HH

// library includes
#include "widgets.hpp"

namespace FGUI
{

  using KEY_BINDER_STYLE = enum struct ESKeybinderStyle_t : int
  {
    CLICK = 0,
    HOLD = 1,
    TOGGLE = 2
  };

  class CKeyBinder : public FGUI::CWidgets
  {
  public:
    CKeyBinder();

    // @brief: set a custom key for the keybinder
    // @args: unsigned int key = custom key code
    void SetKey(unsigned int key_code);

    // @brief: get the current key set on the keybinder
    bool GetKey();

    // @brief: set the keybinder input style (CLICK, HOLD, TOGGLE)
    // @args: FGUI::KEY_BINDER_STYLE style = keybinder style
    void SetStyle(FGUI::KEY_BINDER_STYLE style);

    // @brief: populate widget geometry (draw widget)
    // @args: FGUI::WIDGET_STATUS status = widget status (HOVERED, etc)
    void Geometry(FGUI::WIDGET_STATUS status) override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

    // @brief: save the widget state
    // @args: nlohmann::json module = json module
    void Save(nlohmann::json& module) override;

    // @brief: load the widget state
    // @args: nlohmann::json module = json module
    void Load(nlohmann::json& module) override;

    // @brief: handle widget tooltips
    void Tooltip() override;
    
  private:
    int m_nStyle;
    unsigned int m_uiKey;
    std::string m_strStatus;
    bool m_bIsGettingKey;
    FGUI::KEY_CODES m_kcCodes;
  };

} // namespace FGUI

#endif // FGUI_KEYBINDER_HH