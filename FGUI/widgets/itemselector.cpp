//
// FGUI - feature rich graphical user interface
//

// library includes
#include "itemselector.hpp"

namespace FGUI
{
  CItemSelector::CItemSelector()
  {
    m_strTitle = "ItemSelector";
    m_anyFont = 0;
    m_dmSize = {150, 20};
    m_ullSelectedEntry = 0;
    m_prgpEntries = {};
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::ITEMSELECTOR);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CItemSelector::SetIndex(std::size_t index)
  {
    m_ullSelectedEntry = index;
  }

  std::size_t CItemSelector::GetIndex()
  {
    return m_ullSelectedEntry;
  }

  void CItemSelector::SetValue(std::size_t index, unsigned int value)
  {
    m_prgpEntries.second[index] = value;
  }

  std::size_t CItemSelector::GetValue()
  {
    return m_prgpEntries.second[m_ullSelectedEntry];
  }

  void CItemSelector::AddEntry(std::string name, unsigned int value)
  {
    m_prgpEntries.first.emplace_back(name);
    m_prgpEntries.second.emplace_back(value);
  }

  void CItemSelector::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arLeftButtonRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, 20, m_dmSize.m_iHeight};
    FGUI::AREA arWidgetRegion = {(arLeftButtonRegion.m_iLeft + arLeftButtonRegion.m_iRight), arLeftButtonRegion.m_iTop, (m_dmSize.m_iWidth - (arLeftButtonRegion.m_iRight * 2)), m_dmSize.m_iHeight};
    FGUI::AREA arRightButtonRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight), arWidgetRegion.m_iTop, 20, m_dmSize.m_iHeight};

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);
    FGUI::DIMENSION dmLeftButtonTextSize = FGUI::RENDER.GetTextSize(m_anyFont, "<");
    FGUI::DIMENSION dmRightButtonTextSize = FGUI::RENDER.GetTextSize(m_anyFont, ">");
    FGUI::DIMENSION dmSelectedEntryTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_prgpEntries.first[m_ullSelectedEntry]);

    // item selector body
    FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 220, 220, 220 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 1), (arWidgetRegion.m_iBottom - 2), { 255, 255, 255 });

    // TODO: what the fuck is this?
    if (FGUI::INPUT.IsCursorInArea(arLeftButtonRegion))
    {
      FGUI::RENDER.Outline(arLeftButtonRegion.m_iLeft, arLeftButtonRegion.m_iTop, arLeftButtonRegion.m_iRight, arLeftButtonRegion.m_iBottom, { 195, 195, 195 });
      FGUI::RENDER.Rectangle((arLeftButtonRegion.m_iLeft + 1), (arLeftButtonRegion.m_iTop + 1), (arLeftButtonRegion.m_iRight - 2), (arLeftButtonRegion.m_iBottom - 2), { 50, 50, 50 });
    }
    else
    {
      FGUI::RENDER.Outline(arLeftButtonRegion.m_iLeft, arLeftButtonRegion.m_iTop, arLeftButtonRegion.m_iRight, arLeftButtonRegion.m_iBottom, { 38, 142, 199 });
      FGUI::RENDER.Rectangle((arLeftButtonRegion.m_iLeft + 1), (arLeftButtonRegion.m_iTop + 1), (arLeftButtonRegion.m_iRight - 2), (arLeftButtonRegion.m_iBottom - 2), { 35, 90, 120 });
    }
    
    if (FGUI::INPUT.IsCursorInArea(arRightButtonRegion))
    {
      FGUI::RENDER.Outline(arRightButtonRegion.m_iLeft, arRightButtonRegion.m_iTop, arRightButtonRegion.m_iRight, arRightButtonRegion.m_iBottom, { 195, 195, 195 });
      FGUI::RENDER.Rectangle((arRightButtonRegion.m_iLeft + 1), (arRightButtonRegion.m_iTop + 1), (arRightButtonRegion.m_iRight - 2), (arRightButtonRegion.m_iBottom - 2), { 50, 50, 50 });
    }
    else
    {
      FGUI::RENDER.Outline(arRightButtonRegion.m_iLeft, arRightButtonRegion.m_iTop, arRightButtonRegion.m_iRight, arRightButtonRegion.m_iBottom, { 38, 142, 199 });
      FGUI::RENDER.Rectangle((arRightButtonRegion.m_iLeft + 1), (arRightButtonRegion.m_iTop + 1), (arRightButtonRegion.m_iRight - 2), (arRightButtonRegion.m_iBottom - 2), { 35, 90, 120 });
    }
    
    FGUI::RENDER.Text(arLeftButtonRegion.m_iLeft + (arLeftButtonRegion.m_iRight / 2) - (dmLeftButtonTextSize.m_iWidth / 2), arLeftButtonRegion.m_iTop + (arLeftButtonRegion.m_iBottom / 2) - (dmLeftButtonTextSize.m_iHeight / 2), m_anyFont, {245, 245, 245}, "<");
    FGUI::RENDER.Text(arRightButtonRegion.m_iLeft + (arRightButtonRegion.m_iRight / 2) - (dmRightButtonTextSize.m_iWidth / 2), arRightButtonRegion.m_iTop + (arRightButtonRegion.m_iBottom / 2) - (dmRightButtonTextSize.m_iHeight / 2), m_anyFont, {245, 245, 245}, ">");

    // item selector label
    FGUI::RENDER.Text(arLeftButtonRegion.m_iLeft, (arLeftButtonRegion.m_iTop - dmTitleTextSize.m_iHeight) - 2, m_anyFont, {35, 35, 35}, m_strTitle);

    // draw current selected entry
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (arWidgetRegion.m_iRight / 2) - (dmSelectedEntryTextSize.m_iWidth / 2), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmSelectedEntryTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_prgpEntries.first[m_ullSelectedEntry]);

    IGNORE_ARGS(status);
  }

  void CItemSelector::Update()
  {
  }

  void CItemSelector::Input()
  {
    FGUI::AREA arLeftButtonRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, 20, m_dmSize.m_iHeight};
    FGUI::AREA arWidgetRegion = {(arLeftButtonRegion.m_iLeft + arLeftButtonRegion.m_iRight), arLeftButtonRegion.m_iTop, (m_dmSize.m_iWidth - (arLeftButtonRegion.m_iRight * 2)), m_dmSize.m_iHeight};
    FGUI::AREA arRightButtonRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight), arWidgetRegion.m_iTop, 20, m_dmSize.m_iHeight};

    if (FGUI::INPUT.IsCursorInArea(arLeftButtonRegion))
    {
      if (m_ullSelectedEntry > 0)
      {
        m_ullSelectedEntry--;
      }
    }
    else if (FGUI::INPUT.IsCursorInArea(arRightButtonRegion))
    {
      if (m_ullSelectedEntry < (m_prgpEntries.first.size() - 1))
      {
        m_ullSelectedEntry++;
      }
    }
  }

  void CItemSelector::Save(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName] = m_ullSelectedEntry;
  }

  void CItemSelector::Load(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    // change widget selected entry to the one stored on file
    if (module.contains(strFormatedWidgetName))
    {
      m_ullSelectedEntry = module[strFormatedWidgetName];
    }
  }

  void CItemSelector::Tooltip()
  {
    if (m_strTooltip.length() > 1 && m_ullSelectedEntry == 0)
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