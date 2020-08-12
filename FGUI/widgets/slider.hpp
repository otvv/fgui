//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_SLIDER_HH
#define FGUI_SLIDER_HH

// library includes
#include "widgets.hpp"

namespace FGUI
{

  class CSlider : public FGUI::CWidgets
  {
  public:
    CSlider();

    // @brief: set a custom value for the slider
    // @params: float value = custom slider value (defaults to 0)
    void SetValue(float value);

    // @brief: get the current value from the slider
    float GetValue();

    // @brief: set the slider range (boundaries)
    // @params: float min = min value acceptable by the slider, float max = max value reachable by the slider
    void SetRange(float min, float max);

    // @brief: set a custom prefix for the slider
    // @params: std::string prefix = custom prefix (%, ms, °, etc)
    void SetPrefix(std::string prefix);

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
    float m_flValue;
    bool m_bIsDragging;
    std::string m_strPrefix;
    FGUI::RANGE m_rngBoundaries;
    FGUI::DIMENSION m_dmSliderThumbSize;
  };

} // namespace FGUI

#endif // FGUI_SLIDER_HH