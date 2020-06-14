//
// FGUI - feature rich graphical user interface
//

// library includes
#include "tabs.hpp"

namespace FGUI
{

void CTabs::SetTitle(std::string title)
{
  m_strTitle = title;
}

std::string CTabs::GetTitle()
{
  return m_strTitle;
}

void CTabs::AddWidget(std::shared_ptr<FGUI::CWidgets> widget)
{
  // assign parent form
  widget->m_pParentForm = m_pParentForm;

  // populate widget container
  m_prgpWidgets.emplace_back(widget);
}

void CTabs::SetFont(std::string family, unsigned int size, int flags, bool bold)
{
  FGUI::RENDER.CreateFont(m_ulFont, family, size, flags, bold);
}

void CTabs::SetFont(FGUI::WIDGET_FONT font)
{
  FGUI::RENDER.CreateFont(m_ulFont, font.m_strFamily, font.m_iSize, font.m_nFlags, font.m_bBold);
}

FGUI::FONT CTabs::GetFont()
{
  return m_ulFont;
}

} // namespace FGUI