//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_TEXTBOX_HH
#define FGUI_TEXTBOX_HH

// includes
#include <string>
#include <ctype.h>
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
    // @args: std::string text = custom default text
    void SetText(std::string text);

    // @brief: get the current text of the textbox
    std::string GetText();

    // @brief: set custom text length
    // @args: unsigned int length = text length (characters allowed)
    void SetLength(unsigned int length);

    // @brief: set the textbox style (NORMAL = normal text; UPPERCASE = all text will be on uppercase; PASSWORD = all typed text will be replaced by a '*')
    // @args: FGUI::TEXTBOX_STYLE style = textbox style (flag)
    void SetStyle(FGUI::TEXTBOX_STYLE style);

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
    std::vector<std::string> m_prgstrBackupText;
    std::string m_strCustomText;
    unsigned int m_uiInputPos;
    unsigned int m_uiLength;
    bool m_bIsGettingKey;
    bool m_bIsTextSelected;
    FGUI::KEY_STRINGS m_ksStrings;
  };

} // namespace FGUI

#endif // FGUI_TEXTBOX_HH