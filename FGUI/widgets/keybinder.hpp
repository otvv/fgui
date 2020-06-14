//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_KEYBINDER_HH
#define FGUI_KEYBINDER_HH

// library includes
#include "widgets.hpp"

namespace FGUI
{

class CKeyBinder : public FGUI::CWidgets
{
public:
  CKeyBinder();

  // @brief: set a custom key for the keybinder
  // @params: unsigned int key = custom key code
  void SetKey(unsigned int key_code);

  // @brief: get the current key set on the keybinder
  unsigned int GetKey();

  // @brief: populate widget geometry (draw widget)
  void Geometry() override;

  // @brief: handle update operations on the widget
  void Update() override;

  // @brief: handle input inside the widget
  void Input() override;
private:
 unsigned int m_uiKey;
 std::string m_strStatus;
 bool m_bIsGettingKey;
 FGUI::KEY_CODES m_kcCodes;
};

} // namespace FGUI

#endif // FGUI_KEYBINDER_HH