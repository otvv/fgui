/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include <string>
#include <memory>
#include <fstream>
#include <functional>

// framework includes
#include "../dependencies/json.hh"
#include "../dependencies/aliases.hh"
#include "../dependencies/definitions.hh"

namespace fgui {

	// declarations
	class container;

	class element : public std::enable_shared_from_this<fgui::element> {
		friend class fgui::container;
	public:

		// sets a custom position for the element
		inline void set_position(const int &x, const int &y) noexcept {
			m_x = x;
			m_y = y;
		}

		// sets the a custom size for the element
		inline void set_size(const int &width, const int &height) noexcept {

			m_width = width;
			m_height = height;
		}

		// check if the element is being controlled by a controller
		bool unlocked();

		// get the current size of the element
		inline fgui::dimension get_size() const noexcept {

			return { m_width, m_height };
		}

		// get the current position of the element
		inline fgui::point get_position() const noexcept {

			return { m_x, m_y };
		}

		// sets a custom title for the element
		inline void set_title(const std::string_view title) noexcept {

			m_title = title;
		}

		// returns the title of the element
		inline std::string_view get_title() const noexcept {
			
			return m_title;
		}

		// sets a custom tooltip for the element 
		inline void set_tooltip(const std::string_view tooltip) noexcept {

			m_tooltip = tooltip;
		}
		
		// get the container that is behaving like a window
		std::shared_ptr<fgui::element> get_window();

		// get the first container available
		std::shared_ptr<fgui::element> get_first_container();

		// get the container window area (position)
		fgui::point get_absolute_position();

		// sets a custom flag for the element
		inline void set_flag(const int &flag) noexcept {
			
			m_flags |=  static_cast<int>(flag);
		}

		// get the flag of the element
		inline bool get_flag(const fgui::detail::element_flags &flag) const noexcept {

			if (m_flags & static_cast<int>(flag))
				return true;

			return false;
		}

		// set the element family
		inline void set_family(const int &type) noexcept {

			m_type =  static_cast<int>(type);
		}

		// get the element type
		inline bool get_family(const fgui::detail::element_type &type) const noexcept {
			
			if (m_type ==  static_cast<int>(type))
				return true;

			return false;
		}

		// set the element page controller (element bound)
		inline void set_controller(const std::shared_ptr<fgui::element> &controller) noexcept {

			m_controller = controller;
		}

		// sets a custom indentificator for the element (this is used by the config system)
		inline void set_identificator(const std::string_view identificator) noexcept {

			m_identificator = identificator;
		}

		// get the current identificator of the element
		inline std::string_view get_identificator() const noexcept {

			return m_identificator;
		}

		// allows the user to change the font of the element
		inline void set_font(const std::string_view font_family, int size, int flags = 0, bool bold = false) noexcept {

			fgui::render.create_font(m_font, font_family, size, flags, bold);
		}

		inline void set_font(const fgui::element_font &element_font) noexcept {

			fgui::render.create_font(m_font, element_font.family, element_font.size, element_font.flags, element_font.bold);
		}

		// returns the font that the element is currently using
		inline fgui::font get_font() const noexcept {

			return m_font;
		}
		
	protected:
		virtual void draw() = 0; // draw the element
		virtual void handle_input() = 0; // handles the element keyboard and mouse input
		virtual void update() = 0; // handles the element updates
		virtual void tooltip() = 0; // draw the element tooltip
		virtual void save(nlohmann::json& json_module) = 0; // write the element state on a file
		virtual void load(const std::string_view file_name) = 0; // read the element state of a file
	protected:
		int m_type;
		int m_flags;
		int m_x, m_y;
		int m_page_index;
		fgui::font m_font;
		int m_width, m_height;
		std::string_view m_title;
		std::string_view m_tooltip;
		std::string_view m_identificator;
		fgui::point m_absolute_position;
		int m_original_width, m_original_height;
		std::shared_ptr<fgui::element> m_controller;
		std::shared_ptr<fgui::element> m_parent_element;
	};
}
