//
// FGUI - feature rich graphical user interface
//

// library includes
#include "slider.hpp"
#include "container.hpp"

namespace FGUI
{

  CSlider::CSlider()
  {
    m_strTitle = "Slider";
    m_strPrefix = "";
    m_dmSize = {100, 2};
    m_dmSliderThumbSize = {8, 6};
    m_flValue = 0.f;
    m_bIsDragging = false;
    m_rngBoundaries = {0.f, 0.f};
    m_anyFont = 0;
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::SLIDER);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CSlider::SetValue(float value)
  {
    m_flValue = value;
  }

  float CSlider::GetValue()
  {
    return m_flValue;
  }

  void CSlider::SetRange(float min, float max)
  {
    m_rngBoundaries.m_flMin = min;
    m_rngBoundaries.m_flMax = max;
  }

  void CSlider::SetPrefix(std::string prefix)
  {
    m_strPrefix = prefix;
  }

  void CSlider::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);
    FGUI::DIMENSION dmValueTextSize = FGUI::RENDER.GetTextSize(m_anyFont, std::to_string(static_cast<int>(m_flValue)) + " " + m_strPrefix);

    // slider position ratio
    float flRatio = (m_flValue - m_rngBoundaries.m_flMin) / (m_rngBoundaries.m_flMax - m_rngBoundaries.m_flMin);
    float flLocation = (flRatio * m_dmSize.m_iWidth);

    // slider body
    FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {20, 50, 70});

    // slider thumb
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + flLocation), (arWidgetRegion.m_iTop - 2), m_dmSliderThumbSize.m_iWidth, m_dmSliderThumbSize.m_iHeight, {180, 25, 25});

    // slider label & value
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop - dmTitleTextSize.m_iHeight) - 2, m_anyFont, {35, 35, 35}, m_strTitle);
    FGUI::RENDER.Text((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - dmValueTextSize.m_iWidth, (arWidgetRegion.m_iTop - dmTitleTextSize.m_iHeight) - 2, m_anyFont, {30, 30, 30}, std::to_string(static_cast<int>(m_flValue)) + (m_strPrefix.length() > 0 ? +" " + m_strPrefix : ""));

    IGNORE_ARGS(status);
  }

  void CSlider::Update()
  {
    // if the user is dragging the slider
    if (m_bIsDragging)
    {
      FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

      if (FGUI::INPUT.IsKeyHeld(MOUSE_1))
      {
        float flXPosDelta = 0.f;
        float flRatio = 0.f;

        // change slider value based on mouse movement
        flXPosDelta = (ptCursorPos.m_iX - GetAbsolutePosition().m_iX);

        // clamp thumb position
        if (flXPosDelta < 0.f)
        {
          flXPosDelta = 0.f;
        }
        else if (flXPosDelta >= m_dmSize.m_iWidth)
        {
          flXPosDelta = m_dmSize.m_iWidth;
        }

        // calculate slider ratio
        flRatio = flXPosDelta / static_cast<float>(m_dmSize.m_iWidth);

        // change slider value
        m_flValue = m_rngBoundaries.m_flMin + (m_rngBoundaries.m_flMax - m_rngBoundaries.m_flMin) * flRatio;
      }
      else
      {
        m_bIsDragging = false;
      }
    }

    // stop slider if another widget is being focused
    if (std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->GetFocusedWidget())
    {
      m_bIsDragging = false;
    }
  }

  void CSlider::Input()
  {
    m_bIsDragging = true;
  }

  void CSlider::Save(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName] = m_flValue;
  }

  void CSlider::Load(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    // change widget value to the one stored on file
    if (module.contains(strFormatedWidgetName))
    {
      m_flValue = module[strFormatedWidgetName];
    }
  }

  void CSlider::Tooltip()
  {
    if (m_strTooltip.length() > 1 && !m_bIsDragging)
    {
      FGUI::DIMENSION dmTooltipTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTooltip);

      FGUI::AREA arTooltipRegion = {(FGUI::INPUT.GetCursorPos().m_iX + 10), (FGUI::INPUT.GetCursorPos().m_iY + 10), (dmTooltipTextSize.m_iWidth + 10), (dmTooltipTextSize.m_iHeight + 10)};

      FGUI::RENDER.Outline(arTooltipRegion.m_iLeft, arTooltipRegion.m_iTop, arTooltipRegion.m_iRight, arTooltipRegion.m_iBottom, {180, 95, 95});
      FGUI::RENDER.Rectangle((arTooltipRegion.m_iLeft + 1), (arTooltipRegion.m_iTop + 1), (arTooltipRegion.m_iRight - 2), (arTooltipRegion.m_iBottom - 2), {225, 90, 75});
      FGUI::RENDER.Text(arTooltipRegion.m_iLeft + (arTooltipRegion.m_iRight / 2) - (dmTooltipTextSize.m_iWidth / 2),
                        arTooltipRegion.m_iTop + (arTooltipRegion.m_iBottom / 2) - (dmTooltipTextSize.m_iHeight / 2), m_anyFont, {245, 245, 245}, m_strTooltip);
    }
  }

} // namespace FGUI