//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_WIDGETS_HH
#define FGUI_WIDGETS_HH

// includes
#include <memory>
#include <string>

// library includes
#include "form.hpp"
#include "../dependencies/aliases.hpp"
#include "../dependencies/definitions.hpp"

namespace FGUI
{

class CForm;
class CTabs;

class CWidgets : public std::enable_shared_from_this<FGUI::CWidgets>
{
  friend class FGUI::CForm;
  friend class FGUI::CTabs;
public:
  // @brief: set the default position of the widget
  // @params: unsigned int x, unsigned int y = pixels coordinates (on the screen)
  void SetPosition(unsigned int x, unsigned int y);

  // @brief: get the default position of the widget
  const FGUI::POINT &GetPosition();

  // @brief: get the widget's absolute position
  const FGUI::POINT GetAbsolutePosition();

  // @brief: set the default size of the widget
  // @params: unsigned int width, unsigned int height = width and height of the menu in pixels
  void SetSize(unsigned int width, unsigned int height);

  // @brief: get the widget default size
  const FGUI::DIMENSION &GetSize();

  // @brief: set the default title of the widget
  // @params: std::string title = default title of the widget
  void SetTitle(const std::string &title);

  // @brief: get the widget's default title
  const std::string &GetTitle();

  // @brief: set the widget flags
  // @params: int flags = widget default/custom flags
  void SetFlags(int flags);

  // @brief: return true if the widget has the flag we're looking for
  // @params: FGUI::WIDGET_FLAG flag = widget flag
  bool GetFlag(const FGUI::WIDGET_FLAG &flags);

  // @brief: checks if the widget is unlocked (can be drawned)
  bool IsUnlocked();

  // @brief: return an instance of the widget's parent form
  const std::shared_ptr<FGUI::CForm> &GetParentForm();

  // @brief: set the widget that will behave like a medium (controller) for the parent widget
  // @params: std::shared_ptr<FGUI::CWidgets> medium = controller (element that will control the other)
  // unsigned int page = widget page
  void SetMedium(const std::shared_ptr<FGUI::CWidgets> &medium, unsigned int page);

  // @brief: return an instance of the current medium (controller widget)
  const std::shared_ptr<FGUI::CWidgets> &GetMedium();

  // @brief: get current widget page
  int GetPage();

  // @brief: return the widget type (family)
  int GetType();

  // @brief: set the default font of the widget
  // @params: std::string family = font family name, int size = font size, bool bold = make the font bold,  int flags = font flags
  void SetFont(const std::string &family, int size, bool bold = false, int flags = 0x0);

  // @brief: set the default font of the widget
  // @params: FGUI::WIDGET_FONT font = widget font struct
  void SetFont(const FGUI::WIDGET_FONT &font);

  // @brief: get the widget's default font
  FGUI::FONT GetFont();

protected:

  // @brief: populate widget geometry (draw widget)
  virtual void Geometry() = 0;

  // @brief: handle update operations on the widget
  virtual void Update() = 0;

  // @brief: handle input inside the widget
  virtual void Input() = 0;

protected:
  int m_nFlags;
  int m_nType;
  int m_iPage;
  std::shared_ptr<FGUI::CForm> m_pParentForm;
  std::shared_ptr<FGUI::CWidgets> m_pMedium;
  std::string m_strTitle;
  FGUI::FONT m_ulFont;
  FGUI::DIMENSION m_dmSize;
  FGUI::POINT m_ptPosition;
};

} // namespace FGUI

#endif // FGUI_WIDGETS_HH