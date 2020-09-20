//
// FGUI - feature rich graphical user interface
//

// library includes
#include "colorpicker.hpp"
#include "container.hpp"

namespace FGUI
{
  CColorPicker::CColorPicker()
  {
    m_strTitle = "";
    m_bIsOpened = false;
    m_dmSize = {20, 16};
    m_prRelativePos = {5.f, 5.f};
    m_clrDefault = {1, 1, 1};
    m_anyFont = 0;
    m_uiPixelation = 2;
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::COLORPICKER);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::FOCUSABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CColorPicker::SetColor(FGUI::COLOR color)
  {
    m_clrDefault = color;
  }

  FGUI::COLOR CColorPicker::GetColor()
  {
    return m_clrDefault;
  }

  void CColorPicker::SetPixelation(unsigned int pixelation)
  {
    m_uiPixelation = pixelation;
  }

  unsigned int CColorPicker::GetPixelation()
  {
    return m_uiPixelation;
  }

  void CColorPicker::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    // color picker button body
    FGUI::RENDER.Outline((arWidgetRegion.m_iLeft), (arWidgetRegion.m_iTop + 2), m_dmSize.m_iWidth, (m_dmSize.m_iHeight - 2), {220, 220, 220});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft) + 1, (arWidgetRegion.m_iTop + 3), (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 4), {195, 195, 195});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft) + 1, (arWidgetRegion.m_iTop + 3), (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 4), m_clrDefault);

    if (m_bIsOpened)
    {
      static constexpr FGUI::DIMENSION dmColorPickerSize = {135, 135};

      FGUI::AREA arColorPickerRegion = {(arWidgetRegion.m_iLeft + 25), arWidgetRegion.m_iTop, dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight};

      // color picker body
      FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom, {100, 100, 100});
      FGUI::RENDER.Outline(arColorPickerRegion.m_iLeft - 1, arColorPickerRegion.m_iTop - 1, (arColorPickerRegion.m_iRight + 3), (arColorPickerRegion.m_iBottom + 3), {220, 220, 220});
      FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, (arColorPickerRegion.m_iRight + 40), arColorPickerRegion.m_iBottom, {245, 245, 245});

      for (std::size_t i = 0; i < static_cast<unsigned int>(arColorPickerRegion.m_iBottom); i += GetPixelation())
      {
        // color hue
        FGUI::COLOR clrHue = FGUI::COLOR::HSBToRGB((i / 150.f), 1.f, 1.f);

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, (arColorPickerRegion.m_iTop + i), 10, GetPixelation(), clrHue);

        // color alpha
        FGUI::COLOR clrAlpha = FGUI::COLOR(m_clrDefault.m_ucRed, m_clrDefault.m_ucGreen, m_clrDefault.m_ucBlue, i / static_cast<float>(arColorPickerRegion.m_iBottom) * 255);

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30, (arColorPickerRegion.m_iTop + i), 10, GetPixelation(), clrAlpha);

        for (std::size_t j = 0; j < static_cast<unsigned int>(arColorPickerRegion.m_iRight); j += GetPixelation())
        {
          // color hsb
          FGUI::COLOR clrHSB = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_clrDefault), j / static_cast<float>(arColorPickerRegion.m_iRight), i / static_cast<float>(arColorPickerRegion.m_iBottom), m_clrDefault.m_ucAlpha);

          FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + j), (arColorPickerRegion.m_iTop + i), GetPixelation(), GetPixelation(), clrHSB);
        }
      }

      const int iClampedRelativePosX = std::clamp(static_cast<int>(m_prRelativePos.m_flX), 0, std::max(5, (arColorPickerRegion.m_iRight - 4)));
      const int iClampedRelativePosY = std::clamp(static_cast<int>(m_prRelativePos.m_flY), 0, std::max(5, (arColorPickerRegion.m_iBottom - 4)));

      // color hsb body
      FGUI::RENDER.Outline((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 1, (arColorPickerRegion.m_iTop + 1), 1, arColorPickerRegion.m_iBottom + 2, {220, 220, 220});
      FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + iClampedRelativePosX), (arColorPickerRegion.m_iTop + iClampedRelativePosY), 5, 5, {35, 35, 35});

      // hue bar body
      FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10) - 1, arColorPickerRegion.m_iTop - 1, (10 + 2), arColorPickerRegion.m_iBottom + 2, {220, 220, 220});
      FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 5), arColorPickerRegion.m_iTop + (arColorPickerRegion.m_iBottom * FGUI::COLOR::GetHue(m_clrDefault)), 3, 3, {35, 35, 35});

      // alpha bar body
      FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30) - 1, arColorPickerRegion.m_iTop - 1, (10 + 2), arColorPickerRegion.m_iBottom + 2, {220, 220, 220});
      FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 25), arColorPickerRegion.m_iTop + (arColorPickerRegion.m_iBottom * (m_clrDefault.m_ucAlpha / 255.f)), 3, 3, {35, 35, 35});
    }

    IGNORE_ARGS(status);
  }

  void CColorPicker::Update()
  {
    m_dmSize = {20, 15}; // this is required to keep the widget from being padded on groupboxes

    static constexpr FGUI::DIMENSION dmColorPickerSize = {135, 135};

    if (m_bIsOpened)
    {
      FGUI::AREA arColorPickerRegion = {(GetAbsolutePosition().m_iX + 25), GetAbsolutePosition().m_iY, dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight};
      FGUI::AREA arColorHSBRegion = {arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom};
      FGUI::AREA arColorHueRegion = {(arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, arColorPickerRegion.m_iTop, 10, arColorPickerRegion.m_iBottom};
      FGUI::AREA arColorAlphaRegion = {(arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30, arColorPickerRegion.m_iTop, 10, arColorPickerRegion.m_iBottom};

      // switches
      static bool bColorHSBSelected = false;
      static bool bColorHueSelected = false;
      static bool bColorAlphaSelected = false;

      FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

      if (FGUI::INPUT.IsKeyPressed(MOUSE_1))
      {
        bColorHSBSelected = FGUI::INPUT.IsCursorInArea(arColorHSBRegion);
        bColorHueSelected = FGUI::INPUT.IsCursorInArea(arColorHueRegion);
        bColorAlphaSelected = FGUI::INPUT.IsCursorInArea(arColorAlphaRegion);
      }
      else if (FGUI::INPUT.IsKeyReleased(MOUSE_1))
      {
        bColorHSBSelected = false;
        bColorHueSelected = false;
        bColorAlphaSelected = false;
      }

      if (bColorHSBSelected)
      {
        m_prRelativePos = {static_cast<float>(ptCursorPos.m_iX) - static_cast<float>(arColorHSBRegion.m_iLeft), static_cast<float>(ptCursorPos.m_iY) - static_cast<float>(arColorHSBRegion.m_iTop)};

        m_clrDefault = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_clrDefault), (m_prRelativePos.m_flX / arColorHSBRegion.m_iRight), (m_prRelativePos.m_flY / arColorHSBRegion.m_iBottom), m_clrDefault.m_ucAlpha);
      }
      else if (bColorHueSelected)
      {
        float flHue = (ptCursorPos.m_iY - arColorHueRegion.m_iTop) / 150.f;

        m_clrDefault = FGUI::COLOR::HSBToRGB(std::clamp(flHue, 0.f, 0.999f), 1.f, 1.f);
      }
      else if (bColorAlphaSelected)
      {
        float flAlpha = (static_cast<float>(ptCursorPos.m_iY - arColorAlphaRegion.m_iTop) / 150.f) * 255.f;

        m_clrDefault.m_ucAlpha = std::clamp(flAlpha, 0.f, 255.f);
      }

      // keep widget focused
      std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->SetFocusedWidget(shared_from_this());

      if (FGUI::INPUT.IsCursorInArea(arColorHueRegion))
      {
        // change cursor
        std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->SetCursor(CURSOR_STYLE::PIPETTE);
      }
    }
  }

  void CColorPicker::Input()
  {
    m_bIsOpened = !m_bIsOpened;
  }

  void CColorPicker::Save(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName]["red"] = m_clrDefault.m_ucRed;
    module[strFormatedWidgetName]["green"] = m_clrDefault.m_ucGreen;
    module[strFormatedWidgetName]["blue"] = m_clrDefault.m_ucBlue;
    module[strFormatedWidgetName]["alpha"] = m_clrDefault.m_ucAlpha;
  }

  void CColorPicker::Load(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    // change widget color to the one stored on file
    if (module.contains(strFormatedWidgetName))
    {
      m_clrDefault.m_ucRed = module[strFormatedWidgetName]["red"];
      m_clrDefault.m_ucGreen = module[strFormatedWidgetName]["green"];
      m_clrDefault.m_ucBlue = module[strFormatedWidgetName]["blue"];
      m_clrDefault.m_ucAlpha = module[strFormatedWidgetName]["alpha"];
    }
  }

  void CColorPicker::Tooltip()
  {
    if (m_strTooltip.length() > 1 && !m_bIsOpened)
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