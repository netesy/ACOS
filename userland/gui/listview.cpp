#include <acos/process.h>
#include <acos/runtime.h>
#include "listview.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

ListView::ListView() : m_item_count(0), m_selected_index(-1) {
    m_rect = {0, 0, 200, 300};
    for (int i = 0; i < 64; i++) m_items[i] = m_item_storage[i];
}

ListView::~ListView() {}

void ListView::add_item(const char* item) {
    if (m_item_count >= 64 || !item) return;

    usize i = 0;
    while (item[i] && i < 63) {
        m_item_storage[m_item_count][i] = item[i];
        i++;
    }
    m_item_storage[m_item_count][i] = '\0';
    m_item_count++;
    set_paint_dirty();
}

void ListView::clear() {
    m_item_count = 0;
    m_selected_index = -1;
    set_paint_dirty();
}

Ref<RenderObject> ListView::create_render_object() {
    return UIContext::get().region().alloc<RenderListView>();
}

void ListView::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
    auto rl = static_cast<RenderListView*>(render_object.operator->());
    if (rl) {
        rl->set_items(m_items, m_item_count);
        rl->set_selected(m_selected_index);
    }
}

} // namespace acos::gui::widgets
