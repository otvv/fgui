//
// FGUI - feature rich graphical user interface
//

// library includes
#include "listbox.hpp"
#include "container.hpp"

namespace FGUI
{

  CListBox::CListBox()
  {
    m_strTitle = "ListBox";
    m_anyFont = 0;
    m_iEntrySpacing = 20;
    m_dmSize = {250, 300};
    m_ullSelectedEntry = 0;
    m_iScrollThumbPosition = 0;
    m_fnctCallback = nullptr;
    m_bIsDraggingThumb = false;
    m_prgpEntries = {};
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::LISTBOX);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CListBox::SetIndex(std::size_t index)
  {
    m_ullSelectedEntry = index;
  }

  std::size_t CListBox::GetIndex()
  {
    return m_ullSelectedEntry;
  }

  int CListBox::GetValue()
  {
    return m_prgpEntries.second[m_ullSelectedEntry];
  }

  void CListBox::AddEntry(std::string name, unsigned int value)
  {
    m_prgpEntries.first.emplace_back(name);
    m_prgpEntries.second.emplace_back(value);
  }

  void CListBox::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CListBox::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    FGUI::AREA arScrollBarRegion = { (arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, arWidgetRegion.m_iTop, 15, m_dmSize.m_iHeight };

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    // entries displayed
    int iEntriesDisplayed = 0;

    // calculate the amount of entries that will be drawn on the listbox
    int iCalculatedEntries = (m_dmSize.m_iHeight / m_iEntrySpacing);

    // listbox body
    FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (iEntriesDisplayed * m_iEntrySpacing), m_dmSize.m_iWidth, m_dmSize.m_iHeight, { 220, 220, 220 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + (iEntriesDisplayed * m_iEntrySpacing)) + 1, (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 2), { 255, 255, 255 });

    // listbox label
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop - dmTitleTextSize.m_iHeight) - 2, m_anyFont, { 35, 35, 35 }, m_strTitle);

    for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpEntries.first.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
    {
      FGUI::AREA arEntryRegion = { arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed), (arWidgetRegion.m_iRight - arScrollBarRegion.m_iRight), m_iEntrySpacing };

      // check if the user is hovering something on the listbox
      if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
      {
        FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, arEntryRegion.m_iTop, arEntryRegion.m_iRight, arEntryRegion.m_iBottom, { 255, 255, 235 });
        FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom) - 1, arEntryRegion.m_iRight, 1, { 205, 205, 205 });
        FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 3), m_anyFont, { 35, 35, 35 }, m_prgpEntries.first[i]);
      }
      else
      {
        FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom) - 1, arEntryRegion.m_iRight, 1, { 205, 205, 205 });
        FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 3), m_anyFont, { 35, 35, 35 }, m_prgpEntries.first[i]);
      }

      // if the user selects an entry on the listbox
      if (m_ullSelectedEntry == i)
      {
        FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, arEntryRegion.m_iTop, arEntryRegion.m_iRight, arEntryRegion.m_iBottom, { 25, 145, 255 });
        FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 3), m_anyFont, { 245, 245, 245 }, m_prgpEntries.first[i]);
      }

      iEntriesDisplayed++;
    }

    static constexpr FGUI::DIMENSION dmScrollBarThumb = { 8, 5 };

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
    FGUI::RENDER.Rectangle(arScrollBarRegion.m_iLeft, arScrollBarRegion.m_iTop, arScrollBarRegion.m_iRight, arScrollBarRegion.m_iBottom, { 235, 235, 235 });

    if (m_prgpEntries.first.size() > 50)
    {
      FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumb.m_iWidth, dmScrollBarThumb.m_iHeight, { 220, 223, 231 });
    }
    else
    {
      FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumb.m_iWidth, flCalculatedSize, { 220, 223, 231 });
    }
    
    IGNORE_ARGS(status);
  }

  void CListBox::Update()
  {
    if (m_bIsDraggingThumb)
    {
      // calculate the amount of entries that will be drawn on the listbox
      int iCalculatedEntries = (m_dmSize.m_iHeight / m_iEntrySpacing);

      FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

      if (FGUI::INPUT.IsKeyHeld(MOUSE_1))
      {
        // move thumb vertically
        ptCursorPos.m_iY -= GetAbsolutePosition().m_iY;

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

    // stop scrolling if another widget is being focused
    if (std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->GetFocusedWidget())
    {
      m_bIsDraggingThumb = false;
    }
  }

  void CListBox::Input()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    static constexpr FGUI::DIMENSION dmScrollBarThumb = { 8, 5 };

    FGUI::AREA arScrollBarRegion = { ((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15), arWidgetRegion.m_iTop, dmScrollBarThumb.m_iWidth, (m_dmSize.m_iHeight - m_iEntrySpacing) };

    if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
    {
      m_bIsDraggingThumb = true;
    }

    // entries displayed
    int iEntriesDisplayed = 0;

    // calculate the amount of entries that will be drawn on the listbox
    int iCalculatedEntries = (m_dmSize.m_iHeight / m_iEntrySpacing);

    // listbox entries
    for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpEntries.first.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
    {
      FGUI::AREA arEntryRegion = { arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed), (arWidgetRegion.m_iRight - 15), m_iEntrySpacing };

      // select an entry
      if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
      {
        m_ullSelectedEntry = i;
      }

      if (m_ullSelectedEntry == i)
      {
        if (m_fnctCallback)
        {
          // call function
          m_fnctCallback();
        }
      }

      iEntriesDisplayed++;
    }
  }

  void CListBox::Save(nlohmann::json& module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName] = m_ullSelectedEntry;
  }

  void CListBox::Load(nlohmann::json& module)
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

  void CListBox::Tooltip()
  {
    if (m_strTooltip.length() > 1)
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