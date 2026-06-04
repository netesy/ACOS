#pragma once
#include "widget.h"
#include "signal.h"

namespace acos::gui {

class Menu : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    Menu();
    virtual ~Menu();


    void add_item(const char* label);

    Signal<u32> on_item_selected;

private:
    const char* m_items[16];
    u32 m_count;
    i32 m_hovered_index;
};

} // namespace acos::gui
