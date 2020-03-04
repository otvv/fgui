//
// FGUI - feature rich graphical user interface
//

// library includes
#include "listbox.hpp"

namespace FGUI
{

// ----------------------------------------------- //
CListBox::CListBox()
{
  m_strTitle = "ListBox";
  m_ulFont = 0;
  m_iEntrySpacing = 20;
  m_uiSelectedEntry = 0;
  m_iScrollThumbPosition = 0;
  m_fnctCallback = nullptr;
  m_prgpEntries = {};
  m_nType = static_cast<int>(WIDGET_TYPE::LISTBOX);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
}

// ----------------------------------------------- //
void CListBox::SetIndex(std::size_t index)
{
  m_uiSelectedEntry = index;
}

// ----------------------------------------------- //
std::size_t CListBox::GetIndex()
{
  return m_uiSelectedEntry;
}

// ----------------------------------------------- //
int CListBox::GetValue()
{
  return m_prgpEntries.second[m_uiSelectedEntry];
}

// ----------------------------------------------- //
void CListBox::AddEntry(const std::string &name, unsigned int value)
{
  m_prgpEntries.first.emplace_back(name);
  m_prgpEntries.second.emplace_back(value);
}

// ----------------------------------------------- //
void CListBox::AddCallback(const std::function<void()> &callback)
{
  m_fnctCallback = callback;
}

// ----------------------------------------------- //
void CListBox::Geometry()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  // scrollbar area
  const FGUI::AREA &arScrollBarRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, arWidgetRegion.m_iTop, 15, m_dmSize.m_iHeight};

  // widget's title text size
  const FGUI::DIMENSION &dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // entries displayed
  int iEntriesDisplayed = 0;

  // calculate the amount of entries that will be drawn on the listbox
  int iCalculatedEntries = (m_dmSize.m_iHeight / m_iEntrySpacing);

  // listbox body
  FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (iEntriesDisplayed * m_iEntrySpacing), m_dmSize.m_iWidth, m_dmSize.m_iHeight, {220, 220, 220});
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + (iEntriesDisplayed * m_iEntrySpacing)) + 1, (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 2), {255, 255, 255});

  // listbox label
  FGUI::RENDER.Text(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop - dmTitleTextSize.m_iHeight) - 2, m_ulFont, {0, 0, 0}, m_strTitle);

  // listbox entries
  for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpEntries.first.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
  {
    // entry area
    const FGUI::AREA &arEntryRegion = {arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed), (arWidgetRegion.m_iRight - arScrollBarRegion.m_iRight), m_iEntrySpacing};

    // check if the user is hovering something on the listbox
    if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
    {
      FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, arEntryRegion.m_iTop, arEntryRegion.m_iRight, arEntryRegion.m_iBottom, {255, 255, 235});
      FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom) - 1, arEntryRegion.m_iRight, 1, {205, 205, 205});
      FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 3), m_ulFont, {0, 0, 0}, m_prgpEntries.first[i]);
    }
    else
    {
      FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom) - 1, arEntryRegion.m_iRight, 1, {205, 205, 205});
      FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 3), m_ulFont, {0, 0, 0}, m_prgpEntries.first[i]);
    }

    // if the user selects an entry on the listbox
    if (m_uiSelectedEntry == i)
    {
      FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, arEntryRegion.m_iTop, arEntryRegion.m_iRight, arEntryRegion.m_iBottom, {25, 145, 255});
      FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 3), m_ulFont, {245, 245, 245}, m_prgpEntries.first[i]);
    }

    iEntriesDisplayed++;
  }

  // thumb properties
  static constexpr FGUI::DIMENSION dmScrollBarThumbWidth = {8, 5};

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
  FGUI::RENDER.Rectangle(arScrollBarRegion.m_iLeft, arScrollBarRegion.m_iTop, arScrollBarRegion.m_iRight, arScrollBarRegion.m_iBottom, {235, 235, 235});

  if (m_prgpEntries.first.size() > 50)
  {
    FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumbWidth.m_iWidth, dmScrollBarThumbWidth.m_iHeight, {220, 223, 231});
  }
  else
  {
    FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumbWidth.m_iWidth, flCalculatedSize, {220, 223, 231});
  }
}

// ----------------------------------------------- //
void CListBox::Update()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  if (m_bIsDragging)
  {
    // calculate the amount of entries that will be drawn on the listbox
    int iCalculatedEntries = (m_dmSize.m_iHeight / m_iEntrySpacing);

    // cursor position
    FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

    if (FGUI::INPUT.GetKeyState(107))
    {
      // move thumb vertically
      ptCursorPos.m_iY -= ptAbsPosition.m_iY;

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

      // clamp position (don't let the user drag the scrollthumb if it reaches the "start" of the scrollbar area)
      if (m_iScrollThumbPosition <= 0)
      {
        m_iScrollThumbPosition = 0;
      }
    }
    else
    {
      m_bIsDragging = false;
    }
  }
}

// ----------------------------------------------- //
void CListBox::Input()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  // thumb properties
  static constexpr FGUI::DIMENSION dmScrollBarThumbWidth = {8, 5};

  // scrollbar area
  const FGUI::AREA &arScrollBarRegion = {((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15), arWidgetRegion.m_iTop, dmScrollBarThumbWidth.m_iWidth, (m_dmSize.m_iHeight - m_iEntrySpacing)};

  if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
  {
    m_bIsDragging = true;
  }

  // entries displayed
  int iEntriesDisplayed = 0;

  // calculate the amount of entries that will be drawn on the listbox
  int iCalculatedEntries = (m_dmSize.m_iHeight / m_iEntrySpacing);

  // listbox entries
  for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpEntries.first.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
  {
    // entry area
    const FGUI::AREA &arEntryRegion = {arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed), (arWidgetRegion.m_iRight - 15), m_iEntrySpacing};

    // select an entry
    if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
    {
      m_uiSelectedEntry = i;
    }

    if (m_uiSelectedEntry == i)
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

} // namespace FGUI