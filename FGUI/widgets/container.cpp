//
// FGUI - feature rich graphical user interface
//

// library includes
#include "container.hpp"

namespace FGUI
{

  CContainer::CContainer()
  {
    m_strTitle = "Container";
    m_bScrollBarState = false;
    m_bIsOpened = false;
    m_uiKey = 0;
    m_iWidgetScrollOffset = 0;
    m_fnctCallback = nullptr;
    m_bIsFocusingOnWidget = false;
    m_pParentWidget = nullptr;
    m_pFocusedWidget = nullptr;
    m_anyFont = 0;
    m_strTooltip = "";
    m_nType = static_cast<int>(WIDGET_TYPE::CONTAINER);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE);
  }

  void CContainer::Render()
  {
    // listen for input
    FGUI::INPUT.PullInput();

    if (!GetParentWidget())
    {
      if (FGUI::INPUT.IsKeyPressed(GetKey()))
      {
        SetState(!GetState());
      }

      if (GetState())
      {
        Update();
        Geometry();
        Tooltip();
      }
    }
  }

  void CContainer::SaveToFile(std::string file)
  {
    nlohmann::json jsModule;

    // don't proceed if the container doesn't have any widgets
    if (m_prgpWidgets.empty())
    {
      return;
    }

    for (std::shared_ptr<FGUI::CWidgets> pWidgets : m_prgpWidgets)
    {
      // save widget state
      pWidgets->Save(jsModule);
    }

    std::ofstream ofsFileToSave(file);

    if (ofsFileToSave.fail())
    {
      return; // TODO: handle this properly
    }

    // write the file
    ofsFileToSave << std::setw(4) << jsModule << std::endl;
  }

  void CContainer::SetState(bool state)
  {
    m_bIsOpened = state;
  }

  bool CContainer::GetState()
  {
    return m_bIsOpened;
  }

  void CContainer::SetScrollBarState(bool state)
  {
    m_bScrollBarState = state;
  }

  bool CContainer::GetScrollBarState()
  {
    return m_bScrollBarState;
  }

  int CContainer::GetScrollOffset()
  {
    return m_iWidgetScrollOffset;
  }

  void CContainer::SetFocusedWidget(std::shared_ptr<FGUI::CWidgets> widget)
  {
    m_pFocusedWidget = widget;

    if (widget)
    {
      m_bIsFocusingOnWidget = true;
    }
    else
    {
      m_bIsFocusingOnWidget = false;
    }
  }

  std::shared_ptr<FGUI::CWidgets> CContainer::GetFocusedWidget()
  {
    return m_pFocusedWidget;
  }

  void CContainer::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CContainer::SetKey(unsigned int key)
  {
    m_uiKey = key;
  }

  unsigned int CContainer::GetKey()
  {
    return m_uiKey;
  }

  void CContainer::AddWidget(std::shared_ptr<FGUI::CWidgets> widget, bool padding)
  {
    // configure padding
    if (padding)
    {
      constexpr int iScrollBarWidth = 15;

      if (GetParentWidget())
      {
        if (m_bScrollBarState)
        {
          widget->SetSize(m_dmSize.m_iWidth - (widget->GetPosition().m_iX * 2) - iScrollBarWidth, widget->GetSize().m_iHeight);
        }
        else
        {
          widget->SetSize(m_dmSize.m_iWidth - (widget->GetPosition().m_iX * 2), widget->GetSize().m_iHeight);
        }
      }
      else
      {
        widget->SetSize(m_dmSize.m_iWidth - (widget->GetPosition().m_iX * 2), widget->GetSize().m_iHeight);
      }
    }

    // set the parent widget
    widget->SetParentWidget(shared_from_this());

    m_prgpWidgets.emplace_back(widget);
  }

  void CContainer::Geometry()
  {
    FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    // if the container doesn't have a parent widget, it will behave like a normal window
    if (!GetParentWidget())
    {
      // container body
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, {45, 45, 45});
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft + 1, arWidgetRegion.m_iTop + 31, arWidgetRegion.m_iRight - 2, (arWidgetRegion.m_iBottom - 30) - 2, {245, 245, 245});
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft + 10, (arWidgetRegion.m_iTop + 31) + 20 + 25, arWidgetRegion.m_iRight - 20, (arWidgetRegion.m_iBottom - 31) - 60, {195, 195, 195});

      // container title
      FGUI::RENDER.Text(m_ptPosition.m_iX + 10, m_ptPosition.m_iY + 10, m_anyFont, {255, 255, 255}, m_strTitle);

      // if the container has a function
      if (m_fnctCallback)
      {
        // invoke function
        m_fnctCallback();
      }
    }
    else // otherwise, behave like a normal groupbox
    {
      // groupbox body
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, 5, 1, {220, 220, 200});                                                                                           // top1
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + dmTitleTextSize.m_iWidth) + 10, arWidgetRegion.m_iTop, (arWidgetRegion.m_iRight - dmTitleTextSize.m_iWidth) - 10, 1, {220, 220, 200}); // top2
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, 1, arWidgetRegion.m_iBottom, {220, 220, 220});                                                                    // left
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight), arWidgetRegion.m_iTop, 1, arWidgetRegion.m_iBottom, {220, 220, 220});                                        // right
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + arWidgetRegion.m_iBottom), arWidgetRegion.m_iRight, 1, {220, 220, 220});                                        // bottom
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), {245, 245, 245});                      // background

      // groupbox label
      FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop - (dmTitleTextSize.m_iHeight / 2), m_anyFont, {35, 35, 35}, m_strTitle);

      if (m_bScrollBarState)
      {
        FGUI::AREA arScrollBarRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, arWidgetRegion.m_iTop, 15, m_dmSize.m_iHeight};

        static constexpr FGUI::DIMENSION dmScrollBarThumbWidth = {8, 5};

        // scrollbar thumb size
        float flScrollbarThumbSize = (m_dmSize.m_iHeight / static_cast<float>(m_prgpWidgets.back()->GetPosition().m_iY)) * static_cast<float>((m_dmSize.m_iHeight - m_prgpWidgets.back()->GetSize().m_iHeight));

        // calculate the scrollbar thumb position
        float flScrollbarThumbPosition = (m_dmSize.m_iHeight - flScrollbarThumbSize) * static_cast<float>(m_iWidgetScrollOffset /
                                                                                                          static_cast<float>((m_prgpWidgets.back()->GetPosition().m_iY + m_prgpWidgets.back()->GetSize().m_iHeight) - (m_dmSize.m_iHeight - 5)));

        // scrollbar body
        FGUI::RENDER.Rectangle(arScrollBarRegion.m_iLeft, arScrollBarRegion.m_iTop, arScrollBarRegion.m_iRight, arScrollBarRegion.m_iBottom, {235, 235, 235});

        // scrollbar thumb
        FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flScrollbarThumbPosition) + 5, dmScrollBarThumbWidth.m_iWidth, flScrollbarThumbSize, {220, 223, 231});
      }
    }

    // this will tell the form to skip focused widgets (so it can be drawned after all other widgets)
    bool bSkipWidget = false;

    // this will hold the current skipped widget
    std::shared_ptr<FGUI::CWidgets> pWidgetToSkip = nullptr;

    if (m_bIsFocusingOnWidget)
    {
      if (m_pFocusedWidget)
      {
        // set the widget that will be skipped
        pWidgetToSkip = m_pFocusedWidget;

        // tell the container to skip this widget
        bSkipWidget = true;
      }
    }

    // iterate over the rest of the widgets
    for (std::shared_ptr<FGUI::CWidgets> pWidgets : m_prgpWidgets)
    {
      // if a widget is currently being skipped
      if (bSkipWidget)
      {
        // we don't want to draw the skipped widget here
        if (pWidgetToSkip == pWidgets)
        {
          continue;
        }
      }

      // check if widgets are unlocked
      if (pWidgets && pWidgets->IsUnlocked() && pWidgets->GetFlags(WIDGET_FLAG::DRAWABLE))
      {
        if (m_bScrollBarState)
        {
          // check if the widgets are inside the boundaries of the groupbox
          if ((pWidgets->GetAbsolutePosition().m_iY + pWidgets->GetSize().m_iHeight) <= (GetAbsolutePosition().m_iY + GetSize().m_iHeight) && (pWidgets->GetAbsolutePosition().m_iY >= GetAbsolutePosition().m_iY))
          {
            pWidgets->Geometry();
          }
        }
        else
        {
          pWidgets->Geometry();
        }
      }
    }

    // now the container can draw skipped widgets
    if (bSkipWidget)
    {
      // check if the skipped widget can be drawned
      if (pWidgetToSkip && pWidgetToSkip->IsUnlocked() && pWidgetToSkip->GetFlags(WIDGET_FLAG::DRAWABLE))
      {
        if (m_bScrollBarState)
        {
          // check if the widgets are inside the boundaries of the groupbox
          if ((pWidgetToSkip->GetAbsolutePosition().m_iY + pWidgetToSkip->GetSize().m_iHeight) <= (GetAbsolutePosition().m_iY + GetSize().m_iHeight) && (pWidgetToSkip->GetAbsolutePosition().m_iY >= GetAbsolutePosition().m_iY))
          {
            pWidgetToSkip->Geometry();
          }
        }
        else
        {
          pWidgetToSkip->Geometry();
        }
      }
    }
  }

  void CContainer::Update()
  {
    // check if the container is behaving like a window
    if (!GetParentWidget())
    {
      if (GetFlags(WIDGET_FLAG::FULLSCREEN))
      {
        // change container size
        SetSize(FGUI::RENDER.GetScreenSize());
      }

      FGUI::AREA arDraggableArea = {m_ptPosition.m_iX, m_ptPosition.m_iY, m_dmSize.m_iWidth, 30};

      static bool bIsDraggingContainer = false;

      if (FGUI::INPUT.IsCursorInArea(arDraggableArea))
      {
        if (FGUI::INPUT.IsKeyPressed(MOUSE_1))
        {
          bIsDraggingContainer = true;
        }
      }

      // if the user started dragging the container
      if (bIsDraggingContainer)
      {
        FGUI::POINT ptCursorPosDelta = FGUI::INPUT.GetCursorPosDelta();

        // move container
        m_ptPosition.m_iX += ptCursorPosDelta.m_iX;
        m_ptPosition.m_iY += ptCursorPosDelta.m_iY;
      }

      if (FGUI::INPUT.IsKeyReleased(MOUSE_1))
      {
        bIsDraggingContainer = false;
      }
    }
    else // if the container is behaving like a groupbox
    {
      if (m_bScrollBarState)
      {
        static bool bIsDraggingThumb = false;

        FGUI::AREA arWidgetRegion = {GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight};

        FGUI::AREA arScrollBarRegion = {(arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, arWidgetRegion.m_iTop, 15, arWidgetRegion.m_iBottom};

        if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
        {
          if (FGUI::INPUT.IsKeyPressed(MOUSE_1))
          {
            bIsDraggingThumb = true;
          }
        }

        if (bIsDraggingThumb)
        {
          FGUI::POINT ptCursorPosDelta = FGUI::INPUT.GetCursorPosDelta();

          static constexpr int iLinesToScroll = 2;

          if (FGUI::INPUT.IsKeyHeld(MOUSE_1))
          {
            m_iWidgetScrollOffset += (ptCursorPosDelta.m_iY * iLinesToScroll);
          }
          else
          {
            bIsDraggingThumb = false;
          }
        }

        // clamp scrolling
        m_iWidgetScrollOffset = std::clamp(m_iWidgetScrollOffset, 0, std::max(0, ((m_prgpWidgets.back()->GetPosition().m_iY + m_prgpWidgets.back()->GetSize().m_iHeight)) - (m_dmSize.m_iHeight + 5)));
      }
    }

    // this will tell the form to skip focused widgets (so it can be drawned after all other widgets)
    bool bSkipWidget = false;

    // this will hold the current skipped widget
    std::shared_ptr<FGUI::CWidgets> pWidgetToSkip = nullptr;

    // handle skipped widgets first
    if (m_bIsFocusingOnWidget)
    {
      // check if the skipped widget can be used
      if (m_pFocusedWidget && m_pFocusedWidget->IsUnlocked())
      {
        // tell the form to skip this widget
        bSkipWidget = true;

        // assign the widget that will be skipped
        pWidgetToSkip = m_pFocusedWidget;

        FGUI::AREA arSkippedWidgetRegion = {pWidgetToSkip->GetAbsolutePosition().m_iX, pWidgetToSkip->GetAbsolutePosition().m_iY, pWidgetToSkip->GetSize().m_iWidth, pWidgetToSkip->GetSize().m_iHeight};

        if (m_bScrollBarState)
        {
          if ((pWidgetToSkip->GetAbsolutePosition().m_iY + pWidgetToSkip->GetSize().m_iHeight) <= (GetAbsolutePosition().m_iY + GetSize().m_iHeight) && (pWidgetToSkip->GetAbsolutePosition().m_iY >= GetAbsolutePosition().m_iY))
          {
            pWidgetToSkip->Update();

            // check if the skipped widget can be clicked
            if (GetFocusedWidget()->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arSkippedWidgetRegion) && FGUI::INPUT.IsKeyPressed(MOUSE_1) && bSkipWidget)
            {
              pWidgetToSkip->Input();

              // loose unfocus
              SetFocusedWidget(nullptr);

              // reset focused widget state
              pWidgetToSkip.reset();
            }
          }
        }
        else
        {
          pWidgetToSkip->Update();

          // check if the skipped widget can be clicked
          if (GetFocusedWidget()->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arSkippedWidgetRegion) && FGUI::INPUT.IsKeyPressed(MOUSE_1) && bSkipWidget)
          {
            pWidgetToSkip->Input();

            // loose unfocus
            SetFocusedWidget(nullptr);

            // reset focused widget state
            pWidgetToSkip.reset();
          }
        }
      }
    }

    // iterate over the rest of the widgets
    for (std::shared_ptr<FGUI::CWidgets> pWidgets : m_prgpWidgets)
    {
      if (pWidgets->IsUnlocked())
      {
        // if a widget is currently being skipped
        if (bSkipWidget)
        {
          // we don't want to handle skipped widgets here
          if (pWidgetToSkip == pWidgets)
          {
            continue;
          }
        }

        FGUI::AREA arWidgetRegion = {pWidgets->GetAbsolutePosition().m_iX, pWidgets->GetAbsolutePosition().m_iY, pWidgets->GetSize().m_iWidth, pWidgets->GetSize().m_iHeight};

        if (m_bScrollBarState)
        {
          if ((pWidgets->GetAbsolutePosition().m_iY + pWidgets->GetSize().m_iHeight) <= (GetAbsolutePosition().m_iY + GetSize().m_iHeight) && (pWidgets->GetAbsolutePosition().m_iY >= GetAbsolutePosition().m_iY))
          {
            pWidgets->Update();

            // check if the widget can be clicked
            if (pWidgets->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arWidgetRegion) && FGUI::INPUT.IsKeyPressed(MOUSE_1) && !bSkipWidget)
            {
              pWidgets->Input();

              if (pWidgets->GetFlags(WIDGET_FLAG::FOCUSABLE))
              {
                SetFocusedWidget(pWidgets);
              }
              else
              {
                SetFocusedWidget(nullptr);
              }
            }
          }
        }
        else
        {
          pWidgets->Update();

          // check if the widget can be clicked
          if (pWidgets->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arWidgetRegion) && FGUI::INPUT.IsKeyPressed(MOUSE_1) && !bSkipWidget)
          {
            pWidgets->Input();

            if (pWidgets->GetFlags(WIDGET_FLAG::FOCUSABLE))
            {
              SetFocusedWidget(pWidgets);
            }
            else
            {
              SetFocusedWidget(nullptr);
            }
          }
        }
      }
    }
  }

  void CContainer::Input()
  {
  }

  void CContainer::Save(nlohmann::json &module)
  {
    // don't proceed if the container doesn't have any widgets
    if (m_prgpWidgets.empty())
    {
      return;
    }

    for (std::shared_ptr<FGUI::CWidgets> pWidgets : m_prgpWidgets)
    {
      if (pWidgets->GetType() == static_cast<int>(WIDGET_TYPE::CONTAINER))
      {
        pWidgets->Save(module);
      }
      else if (pWidgets->GetFlags(WIDGET_FLAG::SAVABLE)) // check if the widget can be saved
      {
        pWidgets->Save(module);
      }
    }
  }

  void CContainer::Load(std::string file)
  {
    if (m_prgpWidgets.empty())
    {
      return;
    }

    nlohmann::json jsModule;

    std::ifstream ifsFileToLoad(file, std::ifstream::binary);

    if (ifsFileToLoad.fail())
    {
      return; // TODO: handle this properly
    }

    jsModule = nlohmann::json::parse(ifsFileToLoad);

    for (std::shared_ptr<FGUI::CWidgets> pWidgets : m_prgpWidgets)
    {
      if (pWidgets->GetType() == static_cast<int>(WIDGET_TYPE::CONTAINER))
      {
        pWidgets->Load(file);
      }
      else if (pWidgets->GetFlags(WIDGET_FLAG::SAVABLE)) // check if the widget can be loaded
      {
        pWidgets->Load(file);
      }
    }
  }

  void CContainer::Tooltip()
  {
    for (std::shared_ptr<FGUI::CWidgets> pWidgets : m_prgpWidgets)
    {
      // check if widgets are unlocked
      if (pWidgets && pWidgets->IsUnlocked() && pWidgets->GetFlags(WIDGET_FLAG::DRAWABLE))
      {
        // avoid drawing tooltips when a widget is being focused
        if (!std::reinterpret_pointer_cast<FGUI::CContainer>(pWidgets->GetParentWidget())->GetFocusedWidget())
        {
          FGUI::AREA arWidgetRegion = {pWidgets->GetAbsolutePosition().m_iX, pWidgets->GetAbsolutePosition().m_iY, pWidgets->GetSize().m_iWidth, pWidgets->GetSize().m_iHeight};

          if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
          {
            pWidgets->Tooltip();
          }
        }
      }
    }
  }

} // namespace FGUI