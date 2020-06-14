//
// FGUI - feature rich graphical user interface
//

// library includes
#include "form.hpp"
#include "groupbox.hpp"

namespace FGUI
{

	void CForm::Render()
	{
		// handle input system
		FGUI::INPUT.PullInput();

		if (FGUI::INPUT.GetKeyPress(GetKey()))
		{
			// toggle main form on and off
			SetState(!GetState());
		}

		// if the user toggles the main form
		if (GetState())
		{
			// update main form
			Update();

			// handle main form movement
			Movement();

			// populate main form geometry
			Geometry();
		}

		// iterate over child forms
		for (const std::shared_ptr<FGUI::CForm>& childs : m_prgpForms)
		{
			if (FGUI::INPUT.GetKeyPress(childs->GetKey()))
			{
				// toggle child forms on and off
				childs->SetState(!childs->GetState());
			}

			// if the user toggles a child form
			if (childs->GetState())
			{
				// update child forms
				childs->Update();

				// handle child forms movement
				childs->Movement();

				// populate child forms geometry
				childs->Geometry();
			}
		}
	}

	void CForm::SetState(bool onoff)
	{
		m_bIsOpened = onoff;
	}

	bool CForm::GetState()
	{
		return m_bIsOpened;
	}

	void CForm::AddForm(std::shared_ptr<FGUI::CForm> form)
	{
		if (!form)
		{
			return;
		}

		// populate the form container
		m_prgpForms.emplace_back(form);
	}

	void CForm::AddTab(std::shared_ptr<FGUI::CTabs> tab)
	{
		if (!tab)
		{
			return;
		}

		// select the current tab being added (in case the form doesn't select one for us)
		if (!m_prgpTabs.size())
		{
			m_pSelectedTab = tab;
		}

		// set parent form
		tab->m_pParentForm = std::dynamic_pointer_cast<FGUI::CForm>(shared_from_this());

		// populate the tab container
		m_prgpTabs.emplace_back(tab);
	}

	void CForm::AddCallback(std::function<void()> callback)
	{
		m_fnctCallback = callback;
	}

	void CForm::SetKey(unsigned int key_code)
	{
		m_iKey = key_code;
	}

	void CForm::SetPosition(unsigned int x, unsigned int y)
	{
		m_ptPosition.m_iX = x;
		m_ptPosition.m_iY = y;
	}

	void CForm::SetSize(unsigned int width, unsigned int height)
	{
		m_dmSize.m_iWidth = width;
		m_dmSize.m_iHeight = height;
	}

	void CForm::SetSize(FGUI::DIMENSION size)
	{
		m_dmSize.m_iWidth = size.m_iWidth;
		m_dmSize.m_iHeight = size.m_iHeight;
	}

	void CForm::SetTitle(std::string title)
	{
		m_strTitle = title;
	}

	void CForm::SetFlags(int flags)
	{
		m_nFlags = flags;
	}

	int CForm::GetKey()
	{
		return m_iKey;
	}

	std::string CForm::GetTitle()
	{
		return m_strTitle;
	}

	void CForm::SetFont(std::string family, int size, bool bold, int flags)
	{
		FGUI::RENDER.CreateFont(m_ulFont, family, size, flags, bold);
	}

	void CForm::SetFont(FGUI::WIDGET_FONT font)
	{
		FGUI::RENDER.CreateFont(m_ulFont, font.m_strFamily, font.m_iSize, font.m_nFlags, font.m_bBold);
	}

	FGUI::AREA CForm::GetWidgetArea()
	{
		// NOTE: if you plan to change the form design, make sure to edit this as well. (this is the area where widgets will be drawned)
		return { m_ptPosition.m_iX + 10, m_ptPosition.m_iY + 75, m_dmSize.m_iWidth, m_dmSize.m_iHeight };
	}

	void CForm::SetFocusedWidget(std::shared_ptr<FGUI::CWidgets> widget)
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

	std::shared_ptr<FGUI::CWidgets> CForm::GetFocusedWidget()
	{
		return m_pFocusedWidget;
	}

	FGUI::FONT CForm::GetFont()
	{
		return m_ulFont;
	}

	bool CForm::GetFlags(FGUI::WIDGET_FLAG flags)
	{
		if (m_nFlags & static_cast<int>(flags))
		{
			return true;
		}

		return false;
	}

	FGUI::POINT CForm::GetPosition()
	{
		return m_ptPosition;
	}

	FGUI::DIMENSION CForm::GetSize()
	{
		return m_dmSize;
	}

	void CForm::Geometry()
	{
		// form body
		FGUI::RENDER.Rectangle(m_ptPosition.m_iX, m_ptPosition.m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight, { 45, 45, 45 });
		FGUI::RENDER.Rectangle(m_ptPosition.m_iX + 1, m_ptPosition.m_iY + 31, m_dmSize.m_iWidth - 2, (m_dmSize.m_iHeight - 30) - 2, { 245, 245, 245 });

		// form title
		FGUI::RENDER.Text(m_ptPosition.m_iX + 10, m_ptPosition.m_iY + 10, m_ulFont, { 255, 255, 255 }, m_strTitle);

		// widget area
		FGUI::RENDER.Outline(m_ptPosition.m_iX + 10, (m_ptPosition.m_iY + 31) + 20 + 25, m_dmSize.m_iWidth - 20, (m_dmSize.m_iHeight - 31) - 60, { 195, 195, 195 });

		// if the window has a function
		if (m_fnctCallback)
		{
			// invoke function
			m_fnctCallback();
		}

		// don't proceed if the form doesn't have any tabs
		if (m_prgpTabs.empty())
		{
			return;
		}

		// tab buttons
		for (std::size_t i = 0; i < m_prgpTabs.size(); i++)
		{
			// tab button area
			FGUI::AREA arTabRegion = { (m_ptPosition.m_iX + 10) + (static_cast<int>(i) * 113), (m_ptPosition.m_iY + 31) + 20, 110, 25 };

			if (FGUI::INPUT.IsCursorInArea(arTabRegion))
			{
				if (FGUI::INPUT.GetKeyPress(MOUSE_1))
				{
					// select tab
					m_pSelectedTab = m_prgpTabs[i];
				}

				// unfocus widget
				m_pFocusedWidget = nullptr;
			}

			// draw the buttons according to the tab state
			if (m_pSelectedTab == m_prgpTabs[i])
			{
				FGUI::RENDER.Rectangle(arTabRegion.m_iLeft, arTabRegion.m_iTop - 5, arTabRegion.m_iRight, arTabRegion.m_iBottom + 5, { 45, 45, 45 });
				FGUI::RENDER.Text(arTabRegion.m_iLeft + 20, arTabRegion.m_iTop + (arTabRegion.m_iBottom / 2) - 5, m_prgpTabs[i]->GetFont(), { 255, 255, 255 }, m_prgpTabs[i]->GetTitle());
			}
			else
			{
				FGUI::RENDER.Rectangle(arTabRegion.m_iLeft, arTabRegion.m_iTop, arTabRegion.m_iRight, arTabRegion.m_iBottom, { 45, 45, 45 });
				FGUI::RENDER.Text(arTabRegion.m_iLeft + 20, arTabRegion.m_iTop + (arTabRegion.m_iBottom / 2) - 5, m_prgpTabs[i]->GetFont(), { 220, 220, 220 }, m_prgpTabs[i]->GetTitle());
			}
		}

		// if the user selects a tab
		if (m_pSelectedTab)
		{
			// this will tell the form to skip focused elements (so it can be drawned after all others)
			bool bSkipWidget = false;

			// this will hold the skipped element
			std::shared_ptr<FGUI::CWidgets> pWidgetToSkip = nullptr;

			// if the form is focusing on a widget
			if (m_bIsFocusingOnWidget)
			{
				if (m_pFocusedWidget)
				{
					// assign the widget that will be skipped
					pWidgetToSkip = m_pFocusedWidget;

					// tell the form to skip this widget
					bSkipWidget = true;
				}
			}

			// if the tab doesn't have any widgets, don't proceed
			if (m_pSelectedTab->m_prgpWidgets.empty())
			{
				return;
			}

			// iterate over the rest of the widgets
			for (const std::shared_ptr<FGUI::CWidgets>& pWidgets : m_pSelectedTab->m_prgpWidgets)
			{
				// if the menu is having a widget skiped
				if (bSkipWidget)
				{
					// check if the widget inside this iteration is not the one that will be skipped
					if (pWidgetToSkip == pWidgets)
					{
						continue;
					}
				}

				// check if widgets are unlocked (able to be drawned)
				if (pWidgets && pWidgets->GetFlags(WIDGET_FLAG::DRAWABLE) && pWidgets->IsUnlocked())
				{
					// found groupbox
					std::shared_ptr<FGUI::CGroupBox> pFoundGroupBox = nullptr;

					if (pWidgets->GetType() != static_cast<int>(WIDGET_TYPE::GROUPBOX))
					{
						pFoundGroupBox = pWidgets->m_pParentGroupBox ? std::reinterpret_pointer_cast<FGUI::CGroupBox>(pWidgets->m_pParentGroupBox) : nullptr;
					}

					if (pFoundGroupBox)
					{
						// check if the groupbox has scrollbars enabled
						if (pFoundGroupBox->GetScrollbarState())
						{
							// check if the skipped widgets are inside the boundaries of the groupbox
							if ((pWidgets->GetAbsolutePosition().m_iY + pWidgets->GetSize().m_iHeight) <= (pFoundGroupBox->GetAbsolutePosition().m_iY + pFoundGroupBox->GetSize().m_iHeight)
								&& (pWidgets->GetAbsolutePosition().m_iY >= pFoundGroupBox->GetAbsolutePosition().m_iY))
							{
								// draw other skipped widgets
								pWidgets->Geometry();
							}
						}
						else
						{
							// draw other widgets
							pWidgets->Geometry();
						}
					}
					else if (pWidgets->GetType() == static_cast<int>(WIDGET_TYPE::GROUPBOX) || pWidgets->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
					{
						// draw widgets that needs to be outside of a groupbox
						pWidgets->Geometry();
					}
				}
			}

			// now the form can draw skipped widgets
			if (bSkipWidget)
			{
				if (pWidgetToSkip && pWidgetToSkip->GetFlags(WIDGET_FLAG::DRAWABLE) && pWidgetToSkip->IsUnlocked())
				{
					// found groupbox
					std::shared_ptr<FGUI::CGroupBox> pFoundGroupBox = nullptr;

					if (pWidgetToSkip->GetType() != static_cast<int>(WIDGET_TYPE::GROUPBOX))
					{
						pFoundGroupBox = pWidgetToSkip->m_pParentGroupBox ? std::reinterpret_pointer_cast<FGUI::CGroupBox>(pWidgetToSkip->m_pParentGroupBox) : nullptr;
					}

					if (pFoundGroupBox)
					{
						// check if the groupbox has scrollbars enabled
						if (pFoundGroupBox->GetScrollbarState())
						{
							// check if the skipped widgets are inside the boundaries of the groupbox
							if ((pWidgetToSkip->GetAbsolutePosition().m_iY + pWidgetToSkip->GetSize().m_iHeight) <= (pFoundGroupBox->GetAbsolutePosition().m_iY + pFoundGroupBox->GetSize().m_iHeight)
								&& (pWidgetToSkip->GetAbsolutePosition().m_iY >= pFoundGroupBox->GetAbsolutePosition().m_iY))
							{
								// draw other skipped widgets
								pWidgetToSkip->Geometry();
							}
						}
						else
						{
							// draw other skipped widgets
							pWidgetToSkip->Geometry();
						}
					}
					else if (pWidgetToSkip->GetType() == static_cast<int>(WIDGET_TYPE::GROUPBOX) || pWidgetToSkip->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
					{
						// draw widgets that needs to be outside of a groupbox
						pWidgetToSkip->Geometry();
					}
				}
			}
		}
	}

	void CForm::Update()
	{
		// don't do updates while the form is closed
		if (!m_bIsOpened)
		{
			return;
		}

		// form flags
		if (GetFlags(WIDGET_FLAG::FULLSCREEN))
		{
			// change form size
			SetSize(FGUI::RENDER.GetScreenSize());
		}

		// check if the form received a click
		bool bCheckWidgetClicks = false;

		if (FGUI::INPUT.GetKeyPress(MOUSE_1))
		{
			// grab screen size
			FGUI::DIMENSION dmScreenSize = FGUI::RENDER.GetScreenSize();

			// get "clickable" area (you can limit this to the form boundaries instead of using the entire screen.)
			FGUI::AREA arClickableRegion = { m_ptPosition.m_iX, m_ptPosition.m_iY, dmScreenSize.m_iWidth, dmScreenSize.m_iHeight };

			if (FGUI::INPUT.IsCursorInArea(arClickableRegion))
			{
				// tell the form that it had received a click
				bCheckWidgetClicks = true;
			}
		}

		// if the form doesn't have a tab selected, don't proceed
		if (!m_pSelectedTab)
		{
			return;
		}

		// if the tab doesn't have any widgets, don't proceed
		if (m_pSelectedTab->m_prgpWidgets.empty())
		{
			return;
		}

		// this will tell the form to skip focused elements (so it can be drawned after all other's)
		bool bSkipWidget = false;

		// this will hold the skipped element
		std::shared_ptr<FGUI::CWidgets> pWidgetToSkip = nullptr;

		// handle updates on the focused widget first
		if (m_bIsFocusingOnWidget)
		{
			if (m_pFocusedWidget)
			{
				// check if the focused widget is unlocked
				if (m_pFocusedWidget->IsUnlocked())
				{
					// tell the form to skip this widget
					bSkipWidget = true;

					// assign the widget that will be skipped
					pWidgetToSkip = m_pFocusedWidget;

					// get focused widget area
					FGUI::AREA arFocusedWidgetRegion = { pWidgetToSkip->GetAbsolutePosition().m_iX, pWidgetToSkip->GetAbsolutePosition().m_iY, pWidgetToSkip->GetSize().m_iWidth, pWidgetToSkip->GetSize().m_iHeight };

					// update focused widget
					pWidgetToSkip->Update();

					// check if the focused widget can be clicked
					if (pWidgetToSkip->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arFocusedWidgetRegion) && bCheckWidgetClicks)
					{
						// handle input of focused widgets
						pWidgetToSkip->Input();

						// unfocus this widget
						SetFocusedWidget(nullptr);

						// tell the form to look for another click
						bCheckWidgetClicks = false;
					}
				}
			}
		}

		// iterate over the rest of the widgets
		for (const std::shared_ptr<FGUI::CWidgets>& pWidgets : m_pSelectedTab->m_prgpWidgets)
		{
			// check if the widgets are unlocked first
			if (pWidgets->IsUnlocked())
			{
				// if the menu is having a widget skiped
				if (bSkipWidget)
				{
					// check if the widget inside this iteration is not the one that will be skipped
					if (pWidgetToSkip == pWidgets)
					{
						continue;
					}
				}
				// found groupbox
				std::shared_ptr<FGUI::CGroupBox> pFoundGroupBox = nullptr;

				if (pWidgets->GetType() != static_cast<int>(WIDGET_TYPE::GROUPBOX))
				{
					pFoundGroupBox = pWidgets->m_pParentGroupBox ? std::reinterpret_pointer_cast<FGUI::CGroupBox>(pWidgets->m_pParentGroupBox) : nullptr;
				}
				
				// get the widget area
				FGUI::AREA arWidgetRegion = { pWidgets->GetAbsolutePosition().m_iX, pWidgets->GetAbsolutePosition().m_iY, pWidgets->GetSize().m_iWidth, pWidgets->GetSize().m_iHeight };

				if (pFoundGroupBox)
				{
					// check if the groupbox has scrollbars enabled
					if (pFoundGroupBox->GetScrollbarState())
					{
						// check if the skipped widgets are inside the boundaries of the groupbox
						if ((pWidgets->GetAbsolutePosition().m_iY + pWidgets->GetSize().m_iHeight) <= (pFoundGroupBox->GetAbsolutePosition().m_iY + pFoundGroupBox->GetSize().m_iHeight)
							&& (pWidgets->GetAbsolutePosition().m_iY >= pFoundGroupBox->GetAbsolutePosition().m_iY))
						{
							// update widgets
							pWidgets->Update();

							// check if the widget can be clicked
							if (pWidgets->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arWidgetRegion) && bCheckWidgetClicks)
							{
								// handle widget input
								pWidgets->Input();

								// tell the form to look for another click
								bCheckWidgetClicks = false;

								// focus widget
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
						// update widgets
						pWidgets->Update();

						// check if the widget can be clicked
						if (pWidgets->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arWidgetRegion) && bCheckWidgetClicks)
						{
							// handle widget input
							pWidgets->Input();

							// tell the form to look for another click
							bCheckWidgetClicks = false;

							// focus widget
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
				else if (pWidgets->GetType() == static_cast<int>(WIDGET_TYPE::GROUPBOX) || pWidgets->GetType() == static_cast<int>(WIDGET_TYPE::COLORLIST))
				{
					// update widgets outside a groupbox
					pWidgets->Update();

					// check if the widgets can be clicked
					if (pWidgets->GetFlags(WIDGET_FLAG::CLICKABLE) && FGUI::INPUT.IsCursorInArea(arWidgetRegion) && bCheckWidgetClicks)
					{
						// handle input
						pWidgets->Input();

						// tell the form to look for another click
						bCheckWidgetClicks = false;
					}
				}
			}
		}
	}

	void CForm::Movement()
	{
		// don't handle movement while the form is closed
		if (!m_bIsOpened)
		{
			return;
		}

		// form draggable area
		FGUI::AREA arDraggableArea = { m_ptPosition.m_iX, m_ptPosition.m_iY, m_dmSize.m_iWidth, 30 };

		if (FGUI::INPUT.IsCursorInArea(arDraggableArea))
		{
			if (FGUI::INPUT.GetKeyPress(MOUSE_1))
			{
				// drag form
				m_bIsDragging = true;
			}
		}

		// if the user started dragging the form
		if (m_bIsDragging)
		{
			// get cursor position delta
			FGUI::POINT ptCursorPosDelta = FGUI::INPUT.GetCursorPosDelta();

			// move form
			m_ptPosition.m_iX += ptCursorPosDelta.m_iX;
			m_ptPosition.m_iY += ptCursorPosDelta.m_iY;
		}

		if (FGUI::INPUT.GetKeyRelease(MOUSE_1))
		{
			m_bIsDragging = false;
		}
	}

} // namespace FGUI