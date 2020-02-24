//
// FGUI - feature rich graphical user interface
//

// library includes
#include "groupbox.hpp"

namespace FGUI
{

// ----------------------------------------------- //
CGroupBox::CGroupBox()
{
  m_strTitle = "GroupBox";
  m_ulFont = 0;
  m_nType = static_cast<int>(WIDGET_TYPE::GROUPBOX);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE);
}

// ----------------------------------------------- //
void CGroupBox::AddWidget(const std::shared_ptr<FGUI::CWidgets> &widget, const std::shared_ptr<FGUI::CTabs> &tab, bool padding)
{
  // configure padding
  if (padding)
  {
    widget->SetSize(m_dmSize.m_iWidth - (widget->GetPosition().m_iX * 2), widget->GetSize().m_iHeight);
  }

  // set widget position
  widget->SetPosition((m_ptPosition.m_iX + widget->GetPosition().m_iX), (m_ptPosition.m_iY + widget->GetPosition().m_iY));

  // add widget inside the tab container
  tab->AddWidget(widget);
}

// ----------------------------------------------- //
void CGroupBox::Geometry()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  // widget's title text size
  const FGUI::DIMENSION &dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // groupbox body
  FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, 5, 1, {220, 220, 200}); // top1
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + dmTitleTextSize.m_iWidth) + 10, arWidgetRegion.m_iTop, (arWidgetRegion.m_iRight - dmTitleTextSize.m_iWidth) - 10, 1, {220, 220, 200}); // top2
  FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, 1, arWidgetRegion.m_iBottom, {220, 220, 220}); // left
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight), arWidgetRegion.m_iTop, 1, arWidgetRegion.m_iBottom, {220, 220, 220}); // right
  FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + arWidgetRegion.m_iBottom), arWidgetRegion.m_iRight, 1, {220, 220, 220}); // bottom
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {245, 245, 245}); // background

  // groupbox label
  FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop - (dmTitleTextSize.m_iHeight / 2), m_ulFont, {35, 35, 35}, m_strTitle);
}

// ----------------------------------------------- //
void CGroupBox::Update()
{
}

// ----------------------------------------------- //
void CGroupBox::Input()
{
}

} // namespace FGUI