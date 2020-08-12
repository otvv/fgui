//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_COLORPICKER_HH
#define FGUI_COLORPICKER_HH

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CColorPicker : public FGUI::CWidgets
  {
  public:
    CColorPicker();

    // @brief: sets the default color
    // @args: FGUI::COLOR color = default color
    void SetColor(FGUI::COLOR color);

    // @brief: returns the current color
    FGUI::COLOR GetColor();

    // @brief: set the pixelation of the color picker
    // @params: unsigned int pixelation = pixelation amount
    void SetPixelation(unsigned int pixelation);

    // @brief: returns the current pixelation of the color picker
    unsigned int GetPixelation();

    // @brief: populate widget geometry (draw widget)
    void Geometry() override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

    // @brief: save the widget state
    // @params: nlohmann::json module = json module
    void Save(nlohmann::json& module) override;

    // @brief: load the widget state
    // @params: nlohmann::json module = json module
    void Load(nlohmann::json& module) override;

    // @brief: handle widget tooltips
    void Tooltip() override;

  private:
    FGUI::COLOR m_clrDefault;
    unsigned int m_uiPixelation;
    bool m_bIsOpened;
    FGUI::PRECISION m_prRelativePos;
  };

} // namespace FGUI

#endif // FGUI_COLORPICKER_HH