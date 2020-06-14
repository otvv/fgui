//
// FGUI - feature rich graphical user interface
//

// library includes
#include "groupbox.hpp"

namespace FGUI
{

CGroupBox::CGroupBox()
{
  m_strTitle = "GroupBox";
  m_ulFont = 0;
  m_bScrollBarState = false;
  m_iWidgetPositionOffset = 0;
  m_nType = static_cast<int>(WIDGET_TYPE::GROUPBOX);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE);
}

void CGroupBox::AddWidget(std::shared_ptr<FGUI::CWidgets> widget, std::shared_ptr<FGUI::CTabs> tab, bool padding)
{
  // configure padding
  if (padding)
  {
    widget->SetSize(m_dmSize.m_iWidth - (widget->GetPosition().m_iX * 2), widget->GetSize().m_iHeight);
  }

  // set widget position
  widget->SetPosition((m_ptPosition.m_iX + widget->GetPosition().m_iX), (m_ptPosition.m_iY + widget->GetPosition().m_iY));

  // set the parent groupbox of the widget
  widget->m_pParentGroupBox = shared_from_this();

  // add widget inside the tab container
  tab->AddWidget(widget);

  // populate temporary container with all widgets inside the current groupbox
  m_prgpGroupBoxWidgets.emplace_back(widget);
}

void CGroupBox::SetScrollbarState(bool state)
{
  m_bScrollBarState = state;
}

bool CGroupBox::GetScrollbarState()
{
  return m_bScrollBarState;
}

int CGroupBox::GetScrollOffset()
{
  return m_iWidgetPositionOffset;
}

void CGroupBox::Geometry()
{
  // widget's area
  FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  // widget's title text size
  FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // groupbox body
  FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, 5, 1, {220, 220, 200}); // top1
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + dmTitleTextSize.m_iWidth) + 10, arWidgetRegion.m_iTop, (arWidgetRegion.m_iRight - dmTitleTextSize.m_iWidth) - 10, 1, {220, 220, 200}); // top2
  FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, 1, arWidgetRegion.m_iBottom, {220, 220, 220}); // left
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight), arWidgetRegion.m_iTop, 1, arWidgetRegion.m_iBottom, {220, 220, 220}); // right
  FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + arWidgetRegion.m_iBottom), arWidgetRegion.m_iRight, 1, {220, 220, 220}); // bottom
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {245, 245, 245}); // background

  // groupbox label
  FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_strTitle);

  if (m_bScrollBarState)
  {
    // scrollbar area
    FGUI::AREA arScrollBarRegion = { (arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, arWidgetRegion.m_iTop, 15, m_dmSize.m_iHeight };

    static constexpr FGUI::DIMENSION dmScrollBarThumbWidth = { 8, 5 };

    // scrollbar thumb size
    float flScrollbarThumbSize = (m_dmSize.m_iHeight / static_cast<float>(m_prgpGroupBoxWidgets.back()->GetPosition().m_iY)) * static_cast<float>((m_dmSize.m_iHeight - m_prgpGroupBoxWidgets.back()->GetSize().m_iHeight));

    // calculate the scrollbar slider position
    float flScrollbarThumbPosition = (m_dmSize.m_iHeight - flScrollbarThumbSize) * static_cast<float>(m_iWidgetPositionOffset / 
      static_cast<float>((m_prgpGroupBoxWidgets.back()->GetPosition().m_iY + m_prgpGroupBoxWidgets.back()->GetSize().m_iHeight) - (m_dmSize.m_iHeight - 5)));

    // scrollbar body
    FGUI::RENDER.Rectangle(arScrollBarRegion.m_iLeft, arScrollBarRegion.m_iTop, arScrollBarRegion.m_iRight, arScrollBarRegion.m_iBottom, { 235, 235, 235 });

    // scrollbar thumb
    FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flScrollbarThumbPosition) + 5, dmScrollBarThumbWidth.m_iWidth, flScrollbarThumbSize, { 220, 223, 231 });
  }
}

void CGroupBox::Update()
{
  // widget's area
  FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

  // scrollbar area
  FGUI::AREA arScrollBarRegion = { (arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, arWidgetRegion.m_iTop, 15, m_dmSize.m_iHeight };

  // check if the user is hovering the groupbox
  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
  {
    for (const std::shared_ptr<FGUI::CWidgets>& pWidgets : m_pParentForm->m_pSelectedTab->m_prgpWidgets)
    {
      // current groupbox
      std::shared_ptr<FGUI::CGroupBox> pCurrentGroupBox = nullptr;

      if (pWidgets->GetType() != static_cast<int>(WIDGET_TYPE::GROUPBOX))
      {
        pCurrentGroupBox = pWidgets->m_pParentGroupBox ? std::reinterpret_pointer_cast<FGUI::CGroupBox>(pWidgets->m_pParentGroupBox) : nullptr;
      }

      if (pCurrentGroupBox)
      {
        if (pCurrentGroupBox->GetScrollbarState())
        {
          static bool bIsDraggingThumb = false;

          if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
          {
            if (FGUI::INPUT.GetKeyPress(MOUSE_1))
            {
              bIsDraggingThumb = true;
            }
          }

          if (bIsDraggingThumb)
          {
            FGUI::POINT ptCursorPosDelta = FGUI::INPUT.GetCursorPosDelta();

            if (FGUI::INPUT.GetKeyState(MOUSE_1))
            {
              m_iWidgetPositionOffset += (ptCursorPosDelta.m_iY / 7);
            }
            else
            {
              bIsDraggingThumb = false;
            }

            m_pParentForm->SetFocusedWidget(nullptr);
          }

          // clamp scrolling
          m_iWidgetPositionOffset = std::clamp(m_iWidgetPositionOffset, 0, std::max(0, ((m_prgpGroupBoxWidgets.back()->GetPosition().m_iY + m_prgpGroupBoxWidgets.back()->GetSize().m_iHeight)) - (m_dmSize.m_iHeight + 5)));
        }
      }
    }
  }
}

void CGroupBox::Input()
{
}

} // namespace FGUI