//
// FGUI - DirectX 9 Renderer
//

#pragma once

#define FGUI_IMPLEMENTATION
#include <FGUI/FGUI.hpp>

// NOTE: make sure to tell FGUI to use D3D9:
// go to: https://github.com/otvv/fgui/wiki/First-Steps#renderer-helpers for more info.

namespace FGUI_D3D9
{
	// NOTE: you still need to initialize the device.
	inline IDirect3DDevice9Ex* m_pDevice;
	// NOTE: to render sprites you need to initialize the sprite first https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dxcreatesprite
	inline ID3DXSprite* m_pSprite;

	inline void CreateFont(FGUI::FONT &_font, const std::string& _family, int _size, int _flags, bool _bold) // TODO: handle font flags
	{
		D3DXCreateFont(m_pDevice, _size, 0, _bold ? FW_BOLD : FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _family.c_str(), &_font);
	}

	inline const FGUI::DIMENSION& GetScreenSize()
	{
		static int iWidth = GetSystemMetrics(SM_CXSCREEN);
		static int iHeight = GetSystemMetrics(SM_CYSCREEN);

		return { iWidth, iHeight };
	}

	inline const FGUI::DIMENSION& GetTextSize(FGUI::FONT &_font, const std::string& _text)
	{
		RECT rectFontSize = { 0, 0 };

		// there's probably a better way of getting the size of a text, this will do for the moment.
		_font->DrawText(0, _text.c_str(), _text.length(), &rectFontSize, DT_CALCRECT, D3DCOLOR_RGBA(0, 0, 0, 0));

		return { (rectFontSize.right - rectFontSize.left), (rectFontSize.bottom - rectFontSize.top) };
	}

	inline void Text(int _x, int _y, FGUI::FONT _font, const FGUI::COLOR& _color, const std::string& _text)
	{
		D3DCOLOR dwColor = D3DCOLOR_RGBA(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, _color.m_ucAlpha);

		RECT rectFontSize = { _x, _y };

		_font->DrawText(0, _text.c_str(), _text.length(), &rectFontSize, DT_NOCLIP, dwColor);
	}

	inline void Rectangle(int _x, int _y, int _width, int _height, const FGUI::COLOR& _color)
	{
		D3DCOLOR dwColor = D3DCOLOR_RGBA(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, _color.m_ucAlpha);

		const FGUI::VERTEX vtxVertices[4] =
		{
			{_x, _y + _height, 0.f, 1.f, dwColor },
			{_x, _y, 0.f, 1.f, dwColor},
			{_x + _width, _y + _height, 0.f, 1.f, dwColor},
			{_x + _width, _y, 0.f, 1.f, dwColor},
		};

		m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtxVertices, sizeof(FGUI::VERTEX));
	}

	inline void Outline(int _x, int _y, int _width, int _height, const FGUI::COLOR& _color)
	{
		// WARNING: do not repeat this at home.
		Rectangle(_x, _y, _width, 1, _color);
		Rectangle(_x, _y, 1, _height, _color);
		Rectangle(_x + _width - 1, _y, 1, _height, _color);
		Rectangle(_x, _y + _height - 1, _width, 1, _color);
	}

	inline void Line(int _from_x, int _from_y, int _to_x, int _to_y, const FGUI::COLOR& _color)
	{
		D3DCOLOR dwColor = D3DCOLOR_RGBA(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, _color.m_ucAlpha);
		
		const FGUI::VERTEX vtxVertices[2] =
		{
			{_from_x, _from_y, 0.f, 0.f, dwColor },
			{_from_x + _to_x, _from_y + _to_y, 0.f, 0.f, dwColor}
		};

		m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vtxVertices, sizeof(FGUI::VERTEX));
	}

	inline void Gradient(int _x, int _y, int _width, int _height, const FGUI::COLOR &_color1, const FGUI::COLOR &_color2, bool _horizontal)
	{
		// there's probably a better way to do this kind of gradient as well.
		D3DCOLOR dwColor1 = D3DCOLOR_RGBA(_color1.m_ucRed, _color1.m_ucGreen, _color1.m_ucBlue, _color1.m_ucAlpha);
		D3DCOLOR dwColor2 = D3DCOLOR_RGBA(_color2.m_ucRed, _color2.m_ucGreen, _color2.m_ucBlue, _color2.m_ucAlpha);

		const FGUI::VERTEX vtxVertices[4] = 
		{ 
			{ _x, _y, 0.0f, 1.0f, dwColor1 },
			{ _x + _width, _y, 0.0f, 1.0f, _horizontal ? dwColor2 : dwColor1 },
			{ _x, _y + _height, 0.0f, 1.0f, _horizontal ? dwColor1 : dwColor2 },
			{ _x + _width, _y + _height, 0.0f, 1.0f, dwColor2 }
		};

		m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtxVertices, sizeof(FGUI::VERTEX));
	}
  
  	// NOTE: call this function only once (preferably when you initialize your application)
	inline void OnEntryPoint()
	{
		FGUI::RENDER.CreateFont = FGUI_D3D9::CreateFont;
		FGUI::RENDER.GetScreenSize = FGUI_D3D9::GetScreenSize;
		FGUI::RENDER.GetTextSize = FGUI_D3D9::GetTextSize;
		FGUI::RENDER.Rectangle = FGUI_D3D9::Rectangle;
		FGUI::RENDER.Outline = FGUI_D3D9::Outline;
		FGUI::RENDER.Line = FGUI_D3D9::Line;
		FGUI::RENDER.Text = FGUI_D3D9::Text;
		FGUI::RENDER.Gradient = FGUI_D3D9::Gradient;
		FGUI::RENDER.Sprite = FGUI_D3D9::Sprite;
	}

	inline void Sprite(void* textuer, float x, float y, float scale, float rotation, FGUI::COLOR _color1)
	{
		IDirect3DTexture9* tex = (IDirect3DTexture9*)textuer;
		D3DCOLOR color = D3DCOLOR_RGBA(_color1.m_ucRed, _color1.m_ucGreen, _color1.m_ucBlue, _color1.m_ucAlpha);

		float screen_pos_x = x;
		float screen_pos_y = y;

		D3DSURFACE_DESC surfaceDesc;
		int level = 0; //The level to get the width/height of (probably 0 if unsure)
		tex->GetLevelDesc(level, &surfaceDesc);
		// Texture center
		D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)surfaceDesc.Width / 2, (float)surfaceDesc.Height / 2);

		// Screen position of the sprite
		D3DXVECTOR2 trans = D3DXVECTOR2(screen_pos_x, screen_pos_y);

		// Build our matrix to rotate, scale and position our sprite
		D3DXMATRIX mat;

		D3DXVECTOR2 scaling(scale, scale);

		// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);

		//pDevice->SetRenderState(D3DRS_ZENABLE, false);
		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		m_pDevice->SetPixelShader(NULL);
		m_pSprite->Begin(NULL);
		m_pSprite->SetTransform(&mat); // Tell the sprite about the matrix
		m_pSprite->Draw(tex, NULL, NULL, NULL, color);
		m_pSprite->End();
	}
}
