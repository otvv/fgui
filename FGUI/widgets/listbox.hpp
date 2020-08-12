//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_LISTBOX_HH
#define FGUI_LISTBOX_HH

// includes
#include <string>
#include <utility>
#include <vector>
#include <functional>

// library includes
#include "widgets.hpp"

namespace FGUI
{

  class CListBox : public FGUI::CWidgets
  {
  public:
    CListBox();

    // @brief: set the listbox selected index
    // @params: std::size_t index = selected index (starting with 0)
    void SetIndex(std::size_t index);

    // @brief: get the listbox selected index (entry)
    std::size_t GetIndex();

    // @brief: get the listbox selected entry custom value
    int GetValue();

    // @brief: adds a new entry inside the listbox
    // @params: std::string name = entry title, unsigned int value = entry custom value
    void AddEntry(std::string name, unsigned int value);

    // @brief: adds a function callback for the listbox (it will call the function whenever the user selects something on the listbox)
    // @params: std::function<void()> callback = function instance
    void AddCallback(std::function<void()> callback);

    // @brief: populate widget geometry (draw widget)
    void Geometry() override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

    // @brief: save the widget state
    // @params: nlohmann::json module = json module
    void Save(nlohmann::json& module) override;

    // @brief: load the widget state
    // @params: nlohmann::json module = json module
    void Load(nlohmann::json& module) override;

    // @brief: handle widget tooltips
    void Tooltip() override;

  private:
    std::size_t m_ullSelectedEntry;
    int m_iEntrySpacing;
    bool m_bIsDraggingThumb;
    int m_iScrollThumbPosition;
    std::pair<std::vector<std::string>, std::vector<int>> m_prgpEntries;
    std::function<void()> m_fnctCallback;
  };

} // namespace FGUI

#endif // FGUI_LISTBOX_HH