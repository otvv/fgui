//
// FGUI - feature rich graphical user interface
//

// library includes
#include "textbox.hpp"

namespace FGUI
{

// ----------------------------------------------- //
CTextBox::CTextBox()
{
  m_strTitle = "TextBox";
  m_ulFont = 0;
  m_dmSize = {150, 20};
  m_strCustomText = "";
  m_iLength = 24;
  m_iInputPos = 0;
  m_bIsGettingKey = false;
  m_nType = static_cast<int>(WIDGET_TYPE::TEXTBOX);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
}

// ----------------------------------------------- //
void CTextBox::SetText(const std::string &text)
{
  m_strCustomText = text;
}

// ----------------------------------------------- //
const std::string &CTextBox::GetText()
{
  return m_strCustomText;
}

// ----------------------------------------------- //
void CTextBox::SetLength(unsigned int length)
{
  m_iLength = length;
}

// ----------------------------------------------- //
void CTextBox::Geometry()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  // widget's title text size
  const FGUI::DIMENSION &dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // textbox body
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

  // textbox label
  FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_strTitle + ":");

  // textbox current text
  FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_strCustomText);
}

// ----------------------------------------------- //
void CTextBox::Update()
{
  // if the keybinder is listening for a new key press
  if (m_bIsGettingKey)
  {
    for (std::size_t key = 0; key < 256; key++)
    {
      // don't proceed until the user press something
      if (!FGUI::INPUT.GetKeyPress(key))
      {
        continue;
      }

      // key input
      std::string strKeyInput = m_ksStrings.m_strInputSystem[key].data(); // todo: make a function to let the user select wich type of "input system" he wants to use
      //std::string strKeyInput = m_ksStrings.m_strVirtualKeyCodes[key].data();

      // if the user press ESC or ENTER stop the textbox from listening to key input
      if (key == 70 /* KEY_ESCAPE */ || key == 64 /* KEY_ENTER */ || key == 51 /* KEY_PAD_ENTER */) // todo: global keys
      {
        // block listbox
        m_bIsGettingKey = false;
      }

      // upper case handler
      if (FGUI::INPUT.GetKeyState(79 /* KEY_LSHIFT */) || FGUI::INPUT.GetKeyState(80 /* KEY_RSHIFT */))
      {
        std::transform(strKeyInput.begin(), strKeyInput.end(), strKeyInput.begin(), ::toupper);
      }

      // insert text into the textbox
      if (strKeyInput.length() == 1 && (static_cast<int>(m_strCustomText.length()) < m_iLength))
      {
        m_strCustomText.insert(m_iInputPos, strKeyInput);
        m_iInputPos++;
      }

      if (m_strCustomText.length() > 0)
      { 
        if (key == 66 /* KEY_BACKSPACE*/ && (m_iInputPos > -1))
        { 
          m_strCustomText.erase(m_iInputPos, 1);
          m_iInputPos--;

          if (m_iInputPos < 0)
          {
            m_iInputPos = 0;
          }
        }

        else if (key == 73 /* KEY_DELETE */)
        {
          // clear text
          m_strCustomText.clear();

          m_iInputPos = 0;
        }

        // change the current input position
        if (key == 89 /* KEY_LEFT */) 
        {
          m_iInputPos--;

          if (m_iInputPos < 0)
          {
            m_iInputPos = 0;
          }
        }

        else if (key == 91 /* KEY_RIGHT */ && m_iInputPos < (static_cast<int>(m_strCustomText.length())))
        {
          m_iInputPos++;
        }
      }
    }
  }
}

// ----------------------------------------------- //
void CTextBox::Input()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
  {
    m_bIsGettingKey = !m_bIsGettingKey;
  }
}

} // namespace FGUI