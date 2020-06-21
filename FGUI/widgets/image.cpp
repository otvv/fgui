//
// FGUI - feature rich graphical user interface
//

// library includes
#include "image.hpp"

namespace FGUI
{
	CImage::CImage()
	{
		m_strTitle = "Image";
		m_dmSize = { 0, 0 };
		m_ulFont = 0;
		m_nType = static_cast<int>(WIDGET_TYPE::IMAGE);
		m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE);
		m_pImage = nullptr;
		m_fScale = 1.f;
		m_fRotation = 0.f;
		m_clColor = { 255, 255, 255, 255 };
	}
	
	void CImage::SetImage(void* image)
	{
		m_pImage = image;
	}

	void CImage::SetScale(float scale)
	{
		m_fScale = scale;
	}

	void CImage::SetRotation(float rotation)
	{
		m_fRotation = rotation;
	}

	void CImage::SetColor(FGUI::COLOR color)
	{
		m_clColor = color;
	}

	void CImage::Geometry()
	{
		// widget's area
		FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

		if (m_pImage)
			FGUI::RENDER.Sprite(m_pImage, arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_fScale, m_fRotation, m_clColor);
	}

	void CImage::Update()
	{
	}

	void CImage::Input()
	{
	}
} // namespace FGUI