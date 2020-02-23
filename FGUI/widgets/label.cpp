//
// FGUI - feature rich graphical user interface
//

// library includes
#include "label.hpp"

namespace FGUI
{

// ----------------------------------------------- //
CLabel::CLabel()
{
  m_strTitle = "Label";
  m_ulFont = 0;
  m_fnctCallback = nullptr;
  m_nType = static_cast<int>(WIDGET_TYPE::LABEL);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
}

// ----------------------------------------------- //
void CLabel::AddCallback(const std::function<void()> &callback)
{
  m_fnctCallback = callback;
}

// ----------------------------------------------- //
void CLabel::Geometry()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's title text size
  const FGUI::DIMENSION &dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, dmTitleTextSize.m_iWidth, dmTitleTextSize.m_iHeight};

  // label body
  FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_ulFont, {35, 35, 35}, m_strTitle); // todo: label types
}

// ----------------------------------------------- //
void CLabel::Update()
{
}

// ----------------------------------------------- //
void CLabel::Input()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
  {
    if (m_fnctCallback)
    {
      // call function
      m_fnctCallback();
    }
  }
}

} // namespace FGUI