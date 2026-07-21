#include <acos/process.h>
#include <acos/runtime.h>
#include "listview.h"
#include <acos/renderer.h>
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui::widgets {

ListView::ListView() : m_item_count(0), m_selected_index(-1) {
    m_rect = {0, 0, 200, 300};
    for (int i = 0; i < 64; i++) m_items[i] = m_item_storage[i];
}

ListView::~ListView() {}

void ListView::on_event(Event& event) {
    const auto& raw = event.raw;
    if (raw.type == ::acos::abi::InputType::Mouse) {
        ::acos::i32 mx = event.mouse_x;
        ::acos::i32 my = event.mouse_y;
        bool pressed = (raw.value & 0x01) != 0;

        if (m_rect.contains(mx, my)) {
            if (pressed) {
                ::acos::i32 relative_y = my - m_rect.y;
                ::acos::i32 clicked_index = relative_y / 20;
                if (clicked_index >= 0 && clicked_index < (::acos::i32)m_item_count) {
                    m_selected_index = clicked_index;
                    set_paint_dirty();
                }
            }
            event.stop_propagation();
        }
    }
}

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
