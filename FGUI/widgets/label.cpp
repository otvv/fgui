//
// FGUI - feature rich graphical user interface
//

// library includes
#include "label.hpp"

namespace FGUI
{

  CLabel::CLabel()
  {
    m_strTitle = "Label";
    m_anyFont = 0;
    m_fnctCallback = nullptr;
    m_clrLabel = {180, 25, 25};
    m_strTooltip = "";
    m_nStyle = static_cast<int>(LABEL_STYLE::NORMAL);
    m_nType = static_cast<int>(WIDGET_TYPE::LABEL);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
  }

  void CLabel::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CLabel::SetStyle(FGUI::LABEL_STYLE style)
  {
    m_nStyle = static_cast<int>(style);
  }

  void CLabel::SetColor(FGUI::COLOR color)
  {
    if (m_nStyle == static_cast<int>(LABEL_STYLE::COLORED))
    {
      m_clrLabel = color;
    }
  }

  FGUI::COLOR CLabel::GetColor()
  {
    return m_clrLabel;
  }

  int CLabel::GetStyle()
  {
    return m_nStyle;
  }

  void CLabel::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    // label body
    if (m_nStyle == static_cast<int>(LABEL_STYLE::NORMAL))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, {35, 35, 35}, m_strTitle);
    }
    else if (m_nStyle == static_cast<int>(LABEL_STYLE::COLORED))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, m_clrLabel, m_strTitle);
    }
    else if (m_nStyle == static_cast<int>(LABEL_STYLE::LINK))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, {25, 25, 195}, m_strTitle);
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + arWidgetRegion.m_iBottom) + 1, arWidgetRegion.m_iRight, 1, {25, 25, 195});
    }
    else if (m_nStyle == static_cast<int>(LABEL_STYLE::SEPARATOR))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, {35, 35, 35}, m_strTitle);
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) + 10, arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2), 250, 1, {m_clrLabel});
    }

    IGNORE_ARGS(status);
  }

  void CLabel::Update()
  {
    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    m_dmSize = {dmTitleTextSize.m_iWidth, dmTitleTextSize.m_iHeight};
  }

  void CLabel::Input()
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    // check if the label is a link
    if (m_nStyle == static_cast<int>(LABEL_STYLE::LINK))
    {
      if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        if (m_fnctCallback)
        {
          // call function
          m_fnctCallback();
        }
      }
    }
  }

  void CLabel::Save(nlohmann::json &module)
  {
    IGNORE_ARGS(module);
  }

  void CLabel::Load(nlohmann::json &module)
  {
    IGNORE_ARGS(module);
  }

  void CLabel::Tooltip()
  {
    if (m_strTooltip.length() > 1)
    {
      FGUI::DIMENSION dmTooltipTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTooltip);

      FGUI::AREA arTooltipRegion = {(FGUI::INPUT.GetCursorPos().m_iX + 10), (FGUI::INPUT.GetCursorPos().m_iY + 10), (dmTooltipTextSize.m_iWidth + 10), (dmTooltipTextSize.m_iHeight + 10)};

      FGUI::RENDER.Outline(arTooltipRegion.m_iLeft, arTooltipRegion.m_iTop, arTooltipRegion.m_iRight, arTooltipRegion.m_iBottom, {180, 95, 95});
      FGUI::RENDER.Rectangle((arTooltipRegion.m_iLeft + 1), (arTooltipRegion.m_iTop + 1), (arTooltipRegion.m_iRight - 2), (arTooltipRegion.m_iBottom - 2), {225, 90, 75});
      FGUI::RENDER.Text(arTooltipRegion.m_iLeft + (arTooltipRegion.m_iRight / 2) - (dmTooltipTextSize.m_iWidth / 2),
                        arTooltipRegion.m_iTop + (arTooltipRegion.m_iBottom / 2) - (dmTooltipTextSize.m_iHeight / 2), m_anyFont, {245, 245, 245}, m_strTooltip);
    }
  }

} // namespace FGUI