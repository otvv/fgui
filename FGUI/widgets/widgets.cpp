//
// FGUI - feature rich graphical user interface
//

// library includes
#include "widgets.hpp"
#include "checkbox.hpp"
#include "combobox.hpp"
#include "container.hpp"
#include "listbox.hpp"
#include "slider.hpp"
#include "tabpanel.hpp"

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
    static FGUI::POINT ptTemporaryPosition = { 0, 0 };

    static constexpr int iContainerWindowHeaderSize = 35; // NOTE: feel free to change this

    if (!m_pParentWidget)
    {
      return { m_ptPosition.m_iX, m_ptPosition.m_iY };
    }

    ptTemporaryPosition = { (m_ptPosition.m_iX + m_pParentWidget->GetAbsolutePosition().m_iX),
                           (m_ptPosition.m_iY + m_pParentWidget->GetAbsolutePosition().m_iY) };

    // scrollbar movement
    if (m_pParentWidget->GetType() == static_cast<int>(WIDGET_TYPE::CONTAINER) && std::reinterpret_pointer_cast<FGUI::CContainer>(m_pParentWidget)->GetScrollBarState())
    {
      ptTemporaryPosition.m_iY -= std::reinterpret_pointer_cast<FGUI::CContainer>(m_pParentWidget)->GetScrollOffset();
    }

    // widget clickable area
    if (m_pParentWidget == GetWindowContainer())
    {
      ptTemporaryPosition.m_iX += 10;
      ptTemporaryPosition.m_iY += iContainerWindowHeaderSize;
    }

    else if (m_pParentWidget != GetWindowContainer())
    {
      ptTemporaryPosition.m_iX += 1;
      ptTemporaryPosition.m_iY += 1;
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

  void CWidgets::SetTooltip(std::string tooltip)
  {
    m_strTooltip = tooltip;
  }

  std::string CWidgets::GetTooltip()
  {
    return m_strTooltip;
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
    // if the widget doesn't have a medium or we have an invalid page keep it unlocked
    if (!m_pMediumWidget || m_iPage < 0)
    {
      return true;
    }

    // otherwise, it will lock them until certain conditions are met
    switch (m_pMediumWidget->GetType())
    {
      case static_cast<int>(WIDGET_TYPE::LISTBOX) :
      {
        return std::reinterpret_pointer_cast<FGUI::CListBox>(m_pMediumWidget)->GetIndex() == static_cast<std::size_t>(m_iPage);
      }
      case static_cast<int>(WIDGET_TYPE::CHECKBOX) :
      {
        return std::reinterpret_pointer_cast<FGUI::CCheckBox>(m_pMediumWidget)->GetState() == static_cast<bool>(m_iPage);
      }
      case static_cast<int>(WIDGET_TYPE::SLIDER) :
      {
        return std::reinterpret_pointer_cast<FGUI::CSlider>(m_pMediumWidget)->GetValue() == static_cast<float>(m_iPage);
      }
      case static_cast<int>(WIDGET_TYPE::COMBOBOX) :
      {
        return std::reinterpret_pointer_cast<FGUI::CComboBox>(m_pMediumWidget)->GetIndex() == static_cast<std::size_t>(m_iPage);
      }
      case static_cast<int>(WIDGET_TYPE::TABPANEL) :
      {
        return std::reinterpret_pointer_cast<FGUI::CTabPanel>(m_pMediumWidget)->GetIndex() == static_cast<std::size_t>(m_iPage);
      }
    }

    return false;
  }

  void CWidgets::SetMedium(std::shared_ptr<FGUI::CWidgets> medium, int page)
  {
    m_pMediumWidget = medium;
    m_iPage = page;
  }

  std::shared_ptr<FGUI::CWidgets> CWidgets::GetMedium()
  {
    return m_pMediumWidget;
  }

  int CWidgets::GetType()
  {
    return m_nType;
  }

  void CWidgets::SetFont(std::string family, unsigned int size, int flags, bool bold)
  {
    FGUI::RENDER.CreateFont(m_anyFont, family, size, flags, bold);
  }

  void CWidgets::SetFont(FGUI::WIDGET_FONT font)
  {
    FGUI::RENDER.CreateFont(m_anyFont, font.m_strFamily, font.m_iSize, font.m_nFlags, font.m_bBold);
  }

  FGUI::FONT CWidgets::GetFont()
  {
    return m_anyFont;
  }

  std::shared_ptr<FGUI::CWidgets> CWidgets::GetWindowContainer()
  {
    std::shared_ptr<FGUI::CWidgets> pCurrentContainer = shared_from_this();

    while (pCurrentContainer->m_pParentWidget)
    {
      pCurrentContainer = pCurrentContainer->m_pParentWidget;
    }

    return pCurrentContainer;
  }

  void CWidgets::SetParentWidget(std::shared_ptr<FGUI::CWidgets> parent)
  {
    m_pParentWidget = parent;
  }

  std::shared_ptr<FGUI::CWidgets> CWidgets::GetParentWidget()
  {
    return m_pParentWidget;
  }

} // namespace FGUI