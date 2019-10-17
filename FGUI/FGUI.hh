/*                                       *
 * fgui - an extensive oop gui framework *
 *                                       */

#pragma once

 // includes
#include "handler/handler.hh"
#include "controls/tabs.hh"
#include "controls/button.hh"
#include "controls/checkbox.hh"
#include "controls/colorpicker.hh"
#include "controls/combobox.hh"
#include "controls/element.hh"
#include "controls/keybinder.hh"
#include "controls/label.hh"
#include "controls/listbox.hh"
#include "controls/multibox.hh"
#include "controls/slider.hh"
#include "controls/spinner.hh"
#include "controls/textbox.hh"
#include "controls/colorlist.hh"
#include "controls/container.hh"
#include "dependencies/aliases.hh"
#include "notifications/notifications.hh"

#pragma region MACROS

#define REGISTER_TAB( tab, x, y, layout, font, parent, page ) \
{ \
    tab = std::make_shared<fgui::tabs>(); \
    tab->set_position(x, y); \
    tab->set_font(font); \
    tab->set_layout(layout); \
    parent->add_control(tab, page, true);\
} \

#define REGISTER_CURSOR( cursor_type, input_state ); \
{ \
    fgui::handler::set_cursor(cursor_type); \
	fgui::handler::set_input_state(input_state); \
} \

#define REGISTER_NOTIFICATIONS(x, y, notification_font ); \
{ \
    fgui::handler::register_notifications(x, y, notification_font); \
} \

#define ADD_BUTTON( element, x, y, name, width, height, font, parent, page ) \
{ \
    element = std::make_shared<fgui::button>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_size(width, height); \
    element->set_font(font); \
    parent->add_control(element, page, true); \
} \

#define ADD_CHECKBOX( element, x, y, name, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::checkbox>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_COLORLIST( element, x, y, name, width, height, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::colorlist>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_size(width, height); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page, true); \
} \

#define ADD_COLORPICKER( element, x, y, color, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::colorpicker>(); \
    element->set_position(x, y); \
    element->set_color(color); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_COMBOBOX( element, x, y, name, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::combobox>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_GROUPBOX( element, x, y, name, width, height, font, parent, page, scrollable, resizeable, hideable) \
{ \
    element = std::make_shared<fgui::container>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_size(width, height); \
    element->set_font(font); \
    element->set_scrollbar_state(scrollable); \
    element->set_resize_state(resizeable); \
    element->set_hidden_state(hideable); \
    parent->add_control(element, page, true);\
} \

#define ADD_KEYBINDER( element, x, y, name, key, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::keybinder>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_key(key); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_LABEL( element, x, y, text, type, font, parent, page ) \
{ \
    element = std::make_shared<fgui::label>(); \
    element->set_position(x, y); \
    element->set_text(text); \
    element->set_type(type); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_LISTBOX( element, x, y, name, width, height, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::listbox>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_size(width, height); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page, true); \
} \

#define ADD_MULTIBOX( element, x, y, name, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::multibox>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_SLIDER( element, x, y, name, value, min, max, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::slider>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_value(value); \
    element->set_boundaries(min, max); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_SPINNER( element, x, y, name, value, min, max, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::spinner>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_value(value); \
    element->set_boundaries(min, max); \
    element->set_identificator(identificator); \
    element->set_font(font); \
    parent->add_control(element, page, true); \
} \

#define ADD_TEXTBOX( element, x, y, name, text, max_length, flag, identificator, font, parent, page ) \
{ \
    element = std::make_shared<fgui::textbox>(); \
    element->set_position(x, y); \
    element->set_title(name); \
    element->set_text(text); \
    element->set_identificator(identificator); \
    element->set_length(max_length); \
    element->set_text_flag(flag); \
    element->set_font(font); \
    parent->add_control(element, page); \
} \

#define ADD_WINDOW( window, x, y, title, width, height, key, font, resizeable ) \
{ \
    window = std::make_shared<fgui::container>(); \
    window->set_position(x, y); \
    window->set_title(title); \
    window->set_size(width, height); \
    window->set_font(font); \
    window->set_resize_state(resizeable); \
\
\
    fgui::handler::register_window(window); \
    fgui::handler::set_key(key, window); \
} \

#define ADD_TAB( tabs, name ); \
    tabs->add_tab(name); \
\

// comboboxes and multiboxes
#define ADD_ITEM( element, name, value ); \
    element->add_item(name, value); \
\

#define ADD_CONTROLLER( element, controller ) \
    element->set_controller(controller); \
\

#define ADD_TOOLTIP( element, tooltip ) \
    element->set_tooltip(tooltip); \
\

// button, comboboxes and containers
#define ADD_FUNCTION( element, function ) \
    element->set_function(function); \
\

// colorlist
#define ADD_COLOR( element, label, color, gradient ) \
    element->add_color(label, color, gradient); \
\

// slider
#define ADD_BOUNDARIES_TEXT( element, min_text, max_text ) \
    element->set_boundaries_text(min_text, max_text); \
\

#pragma endregion