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

} // namespace acos::gui::widgets
