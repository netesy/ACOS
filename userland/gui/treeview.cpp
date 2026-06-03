#include "treeview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

TreeView::TreeView() : m_root_count(0) {
    m_rect.w = 200;
    m_rect.h = 300;
}

void TreeView::add_root_item(const char* label) {
    if (m_root_count < 16) {
        m_roots[m_root_count] = {label, false, {nullptr}, 0};
        m_root_count++;
    }
}

void TreeView::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    draw_shadow(renderer);
    renderer->blend_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, g_current_theme.surface, 150);
    renderer->draw_rounded_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 4, g_current_theme.border);

    i32 cur_y = m_rect.y + 5;
    for (u32 i = 0; i < m_root_count; i++) {
        draw_item(renderer, &m_roots[i], cur_y, 0);
    }
}

void TreeView::draw_item(acos::graphics::Renderer* renderer, TreeItem* item, i32& y, i32 indent) {
    if (y + 20 > m_rect.y + m_rect.h) return;

    renderer->draw_text(item->expanded ? "v" : ">", m_rect.x + 5 + indent, y, g_current_theme.primary);
    renderer->draw_text(item->label, m_rect.x + 20 + indent, y, g_current_theme.text);
    y += 20;

    if (item->expanded) {
        for (u32 i = 0; i < item->child_count; i++) {
            if (item->children[i]) draw_item(renderer, item->children[i], y, indent + 15);
        }
    }
}

void TreeView::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (pressed && hit_test(mx, my)) {
            i32 relative_y = my - m_rect.y - 5;
            i32 idx = relative_y / 20;
            // This is still simple but better than before
            if (idx >= 0 && idx < (i32)m_root_count) {
                m_roots[idx].expanded = !m_roots[idx].expanded;
            }
        }
    }
}

} // namespace acos::gui
