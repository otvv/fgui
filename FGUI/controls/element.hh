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
#include "../dependencies/definitions.hh"

namespace fgui {

	// declarations
	class container;

	struct element_font {
		std::string m_family;
		int m_size;
		int m_flags;
		bool m_bold;
	};

	class element : public std::enable_shared_from_this<fgui::element> {
		friend class fgui::container;
	public:

		// sets a custom position for the element
		void set_position(int x, int y);

		// sets the a custom size for the element
		void set_size(int width, int height);

		// check if the element is unlocked
		bool unlocked();

		// get the current size of the element
		fgui::dimension get_size();

		// get the current position of the element
		fgui::point get_position();

		// sets a custom title for the element
		void set_title(std::string title);

		// returns the title of the element
		std::string get_title();

		// sets a custom tooltip for the element 
		void set_tooltip(std::string tooltip);
		
		// get the container that is behaving like a window
		std::shared_ptr<fgui::element> get_window();

		// get the first container available
		std::shared_ptr<fgui::element> get_first_container();

		// get the container window area (position)
		fgui::point get_absolute_position();

		// sets a custom flag for the element
		void set_flag(int flag);

		// get the flag of the element
		bool get_flag(fgui::element_flag flag);

		// set the element family
		void set_family(int family);

		// get the element family (type)
		bool get_family(fgui::element_family family);

		// set the element page controller (element bound)
		void set_controller(std::shared_ptr<fgui::element> controller);

		// sets a custom indentificator for the element (this is used by the config system)
		void set_identificator(std::string identificator);

		// get the current identificator of the element
		std::string get_identificator();

		// allows the user to change the font of the element
		void set_font(std::string font_family, int size, int flags = 0, bool bold = false);
		void set_font(fgui::element_font element_font);

		// returns the font that the element is currently using
		fgui::font get_font();
		
	protected:
		virtual void draw() = 0; // draw the element
		virtual void handle_input() = 0; // handles the element keyboard and mouse input
		virtual void update() = 0; // handles the element updates
		virtual void tooltip() = 0; // draw the element tooltip
		virtual void save(const std::string &file_name, nlohmann::json& json_module) = 0; // write the element state on a file
		virtual void load(const std::string &file_name) = 0; // read the element state of a file
	protected:
		int m_flags;
		int m_family;
		int m_x, m_y;
		int m_page_index;
		fgui::font m_font;
		std::string m_title;
		int m_width, m_height;
		std::string m_tooltip;
		std::string m_identificator;
		fgui::point m_absolute_position;
		int m_original_width, m_original_height;
		std::shared_ptr<fgui::element> m_controller;
		std::shared_ptr<fgui::element> m_parent_element;
	};
}
