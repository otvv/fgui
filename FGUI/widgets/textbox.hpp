//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_TEXTBOX_HH
#define FGUI_TEXTBOX_HH

// includes
#include <string>
#include <algorithm>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  using TEXTBOX_STYLE = enum struct ESTextBox_Style : int {
    NORMAL = 1,
    UPPERCASE,
    PASSWORD
  };

  class CTextBox : public FGUI::CWidgets
  {
  public:
    CTextBox();

    // @brief: set a custom text for the textbox
    // @params: std::string text = custom default text
    void SetText(std::string text);

    // @brief: get the current text of the textbox
    std::string GetText();

    // @brief: set custom text length
    // @params: unsigned int length = text length (characters allowed)
    void SetLength(unsigned int length);

    // @brief: set the textbox style (NORMAL = normal text; UPPERCASE = all text will be on uppercase; PASSWORD = all typed text will be replaced by a '*')
    // @params: FGUI::TEXTBOX_STYLE style = textbox style (flag)
    void SetStyle(FGUI::TEXTBOX_STYLE style);

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
    std::string m_strCustomText;
    unsigned int m_uiInputPos;
    unsigned int m_uiLength;
    bool m_bIsGettingKey;
    bool m_bIsTextSelected;
    FGUI::KEY_STRINGS m_ksStrings;
  };

} // namespace FGUI

#endif // FGUI_TEXTBOX_HH
