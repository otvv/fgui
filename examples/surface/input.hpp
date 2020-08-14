//
// FGUI - Valve's Input System Interface
//

#pragma once

#include <array>

#define FGUI_IMPLEMENTATION
#include <FGUI/FGUI.hpp>

// NOTE: make sure to use your input system interface pointer
// replace "IInputSystem" with your pointer

namespace FGUI_IINPUT_SYSTEM
{
    inline std::array<bool, 256> m_prgpCurrentPressedKeys, m_prgpOldPressedKeys;
    inline FGUI::POINT m_ptCursorPosition, m_ptCursorPositionDelta;

    inline void PullInput()
    {
        static FGUI::POINT ptLastKnownPosition = { 0, 0 };

        std::copy(m_prgpCurrentPressedKeys.begin(), m_prgpCurrentPressedKeys.end(), m_prgpOldPressedKeys.begin());

        for (std::size_t i = 0; i < 256; i++)
        {
            m_prgpCurrentPressedKeys.at(i) = IInputSystem->IsButtonDown(i);
        }

        // Get current cursor position
        IInputSystem->GetCursorPosition(&m_ptCursorPosition.m_iX, &m_ptCursorPosition.m_iY));

        // Calculate the cursor position delta
        m_ptCursorPositionDelta = { (m_ptCursorPosition.m_iX - ptLastKnownPosition.m_iX), (m_ptCursorPosition.m_iY - ptLastKnownPosition.m_iY) };

        // Get last known position of the cursor
        ptLastKnownPosition = m_ptCursorPosition;
    }

    inline bool IsKeyHeld(unsigned int _key_code)
    {
        return m_prgpCurrentPressedKeys.at(_key_code);
    }

    inline bool IsKeyReleased(unsigned int _key_code)
    {
        return (!m_prgpCurrentPressedKeys.at(_key_code) && m_prgpOldPressedKeys.at(_key_code));
    }

    inline bool IsKeyPressed(unsigned int _key_code)
    {
        return (m_prgpCurrentPressedKeys.at(_key_code) && !m_prgpOldPressedKeys.at(_key_code));
    }

    inline FGUI::POINT GetCursorPos()
    {
        return m_ptCursorPosition;
    }

    inline FGUI::POINT GetCursorPosDelta()
    {
        return m_ptCursorPositionDelta;
    }

    inline bool IsCursorInArea(FGUI::AREA area)
    {
        return (GetCursorPos().m_iX > area.m_iLeft && GetCursorPos().m_iY > area.m_iTop &&
            GetCursorPos().m_iX < area.m_iLeft + area.m_iRight && GetCursorPos().m_iY < area.m_iTop + area.m_iBottom);
    }

    // NOTE: call this function only once (preferably when you initialize your application)
    inline void OnEntryPoint()
    {
        FGUI::INPUT.PullInput = FGUI_IINPUT_SYSTEM::PullInput;
        FGUI::INPUT.IsKeyHeld = FGUI_IINPUT_SYSTEM::IsKeyHeld;
        FGUI::INPUT.IsKeyReleased = FGUI_IINPUT_SYSTEM::IsKeyReleased;
        FGUI::INPUT.IsKeyPressed = FGUI_IINPUT_SYSTEM::IsKeyPressed;
        FGUI::INPUT.GetCursorPos = FGUI_IINPUT_SYSTEM::GetCursorPos;
        FGUI::INPUT.GetCursorPosDelta = FGUI_IINPUT_SYSTEM::GetCursorPosDelta;
        FGUI::INPUT.IsCursorInArea = FGUI_IINPUT_SYSTEM::IsCursorInArea;
        
        // set input type
        FGUI::INPUT.SetInputType(FGUI::INPUT_TYPE::INPUT_SYSTEM);
    }
}
