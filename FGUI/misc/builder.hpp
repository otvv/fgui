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
#include "../widgets/colorpicker.hpp"
#include "../widgets/combobox.hpp"
#include "../widgets/container.hpp"
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
    // @brief: add a new widget to the queue (to be spawned by the builder pattern)
    // @params: std::shared_ptr<FGUI::CWidgets> widget = widget that will be spawned
    // @note: NEEDS TO BE INITIALIZED FIRST!
    CBuilder &Widget(std::shared_ptr<FGUI::CWidgets> widget)
    {
      m_pTemporaryWidget = widget;

      return *this;
    };

    // @brief: set widget default title
    // @params: std::string title = widget title/name
    CBuilder &Title(std::string title)
    {
      m_pTemporaryWidget->SetTitle(title);

      return *this;
    };

    // @brief: set widget default position
    // @params: unsigned int x = left position (in pixels), unsigned y = top position (in pixels)
    CBuilder &Position(unsigned int x, unsigned int y)
    {
      m_pTemporaryWidget->SetPosition(x, y);

      return *this;
    };

    // @brief: sets the current widget tooltip
    // @params: std::string tooltip = widget custom tooltip
    CBuilder &Tooltip(std::string tooltip)
    {
      m_pTemporaryWidget->SetTooltip(tooltip);

      return *this;
    }

    // @brief: set widget default size
    // @params: unsigned int width = widget width, unsigned int height = widget height
    CBuilder &Size(unsigned int width, unsigned int height)
    {
      m_pTemporaryWidget->SetSize(width, height);

      return *this;
    };

    // @brief: set the widget default font
    // @params: std::string family = font family/name, int size = font size (tall), bool bold = make the font bold, int flags = font custom flags (shadow, outline, etc)
    CBuilder &Font(std::string family, int size, bool bold = false, int flags = 0x0)
    {
      m_pTemporaryWidget->SetFont(family, size, flags, bold);

      return *this;
    };

    // @brief: set the widget default font
    // @params: FGUI::WIDGET_FONT font = widget font struct (same as above)
    CBuilder &Font(FGUI::WIDGET_FONT font)
    {
      m_pTemporaryWidget->SetFont(font);

      return *this;
    };

    // @brief: change widget default flags
    // @params: FGUI::WIDGET_FLAG flags = widget custom flag (DRAWABLE, CLICKABLE, etc)
    CBuilder &Flags(FGUI::WIDGET_FLAG flags)
    {
      m_pTemporaryWidget->SetFlags(static_cast<int>(flags));

      return *this;
    };

    // @brief: container scrollbar state
    // @params: bool state = scrollbar state (enabled/disabled)
    CBuilder &ScrollBar(bool onoff)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CONTAINER))
      {
        std::reinterpret_pointer_cast<FGUI::CContainer>(m_pTemporaryWidget)->SetScrollBarState(onoff);
      }

      return *this;
    };

    // @brief: set the widget medium (controller)
    // @params: std::shared_ptr<FGUI::CWidgets> medium = widget that will "control" the current widget
    // int page = page to draw current widget according to the controller state (selected entry, value, state, etc)
    CBuilder &Medium(std::shared_ptr<FGUI::CWidgets> medium, int page)
    {
      m_pTemporaryWidget->SetMedium(medium, page);

      return *this;
    };

    // @brief: add a new color to the colorlist
    // @params: std::string identifier = color name, FGUI::COLOR color = default color, bool gradient = gradient status (enable/disable interpolation)
    CBuilder &Color(std::string identifier, FGUI::COLOR color, bool gradient = false)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
      {
        std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identifier, color, gradient);
      }

      return *this;
    };

    // @brief: add a new color to the colorlist
    // @params: std::string identifier = color name, std::uint8_t red = red color (0 - 255), std::uint8_t green = green color (0 - 255),
    // std::uint8_t blue = blue color (0 - 255), std::uint8_t alpha = color alpha (0 - 255), bool gradient = gradient status (enable/disable interpolation)
    CBuilder &Color(std::string identifier, std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255, bool gradient = false)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
      {
        std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identifier, {red, green, blue, alpha}, gradient);
      }

      return *this;
    };

    // @brief: set the default color of a widget (colorpicker/label)
    // @params: FGUI::COLOR color = widget color
    CBuilder &Color(FGUI::COLOR color)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
      {
        std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetColor(color);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORPICKER))
      {
        std::reinterpret_pointer_cast<FGUI::CColorPicker>(m_pTemporaryWidget)->SetColor(color);
      }

      return *this;
    };

    // @brief: set the default color of a widget (colorpicker/label)
    // @params: std::uint8_t red = red color (0 - 255), std::uint8_t green = green color (0 - 255),
    // std::uint8_t blue = blue color (0 - 255), std::uint8_t alpha = color alpha (0 - 255)
    CBuilder &Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
      {
        std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetColor({red, green, blue, alpha});
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORPICKER))
      {
        std::reinterpret_pointer_cast<FGUI::CColorPicker>(m_pTemporaryWidget)->SetColor({red, green, blue, alpha});
      }

      return *this;
    };

    // @brief: set the default key of a widget (keybinder and containers)
    // @params: unsigned int key = default key
    // @note: key = selected key on keybinders
    // key = toggle key on window containers
    CBuilder &Key(unsigned int key)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::KEYBINDER))
      {
        std::reinterpret_pointer_cast<FGUI::CKeyBinder>(m_pTemporaryWidget)->SetKey(key);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CONTAINER))
      {
        if (!m_pTemporaryWidget->GetParentWidget())
        {
          std::reinterpret_pointer_cast<FGUI::CContainer>(m_pTemporaryWidget)->SetKey(key);
        }
      }

      return *this;
    };

    // @brief: set the default text of a widget (textbox and labels)
    // @params: std::string text = default text
    CBuilder &Text(std::string text)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CTextBox>(m_pTemporaryWidget)->SetText(text);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
      {
        std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetTitle(text);
      }

      return *this;
    };

    // @brief: set the selected index of a widget (combobox, multibox and listbox)
    // @params: std::size_T index = selected index
    CBuilder &Index(std::size_t index)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LISTBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CListBox>(m_pTemporaryWidget)->SetIndex(index);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COMBOBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CComboBox>(m_pTemporaryWidget)->SetIndex(index);
      }

      return *this;
    };

    // @brief: set the default value of a widget (slider)
    // @params: float value = default value
    CBuilder &Value(float value)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
      {
        std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetValue(value);
      }

      return *this;
    };

    // @brief: set the default prefix of a slider
    // @params: std::string prefix = slider prefix (ms, %, °, etc)
    CBuilder &Prefix(std::string prefix)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
      {
        std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetPrefix(prefix);
      }

      return *this;
    };

    // @brief: set the widget state
    // @params: bool state = widget state
    // @note: state = set the checkbox state (checked or not)
    // state = set combobox dropdown list state (on/off)
    // state = set multibox dropdown list state (on/off)
    // state = set container state (on/off)
    CBuilder &State(bool state)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CHECKBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CCheckBox>(m_pTemporaryWidget)->SetState(state);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COMBOBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CComboBox>(m_pTemporaryWidget)->SetState(state);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->SetState(state);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CONTAINER))
      {
        if (!m_pTemporaryWidget->GetParentWidget())
        {
          std::reinterpret_pointer_cast<FGUI::CContainer>(m_pTemporaryWidget)->SetState(state);
        }
      }

      return *this;
    };

    // @brief: add a new entry to the widget (combobox, multibox and listbox)
    // @params: std::string title = entry title, unsigned int value = custom value
    CBuilder &Entry(std::string title, unsigned int value = 0)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COMBOBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CComboBox>(m_pTemporaryWidget)->AddEntry(title, value);
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->AddEntry(title, static_cast<bool>(value));
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LISTBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CListBox>(m_pTemporaryWidget)->AddEntry(title, value);
      }

      return *this;
    };

    // @brief: set the style of a widget (label and textbox)
    // @params: int style
    // @note: style = label style (normal, colored and link - FGUI::LABEL_STYLE)
    // style = textbox style (normal, uppercase and password (hidden) - FGUI::TEXTBOX_STYLE)
    CBuilder &Style(int style)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
      {
        std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetStyle(static_cast<FGUI::LABEL_STYLE>(style));
      }
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CTextBox>(m_pTemporaryWidget)->SetStyle(static_cast<FGUI::TEXTBOX_STYLE>(style));
      }

      return *this;
    };

    // @brief: add a callback to a widget
    // @params: std::function<void()> callback = function to call
    CBuilder &Callback(std::function<void()> callback)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COMBOBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CComboBox>(m_pTemporaryWidget)->AddCallback(callback);
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
      else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CONTAINER))
      {
        if (!m_pTemporaryWidget->GetParentWidget())
        {
          std::reinterpret_pointer_cast<FGUI::CContainer>(m_pTemporaryWidget)->AddCallback(callback);
        }
      }

      return *this;
    };

    // @brief: widget value range (sliders)
    // @params: float min = min value, float max = max value
    CBuilder &Range(float min, float max)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
      {
        std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetRange(min, max);
      }

      return *this;
    };

    // @brief: set the text length of textboxes
    // @params: unsigned int length = text max length
    CBuilder &Length(unsigned int length)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
      {
        std::reinterpret_pointer_cast<FGUI::CTextBox>(m_pTemporaryWidget)->SetLength(length);
      }

      return *this;
    };

    // @brief: adds a new tab button inside the tab panel
    // @params: std::string tab = tab name
    CBuilder &Tab(std::string tab)
    {
      if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TABS))
      {
        std::reinterpret_pointer_cast<FGUI::CTabs>(m_pTemporaryWidget)->AddTab(tab);
      }

      return *this;
    };

    // @brief: spawn widget inside a container
    // @params: std::shared_ptr<FGUI::CContainer> container = target container
    // padding = toggles widget padding on/off (defaults to true)
    CBuilder &SpawnIn(std::shared_ptr<FGUI::CContainer> container, bool padding = true)
    {
      container->AddWidget(m_pTemporaryWidget, padding);

      return *this;
    }

  private:
    std::shared_ptr<FGUI::CWidgets> m_pTemporaryWidget = nullptr;
  };

} // namespace FGUI

#endif // FGUI_BUILDER_HH