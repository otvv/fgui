//
// FGUI - feature rich graphical user interface
//

// library includes
#include "tabs.hpp"

namespace FGUI
{

// ----------------------------------------------- //
void CTabs::SetTitle(const std::string &title)
{
  m_strTitle = title;
}

// ----------------------------------------------- //
const std::string &CTabs::GetTitle()
{
  return m_strTitle;
}

// ----------------------------------------------- //
void CTabs::AddWidget(const std::shared_ptr<FGUI::CWidgets> &widget)
{
  // assign parent form
  widget->m_pParentForm = m_pParentForm;

  // populate widget container
  m_prgpWidgets.emplace_back(std::move(widget));
}

// ----------------------------------------------- //
void CTabs::SetFont(const std::string &family, int size, int flags, bool bold)
{
  FGUI::RENDER.CreateFont(m_ulFont, family, size, flags, bold);
}

// ----------------------------------------------- //
void CTabs::SetFont(const FGUI::WIDGET_FONT &font)
{
  FGUI::RENDER.CreateFont(m_ulFont, font.m_strFamily, font.m_iSize, font.m_iFlags, font.m_bBold);
}

// ----------------------------------------------- //
FGUI::FONT CTabs::GetFont()
{
  return m_ulFont;
}

} // namespace FGUI