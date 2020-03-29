//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_BUILDER_HH
#define FGUI_BUILDER_HH

// includes
#include <memory>
#include <utility>
#include <functional>

// library includes
#include "../widgets/button.hpp"
#include "../widgets/checkbox.hpp"
#include "../widgets/colorlist.hpp"
#include "../widgets/form.hpp"
#include "../widgets/groupbox.hpp"
#include "../widgets/keybinder.hpp"
#include "../widgets/label.hpp"
#include "../widgets/listbox.hpp"
#include "../widgets/multibox.hpp"
#include "../widgets/slider.hpp"
#include "../widgets/tabs.hpp"
#include "../widgets/textbox.hpp"
#include "../widgets/widgets.hpp"

namespace FGUI
{

class CBuilder
{
public:
  CBuilder &Widget(const std::shared_ptr<FGUI::CWidgets> &widget)
  {
    m_pTemporaryWidget = std::move(widget);
    m_pTemporaryTab = nullptr;
    m_pTemporaryForm = nullptr;

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Widget(const std::shared_ptr<FGUI::CForm> &form)
  {
    m_pTemporaryForm = std::move(form);
    m_pTemporaryWidget = nullptr;
    m_pTemporaryTab = nullptr;

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Widget(const std::shared_ptr<FGUI::CTabs> &tab)
  {
    m_pTemporaryTab = std::move(tab);
    m_pTemporaryWidget = nullptr;
    m_pTemporaryForm = nullptr;

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Title(const std::string &title)
  {
    if (!m_pTemporaryTab && !m_pTemporaryForm)
    {
      m_pTemporaryWidget->SetTitle(title);
    }
    else if (!m_pTemporaryTab && m_pTemporaryForm)
    {
      m_pTemporaryForm->SetTitle(title);
    }
    else
    {
      m_pTemporaryTab->SetTitle(title);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Position(int x, int y)
  {
    if (!m_pTemporaryForm)
    {
      m_pTemporaryWidget->SetPosition(x, y);
    }
    else
    {
      m_pTemporaryForm->SetPosition(x, y);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Size(int width, int height)
  {
    if (!m_pTemporaryForm)
    {
      m_pTemporaryWidget->SetSize(width, height);
    }
    else
    {
      m_pTemporaryForm->SetSize(width, height);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Font(const std::string &family, int size, bool bold = false, int flags = 0x0)
  {
    if (!m_pTemporaryTab && !m_pTemporaryForm)
    {
      m_pTemporaryWidget->SetFont(family, size, bold, flags);
    }
    else if (!m_pTemporaryTab && m_pTemporaryForm)
    {
      m_pTemporaryForm->SetFont(family, size, bold, flags);
    }
    else
    {
      m_pTemporaryTab->SetFont(family, size, bold, flags);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Font(const FGUI::WIDGET_FONT &font)
  {
    if (!m_pTemporaryTab && !m_pTemporaryForm)
    {
      m_pTemporaryWidget->SetFont(font);
    }
    else if (!m_pTemporaryTab && m_pTemporaryForm)
    {
      m_pTemporaryForm->SetFont(font);
    }
    else
    {
      m_pTemporaryTab->SetFont(font);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Medium(const std::shared_ptr<FGUI::CWidgets> &medium, unsigned int page)
  {
    m_pTemporaryWidget->SetMedium(medium, page);

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Color(const std::string &identifier, const FGUI::COLOR &color, bool gradient = false) const noexcept
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
    {
      std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identifier, color, gradient);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

    CBuilder &Color(const std::string &identifier, std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255, bool gradient = false) const noexcept
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
    {
      std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identifier, {red, green, blue, alpha}, gradient);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Color(const FGUI::COLOR &color) const noexcept
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
    {
      std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetColor(color);
    }

    else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORPICKER))
    {
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

    CBuilder &Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255) const noexcept
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
    {
      std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetColor({red, green, blue, alpha});
    }

    else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORPICKER))
    {
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Key(int key = 0)
  {
    if (!m_pTemporaryForm)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::KEYBINDER))
      {
        std::reinterpret_pointer_cast<FGUI::CKeyBinder>(m_pTemporaryWidget)->SetKey(key);
      }
    }
    else
    {
      m_pTemporaryForm->SetKey(key);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Text(const std::string &text)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
    {
      std::reinterpret_pointer_cast<FGUI::CTextBox>(m_pTemporaryWidget)->SetText(text);
    }

    else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
    {
      std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetTitle(text);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Index(std::size_t index)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
    {
      std::reinterpret_pointer_cast<FGUI::CListBox>(m_pTemporaryWidget)->SetIndex(index);
    }

    else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
    {
      std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->SetIndex(index);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Value(float value)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
    {
      std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetValue(value);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Prefix(const std::string &prefix)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
    {
      std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetPrefix(prefix);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &State(bool onoff)
  {
    if (!m_pTemporaryForm)
    {

      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CHECKBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CCheckBox>(m_pTemporaryWidget)->SetState(onoff);
      }

      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->SetState(onoff);
      }
    }
    else
    {
      m_pTemporaryForm->SetState(onoff);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Color(const std::string &identificator, const FGUI::COLOR &color, bool gradient = false)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
    {
      std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identificator, color, gradient);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Color(const std::string &identificator, std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255, bool gradient = false)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
    {
      std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identificator, {red, green, blue, alpha}, gradient);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Entry(const std::string &title, unsigned int value = 0)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
    {
      if (std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->GetStyle() == static_cast<int>(MULTIBOX_STYLE::NORMAL))
      {
        std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->AddEntry(title, value);
      }

      else if (std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->GetStyle() == static_cast<int>(MULTIBOX_STYLE::MULTI))
      {
        std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->AddEntry(title, static_cast<bool>(value));
      }
    }

    else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LISTBOX))
    {
      std::reinterpret_pointer_cast<FGUI::CListBox>(m_pTemporaryWidget)->AddEntry(title, value);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Style(int style)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
    {
      std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->SetStyle(static_cast<FGUI::MULTIBOX_STYLE>(style));
    }

    else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
    {
      std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetStyle(static_cast<FGUI::LABEL_STYLE>(style));
    }

    else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
    {
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Callback(const std::function<void()> &callback)
  {
    if (!m_pTemporaryForm && m_pTemporaryWidget)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->AddCallback(callback);
      }

      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
      {
        std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->AddCallback(callback);
      }

      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CHECKBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CCheckBox>(m_pTemporaryWidget)->AddCallback(callback);
      }

      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::BUTTON))
      {
        std::reinterpret_pointer_cast<FGUI::CButton>(m_pTemporaryWidget)->AddCallback(callback);
      }

      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LISTBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CListBox>(m_pTemporaryWidget)->AddCallback(callback);
      }
    }
    else
    {
      m_pTemporaryForm->AddCallback(callback);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Range(float min = 0.f, float max = 0.f)
  {
    if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
    {
      std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetRange(min, max);
    }

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Spawn(const std::shared_ptr<FGUI::CGroupBox> &groupbox, const std::shared_ptr<FGUI::CTabs> &tab, bool padding = true)
  {
    groupbox->AddWidget(m_pTemporaryWidget, tab, padding);

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Spawn(const std::shared_ptr<FGUI::CTabs> &tab)
  {
    tab->AddWidget(m_pTemporaryWidget);

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Spawn(const std::shared_ptr<FGUI::CForm> &form)
  {
    form->AddTab(m_pTemporaryTab);

    return const_cast<FGUI::CBuilder &>(*this);
  }

  CBuilder &Spawn(const std::shared_ptr<FGUI::CForm> &parent_form, const std::shared_ptr<FGUI::CForm> &child_form)
  {
    parent_form->AddForm(child_form);

    return const_cast<FGUI::CBuilder &>(*this);
  }

private:
  std::shared_ptr<FGUI::CWidgets> m_pTemporaryWidget = nullptr;
  std::shared_ptr<FGUI::CTabs> m_pTemporaryTab = nullptr;
  std::shared_ptr<FGUI::CForm> m_pTemporaryForm = nullptr;
};

} // namespace FGUI

#endif // FGUI_BUILDER_HH