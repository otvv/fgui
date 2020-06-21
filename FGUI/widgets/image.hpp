//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_IMAGE_HH
#define FGUI_IMAGE_HH

// includes
#include <functional>

// library includes
#include "widgets.hpp"

namespace FGUI
{

	class CImage : public FGUI::CWidgets
	{
	public:
		CImage();

		// @brief: set image texture or data
		void SetImage(void* image);

		// @brief: transforms the scale of the image
		void SetScale(float scale);

		// @brief: transforms the rotation of the image
		void SetRotation(float rotation);

		// @brief: sets color modulation of the image
		void SetColor(FGUI::COLOR color);

		// @brief: populate widget geometry (draw widget)
		void Geometry() override;

		// @brief: handle update operations on the widget
		void Update() override;

		// @brief: handle input inside the widget
		void Input() override;
	private:
		void* m_pImage;
		float m_fScale;
		float m_fRotation;
		FGUI::COLOR m_clColor;
	};

} // namespace FGUI

#endif // FGUI_IMAGE_HH