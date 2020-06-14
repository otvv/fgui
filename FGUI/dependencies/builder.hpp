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
		// @brief: add a new widget to the queue (to be spawned by the builder pattern)
		// @args: std::shared_ptr<FGUI::CWidgets> widget = widget that will be spawned
		// @note: NEEDS TO BE INITIALIZED FIRST!
		CBuilder& Widget(std::shared_ptr<FGUI::CWidgets> widget)
		{
			m_pTemporaryWidget = widget;
			m_pTemporaryTab = nullptr;
			m_pTemporaryForm = nullptr;

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: add a new form to the queue (to be spawned by the builder pattern)
		// @args: std::shared_ptr<FGUI::CWidgets> widget = widget that will be spawned
		// @note: NEEDS TO BE INITIALIZED FIRST!
		CBuilder& Widget(std::shared_ptr<FGUI::CForm> form)
		{
			m_pTemporaryForm = form;
			m_pTemporaryWidget = nullptr;
			m_pTemporaryTab = nullptr;

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: add a new tab to the queue (to be spawned by the builder pattern)
		// @args: std::shared_ptr<FGUI::CWidgets> widget = widget that will be spawned
		// @note: NEEDS TO BE INITIALIZED FIRST!
		CBuilder& Widget(std::shared_ptr<FGUI::CTabs> tab)
		{
			m_pTemporaryTab = tab;
			m_pTemporaryWidget = nullptr;
			m_pTemporaryForm = nullptr;

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set widget default title
		// @args: std::string title = widget title/name
		CBuilder& Title(std::string title)
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

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set widget default position
		// @args: unsigned int x = left position (in pixels), unsigned y = top position (in pixels)
		CBuilder& Position(unsigned int x, unsigned int y)
		{
			if (!m_pTemporaryForm)
			{
				m_pTemporaryWidget->SetPosition(x, y);
			}
			else
			{
				m_pTemporaryForm->SetPosition(x, y);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set widget default size
		// @args: unsigned int width = widget width, unsigned int height = widget height
		CBuilder& Size(unsigned int width, unsigned int height)
		{
			if (!m_pTemporaryForm)
			{
				m_pTemporaryWidget->SetSize(width, height);
			}
			else
			{
				m_pTemporaryForm->SetSize(width, height);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the widget default font
		// @args: std::string family = font family/name, int size = font size (tall), bool bold = make the font bold, int flags = font custom flags (shadow, outline, etc)
		CBuilder& Font(std::string family, int size, bool bold = false, int flags = 0x0)
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

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the widget default font
		// @args: FGUI::WIDGET_FONT font = widget font struct (same as above)
		CBuilder& Font(FGUI::WIDGET_FONT font)
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

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: change widget default flags
		// @args: FGUI::WIDGET_FLAG flags = widget custom flag (DRAWABLE, CLICKABLE, etc)
		CBuilder& Flags(FGUI::WIDGET_FLAG flags)
		{
			if (!m_pTemporaryForm && !m_pTemporaryTab)
			{
				m_pTemporaryWidget->SetFlags(static_cast<int>(flags));
			}
			else if (!m_pTemporaryTab && m_pTemporaryForm)
			{
				m_pTemporaryForm->SetFlags(static_cast<int>(flags));
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: groupbox/multibox scrollbar state
		// @args: bool state = scrollbar state (enabled/disabled)
		CBuilder& ScrollBar(bool onoff)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::GROUPBOX))
			{
				std::reinterpret_pointer_cast<FGUI::CGroupBox>(m_pTemporaryWidget)->SetScrollbarState(onoff);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the widget medium (controller)
		// @args: std::shared_ptr<FGUI::CWidgets> medium = widget that will "control" the current widget
		// unsigned int page = page to draw current widget according to the controller state (selected entry, value, state, etc)
		CBuilder& Medium(std::shared_ptr<FGUI::CWidgets> medium, unsigned int page)
		{
			m_pTemporaryWidget->SetMedium(medium, page);

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: add a new color to the colorlist
		// @args: std::string identifier = color name, FGUI::COLOR color = default color, bool gradient = gradient status (enable/disable interpolation)
		CBuilder& Color(std::string identifier, FGUI::COLOR color, bool gradient = false)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
			{
				std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identifier, color, gradient);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: add a new color to the colorlist
		// @args: std::string identifier = color name, std::uint8_t red = red color (0 - 255), std::uint8_t green = green color (0 - 255), 
		// std::uint8_t blue = blue color (0 - 255), std::uint8_t alpha = color alpha (0 - 255), bool gradient = gradient status (enable/disable interpolation)
		CBuilder& Color(std::string identifier, std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255, bool gradient = false)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
			{
				std::reinterpret_pointer_cast<FGUI::CColorList>(m_pTemporaryWidget)->AddColor(identifier, { red, green, blue, alpha }, gradient);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the default color of a widget (colorpicker/label)
		// @args: FGUI::COLOR color = widget color
		CBuilder& Color(FGUI::COLOR color)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
			{
				std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetColor(color);
			}
			else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORPICKER))
			{
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the default color of a widget (colorpicker/label)
		// @args: std::uint8_t red = red color (0 - 255), std::uint8_t green = green color (0 - 255), 
		// std::uint8_t blue = blue color (0 - 255), std::uint8_t alpha = color alpha (0 - 255)
		CBuilder& Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
			{
				std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetColor({ red, green, blue, alpha });
			}
			else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::COLORPICKER))
			{
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the default key of a widget (keybinder and form)
		// @args: unsigned int key = default key
		// @note: key = selected key on keybinders
		// key = toggle key on forms/child forms
		CBuilder& Key(unsigned int key)
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

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the default text of a widget (textbox and labels)
		// @args: std::string text = default text
		CBuilder& Text(std::string text)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
			{
				std::reinterpret_pointer_cast<FGUI::CTextBox>(m_pTemporaryWidget)->SetText(text);
			}
			else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LABEL))
			{
				std::reinterpret_pointer_cast<FGUI::CLabel>(m_pTemporaryWidget)->SetTitle(text);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the selected index of a widget (multibox and listbox)
		// @args: std::size_T index = selected index
		CBuilder& Index(std::size_t index)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::LISTBOX))
			{
				std::reinterpret_pointer_cast<FGUI::CListBox>(m_pTemporaryWidget)->SetIndex(index);
			}
			else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
			{
				std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->SetIndex(index);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the default value of a widget (slider)
		// @args: float value = default value
		CBuilder& Value(float value)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
			{
				std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetValue(value);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the default prefix of a slider
		// @args: std::string prefix = slider prefix (ms, %, °, etc)
		CBuilder& Prefix(std::string prefix)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
			{
				std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetPrefix(prefix);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the widget state
		// @args: bool state = widget state (toggled on/off)
		// @note: state = set the checkbox state (checked or not)
		// state = set multibox dropdown list state (toggled on/off)
		// state = set the form state (on/off)
		CBuilder& State(bool state)
		{
			if (!m_pTemporaryForm)
			{
				if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::CHECKBOX))
				{
					std::reinterpret_pointer_cast<FGUI::CCheckBox>(m_pTemporaryWidget)->SetState(state);
				}
				else if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::MULTIBOX))
				{
					std::reinterpret_pointer_cast<FGUI::CMultiBox>(m_pTemporaryWidget)->SetState(state);
				}
			}
			else
			{
				m_pTemporaryForm->SetState(state);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: add a new entry to the widget (multibox and listbox)
		// @args: std::string title = entry title, unsigned int value = custom value
		CBuilder& Entry(std::string title, unsigned int value = 0)
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

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the style of a widget (multibox, label and textbox)
		// @args: int style
		// @note: style = multibox style (normal and multi - FGUI::MULTIBOX_STYLE)
		// style = label style (normal, colored and link - FGUI::LABEL_STYLE)
		// style = textbox style (normal, password and uppercase - FGUI::TEXTBOX_STYLE)
		CBuilder& Style(int style)
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

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: add a callback to a widget
		// @args: std::function<void()> callback = function to call
		CBuilder& Callback(std::function<void()> callback)
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

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: widget value range (sliders)
		// @args: float min = min value, float max = max value
		CBuilder& Range(float min, float max)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::SLIDER))
			{
				std::reinterpret_pointer_cast<FGUI::CSlider>(m_pTemporaryWidget)->SetRange(min, max);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: set the text length of textboxes
		// @args: unsigned int length = text max length 
		CBuilder& Length(unsigned int length)
		{
			if (m_pTemporaryWidget->GetType() == static_cast<int>(WIDGET_TYPE::TEXTBOX))
			{
				std::reinterpret_pointer_cast<FGUI::CTextBox>(m_pTemporaryWidget)->SetLength(length);
			}

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: spawn widget inside a groupbox
		// @args: std::shared_ptr<FGUI::CGroupBox> groupbox = groupbox that the widget will be spawned, std::shared_ptr<FGUI::CTabs> tab = tab that the groupbox is spawned, 
		// bool padding = enable/disable padding (enabled by default)
		CBuilder& Spawn(std::shared_ptr<FGUI::CGroupBox> groupbox, std::shared_ptr<FGUI::CTabs> tab, bool padding = true)
		{
			groupbox->AddWidget(m_pTemporaryWidget, tab, padding);

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: spawn widget inside a tab
		// @args: std::shared_ptr<FGUI::CTabs> tab = tab to spawn widget
		CBuilder& Spawn(std::shared_ptr<FGUI::CTabs> tab)
		{
			tab->AddWidget(m_pTemporaryWidget);

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: spawn tab inside a form
		// @args: std::shared_ptr<FGUI::CForm> form = form to spawn tab
		CBuilder& Spawn(std::shared_ptr<FGUI::CForm> form)
		{
			form->AddTab(m_pTemporaryTab);

			return const_cast<FGUI::CBuilder&>(*this);
		}

		// @brief: spawn child inside a parent form
		// @args: std::shared_ptr<FGUI::CForm> parent_form = parent form (main form), std::shared_ptr<FGUI::CForm> child_form = child form to spawn
		CBuilder& Spawn(std::shared_ptr<FGUI::CForm> parent_form, std::shared_ptr<FGUI::CForm> child_form)
		{
			parent_form->AddForm(child_form);

			return const_cast<FGUI::CBuilder&>(*this);
		}

	private:
		std::shared_ptr<FGUI::CWidgets> m_pTemporaryWidget = nullptr;
		std::shared_ptr<FGUI::CTabs> m_pTemporaryTab = nullptr;
		std::shared_ptr<FGUI::CForm> m_pTemporaryForm = nullptr;
	};

} // namespace FGUI

#endif // FGUI_BUILDER_HH