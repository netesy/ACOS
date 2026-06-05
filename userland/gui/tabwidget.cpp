#include "tabwidget.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

TabWidget::TabWidget() : m_tab_count(0), m_selected_tab(0) {
    m_rect = {0, 0, 300, 200};
}

TabWidget::~TabWidget() {}

void TabWidget::add_tab(const char* title, Widget* content) {
    if (m_tab_count < 8) {
        m_tabs[m_tab_count++] = {title, content};
        content->set_parent(this);
        content->set_visible(m_tab_count == 1);
    }
}

void TabWidget::select_tab(u32 index) {
    if (index < m_tab_count) {
        m_selected_tab = index;
        for (u32 i = 0; i < m_tab_count; i++) {
            m_tabs[i].content->set_visible(i == index);
        }
    }
}



Ref<RenderObject> TabWidget::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
