//
// FGUI - feature rich graphical user interface
//

// library includes
#include "textbox.hpp"

namespace FGUI
{

  CTextBox::CTextBox()
  {
    m_strTitle = "TextBox";
    m_dmSize = {150, 20};
    m_bIsGettingKey = false;
    m_strCustomText = "Sample Text";
    m_uiLength = 24;
    m_anyFont = 0;
    m_strTooltip = "";
    m_nStyle = static_cast<int>(TEXTBOX_STYLE::NORMAL);
    m_nType = static_cast<int>(WIDGET_TYPE::TEXTBOX);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CTextBox::SetText(std::string text)
  {
    m_strCustomText = text;
  }

  std::string CTextBox::GetText()
  {
    return m_strCustomText;
  }

  void CTextBox::SetLength(unsigned int length)
  {
    m_uiLength = length;
  }

  void CTextBox::SetStyle(FGUI::TEXTBOX_STYLE style)
  {
    m_nStyle = static_cast<int>(style);
  }

  void CTextBox::Geometry()
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

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
    FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_strTitle + ":");

    // textbox current text
    if (m_nStyle == static_cast<int>(FGUI::TEXTBOX_STYLE::NORMAL))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_strCustomText);
    }
    else if (m_nStyle == static_cast<int>(FGUI::TEXTBOX_STYLE::UPPERCASE))
    {
      std::transform(m_strCustomText.begin(), m_strCustomText.end(),m_strCustomText.begin(), ::toupper);

      FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_strCustomText);
    }
    else if (m_nStyle == static_cast<int>(FGUI::TEXTBOX_STYLE::PASSWORD))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, std::string(m_strCustomText.length(), '*'));
    }
  }

  void CTextBox::Update()
  {
    // if the textbox is listening for a new key press
    if (m_bIsGettingKey)
    {
      for (std::size_t key = 0; key < 256; key++)
      {
        if (!FGUI::INPUT.GetKeyPress(key))
        {
          continue;
        }

        // key input
        std::string strKeyInput = m_ksStrings.m_strInputSystem[key].data();
        //std::string strKeyInput = m_ksStrings.m_strVirtualKeyCodes[key].data();

        // if the user press ESC or ENTER, stop the textbox from receiving input
        if (key == KEY_ESCAPE || key == KEY_ENTER)
        {
          // block listbox
          m_bIsGettingKey = false;
        }

        // handle upper case keys
        if (FGUI::INPUT.GetKeyHeld(KEY_LSHIFT) || FGUI::INPUT.GetKeyHeld(KEY_RSHIFT))
        {
          std::transform(strKeyInput.begin(), strKeyInput.end(), strKeyInput.begin(), ::toupper);
        }

        // input position
        std::size_t ulInputPos = 0;

        // insert text
        if (strKeyInput.length() == 1 && (m_strCustomText.length() < m_uiLength))
        {
          m_strCustomText.insert(ulInputPos, strKeyInput);
          ulInputPos++;
        }

        if (m_strCustomText.length() > 0)
        {
          if (key == KEY_BACKSPACE && (ulInputPos > 0))
          {
            m_strCustomText.erase(ulInputPos, 1);
            ulInputPos--;
          }
          else if (key == KEY_DELETE)
          {
            // clear text
            m_strCustomText.clear();
            ulInputPos = 0;
          }

          // change the current input position
          if (key == KEY_LEFT)
          {
            ulInputPos--;
          }
          else if (key == KEY_RIGHT && (ulInputPos < m_strCustomText.length()))
          {
            ulInputPos++;
          }
        }
      }
    }
  }

  void CTextBox::Input()
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      m_bIsGettingKey = !m_bIsGettingKey;
    }
  }

  void CTextBox::Save(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName] = m_strCustomText;
  }

  void CTextBox::Load(std::string file)
  {
    nlohmann::json jsModule;

    std::ifstream ifsFileToLoad(file, std::ifstream::binary);

    if (ifsFileToLoad.fail())
    {
      return; // TODO: handle this properly
    }

    jsModule = nlohmann::json::parse(ifsFileToLoad);

    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    // change widget text to the one stored on file
    m_strCustomText = jsModule[strFormatedWidgetName];
  }

  void CTextBox::Tooltip()
  {
    if (m_strTooltip.length() > 1 && !m_bIsGettingKey)
    {
      FGUI::DIMENSION dmTooltipTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTooltip);

      FGUI::AREA arWidgetRegion = {(FGUI::INPUT.GetCursorPos().m_iX + 10), (FGUI::INPUT.GetCursorPos().m_iY + 10), (dmTooltipTextSize.m_iWidth + 10), (dmTooltipTextSize.m_iHeight + 10)};

      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {180, 95, 95});
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {225, 90, 75});
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (arWidgetRegion.m_iRight / 2) - (dmTooltipTextSize.m_iWidth / 2),
                        arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTooltipTextSize.m_iHeight / 2), m_anyFont, {245, 245, 245}, m_strTooltip);
    }
  }

} // namespace FGUI