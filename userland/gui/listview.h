#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class ListView : public Widget {
public:
    Ref<RenderObject> create_render_object() override;
    void update_render_object(Ref<RenderObject> render_object) override;

    ListView();
    virtual ~ListView();

    void on_event(Event& event) override;

    void add_item(const char* item);
    void clear();
    void set_selected(i32 index) { m_selected_index = index; set_paint_dirty(); }
    i32 get_selected() const { return m_selected_index; }
    const char* get_item(i32 index) const {
        if (index >= 0 && index < (i32)m_item_count) {
            return m_item_storage[index];
        }
        return nullptr;
    }

private:
    char m_item_storage[64][64];
    const char* m_items[64];
    usize m_item_count;
    i32 m_selected_index;
};

} // namespace acos::gui::widgets
