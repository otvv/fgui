//
// FGUI - feature rich graphical user interface
//

// library includes
#include "widgets.hpp"
#include "listbox.hpp"
#include "multibox.hpp"
#include "checkbox.hpp"
#include "groupbox.hpp"
#include "slider.hpp"

namespace FGUI
{

void CWidgets::SetPosition(unsigned int x, unsigned int y)
{
  m_ptPosition.m_iX = x;
  m_ptPosition.m_iY = y;
}

FGUI::POINT CWidgets::GetPosition()
{
  return m_ptPosition;
}

FGUI::POINT CWidgets::GetAbsolutePosition()
{
  static FGUI::POINT ptTemporaryPosition = {0, 0};

  if (!m_pParentForm)
  {
    return {0, 0};
  }

  if (m_pParentForm)
  {
    // get the parent form's widget area
    FGUI::AREA arWidgetArea = m_pParentForm->GetWidgetArea();

    ptTemporaryPosition = { (m_ptPosition.m_iX + arWidgetArea.m_iLeft), (m_ptPosition.m_iY + arWidgetArea.m_iTop) };

    // scrolling
    if (m_pParentGroupBox && std::reinterpret_pointer_cast<FGUI::CGroupBox>(m_pParentGroupBox)->GetScrollbarState())
    {
      ptTemporaryPosition.m_iY -= std::reinterpret_pointer_cast<FGUI::CGroupBox>(m_pParentGroupBox)->GetScrollOffset();
    }
  }

  return ptTemporaryPosition;
}

void CWidgets::SetSize(unsigned int width, unsigned int height)
{
  m_dmSize.m_iWidth = width;
  m_dmSize.m_iHeight = height;
}

void CWidgets::SetSize(FGUI::DIMENSION size)
{
  m_dmSize.m_iWidth = size.m_iWidth;
  m_dmSize.m_iHeight = size.m_iHeight;
}

FGUI::DIMENSION CWidgets::GetSize()
{
  return m_dmSize;
}

void CWidgets::SetTitle(std::string title)
{
  m_strTitle = title;
}

std::string CWidgets::GetTitle()
{
  return m_strTitle;
}

void CWidgets::SetFlags(int flags)
{
  m_nFlags = flags;
}

bool CWidgets::GetFlags(FGUI::WIDGET_FLAG flags)
{
  if (m_nFlags & static_cast<int>(flags))
  {
    return true;
  }

  return false;
}

bool CWidgets::IsUnlocked()
{ 
  // if the parent form is closed or null, keep widgets locked
  if (!m_pParentForm || !m_pParentForm->GetState())
  {
    return false;
  }

  // if the widget doesn't have a medium or we have an invalid page keep it unlocked
  if (!m_pMedium || m_iPage < 0)
  {
    return true;
  }

  // otherwise, it will lock them until cetain conditions are met
  switch (m_pMedium->m_nType)
  {
  case static_cast<int>(WIDGET_TYPE::LISTBOX):
  {
    return std::reinterpret_pointer_cast<FGUI::CListBox>(m_pMedium)->GetIndex() == static_cast<std::size_t>(m_iPage);
  }
  case static_cast<int>(WIDGET_TYPE::CHECKBOX):
  {
    return std::reinterpret_pointer_cast<FGUI::CCheckBox>(m_pMedium)->GetState() == static_cast<bool>(m_iPage);
  }
  case static_cast<int>(WIDGET_TYPE::SLIDER) :
  {
    return std::reinterpret_pointer_cast<FGUI::CSlider>(m_pMedium)->GetValue() == static_cast<float>(m_iPage);
  }
  case static_cast<int>(WIDGET_TYPE::MULTIBOX):
  {
    if (std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pMedium)->GetStyle() == static_cast<int>(MULTIBOX_STYLE::NORMAL))
    {
      return std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pMedium)->GetIndex() == static_cast<std::size_t>(m_iPage);
    }
  }
  }

  return false;
}

std::shared_ptr<FGUI::CForm> CWidgets::GetParentForm()
{
  return m_pParentForm;
}

void CWidgets::SetMedium(std::shared_ptr<FGUI::CWidgets> medium, unsigned int page)
{
  m_pMedium = medium;
  m_iPage = page;
}

std::shared_ptr<FGUI::CWidgets> CWidgets::GetMedium()
{
  return m_pMedium;
}

unsigned int CWidgets::GetPage()
{
  return m_iPage;
}

int CWidgets::GetType()
{
  return m_nType;
}

void CWidgets::SetFont(std::string family, unsigned int size, bool bold, int flags)
{
  FGUI::RENDER.CreateFont(m_ulFont, family, size, flags, bold);
}

void CWidgets::SetFont(FGUI::WIDGET_FONT font)
{
  FGUI::RENDER.CreateFont(m_ulFont, font.m_strFamily, font.m_iSize, font.m_nFlags, font.m_bBold);
}

FGUI::FONT CWidgets::GetFont()
{
  return m_ulFont;
}

} // namespace FGUI