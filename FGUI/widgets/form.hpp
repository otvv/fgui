//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_FORM_HH
#define FGUI_FORM_HH

// includes
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <vector>

// library includes
#include "../dependencies/aliases.hpp"
#include "../dependencies/definitions.hpp"
#include "tabs.hpp"

namespace FGUI
{

  class CTabs;
  class CGroupBox;
  class CWidgets;

  class CForm : public std::enable_shared_from_this<FGUI::CForm>
  {
    friend class FGUI::CWidgets;
    friend class FGUI::CGroupBox;
  public:
    // @brief: handles rendering of forms and widgets
    void Render();

    // @brief: set the form state (toggle on/off)
    // @params: bool onoff = form state
    void SetState(bool onoff);

    // @brief: get the form state (toggled or not)
    bool GetState();

    // @brief: add a new form into the container
    // @params: std::shared_ptr<FGUI::CForm> form = form instance (pointer)
    void AddForm(std::shared_ptr<FGUI::CForm> form);

    // @brief: add a new tab into the form
    // @params: std::shared_ptr<FGUI::CTabs> tab = tab instance (pointer)
    void AddTab(std::shared_ptr<FGUI::CTabs> tab);

    // @brief: adds a function callback for the form (it will call the function whenever the opens the form)
    // @params: std::function<void()> callback = function instance
    void AddCallback(std::function<void()> callback);

    // @brief: set the key that will toggle the form on and off
    // @params: unsigned int key_code = virtual key code
    void SetKey(unsigned int key_code);

    // @brief: set the default position of the form
    // @params: unsigned int x, unsigned int y = pixels coordinates (on the screen)
    void SetPosition(unsigned int x, unsigned int y);

    // @brief: set the default size of the form
    // @params: unsigned int width, unsigned int height = width and height of the menu in pixels
    void SetSize(unsigned int width, unsigned int height);

    // @brief: set the default size of the form
    // @params: FGUI::DIMENSION size = width and height of the menu in pixels
    void SetSize(FGUI::DIMENSION size);

    // @brief: set the default title of the form
    // @params: std::string title = default title of the form
    void SetTitle(std::string title);

    // @brief: adds a flag to the form
    // @params: form default/custom flags
    void SetFlags(int flags);

    // @brief: return the font toggle key
    int GetKey();

    // @brief: get the form's default title
    std::string GetTitle();

    // @brief: set the default font of the form
    // @params: std::string family = font family name, int size = font size, bool bold = make the font bold, int flags = font flags
    void SetFont(std::string family, int size, bool bold = false, int flags = 0x0);

    // @brief: set the default font of the form
    // @params: FGUI::WIDGET_FONT font = widget font struct
    void SetFont(FGUI::WIDGET_FONT font);

    // @brief: get the widget drawable area inside the form (this will set where the widgets will be drawned)
    FGUI::AREA GetWidgetArea();

    // @brief: make a widget be focused
    // @params: std::shared_ptr<FGUI::CWidgets> widget = widget instance (instance)
    void SetFocusedWidget(std::shared_ptr<FGUI::CWidgets> widget);

    // @brief: get the current focused widget
    std::shared_ptr<FGUI::CWidgets> GetFocusedWidget();

    // @brief: get the form's default font
    FGUI::FONT GetFont();

    // @brief: return true if the form has the flag we're looking for
    // @params: FGUI::WIDGET_FLAG flag = widget flag
    bool GetFlags(FGUI::WIDGET_FLAG flags);

    // @brief: get the current position of the form
    FGUI::POINT GetPosition();

    // @brief: get the form default size
    FGUI::DIMENSION GetSize();

  protected:
    // @brief: populate form geometry (draw form)
    void Geometry();

    // @brief: handle update operations on the form
    void Update();

    // @brief: handles form movement
    void Movement();

  private:
    bool m_bIsOpened;
    bool m_bIsDragging;
    bool m_bIsFocusingOnWidget;
    int m_iKey;
    int m_nFlags;
    std::function<void()> m_fnctCallback;
    std::shared_ptr<FGUI::CTabs> m_pSelectedTab;
    std::shared_ptr<FGUI::CWidgets> m_pFocusedWidget;
    std::vector<std::shared_ptr<FGUI::CTabs>> m_prgpTabs;
    std::vector<std::shared_ptr<FGUI::CForm>> m_prgpForms;
    std::string m_strTitle;
    FGUI::POINT m_ptPosition;
    FGUI::DIMENSION m_dmSize;
    FGUI::FONT m_ulFont;
  };

} // namespace FGUI

#endif // FGUI_FORM_HH