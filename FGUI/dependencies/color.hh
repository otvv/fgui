/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <cmath>
#include <math.h>
#include <algorithm>

namespace fgui {

	class color {
	public:

		color(int red, int green, int blue, int alpha = 255) {
			m_red = std::clamp<int>(red, 0, 255);
			m_green = std::clamp<int>(green, 0, 255);
			m_blue = std::clamp<int>(blue, 0, 255);
			m_alpha = std::clamp<int>(alpha, 0, 255);
		}

		color(fgui::color color, int alpha) {
			m_red = std::clamp<int>(color.m_red, 0, 255);
			m_green = std::clamp<int>(color.m_green, 0, 255);
			m_blue = std::clamp<int>(color.m_blue, 0, 255);
			m_alpha = std::clamp<int>(alpha, 0, 255);
		}

		static fgui::color hsb_to_rgb(float hue, float saturation, float brightness, int alpha = 255) {

			hue = std::clamp(hue, 0.f, 1.f);
			saturation = std::clamp(saturation, 0.f, 1.f);
			brightness = std::clamp(brightness, 0.f, 1.f);

			float h = (hue == 1.f) ? 0.f : (hue * 6.f);
			float f = h - static_cast<int>(h);
			float p = brightness * (1.f - saturation);
			float q = brightness * (1.f - saturation * f);
			float t = brightness * (1.f - (saturation * (1.f - f)));

			if (h < 1)
				return fgui::color(brightness * 255, t * 255, p * 255, alpha);

			else if (h < 2)
				return fgui::color(q * 255, brightness * 255, p * 255, alpha);

			else if (h < 3)
				return fgui::color(p * 255, brightness * 255, t * 255, alpha);

			else if (h < 4)
				return fgui::color(p * 255, q * 255, brightness * 255, alpha);

			else if (h < 5)
				return fgui::color(t * 255, p * 255, brightness * 255, alpha);

			else
				return fgui::color(brightness * 255, p * 255, q * 255, alpha);

		}

		static float get_hue(fgui::color color) {

			float r = (std::clamp<int>(color.m_red, 0, 255) / 255.f);
			float g = (std::clamp<int>(color.m_green, 0, 255) / 255.f);
			float b = (std::clamp<int>(color.m_blue, 0, 255) / 255.f);
			float max = std::fmaxf(std::fmaxf(r, g), b);
			float min = std::fminf(std::fminf(r, g), b);
			float delta = max - min;

			if (delta != 0) {

				float hue;

				if (r == max)
					hue = (g - b) / delta;

				else {

					if (g == max)
						hue = 2 + (b - r) / delta;
					else
						hue = 4 + (r - g) / delta;
				}

				hue *= 60;

				if (hue < 0)
					hue += 360;

				return hue / 360;
			}

			else
				return 0;
		}

		static fgui::color interpolate(fgui::color color1, fgui::color color2, float ttt) {

			float r = (std::clamp<int>(color1.m_red, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_red, 0, 255)* ttt);
			float g = (std::clamp<int>(color1.m_green, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_green, 0, 255) * ttt);
			float b = (std::clamp<int>(color1.m_blue, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_blue, 0, 255) * ttt);
			float a = (std::clamp<int>(color1.m_alpha, 0, 255) * (1.f - ttt) + std::clamp<int>(color2.m_alpha, 0, 255) * ttt);

			return fgui::color(r, g, b, a);
		}

		unsigned char m_red, m_green, m_blue, m_alpha;
	};
}
