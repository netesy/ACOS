#pragma once
#include "widget.h"

namespace acos::gui {

class ListView : public Widget {
public:
    ListView();
    void draw(u32* buffer, u32 pitch) override;
    void add_item(const char* item);

private:
    const char* m_items[64];
    usize m_item_count;
    i32 m_selected_index;
};

} // namespace acos::gui
