//
// FGUI - feature rich graphical user interface
//

// library includes
#include "keybinder.hpp"

namespace FGUI
{

CKeyBinder::CKeyBinder()
{
  m_strTitle = "KeyBinder";
  m_ulFont = 0;
  m_dmSize = {150, 20};
  m_uiKey = 0;
  m_strStatus = "None";
  m_bIsGettingKey = false;
  m_nType = static_cast<int>(WIDGET_TYPE::KEYBINDER);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
}

void CKeyBinder::SetKey(unsigned int key_code)
{
  m_uiKey = key_code;
}

unsigned int CKeyBinder::GetKey()
{
  return m_uiKey;
}

void CKeyBinder::Geometry()
{
  // widget's area
  FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  // widget's title text size
  FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // keybinder body
  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion) || m_bIsGettingKey)
  {
    FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {195, 195, 195});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {255, 255, 235});
  }
  else
  {
    FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {220, 220, 220});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {255, 255, 255});
  }

  // keybinder label
  FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_strTitle + ":");

  // keybinder current key
  FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_strStatus);
}

void CKeyBinder::Update()
{
  if (m_bIsGettingKey)
  {
    for (std::size_t key = 0; key < 256; key++)
    { 
      // if the user has pressed a valid key
      if (FGUI::INPUT.GetKeyPress(key))
      { 
        // if the user press ESCAPE
        if (key == KEY_ESCAPE)
        { 
          // change the key to an invalid key
          m_uiKey = 0;

          // reset status
          m_strStatus = "None";

          // block keybinder
          m_bIsGettingKey = false;
        }
        else // iterate the rest of the keys
        { 
          // set key 
          m_uiKey = key;

          // change status to currently pressed key
          // m_strStatus = m_kcCodes.m_strInputSystem[key].data(); // TODO: make a function to let users select which type of "input system" they want
          m_strStatus = m_kcCodes.m_strVirtualKeyCodes[key].data();

          // block keybinder from receiving input
          m_bIsGettingKey = false;
        } 
      }
    }
  }
}

void CKeyBinder::Input()
{
  // widget's area
  FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
  {
    m_bIsGettingKey = !m_bIsGettingKey;
  }
}

} // namespace FGUI