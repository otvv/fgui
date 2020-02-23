//
// FGUI - feature rich graphical user interface
//

// library includes
#include "slider.hpp"

namespace FGUI
{

// ----------------------------------------------- //
CSlider::CSlider()
{
  m_strTitle = "Slider";
  m_strPrefix = "";
  m_dmSize = {100, 2};
  m_dmSliderThumbSize = {8, 6};
  m_flValue = 0.f;
  m_rngBoundaries = {0.f, 0.f};
  m_ulFont = 0;
  m_nType = static_cast<int>(WIDGET_TYPE::SLIDER);
  m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
}

// ----------------------------------------------- //
void CSlider::SetValue(float value)
{
  m_flValue = value;
}

// ----------------------------------------------- //
float CSlider::GetValue()
{
  return m_flValue;
}

// ----------------------------------------------- //
void CSlider::SetRange(float min, float max)
{
  m_rngBoundaries.m_flMin = min;
  m_rngBoundaries.m_flMax = max;
}

// ----------------------------------------------- //
void CSlider::SetPrefix(const std::string &prefix)
{
  m_strPrefix = prefix;
}

// ----------------------------------------------- //
void CSlider::Geometry()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

  // widget's title text size
  const FGUI::DIMENSION &dmTitleTextSize = FGUI::RENDER.GetTextSize(m_ulFont, m_strTitle);

  // slider value text size
  const FGUI::DIMENSION &dmValueTextSize = FGUI::RENDER.GetTextSize(m_ulFont, std::to_string(static_cast<int>(m_flValue)) + " " + m_strPrefix);

  // slider position ratio
  float flRatio = (m_flValue - m_rngBoundaries.m_flMin) / (m_rngBoundaries.m_flMax - m_rngBoundaries.m_flMin);
  float flLocation = (flRatio * m_dmSize.m_iWidth);

  // slider body
  FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_dmSize.m_iWidth, m_dmSize.m_iHeight, {20, 50, 70});

  // slider thumb
  FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + flLocation), (arWidgetRegion.m_iTop - 2), m_dmSliderThumbSize.m_iWidth, m_dmSliderThumbSize.m_iHeight, {180, 25, 25});

  // slider label & value
  FGUI::RENDER.Text(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop - dmTitleTextSize.m_iHeight) - 2, m_ulFont, {0, 0, 0}, m_strTitle);
  FGUI::RENDER.Text((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - dmValueTextSize.m_iWidth, (arWidgetRegion.m_iTop - dmTitleTextSize.m_iHeight) - 2, m_ulFont, {0, 0, 0}, std::to_string(static_cast<int>(m_flValue)) + " " + m_strPrefix);
}

// ----------------------------------------------- //
void CSlider::Update()
{
  // widget's absolute position
  const FGUI::POINT &ptAbsPosition = GetAbsolutePosition();

  // cursor position
  const FGUI::POINT &ptCursorPos = FGUI::INPUT.GetCursorPos();

  // custom height in pixels from the "clickable" area
  static constexpr int iCustomHeight = 15;

  // widget's area
  const FGUI::AREA &arWidgetRegion = {ptAbsPosition.m_iX, ptAbsPosition.m_iY, m_dmSize.m_iWidth, iCustomHeight};

  if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
  {
    if (FGUI::INPUT.GetKeyPress(107))
    {
      m_bIsDragging = true;
    }
  }

  // if the user is dragging the slider
  if (m_bIsDragging)
  {
    if (FGUI::INPUT.GetKeyState(107))
    {
      float flXPosDelta = 0.f;
      float flRatio = 0.f;

      // change slider value based on mouse movement
      flXPosDelta = (ptCursorPos.m_iX - ptAbsPosition.m_iX);

      // clamp values
      if (flXPosDelta <= m_rngBoundaries.m_flMin)
      {
        flXPosDelta = m_rngBoundaries.m_flMin;
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
}

// ----------------------------------------------- //
void CSlider::Input()
{
}

} // namespace FGUI