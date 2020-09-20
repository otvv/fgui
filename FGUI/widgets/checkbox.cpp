//
// FGUI - feature rich graphical user interface
//

// library includes
#include "checkbox.hpp"

namespace FGUI
{

  CCheckBox::CCheckBox()
  {
    m_strTitle = "CheckBox";
    m_dmSize = { 16, 16 };
    m_anyFont = 0;
    m_strTooltip = "";
    m_bIsChecked = false;
    m_fnctCallback = nullptr;
    m_nType = static_cast<int>(WIDGET_TYPE::CHECKBOX);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CCheckBox::SetState(bool onoff)
  {
    m_bIsChecked = onoff;
  }

  bool CCheckBox::GetState()
  {
    return m_bIsChecked;
  }

  void CCheckBox::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CCheckBox::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    // checkbox body
    FGUI::RENDER.Outline((arWidgetRegion.m_iLeft - 1), (arWidgetRegion.m_iTop - 1), arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 220, 220, 220 });
    FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), { 255, 255, 255 });

    if (m_bIsChecked)
    {
      if (status == FGUI::WIDGET_STATUS::HOVERED)
      {
        FGUI::RENDER.Outline((arWidgetRegion.m_iLeft - 1), (arWidgetRegion.m_iTop - 1), arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 180, 25, 25 });
      }

      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 3), (arWidgetRegion.m_iTop + 3), (arWidgetRegion.m_iRight - 8), (arWidgetRegion.m_iBottom - 8), { 180, 25, 25 });
    }
    else
    {
      if (status == FGUI::WIDGET_STATUS::HOVERED)
      {
        FGUI::RENDER.Outline((arWidgetRegion.m_iLeft - 1), (arWidgetRegion.m_iTop - 1), arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 195, 195, 195 });
      }
    }

    // checkbox label
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (arWidgetRegion.m_iRight + 5), arWidgetRegion.m_iTop, m_anyFont, { 35, 35, 35 }, m_strTitle);
  }

  void CCheckBox::Update()
  {
    m_dmSize = { 16, 16 }; // this is required to keep the widget from being padded on Containers
    
    if (m_bIsChecked)
    {
      if (m_fnctCallback)
      {
        // call function
        m_fnctCallback();
      }
    }
  }

  void CCheckBox::Input()
  {
    m_bIsChecked = !m_bIsChecked;
  }

  void CCheckBox::Save(nlohmann::json& module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName] = m_bIsChecked;
  }

  void CCheckBox::Load(nlohmann::json& module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    // change widget state to the one stored on file
    if (module.contains(strFormatedWidgetName))
    {
      m_bIsChecked = module[strFormatedWidgetName];
    }
  }

  void CCheckBox::Tooltip()
  {
    if (m_strTooltip.length() > 1 && !m_bIsChecked)
    {
      FGUI::DIMENSION dmTooltipTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTooltip);

      FGUI::AREA arTooltipRegion = { (FGUI::INPUT.GetCursorPos().m_iX + 10), (FGUI::INPUT.GetCursorPos().m_iY + 10), (dmTooltipTextSize.m_iWidth + 10), (dmTooltipTextSize.m_iHeight + 10) };

      FGUI::RENDER.Outline(arTooltipRegion.m_iLeft, arTooltipRegion.m_iTop, arTooltipRegion.m_iRight, arTooltipRegion.m_iBottom, { 180, 95, 95 });
      FGUI::RENDER.Rectangle((arTooltipRegion.m_iLeft + 1), (arTooltipRegion.m_iTop + 1), (arTooltipRegion.m_iRight - 2), (arTooltipRegion.m_iBottom - 2), { 225, 90, 75 });
      FGUI::RENDER.Text(arTooltipRegion.m_iLeft + (arTooltipRegion.m_iRight / 2) - (dmTooltipTextSize.m_iWidth / 2),
        arTooltipRegion.m_iTop + (arTooltipRegion.m_iBottom / 2) - (dmTooltipTextSize.m_iHeight / 2), m_anyFont, { 245, 245, 245 }, m_strTooltip);
    }
  }

} // namespace FGUI