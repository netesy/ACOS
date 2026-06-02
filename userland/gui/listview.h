#pragma once
#include "widget.h"

namespace acos::gui {

class ListView : public Widget {
public:
    ListView();
    void draw(acos::graphics::Renderer* renderer) override;
    void handle_event(const acos::input::InputEvent& event) override;
    void draw_to_buffer(u32* buffer, u32 pitch);
    void add_item(const char* item);
    void clear();
    void set_selected(i32 index) { m_selected_index = index; }
    i32 get_selected() const { return m_selected_index; }

private:
    const char* m_items[64];
    usize m_item_count;
    i32 m_selected_index;
};

} // namespace acos::gui
