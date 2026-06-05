#include "treeview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

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


Ref<RenderObject> TreeView::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> TreeView::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
