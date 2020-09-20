//
// FGUI - feature rich graphical user interface
//

// library includes
#include "button.hpp"

namespace FGUI
{

  CButton::CButton()
  {
    m_strTitle = "Button";
    m_dmSize = {100, 25};
    m_strTooltip = "";
    m_anyFont = 0;
    m_fnctCallback = nullptr;
    m_nType = static_cast<int>(WIDGET_TYPE::BUTTON);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
  }

  void CButton::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CButton::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    // button body
    if (status == FGUI::WIDGET_STATUS::HOVERED)
    {
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {50, 50, 50});
    }
    else
    {
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {35, 90, 120});
    }

    // button label
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (arWidgetRegion.m_iRight / 2) - (dmTitleTextSize.m_iWidth / 2),
                      arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {245, 245, 245}, m_strTitle);
  }

  void CButton::Update()
  {
  }

  void CButton::Input()
  {
    if (m_fnctCallback)
    {
      // call function
      m_fnctCallback();
    }
  }

  void CButton::Save(nlohmann::json &module)
  {
    IGNORE_ARGS(module);
  }

  void CButton::Load(nlohmann::json &module)
  {
    IGNORE_ARGS(module);
  }

  void CButton::Tooltip()
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