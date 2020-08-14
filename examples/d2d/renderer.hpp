//
// FGUI - Direct2D Renderer
//

#pragma once

#define FGUI_IMPLEMENTATION
#include <FGUI/FGUI.hpp>


// You need to implement your own StringConverter::ToUnicode and StringFormat::format
// NOTE: make sure to tell FGUI to use D2D:
// go to: https://github.com/otvv/fgui/wiki/First-Steps#renderer-helpers for more info.

#define RET_CHK(x) if ( x != S_OK ) return

namespace FGUI_D2D
{
	// NOTE: you still need to initialize these.
	ID2D1Factory* Interface;
	ID2D1RenderTarget* Canvas;
	IDWriteFactory1* TextEngine;
	ID2D1SolidColorBrush* SolidColor;

	inline void CreateFont(FGUI::FONT &_font, std::string _family, int _size, int _flags, bool _bold) // TODO: handle font flags
	{
		std::wstring _name = StringConverter::ToUnicode(_family);

		FGUI::FONT cFont = new FGUI::CFont();

		cFont->name = _name;
		cFont->size = _size;

		if(_bold)
			TextEngine->CreateTextFormat(_name.c_str(), NULL, DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, _size, L"", &cFont->textFmt);
		else
			TextEngine->CreateTextFormat(_name.c_str(), NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, _size, L"", &cFont->textFmt);
		
		_font = cFont;
	}

	inline FGUI::DIMENSION GetScreenSize()
	{
		static int iWidth = GetSystemMetrics(SM_CXSCREEN);
		static int iHeight = GetSystemMetrics(SM_CYSCREEN);

		return { iWidth, iHeight };
	}

	inline FGUI::DIMENSION GetTextSize(FGUI::FONT _font, std::string _text)
	{
		FGUI::DIMENSION screenSize = GetScreenSize();
		int textW, textH = 0;

		const auto str = StringConverter::ToUnicode(_text);
		const auto str_len = static_cast<std::uint32_t>(str.size());

		IDWriteTextLayout* dwrite_layout = nullptr;
		RET_CHK(TextEngine->CreateTextLayout(str.c_str(), str_len, _font->textFmt, screenSize.m_iWidth, screenSize.m_iHeight, &dwrite_layout)) { 0, 0};

		const DWRITE_TEXT_RANGE range
		{
			0,
			str_len
		};

		dwrite_layout->SetFontSize(_font->size, range);
        DWRITE_TEXT_METRICS metrics;
        dwrite_layout->GetMetrics(&metrics);

        textW = metrics.width;
        textH = metrics.height;

		return { textW, textH };
	}

	inline void Text(int _x, int _y, FGUI::FONT _font, FGUI::COLOR _color, std::string _text)
	{
		FGUI::DIMENSION screenSize = GetScreenSize();
		const auto str = StringConverter::ToUnicode(_text);
		const auto str_len = static_cast<std::uint32_t>(str.size());

		IDWriteTextLayout* dwrite_layout = nullptr;
		RET_CHK(TextEngine->CreateTextLayout(str.c_str(), str_len, _font->textFmt, screenSize.m_iWidth, screenSize.m_iHeight, &dwrite_layout));

		const DWRITE_TEXT_RANGE range
		{
			0,
			str_len
		};

		dwrite_layout->SetFontSize(_font->size, range);

		SolidColor->SetColor(D2D1::ColorF(D3DCOLOR_RGBA(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, 255), _color.m_ucAlpha / 255.f));
		Canvas->DrawTextLayout(D2D1::Point2F(float(_x), float(_y)), dwrite_layout, SolidColor);

		dwrite_layout->Release();
	}

	inline void Rectangle(int _x, int _y, int _width, int _height, FGUI::COLOR _color)
	{
		SolidColor->SetColor(D2D1::ColorF(D3DCOLOR_RGBA(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, 255), _color.m_ucAlpha / 255.f));
		Canvas->FillRectangle(D2D1::RectF(float(_x), float(_y), float(_x) + float(_width), float(_y) + float(_height)), SolidColor);
	}

	inline void Outline(int _x, int _y, int _width, int _height, FGUI::COLOR _color)
	{
		// WARNING: do not repeat this at home.
		Rectangle(_x, _y, _width, 1, _color);
		Rectangle(_x, _y, 1, _height, _color);
		Rectangle(_x + _width - 1, _y, 1, _height, _color);
		Rectangle(_x, _y + _height - 1, _width, 1, _color);
	}

	inline void Line(int _from_x, int _from_y, int _to_x, int _to_y, FGUI::COLOR _color)
	{
		SolidColor->SetColor(D2D1::ColorF(D3DCOLOR_RGBA(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, 255), _color.m_ucAlpha / 255.f));
		Canvas->DrawLine({ float(_from_x), float(_from_y) }, { float(_to_x), float(_to_y) }, SolidColor, 1.0f);
	}

	inline void Gradient(int _x, int _y, int _width, int _height, FGUI::COLOR _color1, FGUI::COLOR _color2, bool _horizontal)
	{
        D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES linearGradientBrushProperties = {};
		ID2D1GradientStopCollection *pGradientStops = NULL;
		ID2D1LinearGradientBrush *m_pLinearGradientBrush;

		D2D1_GRADIENT_STOP gradientStops[2];
		gradientStops[0].color = D2D1::ColorF(D3DCOLOR_RGBA(_color1.m_ucRed, _color1.m_ucGreen, _color1.m_ucBlue, 255), _color1.m_ucAlpha / 255.f);
		gradientStops[0].position = 0.0f;
		gradientStops[1].color = D2D1::ColorF(D3DCOLOR_RGBA(_color2.m_ucRed, _color2.m_ucGreen, _color2.m_ucBlue, 255), _color2.m_ucAlpha / 255.f);
		gradientStops[1].position = 1.0f;
		
		RET_CHK(Canvas->CreateGradientStopCollection(
			gradientStops,
			2,
			D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP,
			&pGradientStops
		));

		RET_CHK(Canvas->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(
				D2D1::Point2F(float(_x), float(_y)),
				D2D1::Point2F(float(_x) + float(_width), float(_horizontal) ? float(_y) : float(_y) + float(_height))
			),
			pGradientStops,
			&m_pLinearGradientBrush
		));
		
		Canvas->FillRectangle(D2D1::RectF(float(_x), float(_y), float(_x) + float(_width), float(_y) + float(_height)), m_pLinearGradientBrush);
	}
  
  	// NOTE: call this function only once (preferably when you initialize your application)
	inline void OnEntryPoint()
	{
		FGUI::RENDER.CreateFont = FGUI_D2D::CreateFont;
		FGUI::RENDER.GetScreenSize = FGUI_D2D::GetScreenSize;
		FGUI::RENDER.GetTextSize = FGUI_D2D::GetTextSize;
		FGUI::RENDER.Rectangle = FGUI_D2D::Rectangle;
		FGUI::RENDER.Outline = FGUI_D2D::Outline;
		FGUI::RENDER.Line = FGUI_D2D::Line;
		FGUI::RENDER.Text = FGUI_D2D::Text;
		FGUI::RENDER.Gradient = FGUI_D2D::Gradient;
	}
}
