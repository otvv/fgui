//
// FGUI - feature rich graphical user interface
//

// library includes
#include "multibox.hpp"
#include "container.hpp"

namespace FGUI
{

  CMultiBox::CMultiBox()
  {
    m_strTitle = "MultiBox";
    m_anyFont = 0;
    m_dmSize = {150, 20};
    m_iCustomHeight = {m_dmSize.m_iHeight};
    m_iEntrySpacing = 20;
    m_prgpEntries = {};
    m_bIsOpened = false;
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::MULTIBOX);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::FOCUSABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CMultiBox::SetState(bool onoff)
  {
    m_bIsOpened = onoff;
  }

  bool CMultiBox::GetState()
  {
    return m_bIsOpened;
  }

  void CMultiBox::SetValue(std::size_t index, bool value)
  {
    m_prgpEntries.second[index] = value;
  }

  std::size_t CMultiBox::GetValue(std::size_t index)
  {
    return m_prgpEntries.second[index];
  }

  void CMultiBox::AddEntry(std::string name, bool value)
  {
    m_prgpEntries.first.emplace_back(name);
    m_prgpEntries.second.emplace_back(value);
  }

  void CMultiBox::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_iCustomHeight};

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    // multibox body
    if (status == FGUI::WIDGET_STATUS::HOVERED || m_bIsOpened)
    {
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {195, 195, 195});
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {255, 255, 235});
    }
    else
    {
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {220, 220, 220});
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {255, 255, 255});
    }

    // multibox label
    FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_strTitle + ":");

    // string format
    std::string strMultiString = {};

    for (std::size_t i = 0; i < m_prgpEntries.first.size(); ++i)
    {
      // switches
      bool bHasReachedLength = strMultiString.length() > 15;
      bool bIsFirstItem = strMultiString.length() == 0;

      if (m_prgpEntries.second[i] && !bHasReachedLength)
      {
        if (!m_prgpEntries.first[i].empty())
        {
          if (!bIsFirstItem)
          {
            strMultiString.append(", ");
          }

          strMultiString.append(m_prgpEntries.first[i]);
        }
      }
      else if (bHasReachedLength && !bIsFirstItem)
      {
        strMultiString.append(" ...");

        break;
      }
    }

    if (strMultiString.length() == 0)
    {
      strMultiString.assign("None");
    }

    // draw current selected entry
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, strMultiString);

    if (m_bIsOpened)
    {
      // dropdown list body
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21), arWidgetRegion.m_iRight, (m_prgpEntries.first.size() * m_iEntrySpacing), {121, 180, 209});
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 21) + 1, (arWidgetRegion.m_iRight - 2), (m_prgpEntries.first.size() * m_iEntrySpacing) - 2, {255, 255, 255});

      for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
      {
        FGUI::AREA arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing};

        // check if the user is hovering/have selected an entry
        if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_prgpEntries.second[i])
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, arEntryRegion.m_iTop, arEntryRegion.m_iRight - 2, arEntryRegion.m_iBottom, {25, 145, 255});
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_anyFont, {255, 255, 255}, m_prgpEntries.first[i]);
        }
        else
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom), arEntryRegion.m_iRight - 1, 1, {205, 205, 205});
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_anyFont, {35, 35, 35}, m_prgpEntries.first[i]);
        }
      }
    }

    // multibox dropdown arrow body
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 8, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 1, 8, 1, {20, 20, 20});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 7, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 2, 6, 1, {20, 20, 20});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 6, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 3, 4, 1, {20, 20, 20});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 5, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 4, 2, 1, {20, 20, 20});
  }

  void CMultiBox::Update()
  {
    if (m_bIsOpened)
    {
      // keep widget focused
      std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->SetFocusedWidget(shared_from_this());

      m_dmSize.m_iHeight = m_iEntrySpacing + (m_prgpEntries.first.size() * m_iEntrySpacing) + 2;
    }
    else
    {
      // restore widget size
      m_dmSize.m_iHeight = m_iCustomHeight;
    }

    // close dropdown if another widget is being focused
    if (std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->GetFocusedWidget() != shared_from_this())
    {
      m_bIsOpened = false;
    }
  }

  void CMultiBox::Input()
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_iCustomHeight};

    // toggle dropdown list on and off
    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      m_bIsOpened = !m_bIsOpened;
    }

    if (m_bIsOpened)
    {
      if (!FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
        {
          FGUI::AREA arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing};

          if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
          {
            // select an entry
            m_prgpEntries.second[i] = !m_prgpEntries.second[i];

            if (m_prgpEntries.second[i])
            {
              // close dropdown list after selecting something
              // NOTE: maybe remove this?
              m_bIsOpened = false;
            }
          }
        }
      }
    }
  }

  void CMultiBox::Save(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
    {
      bool bDummyChecked = m_prgpEntries.second[i];

      // remove spaces from the entry name
      std::string strFormatedEntryName = m_prgpEntries.first[i];
      std::replace(strFormatedEntryName.begin(), strFormatedEntryName.end(), ' ', '_');

      module[strFormatedWidgetName][strFormatedEntryName] = bDummyChecked;
    }
  }

  void CMultiBox::Load(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    if (module.contains(strFormatedWidgetName))
    {
      for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
      {
        // remove spaces from the entry name
        std::string strFormatedEntryName = m_prgpEntries.first[i];
        std::replace(strFormatedEntryName.begin(), strFormatedEntryName.end(), ' ', '_');

        if (module.contains(strFormatedEntryName))
        {
          // change widget state to the one stored on file
          SetValue(i, module[strFormatedWidgetName][strFormatedEntryName]);
        }
      }
    }
  }

  void CMultiBox::Tooltip()
  {
    if (m_strTooltip.length() > 1 && !m_bIsOpened)
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