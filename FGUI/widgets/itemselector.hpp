//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_ITEMSELECTOR_HH
#define FGUI_ITEMSELECTOR_HH

// includes
#include <functional>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CItemSelector : public FGUI::CWidgets
  {
  public:
    CItemSelector();

    // @brief: set the item selector selected index
    // @args: std::size_t index = selected index (starting with 0)
    void SetIndex(std::size_t index);

    // @brief: get the item selector selected index (entry)
    std::size_t GetIndex();

    // @brief: sets a custom value to a specific entry inside the item selector
    // @args: std::size_t index = entry index, unsigned int value = custom value
    void SetValue(std::size_t index, unsigned int value);

    // @brief: get the item selector selected entry custom value
    std::size_t GetValue();

    // @brief: adds a new entry inside the item selector
    // @args: std::string name = entry title, unsigned int value = entry custom value
    void AddEntry(std::string name, unsigned int value = 0);

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
    // @args: nlohmann::json module = json module
    void Load(nlohmann::json& module) override;

    // @brief: handle widget tooltips
    void Tooltip() override;

  private:
    FGUI::RANGE m_rngBoundaries;
    std::size_t m_ullSelectedEntry;
    std::pair<std::vector<std::string>, std::vector<int>> m_prgpEntries;
  };
} // namespace FGUI

#endif // FGUI_ITEMSELECTOR_HH