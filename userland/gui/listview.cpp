#include "listview.h"
#include "theme.h"

namespace acos::gui {

ListView::ListView() : m_item_count(0), m_selected_index(-1) {
    m_rect.w = 200;
    m_rect.h = 150;
}

void ListView::draw(u32* buffer, u32 pitch) {
    for (i32 y = m_rect.y; y < m_rect.y + m_rect.h; y++) {
        for (i32 x = m_rect.x; x < m_rect.x + m_rect.w; x++) {
            buffer[y * pitch + x] = g_current_theme.widget_bg;
        }
    }
}

void ListView::add_item(const char* item) {
    if (m_item_count < 64) {
        m_items[m_item_count++] = item;
    }
}

} // namespace acos::gui
