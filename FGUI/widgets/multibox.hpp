//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_MULTIBOX_HH
#define FGUI_MULTIBOX_HH

// includes
#include <string>
#include <utility>
#include <vector>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CMultiBox : public FGUI::CWidgets
  {
  public:
    CMultiBox();

    // @brief: set the multibox state (toggle dropdown list on/off)
    // @args: bool onoff = dropdown state
    void SetState(bool onoff);

    // @brief: get the multibox state (dropdown list enabled or not)
    bool GetState();

    // @brief: sets a custom value to a specific entry on the dropdown
    // @args: std::size_t index = entry index, bool state = entry state
    void SetValue(std::size_t index, bool state);

    // @brief: get the multibox selected entry custom value or state
    // @args: std::size_t index = index of the entry that you want to get the value
    std::size_t GetValue(std::size_t index = 0);

    // @brief: adds a new entry inside the multibox
    // @args: std::string name = entry title, bool value = entry custom value
    void AddEntry(std::string name, bool value = false);

    // @brief: populate widget geometry (draw widget)
    // @args: FGUI::WIDGET_STATUS status = widget status (HOVERED, etc)
    void Geometry(FGUI::WIDGET_STATUS status) override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

    // @brief: save the widget state
    // @args: nlohmann::json module = json module
    void Save(nlohmann::json& module) override;

    // @brief: load the widget state
    // @args: nlohmann::json module = json modulej
    void Load(nlohmann::json& module) override;

    // @brief: handle widget tooltips
    void Tooltip() override;

  private:
    bool m_bIsOpened;
    int m_iEntrySpacing;
    int m_iCustomHeight;
    std::pair<std::vector<std::string>, std::vector<bool>> m_prgpEntries;
  };

} // namespace FGUI

#endif // FGUI_MULTIBOX_HH