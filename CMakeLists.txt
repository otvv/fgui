##
## library project file
##

# minimum cmake version required
cmake_minimum_required(VERSION 2.8)

# enable c++ 17
set(CMAKE_CXX_STANDARD 17)

# project name
project(fgui)

# disable warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-narrowing")

# library source files
add_library(fgui SHARED

    # elements
    FGUI/controls/button.cc
    FGUI/controls/checkbox.cc
    FGUI/controls/colorlist.cc
    FGUI/controls/colorpicker.cc
    FGUI/controls/combobox.cc
    FGUI/controls/container.cc
    FGUI/controls/element.cc
    FGUI/controls/keybinder.cc
    FGUI/controls/label.cc
    FGUI/controls/listbox.cc
    FGUI/controls/multibox.cc
    FGUI/controls/slider.cc
    FGUI/controls/spinner.cc
    FGUI/controls/tabs.cc
    FGUI/controls/textbox.cc

    # other
    FGUI/handler/handler.cc
    FGUI/notifications/notifications.cc)
 
