#include "listview.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>

namespace acos::gui::widgets {

ListView::ListView() : m_item_count(0), m_selected_index(-1) {
    m_rect.w = 200;
    m_rect.h = 150;
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled | (u32)WidgetFlags::Focusable;
}


void ListView::draw_to_buffer(u32* buffer [[maybe_unused]], u32 pitch [[maybe_unused]]) {}


void ListView::add_item(const char* item) {
    if (m_item_count < 64 && item) {
        m_items[m_item_count++] = item;
    }
}

void ListView::clear() {
    m_item_count = 0;
    m_selected_index = -1;
}

Ref<RenderObject> Listview::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> ListView::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
