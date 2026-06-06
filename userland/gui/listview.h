#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class ListView : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    ListView();
    virtual ~ListView();

    void add_item(const char* item);
    void clear();
    void set_selected(i32 index) { m_selected_index = index; set_paint_dirty(); }
    i32 get_selected() const { return m_selected_index; }

private:
    char m_item_storage[64][64];
    const char* m_items[64];
    usize m_item_count;
    i32 m_selected_index;
};

} // namespace acos::gui::widgets
