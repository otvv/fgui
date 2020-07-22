//
// FGUI - feature rich graphical user interface
//

// library includes
#include "colorlist.hpp"

// additional includes
#include "button.hpp"
#include "slider.hpp"
#include "checkbox.hpp"

namespace FGUI
{

  SColorInfo_t::SColorInfo_t(std::string identificator, FGUI::COLOR color, bool gradient)
  {
    m_strIdentificator = identificator;
    m_bIsSecondColorAdded = false;
    m_clrFirst = color;
    m_clrSecond = {1, 1, 1};

    // initialize widgets
    m_pPlusButton = std::make_shared<FGUI::CButton>();
    m_pMinusButton = std::make_shared<FGUI::CButton>();
    m_pGradientCheckBox = std::make_shared<FGUI::CCheckBox>();
    m_pAlphaSlider = std::make_shared<FGUI::CSlider>();

    // setup widgets
    m_pPlusButton->SetTitle("+");
    m_pPlusButton->SetSize(16, 16);
    m_pPlusButton->SetTooltip("Add a new color into the sequence.");
    m_pPlusButton->SetFont("Tahoma", 13, 0x0, false);

    m_pMinusButton->SetTitle("-");
    m_pMinusButton->SetSize(16, 16);
    m_pMinusButton->SetTooltip("Remove a color from the sequence.");
    m_pMinusButton->SetFont("Tahoma", 13, 0x0, false);

    m_pGradientCheckBox->SetTitle("Gradient");
    m_pGradientCheckBox->SetTooltip("Enables color interpolation (gradient).");
    m_pGradientCheckBox->SetFont("Tahoma", 13, 0x0, false);
    m_pGradientCheckBox->SetState(gradient);

    m_pAlphaSlider->SetTitle("alpha");
    m_pAlphaSlider->SetValue((m_clrFirst.m_ucAlpha / 2.55f));
    m_pAlphaSlider->SetRange(0.f, (255 / 2.55f));
    m_pAlphaSlider->SetSize(150, 2);
    m_pAlphaSlider->SetTooltip("Color alpha (transparency).");
    m_pAlphaSlider->SetFont("Tahoma", 13, 0x0, false);
    m_pAlphaSlider->SetPrefix("%");
  }

  CColorList::CColorList()
  {
    m_strTitle = "ColorList";
    m_iEntrySpacing = 20;
    m_prRelativePos = {5.f, 5.f};
    m_iScrollThumbPosition = 0;
    m_uiSelectedEntry = false;
    m_bIsDraggingThumb = false;
    m_anyFont = 0;
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::COLORLIST);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CColorList::AddColor(std::string identificator, FGUI::COLOR color, bool gradient)
  {
    m_prgpColorInfo.emplace_back(identificator, color, gradient);
  }

  void CColorList::SetColor(std::size_t index, FGUI::COLOR color, bool gradient)
  {
    m_prgpColorInfo[index].m_clrFirst = color;
    m_prgpColorInfo[index].m_pGradientCheckBox->SetState(gradient);
  }

  FGUI::COLOR CColorList::GetColor(std::size_t index)
  {
    if (m_prgpColorInfo[index].m_pGradientCheckBox->GetState())
    {
      static float flFirstTimeFraction = 0.f;

      flFirstTimeFraction = std::fminf(flFirstTimeFraction + 0.0005f, 1.f);

      if (flFirstTimeFraction >= 1.f)
      {
        static float flSecondTimeFraction = 0.f;

        // ghetto way to return back to the first color
        flSecondTimeFraction = std::fminf(flSecondTimeFraction + 0.0005f, 1.f);

        if (flSecondTimeFraction >= 1.f)
        {
          flSecondTimeFraction = 0.f;
          flFirstTimeFraction = 0.f;
        }

        return FGUI::COLOR::Interpolate(m_prgpColorInfo[index].m_clrSecond, m_prgpColorInfo[index].m_clrFirst, flSecondTimeFraction);
      }

      return FGUI::COLOR::Interpolate(m_prgpColorInfo[index].m_clrFirst, m_prgpColorInfo[index].m_clrSecond, flFirstTimeFraction);
    }

    return m_prgpColorInfo[index].m_clrFirst;
  }

  void CColorList::Geometry()
  {
    // color gap
    static constexpr int iColorPickerGap = 250;

    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, (m_dmSize.m_iWidth - iColorPickerGap), m_dmSize.m_iHeight};
    FGUI::AREA arScrollBarRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, (arWidgetRegion.m_iTop + 20), 15, (m_dmSize.m_iHeight - 20)};

    // entries displayed
    int iEntriesDisplayed = 0;

    // calculate the amount of entries (colors) that will be drawn inside the colorlist
    int iCalculatedEntries = ((m_dmSize.m_iHeight - 20) / m_iEntrySpacing);

    // colorlist body
    FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop - 5), arWidgetRegion.m_iRight, 1, {220, 220, 220});
    FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 17), arWidgetRegion.m_iRight, 1, {220, 220, 220});
    FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 20) - 1, (arWidgetRegion.m_iRight + 1), (arWidgetRegion.m_iBottom - 20) + 1, {220, 220, 220});
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 20) + 1, arWidgetRegion.m_iRight - 2, (arWidgetRegion.m_iBottom - 20) - 2, {255, 255, 255});

    // colorlist entries
    for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpColorInfo.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
    {
      FGUI::AREA arEntryRegion = {arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed) + 20, (arWidgetRegion.m_iRight - arScrollBarRegion.m_iRight), m_iEntrySpacing};

      // check if the user is hovers or selects something on the colorlist
      if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_uiSelectedEntry == i)
      {
        FGUI::RENDER.Rectangle((arEntryRegion.m_iLeft + 1), arEntryRegion.m_iTop, (arWidgetRegion.m_iRight - 2), arEntryRegion.m_iBottom, {235, 235, 255});
      }

      static constexpr FGUI::DIMENSION dmColorButtonSize = {20, 16};

      // color button body
      FGUI::RENDER.Outline((arEntryRegion.m_iLeft + 95), (arEntryRegion.m_iTop + 2), dmColorButtonSize.m_iWidth, (dmColorButtonSize.m_iHeight - 2), {220, 220, 220});
      FGUI::RENDER.Rectangle((arEntryRegion.m_iLeft + 95) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), {195, 195, 195});
      FGUI::RENDER.Rectangle((arEntryRegion.m_iLeft + 95) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), m_prgpColorInfo[i].m_clrFirst);

      // if the user adds a second color sequence
      if (m_prgpColorInfo[i].m_bIsSecondColorAdded)
      {
        FGUI::RENDER.Outline((arEntryRegion.m_iLeft + 95) + 25, (arEntryRegion.m_iTop + 2), dmColorButtonSize.m_iWidth, (dmColorButtonSize.m_iHeight - 2), {220, 220, 220});
        FGUI::RENDER.Rectangle(((arEntryRegion.m_iLeft + 95) + 25) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), {195, 195, 195});
        FGUI::RENDER.Rectangle(((arEntryRegion.m_iLeft + 95) + 25) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), m_prgpColorInfo[i].m_clrSecond);
      }

      // color separator
      FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom) - 1, arWidgetRegion.m_iRight, 1, {205, 205, 205});

      // color button label
      FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 2), m_anyFont, {35, 35, 35}, m_prgpColorInfo[i].m_strIdentificator);

      iEntriesDisplayed++;
    }

    // color picker size
    static constexpr FGUI::DIMENSION dmColorPickerSize = {150, 150};

    FGUI::AREA arColorPickerRegion = {(GetAbsolutePosition().m_iX + (m_dmSize.m_iWidth - iColorPickerGap) + 10), (GetAbsolutePosition().m_iY + 20), dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight};

    static constexpr int iPixelation = 2; // TODO: make a function for this

    // color picker body
    FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom, {100, 100, 100});

    for (std::size_t i = 0; i < static_cast<unsigned int>(arColorPickerRegion.m_iBottom); i += iPixelation)
    {
      // color hue
      FGUI::COLOR clrHue = FGUI::COLOR::HSBToRGB((i / 150.f), 1.f, 1.f);

      FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, (arColorPickerRegion.m_iTop + i), 15, iPixelation, clrHue);

      for (std::size_t j = 0; j < static_cast<unsigned int>(arColorPickerRegion.m_iRight); j += iPixelation)
      {
        // color hsb
        FGUI::COLOR clrHSB = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst), j / static_cast<float>(arColorPickerRegion.m_iRight), i / static_cast<float>(arColorPickerRegion.m_iBottom), m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha);

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + j), (arColorPickerRegion.m_iTop + i), iPixelation, iPixelation, clrHSB);
      }
    }

    const int iClampedRelativePosX = std::clamp(static_cast<int>(m_prRelativePos.m_flX), 0, std::max(10, arColorPickerRegion.m_iRight));
    const int iClampedRelativePosY = std::clamp(static_cast<int>(m_prRelativePos.m_flY), 0, std::max(10, arColorPickerRegion.m_iBottom));

    // color hsb body
    FGUI::RENDER.Outline(arColorPickerRegion.m_iLeft - 1, arColorPickerRegion.m_iTop - 1, arColorPickerRegion.m_iRight + 2, arColorPickerRegion.m_iBottom + 2, {220, 220, 220});
    FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + iClampedRelativePosX) - 6, (arColorPickerRegion.m_iTop + iClampedRelativePosY) - 6, 10, 10, {35, 35, 35});

    // hue bar body
    FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10) - 1, arColorPickerRegion.m_iTop - 1, (15 + 2), arColorPickerRegion.m_iBottom + 2, {220, 220, 220});
    FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 5), arColorPickerRegion.m_iTop + (arColorPickerRegion.m_iBottom * FGUI::COLOR::GetHue(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst)), 3, 3, {35, 35, 35});

    // r, g, b color text size
    FGUI::DIMENSION dmColorRedTextSize = FGUI::RENDER.GetTextSize(m_anyFont, std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucRed));
    FGUI::DIMENSION dmColorGreenTextSize = FGUI::RENDER.GetTextSize(m_anyFont, std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucGreen));
    FGUI::DIMENSION dmColorBlueTextSize = FGUI::RENDER.GetTextSize(m_anyFont, std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucBlue));

    // color preview body
    FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35) - 1, arColorPickerRegion.m_iTop - 1, (45 + 2), (45 + 2), {220, 220, 220});
    FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35), arColorPickerRegion.m_iTop, 45, 45, m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst);

    // color preview value
    FGUI::RENDER.Text((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35, (arColorPickerRegion.m_iTop - 20) + (arColorPickerRegion.m_iBottom / 2) - (dmColorRedTextSize.m_iHeight / 2) + 10, m_anyFont, {35, 35, 35}, "R: " + std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucRed));
    FGUI::RENDER.Text((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35, (arColorPickerRegion.m_iTop - 20) + (arColorPickerRegion.m_iBottom / 2) - (dmColorGreenTextSize.m_iHeight / 2) + 30, m_anyFont, {35, 35, 35}, "G: " + std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucGreen));
    FGUI::RENDER.Text((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35, (arColorPickerRegion.m_iTop - 20) + (arColorPickerRegion.m_iBottom / 2) - (dmColorBlueTextSize.m_iHeight / 2) + 50, m_anyFont, {35, 35, 35}, "B: " + std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucBlue));

    // sequence label
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, {35, 35, 35}, "Sequences");

    // plus button
    FGUI::POINT ptPlusButtonPos = {(GetAbsolutePosition().m_iX + 70), (GetAbsolutePosition().m_iY - 1)};
    m_prgpColorInfo[m_uiSelectedEntry].m_pPlusButton->SetPosition(ptPlusButtonPos.m_iX, ptPlusButtonPos.m_iY);
    m_prgpColorInfo[m_uiSelectedEntry].m_pPlusButton->Geometry();

    // minus button
    FGUI::POINT ptMinusButtonPos = {(GetAbsolutePosition().m_iX + 90), (GetAbsolutePosition().m_iY - 1)};
    m_prgpColorInfo[m_uiSelectedEntry].m_pMinusButton->SetPosition(ptMinusButtonPos.m_iX, ptMinusButtonPos.m_iY);
    m_prgpColorInfo[m_uiSelectedEntry].m_pMinusButton->Geometry();

    // gradient checkbox
    FGUI::POINT ptCheckboxPos = {(GetAbsolutePosition().m_iX + 115), (GetAbsolutePosition().m_iY - 1)};
    m_prgpColorInfo[m_uiSelectedEntry].m_pGradientCheckBox->SetPosition(ptCheckboxPos.m_iX, ptCheckboxPos.m_iY);
    m_prgpColorInfo[m_uiSelectedEntry].m_pGradientCheckBox->Geometry();

    // alpha slider
    FGUI::POINT ptSliderPos = {arColorPickerRegion.m_iLeft, (arColorPickerRegion.m_iTop + arColorPickerRegion.m_iBottom) + 40};
    m_prgpColorInfo[m_uiSelectedEntry].m_pAlphaSlider->SetPosition(ptSliderPos.m_iX, ptSliderPos.m_iY);
    m_prgpColorInfo[m_uiSelectedEntry].m_pAlphaSlider->Geometry();

    static constexpr FGUI::DIMENSION dmScrollBarThumbWidth = {8, 5};

    // calculate thumb position
    float flCalculatedPosition = static_cast<float>(m_iScrollThumbPosition) / static_cast<float>(m_prgpColorInfo.size());

    if (flCalculatedPosition >= 1.f)
    {
      flCalculatedPosition = 1.f;
    }

    flCalculatedPosition *= ((m_dmSize.m_iHeight - 20) - m_iEntrySpacing) - 10;

    // calculate thumb size
    float flCalculatedSize = static_cast<float>(iCalculatedEntries) / static_cast<float>(m_prgpColorInfo.size());

    if (flCalculatedSize > 1.f)
    {
      flCalculatedSize = 1.f;
    }

    flCalculatedSize *= ((m_dmSize.m_iHeight - 20) - m_iEntrySpacing);

    // scrollbar body
    FGUI::RENDER.Rectangle(arScrollBarRegion.m_iLeft, arScrollBarRegion.m_iTop, arScrollBarRegion.m_iRight, arScrollBarRegion.m_iBottom, {235, 235, 235});

    if (m_prgpColorInfo.size() > 50)
    {
      FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumbWidth.m_iWidth, dmScrollBarThumbWidth.m_iHeight, {220, 223, 231});
    }
    else
    {
      FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumbWidth.m_iWidth, flCalculatedSize, {220, 223, 231});
    }
  }

  void CColorList::Update()
  {
    if (m_bIsDraggingThumb)
    {
      // calculate the amount of entries that will be drawn on the colorlist
      int iCalculatedEntries = ((m_dmSize.m_iHeight - 20) / m_iEntrySpacing);

      FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

      if (FGUI::INPUT.IsKeyHeld(MOUSE_1))
      {
        // move thumb vertically
        ptCursorPos.m_iY -= (GetAbsolutePosition().m_iY + 20);

        // ratio of how many visible to how many are hidden
        float flVisibleRatio = static_cast<float>(iCalculatedEntries) / static_cast<float>(m_prgpColorInfo.size());
        flVisibleRatio *= ((m_dmSize.m_iHeight - 20) - m_iEntrySpacing);

        // calculate height delta
        float flHeightDelta = static_cast<float>(ptCursorPos.m_iY + flVisibleRatio) - static_cast<float>((m_dmSize.m_iHeight - 20));

        if (flHeightDelta >= 0.f)
        {
          ptCursorPos.m_iY -= flHeightDelta;
        }

        // new vertical position ratio
        float flNewYRatio = static_cast<float>(ptCursorPos.m_iY) / static_cast<float>(m_dmSize.m_iHeight - 20);
        m_iScrollThumbPosition = (flNewYRatio * m_prgpColorInfo.size());

        // clamp position (don't let the user drag the scrollthumb if it reaches the "start" of the scrollbar area)
        if (m_iScrollThumbPosition <= 0)
        {
          m_iScrollThumbPosition = 0;
        }
      }
      else
      {
        m_bIsDraggingThumb = false;
      }
    }

    if (m_prgpColorInfo.size() > 0)
    {
      // update other widgets
      m_prgpColorInfo[m_uiSelectedEntry].m_pPlusButton->Update();
      m_prgpColorInfo[m_uiSelectedEntry].m_pMinusButton->Update();
      m_prgpColorInfo[m_uiSelectedEntry].m_pGradientCheckBox->Update();
      m_prgpColorInfo[m_uiSelectedEntry].m_pAlphaSlider->Update();

      // color gap
      static constexpr int iColorPickerGap = 250;

      static constexpr FGUI::DIMENSION dmColorPickerSize = {150, 150};

      FGUI::AREA arColorPickerRegion = {(GetAbsolutePosition().m_iX + (m_dmSize.m_iWidth - iColorPickerGap) + 10), (GetAbsolutePosition().m_iY + 20), dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight};
      FGUI::AREA arColorHSBRegion = {arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom};
      FGUI::AREA arColorHueRegion = {(arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, arColorPickerRegion.m_iTop, 15, arColorPickerRegion.m_iBottom};

      // switches
      static bool bColorHSBSelected = false;
      static bool bColorHueSelected = false;

      FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

      if (FGUI::INPUT.IsKeyPressed(MOUSE_1))
      {
        bColorHSBSelected = FGUI::INPUT.IsCursorInArea(arColorHSBRegion);
        bColorHueSelected = FGUI::INPUT.IsCursorInArea(arColorHueRegion);
      }
      else if (FGUI::INPUT.IsKeyReleased(MOUSE_1))
      {
        bColorHSBSelected = false;
        bColorHueSelected = false;
      }

      if (bColorHSBSelected)
      {
        m_prRelativePos = {ptCursorPos.m_iX - static_cast<float>(arColorHSBRegion.m_iLeft), ptCursorPos.m_iY - static_cast<float>(arColorHSBRegion.m_iTop)};

        m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst), (m_prRelativePos.m_flX / arColorPickerRegion.m_iRight), (m_prRelativePos.m_flY / arColorPickerRegion.m_iBottom), m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha);
      }
      else if (bColorHueSelected)
      {
        float flHue = (ptCursorPos.m_iY - arColorHueRegion.m_iTop) / 150.f;

        m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst = FGUI::COLOR::HSBToRGB(std::clamp(flHue, 0.f, 999.f), 1.f, 1.f);
      }
    }
  }

  void CColorList::Input()
  {
    // color gap
    static constexpr int iColorPickerGap = 250;

    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, (m_dmSize.m_iWidth - iColorPickerGap), m_dmSize.m_iHeight};
    FGUI::AREA arScrollBarRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, (arWidgetRegion.m_iTop + 20), 15, (m_dmSize.m_iHeight - 20)};

    if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
    {
      m_bIsDraggingThumb = true;
    }

    if (m_prgpColorInfo.size() > 0)
    {
      // handle input of other widgets
      m_prgpColorInfo[m_uiSelectedEntry].m_pGradientCheckBox->Input();
      m_prgpColorInfo[m_uiSelectedEntry].m_pAlphaSlider->Input();

      FGUI::AREA arPlusButtonRegion = {(GetAbsolutePosition().m_iX + 70), (GetAbsolutePosition().m_iY - 1), 16, 16};
      FGUI::AREA arMinusButtonRegion = {(GetAbsolutePosition().m_iX + 90), (GetAbsolutePosition().m_iY - 1), 16, 16};

      if (FGUI::INPUT.IsCursorInArea(arPlusButtonRegion))
      {
        if (!m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded)
        {
          // make the first color be the secondary color
          m_prgpColorInfo[m_uiSelectedEntry].m_clrSecond = m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst;

          // add a new color into the sequence
          m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded = true;
        }
      }
      else if (FGUI::INPUT.IsCursorInArea(arMinusButtonRegion))
      {
        if (m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded)
        {
          // remeve color from sequence
          m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded = false;

          // set gradient checkbox state
          m_prgpColorInfo[m_uiSelectedEntry].m_pGradientCheckBox->SetState(false);
        }
      }
    }

    // entries displayed
    int iEntriesDisplayed = 0;

    // calculate the amount of entries that will be drawn on the colorlist
    int iCalculatedEntries = ((m_dmSize.m_iHeight - 20) / m_iEntrySpacing);

    // colorlist entries
    for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpColorInfo.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
    {
      FGUI::AREA arEntryRegion = {arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed) + 20, (arWidgetRegion.m_iRight - 15), m_iEntrySpacing};

      // select an entry
      if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
      {
        m_uiSelectedEntry = i;
      }

      iEntriesDisplayed++;
    }
  }

  void CColorList::Save(nlohmann::json &module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    for (std::size_t i = 0; i < m_prgpColorInfo.size(); i++)
    {
      // remove spaces from the color identificator
      std::string strFormatedColorIdentificator = m_prgpColorInfo[i].m_strIdentificator;
      std::replace(strFormatedColorIdentificator.begin(), strFormatedColorIdentificator.end(), ' ', '_');

      module[strFormatedWidgetName][strFormatedColorIdentificator]["red"] = m_prgpColorInfo[i].m_clrFirst.m_ucRed;
      module[strFormatedWidgetName][strFormatedColorIdentificator]["green"] = m_prgpColorInfo[i].m_clrFirst.m_ucGreen;
      module[strFormatedWidgetName][strFormatedColorIdentificator]["blue"] = m_prgpColorInfo[i].m_clrFirst.m_ucBlue;
      module[strFormatedWidgetName][strFormatedColorIdentificator]["alpha"] = m_prgpColorInfo[i].m_clrFirst.m_ucAlpha;
    }
  }

  void CColorList::Load(std::string file)
  {
    nlohmann::json jsModule;

    std::ifstream ifsFileToLoad(file, std::ifstream::binary);

    if (ifsFileToLoad.fail())
    {
      return; // TODO: handle this properly
    }

    jsModule = nlohmann::json::parse(ifsFileToLoad);

    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    for (std::size_t i = 0; i < m_prgpColorInfo.size(); i++)
    {
      // remove spaces from the color identificator
      std::string strFormatedColorIdentificator = m_prgpColorInfo[i].m_strIdentificator;
      std::replace(strFormatedColorIdentificator.begin(), strFormatedColorIdentificator.end(), ' ', '_');

      m_prgpColorInfo[i].m_clrFirst.m_ucRed = jsModule[strFormatedWidgetName][strFormatedColorIdentificator]["red"];
      m_prgpColorInfo[i].m_clrFirst.m_ucGreen = jsModule[strFormatedWidgetName][strFormatedColorIdentificator]["green"];
      m_prgpColorInfo[i].m_clrFirst.m_ucBlue = jsModule[strFormatedWidgetName][strFormatedColorIdentificator]["blue"];
      m_prgpColorInfo[i].m_clrFirst.m_ucAlpha = jsModule[strFormatedWidgetName][strFormatedColorIdentificator]["alpha"];
    }
  }

  void CColorList::Tooltip()
  {
  }

} // namespace FGUI