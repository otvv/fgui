//
// FGUI - feature rich graphical user interface
//

// library includes
#include "combobox.hpp"
#include "container.hpp"

namespace FGUI
{
  CComboBox::CComboBox()
  {
    m_strTitle = "ComboBox";
    m_anyFont = 0;
    m_dmSize = {150, 20};
    m_iCustomHeight = {m_dmSize.m_iHeight};
    m_iEntrySpacing = 20;
    m_ullSelectedEntry = 0;
    m_iScrollThumbPosition = 0;
    m_bIsDraggingThumb = false;
    m_bIsOpened = false;
    m_prgpEntries = {};
    m_fnctCallback = nullptr;
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::COMBOBOX);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::FOCUSABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CComboBox::SetState(bool onoff)
  {
    m_bIsOpened = onoff;
  }

  bool CComboBox::GetState()
  {
    return m_bIsOpened;
  }

  void CComboBox::SetIndex(std::size_t index)
  {
    m_ullSelectedEntry = index;
  }

  std::size_t CComboBox::GetIndex()
  {
    return m_ullSelectedEntry;
  }

  void CComboBox::SetValue(std::size_t index, unsigned int value)
  {
    m_prgpEntries.second[index] = value;
  }

  std::size_t CComboBox::GetValue()
  {
    return m_prgpEntries.second[m_ullSelectedEntry];
  }

  void CComboBox::AddEntry(std::string name, unsigned int value)
  {
    m_prgpEntries.first.emplace_back(name);
    m_prgpEntries.second.emplace_back(value);
  }

  void CComboBox::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CComboBox::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_iCustomHeight};
    FGUI::AREA arScrollBarRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, (arWidgetRegion.m_iTop + 21), 15, (m_dmSize.m_iHeight - m_iEntrySpacing)};

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    // combobox body
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

    // combobox label
    FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_strTitle + ":");

    // draw current selected entry
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_prgpEntries.first[m_ullSelectedEntry]);

    if (m_bIsOpened)
    {
      if (m_prgpEntries.first.size() > 14)
      {
        // dropdown list body
        FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21), arWidgetRegion.m_iRight, (10 * m_iEntrySpacing), {121, 180, 209});
        FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 21) + 1, (arWidgetRegion.m_iRight - 2), (10 * m_iEntrySpacing) - 2, {255, 255, 255});

        // entries displayed
        int iEntriesDisplayed = 0;

        // calculate the amount of entries that will be drawn on the dropdown list
        int iCalculatedEntries = (m_dmSize.m_iHeight - m_iEntrySpacing) / m_iEntrySpacing;

        for (std::size_t i = m_iScrollThumbPosition; i < m_prgpEntries.first.size() && iEntriesDisplayed < iCalculatedEntries; i++)
        {
          FGUI::AREA arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (iEntriesDisplayed * m_iEntrySpacing), (arWidgetRegion.m_iRight - arScrollBarRegion.m_iRight), (m_iEntrySpacing - 2)};

          // check if the user is hovering/have selected an entry
          if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_ullSelectedEntry == i)
          {
            FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, arEntryRegion.m_iTop, arEntryRegion.m_iRight - 2, arEntryRegion.m_iBottom, {25, 145, 255});
            FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_anyFont, {255, 255, 255}, m_prgpEntries.first[i]);
          }
          else
          {
            FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom), arEntryRegion.m_iRight - 1, 1, {205, 205, 205});
            FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_anyFont, {35, 35, 35}, m_prgpEntries.first[i]);
          }

          iEntriesDisplayed++;
        }

        static constexpr FGUI::DIMENSION dmScrollBarThumb = {8, 5};

        // calculate thumb position
        float flCalculatedPosition = static_cast<float>(m_iScrollThumbPosition) / static_cast<float>(m_prgpEntries.first.size());

        if (flCalculatedPosition >= 1.f)
        {
          flCalculatedPosition = 1.f;
        }

        flCalculatedPosition *= (m_dmSize.m_iHeight - m_iEntrySpacing) - 10;

        // calculate thumb size
        float flCalculatedSize = static_cast<float>(iCalculatedEntries) / static_cast<float>(m_prgpEntries.first.size());

        if (flCalculatedSize > 1.f)
        {
          flCalculatedSize = 1.f;
        }

        flCalculatedSize *= (m_dmSize.m_iHeight - m_iEntrySpacing);

        // scrollbar body
        FGUI::RENDER.Rectangle(arScrollBarRegion.m_iLeft, (arScrollBarRegion.m_iTop + 1), (arScrollBarRegion.m_iRight - 1), (arScrollBarRegion.m_iBottom - 3), {235, 235, 235});

        if (m_prgpEntries.first.size() > 50)
        {
          FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 3), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumb.m_iWidth, dmScrollBarThumb.m_iHeight, {220, 223, 231});
        }
        else
        {
          FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 3), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumb.m_iWidth, (flCalculatedSize - 10), {220, 223, 231});
        }
      }
      else
      {
        // dropdown list body
        FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21), arWidgetRegion.m_iRight, (m_prgpEntries.first.size() * m_iEntrySpacing), {121, 180, 209});
        FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 21) + 1, (arWidgetRegion.m_iRight - 2), (m_prgpEntries.first.size() * m_iEntrySpacing) - 2, {255, 255, 255});

        for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
        {
          FGUI::AREA arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, (m_iEntrySpacing - 2)};

          // check if the user is hovering/have selected an entry
          if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_ullSelectedEntry == i)
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
    }

    // combobox dropdown arrow body
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 8, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 1, 8, 1, {20, 20, 20});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 7, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 2, 6, 1, {20, 20, 20});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 6, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 3, 4, 1, {20, 20, 20});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 5, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 4, 2, 1, {20, 20, 20});
  }

  void CComboBox::Update()
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_iCustomHeight};
    FGUI::AREA arScrollBarRegion = {((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15), (arWidgetRegion.m_iTop + 21), 15, (m_dmSize.m_iHeight - m_iEntrySpacing)};

    if (m_bIsOpened)
    {
      // keep widget focused
      std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->SetFocusedWidget(shared_from_this());

      if (m_prgpEntries.first.size() > 14)
      {
        m_dmSize.m_iHeight = m_iEntrySpacing + (10 * m_iEntrySpacing) + 1;
      }
      else
      {
        m_dmSize.m_iHeight = m_iEntrySpacing + (m_prgpEntries.first.size() * m_iEntrySpacing) + 1;
      }
    }
    else
    {
      // restore widget size
      m_dmSize.m_iHeight = m_iCustomHeight;
    }

    if (m_prgpEntries.first.size() > 14)
    {
      if (m_bIsDraggingThumb)
      {
        // calculate the amount of entries that will be drawn on the dropdown list
        int iCalculatedEntries = (m_dmSize.m_iHeight - m_iEntrySpacing) / m_iEntrySpacing;

        FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

        if (FGUI::INPUT.IsKeyHeld(MOUSE_1))
        {
          // move thumb vertically
          ptCursorPos.m_iY -= (GetAbsolutePosition().m_iY + 21);

          // ratio of how many visible to how many are hidden
          float flVisibleRatio = static_cast<float>(iCalculatedEntries) / static_cast<float>(m_prgpEntries.first.size());
          flVisibleRatio *= (m_dmSize.m_iHeight - m_iEntrySpacing);

          // calculate height delta
          float flHeightDelta = static_cast<float>(ptCursorPos.m_iY + flVisibleRatio) - static_cast<float>(m_dmSize.m_iHeight);

          if (flHeightDelta >= 0.f)
          {
            ptCursorPos.m_iY -= flHeightDelta;
          }

          // new vertical position ratio
          float flNewYRatio = static_cast<float>(ptCursorPos.m_iY) / static_cast<float>(m_dmSize.m_iHeight);
          m_iScrollThumbPosition = (flNewYRatio * m_prgpEntries.first.size());

          // clamp position (don't let the user drag the scroll thumb if it reaches the "start" of the scrollbar area)
          if (m_iScrollThumbPosition <= 0)
          {
            m_iScrollThumbPosition = 0;
          }
        }
        else
        {
          m_bIsDraggingThumb = false;
        }
      }

      // keep dropdown opened if the user is scrolling
      if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
      {
        if (FGUI::INPUT.IsKeyHeld(MOUSE_1))
        {
          m_bIsOpened = true;
        }
      }
    }

    // close dropdown if another widget is being focused
    if (std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->GetFocusedWidget() != shared_from_this())
    {
      m_bIsOpened = false;
      m_bIsDraggingThumb = false;
    }
  }

  void CComboBox::Input()
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_iCustomHeight};
    FGUI::AREA arScrollBarRegion = {((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15), (arWidgetRegion.m_iTop + 21), 15, (m_dmSize.m_iHeight - m_iEntrySpacing)};

    // toggle dropdown list on and off
    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      m_bIsOpened = !m_bIsOpened;
    }

    if (m_bIsOpened)
    {
      if (!FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        FGUI::AREA arEntryRegion = {0, 0, 0, 0};

        if (m_prgpEntries.first.size() > 14)
        {
          if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
          {
            m_bIsDraggingThumb = true;
          }

          // entries displayed
          int iEntriesDisplayed = 0;

          // calculate the amount of entries that will be drawn on the dropdown list
          int iCalculatedEntries = (m_dmSize.m_iHeight - m_iEntrySpacing) / m_iEntrySpacing;

          for (std::size_t i = m_iScrollThumbPosition; i < m_prgpEntries.first.size() && iEntriesDisplayed < iCalculatedEntries; i++)
          {
            arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (iEntriesDisplayed * m_iEntrySpacing), (arWidgetRegion.m_iRight - arScrollBarRegion.m_iRight), (m_iEntrySpacing - 2)};

            if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
            {
              // select an entry
              m_ullSelectedEntry = i;

              if (m_ullSelectedEntry == i)
              {
                if (m_fnctCallback)
                {
                  // call function
                  m_fnctCallback();
                }

                // close dropdown list after selecting something
                m_bIsOpened = false;
              }
            }

            iEntriesDisplayed++;
          }
        }
        else
        {
          for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
          {
            arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, (m_iEntrySpacing - 2)};

            if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
            {
              // select an entry
              m_ullSelectedEntry = i;

              if (m_ullSelectedEntry == i)
              {
                if (m_fnctCallback)
                {
                  // call function
                  m_fnctCallback();
                }

                // close dropdown list after selecting something
                m_bIsOpened = false;
              }
            }
          }
        }
      }
    }
  }

  void CComboBox::Save(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName] = m_ullSelectedEntry;
  }

  void CComboBox::Load(nlohmann::json &module)
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

  void CComboBox::Tooltip()
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