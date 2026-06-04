#pragma once
#include "widget.h"

namespace acos::gui {

struct Tab {
    const char* title;
    Widget* content;
};

class TabWidget : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    TabWidget();
    virtual ~TabWidget();


    void add_tab(const char* title, Widget* content);
    void select_tab(u32 index);

private:
    Tab m_tabs[8];
    u32 m_tab_count;
    u32 m_selected_tab;
};

} // namespace acos::gui
