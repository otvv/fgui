//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_COLORLIST_HH
#define FGUI_COLORLIST_HH

// includes
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CButton;
  class CCheckBox;
  class CSlider;

  using COLOR_INFO = struct SColorInfo_t
  {
    SColorInfo_t(std::string identificator, FGUI::COLOR color, bool gradient);

    std::string m_strIdentificator;
    FGUI::COLOR m_clrFirst;
    FGUI::COLOR m_clrSecond;
    bool m_bIsSecondColorAdded;

    std::shared_ptr<FGUI::CButton> m_pPlusButton;
    std::shared_ptr<FGUI::CButton> m_pMinusButton;
    std::shared_ptr<FGUI::CCheckBox> m_pGradientCheckBox;
    std::shared_ptr<FGUI::CSlider> m_pAlphaSlider;
  };

  class CColorList : public FGUI::CWidgets
  {
  public:
    CColorList();

    // @brief: adds a new color into the list
    // @params: std::string identificator = color identificator (label), FGUI::COLOR color = color, bool gradient = interpolation state
    void AddColor(std::string identificator, FGUI::COLOR color, bool gradient);

    // @brief: set a custom color and the gradient state of an entry on the list
    // @params: std::size_t index = entry index, FGUI::COLOR color = color, bool gradient = gradient state
    void SetColor(std::size_t index, FGUI::COLOR color, bool gradient);

    // @brief: returns the current color from a entry on the list
    // @params: std::size_t index = entry index
    FGUI::COLOR GetColor(std::size_t index);

    // @brief: set the pixelation of the color pallet
    // @params: unsigned int pixelation = pixelation amount
    void SetPixelation(unsigned int pixelation);

    // @brief: returns the current pixelation of the color pallet
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
    std::size_t m_uiSelectedEntry;
    int m_iEntrySpacing;
    unsigned int m_uiPixelation;
    bool m_bIsDraggingThumb;
    int m_iScrollThumbPosition;
    FGUI::PRECISION m_prRelativePos;
    std::vector<FGUI::COLOR_INFO> m_prgpColorInfo;
  };

} // namespace FGUI

#endif // FGUI_COLORLIST_hH