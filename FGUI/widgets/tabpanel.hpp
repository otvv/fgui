//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_TABPANEL_HH
#define FGUI_TABPANEL_HH

// includes
#include <vector>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  using TAB_STYLE = enum struct ESTabLayout_t : int {
    HORIZONTAL = 0,
    VERTICAL = 1
  };

  class CTabPanel : public FGUI::CWidgets
  {
  public:
    CTabPanel();

    // @brief: adds a new tab button into the tab panel
    // @params: std::string title = tab title
    void AddTab(std::string title);

    // @brief: set a default selected tab
    // @params: std::size_t index = tab to select
    void SetIndex(std::size_t index);

    // @brief: returns the current selected tab of the panel
    std::size_t GetIndex();

    // @brief: set the tab style (HORIZONTAL = it will draw the tab panel horizontaly; VERTICAL = it will draw the tab panel verticaly)
    // @params: FGUI::TAB_STYLE style = tab panel style (layout)
    void SetStyle(FGUI::TAB_STYLE style);

    // @brief: returns the current style of the tab panel
    int GetStyle();

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
    int m_iEntrySpacing;
    std::size_t m_ullSelectedEntry;
    std::vector<std::string> m_prgpTabButtons;
    int m_nStyle;
  };

} // namespace FGUI

#endif // FGUI_TABPANEL_HH