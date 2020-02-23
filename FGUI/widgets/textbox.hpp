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

class CTextBox : public FGUI::CWidgets
{
public:
  CTextBox();

  // @brief: set a custom text for the textbox
  // @params: std::string text = custom default text
  void SetText(const std::string &text);

  // @brief: get the current text of the textbox
  const std::string& GetText();

  // @brief: set custom text length
  // @params: unsigned int length = text length (characters allowed)
  void SetLength(unsigned int length);

  // @brief: populate widget geometry (draw widget)
  void Geometry() override;

  // @brief: handle update operations on the widget
  void Update() override;

  // @brief: handle input inside the widget
  void Input() override;
private:
 std::string m_strCustomText;
 int m_iLength;
 int m_iInputPos;
 bool m_bIsGettingKey;
 FGUI::KEY_STRINGS m_ksStrings;
};

} // namespace FGUI

#endif // FGUI_TEXTBOX_HH