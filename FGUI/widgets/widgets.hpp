//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_WIDGETS_HH
#define FGUI_WIDGETS_HH

// includes
#include <memory>
#include <string>
#include <fstream>
#include <exception>

// library internal includes
#include "../internal/aliases.hpp"
#include "../internal/definitions.hpp"

// external dependencies
#include "../dependencies/external/json.hpp"

namespace FGUI
{
  class CContainer;

  class CWidgets : public std::enable_shared_from_this<FGUI::CWidgets>
  {
    friend class FGUI::CContainer;
  public:
    // @brief: set the default position of the widget
    // @params: unsigned int x, unsigned int y = pixels coordinates (on the screen)
    void SetPosition(unsigned int x, unsigned int y);

    // @brief: get the default position of the widget
    FGUI::POINT GetPosition();

    // @brief: get the widget's absolute position
    FGUI::POINT GetAbsolutePosition();

    // @brief: set the default size of the widget
    // @params: unsigned int width, unsigned int height = width and height of the menu in pixels
    void SetSize(unsigned int width, unsigned int height);

    // @brief: set the default size of the widget
    // @params: FGUI::DIMENSION size = width and height of the menu in pixels
    void SetSize(FGUI::DIMENSION size);

    // @brief: get the widget default size
    FGUI::DIMENSION GetSize();

    // @brief: set the default title of the widget
    // @params: std::string title = default title of the widget
    void SetTitle(std::string title);

    // @brief: get the widget's default title
    std::string GetTitle();

    // @brief: adds a new tooltip to the widget
    // @params: std::string tooltio = widget brief description
    void SetTooltip(std::string tooltip);

    // @brief: get the widget's current tooltip
    std::string GetTooltip();

    // @brief: set the widget flags
    // @params: int flags = widget default/custom flag
    void SetFlags(int flags);

    // @brief: return true if the widget has the flag we're looking for
    // @params: FGUI::WIDGET_FLAG flag = widget flag
    bool GetFlags(FGUI::WIDGET_FLAG flags);

    // @brief: checks if the widget is unlocked (can be drawned)
    bool IsUnlocked();

    // @brief: set the widget that will behave like a medium (controller) for the parent widget
    // @params: std::shared_ptr<FGUI::CWidgets> medium = controller (element that will control the other)
    // int page = widget page
    void SetMedium(std::shared_ptr<FGUI::CWidgets> medium, int page);

    // @brief: return an instance of the current medium (controller widget)
    std::shared_ptr<FGUI::CWidgets> GetMedium();

    // @brief: return the widget type (family)
    int GetType();

    // @brief: set the default font of the widget
    // @params: std::string family = font family name, unsigned int size = font size, int flags = font flags, bool bold = make the font bold
    void SetFont(std::string family, unsigned int size, int flags, bool bold);

    // @brief: set the default font of the widget
    // @params: FGUI::WIDGET_FONT font = widget font struct
    void SetFont(FGUI::WIDGET_FONT font);

    // @brief: get the widget's default font
    FGUI::FONT GetFont();

    // @brief: get the container behaving like a window
    std::shared_ptr<FGUI::CWidgets> GetWindowContainer();

    // @brief: set the parent widget of the current widget
    // @params: std::shared_ptr<FGUI::CWidgets> parent = parent widget
    void SetParentWidget(std::shared_ptr<FGUI::CWidgets> parent);

    // @brief: get the current parent widget
    std::shared_ptr<FGUI::CWidgets> GetParentWidget();

  protected:
    // @brief: populate widget geometry (draw widget)
    virtual void Geometry() = 0;

    // @brief: handle update operations on the widget
    virtual void Update() = 0;

    // @brief: handle input inside the widget
    virtual void Input() = 0;

    // @brief: save the widget state
    // @params: nlohmann::json module = json module
    virtual void Save(nlohmann::json& module) = 0;

    // @brief: load the widget state
    // @params: nlohmann::json module = json module
    virtual void Load(nlohmann::json& module) = 0;

    // @brief: handle widget tooltips
    virtual void Tooltip() = 0;

    int m_nFlags;
    int m_nType;
    int m_iPage;
    std::shared_ptr<FGUI::CWidgets> m_pParentWidget;
    std::shared_ptr<FGUI::CWidgets> m_pMediumWidget;
    std::string m_strTooltip;
    std::string m_strTitle;
    FGUI::FONT m_anyFont;
    FGUI::DIMENSION m_dmSize;
    FGUI::POINT m_ptPosition;
  };

} // namespace FGUI

#endif // FGUI_WIDGETS_HH