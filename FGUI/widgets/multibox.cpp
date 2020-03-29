//
// FGUI - feature rich graphical user interface
//

// library includes
#include "multibox.hpp"

namespace FGUI
{

// ----------------------------------------------- //
CMultiBox::CMultiBox()
{
  m_strTitle = "MultiBox";
  m_ulFont = 0;
  m_dmSize = {150, 20};
  m_dmBackupSize = {m_dmSize};
  m_iEntrySpacing = 20;
  m_uiSelectedEntry = 0;
  m_fnctCallback = nullptr;
  m_prgpNormalEntries = {};
  m_prgpMultiEntries = {};
  m_bIsOpened = false;
  m_nStyle = static_cast<int>(MULTIBOX_STYLE::NORMAL);
  m_nType = static_cast<int>(WIDGET_TYPE::MULTIBOX);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::FOCUSABLE);
}

// ----------------------------------------------- //
void CMultiBox::SetState(bool onoff)
{
  m_bIsOpened = onoff;
}

// ----------------------------------------------- //
bool CMultiBox::GetState()
{
  return m_bIsOpened;
}

// ----------------------------------------------- //
void CMultiBox::SetIndex(std::size_t index)
{
  m_uiSelectedEntry = index;
}

// ----------------------------------------------- //
std::size_t CMultiBox::GetIndex()
{
  return m_uiSelectedEntry;
}

// ----------------------------------------------- //
void CMultiBox::SetValue(std::size_t index, unsigned int value)
{
  if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::NORMAL))
  {
    m_prgpNormalEntries.second[index] = value;
  }

  else if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::MULTI))
  {
    m_prgpMultiEntries.second[index] = value;
  }
}

// ----------------------------------------------- //
std::size_t CMultiBox::GetValue(std::size_t index)
{
  if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::NORMAL))
  {
    return m_prgpNormalEntries.second[m_uiSelectedEntry];
  }

  else if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::MULTI))
  {
    return m_prgpMultiEntries.second[index];
  }

  return {};
}

// ----------------------------------------------- //
std::pair<std::vector<std::string>, std::vector<bool>> CMultiBox::GetMultiEntryInfo()
{
  return m_prgpMultiEntries;
}

// ----------------------------------------------- //
void CMultiBox::SetStyle(const FGUI::MULTIBOX_STYLE &style)
{
  m_nStyle = static_cast<int>(style);
}

// ----------------------------------------------- //
int CMultiBox::GetStyle()
{
  return m_nStyle;
}

// ----------------------------------------------- //
void CMultiBox::AddEntry(const std::string &name, unsigned int value)
{
  if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::NORMAL))
  {
    m_prgpNormalEntries.first.emplace_back(name);
    m_prgpNormalEntries.second.emplace_back(value);
  }

  else if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::MULTI))
  {
    m_prgpMultiEntries.first.emplace_back(name);
    m_prgpMultiEntries.second.emplace_back(value);
  }
}

// ----------------------------------------------- //
void CMultiBox::AddCallback(const std::function<void()> &callback)
{
  m_fnctCallback = callback;
}

// ----------------------------------------------- //
void CMultiBox::Geometry()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmBackupSize.m_iHeight};

  // widget's title text size
  const FGUI::DIMENSION &dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // multibox body
  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion) || m_bIsOpened)
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
  FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_strTitle + ":");

  if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::NORMAL))
  {
    // draw current selected entry
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_prgpNormalEntries.first[m_uiSelectedEntry]);

    if (m_bIsOpened)
    {
      // dropdown list body
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21), arWidgetRegion.m_iRight, (m_prgpNormalEntries.first.size() * m_iEntrySpacing), {121, 180, 209});
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 21) + 1, (arWidgetRegion.m_iRight - 2), (m_prgpNormalEntries.first.size() * m_iEntrySpacing) - 2, {255, 255, 255});

      for (std::size_t i = 0; i < m_prgpNormalEntries.first.size(); i++)
      {
        // entry area
        const FGUI::AREA &arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing};

        // check if the user is hovering/have selected an entry
        if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_uiSelectedEntry == i)
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, arEntryRegion.m_iTop, arEntryRegion.m_iRight - 2, arEntryRegion.m_iBottom, {25, 145, 255});
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_ulFont, {255, 255, 255}, m_prgpNormalEntries.first[i]);
        }
        else
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom), arEntryRegion.m_iRight - 1, 1, {205, 205, 205});
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_ulFont, {0, 0, 0}, m_prgpNormalEntries.first[i]);
        }
      }
    }
  }

  else if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::MULTI))
  {
    // string format (this needs to be initialized as an empty string)
    std::string strMultiString = "";

    for (std::size_t i = 0; i < m_prgpMultiEntries.first.size(); ++i)
    {
      // switches
      bool bHasReachedLength = strMultiString.length() > 15;
      bool bIsFirstItem = strMultiString.length() <= 0;

      if (m_prgpMultiEntries.second[i] && !bHasReachedLength)
      {
        if (!m_prgpMultiEntries.first[i].empty())
        {
          if (!bIsFirstItem)
          {
            strMultiString.append(", ");
          }

          strMultiString.append(m_prgpMultiEntries.first[i]);
        }
      }

      else if (bHasReachedLength && !bIsFirstItem)
      {
        strMultiString.append(" ...");

        break;
      }
    }

    if (strMultiString.length() <= 0)
    {
      strMultiString.assign("None");
    }

    // draw current selected entry
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, strMultiString);

    if (m_bIsOpened)
    {
      // dropdown list body
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21), arWidgetRegion.m_iRight, (m_prgpMultiEntries.first.size() * m_iEntrySpacing), {121, 180, 209});
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 21) + 1, (arWidgetRegion.m_iRight - 2), (m_prgpMultiEntries.first.size() * m_iEntrySpacing) - 2, {255, 255, 255});

      for (std::size_t i = 0; i < m_prgpMultiEntries.first.size(); i++)
      {
        // entry area
        const FGUI::AREA &arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing};

        // check if the user is hovering/have selected an entry
        if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_prgpMultiEntries.second[i])
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, arEntryRegion.m_iTop, arEntryRegion.m_iRight - 2, arEntryRegion.m_iBottom, {25, 145, 255});
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_ulFont, {255, 255, 255}, m_prgpMultiEntries.first[i]);
        }
        else
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom), arEntryRegion.m_iRight - 1, 1, {205, 205, 205});
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_ulFont, {0, 0, 0}, m_prgpMultiEntries.first[i]);
        }
      }
    }
  }

  // multibox dropdown arrow body
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 8, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 1, 8, 1, {20, 20, 20});
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 7, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 2, 6, 1, {20, 20, 20});
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 6, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 3, 4, 1, {20, 20, 20});
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 5, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 4, 2, 1, {20, 20, 20});
}

// ----------------------------------------------- //
void CMultiBox::Update()
{
  if (m_bIsOpened)
  {
    if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::NORMAL))
    {
      // close dropdown list if the user clicks on something else
      if (GetParentForm()->GetFocusedWidget() != shared_from_this())
      {
        m_bIsOpened = false;
      }

      m_dmSize.m_iHeight = m_iEntrySpacing + (m_prgpNormalEntries.first.size() * m_iEntrySpacing) + 2;
    }

    else if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::MULTI))
    {
      // close dropdown list if the user clicks on something else
      if (GetParentForm()->GetFocusedWidget() != shared_from_this())
      {
        GetParentForm()->SetFocusedWidget(shared_from_this());
      }

      // widget's absolute position
      const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

      // widget's area
      const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

      // close dropdown if the user clicks on something else
      if (!FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        if (FGUI::INPUT.GetKeyPress(107))
        {
          m_bIsOpened = false;
        }
      }

      m_dmSize.m_iHeight = m_iEntrySpacing + (m_prgpMultiEntries.first.size() * m_iEntrySpacing) + 2;
    }
  }
  else
  {
    // restore widget size
    m_dmSize.m_iHeight = m_dmBackupSize.m_iHeight;
  }
}

// ----------------------------------------------- //
void CMultiBox::Input()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmBackupSize.m_iHeight};

  // toggle dropdown list on and off
  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
  {
    m_bIsOpened = !m_bIsOpened;
  }

  if (m_bIsOpened)
  {
    if (!FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::NORMAL))
      {
        for (std::size_t i = 0; i < m_prgpNormalEntries.first.size(); i++)
        {
          // entry area
          const FGUI::AREA &arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing};

          if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
          {
            // select an entry
            m_uiSelectedEntry = i;

            if (m_uiSelectedEntry == i)
            {
              if (m_fnctCallback)
              {
                // call function
                m_fnctCallback();
              }
            }
          }
        }
      }

      else if (m_nStyle == static_cast<int>(MULTIBOX_STYLE::MULTI))
      {
        for (std::size_t i = 0; i < m_prgpMultiEntries.first.size(); i++)
        {
          // entry area
          const FGUI::AREA &arEntryRegion = {arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing};

          if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
          {
            // select an entry
            m_prgpMultiEntries.second[i] = !m_prgpMultiEntries.second[i];
          }
        }
      }
    }
  }
}

} // namespace FGUI