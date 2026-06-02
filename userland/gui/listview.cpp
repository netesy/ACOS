#include "listview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui {

ListView::ListView() : m_item_count(0), m_selected_index(-1) {
    m_rect.w = 200;
    m_rect.h = 150;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Focusable;
}

void ListView::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible) || !renderer) return;

    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 180);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.widget_radius, g_current_theme.border);

    i32 item_y = m_rect.y + 5;
    constexpr i32 item_height = 24;
    for (usize i = 0; i < m_item_count; ++i) {
        if (item_y + item_height > m_rect.y + m_rect.h) break;
        if (static_cast<i32>(i) == m_selected_index) {
            renderer->blend_rect(m_rect.x + 4, item_y, m_rect.w - 8, item_height, g_current_theme.primary, 100);
            renderer->draw_rounded_rect(m_rect.x + 4, item_y, m_rect.w - 8, item_height, 4, g_current_theme.primary);
        }
        renderer->draw_text(m_items[i], m_rect.x + 10, item_y + 4, g_current_theme.text);
        item_y += item_height;
    }
}

void ListView::draw_to_buffer(u32* buffer [[maybe_unused]], u32 pitch [[maybe_unused]]) {
    // Legacy support not needed as we use the renderer
}

void ListView::add_item(const char* item) {
    if (m_item_count < 64 && item) {
        m_items[m_item_count++] = item;
    }
}

void ListView::clear() {
    m_item_count = 0;
    m_selected_index = -1;
}

} // namespace acos::gui
