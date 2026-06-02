#include "tabwidget.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

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

void TabWidget::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    i32 tab_h = 30;
    i32 tab_w = m_rect.w / (m_tab_count ? m_tab_count : 1);

    // Draw tabs
    for (u32 i = 0; i < m_tab_count; i++) {
        i32 tx = m_rect.x + i * tab_w;
        u32 bg = (i == m_selected_tab) ? g_current_theme.surface : g_current_theme.background;
        renderer->blend_rect(tx, m_rect.y, tab_w, tab_h, bg, 200);
        renderer->draw_rect(tx, m_rect.y, tab_w, tab_h, g_current_theme.border);
        renderer->draw_text(m_tabs[i].title, tx + 8, m_rect.y + 8, g_current_theme.text);
    }

    // Content area
    renderer->blend_rect(m_rect.x, m_rect.y + tab_h, m_rect.w, m_rect.h - tab_h, g_current_theme.surface, 150);
    renderer->draw_rect(m_rect.x, m_rect.y + tab_h, m_rect.w, m_rect.h - tab_h, g_current_theme.border);

    if (m_selected_tab < m_tab_count) {
        m_tabs[m_selected_tab].content->set_position(m_rect.x + 4, m_rect.y + tab_h + 4);
        m_tabs[m_selected_tab].content->set_size(m_rect.w - 8, m_rect.h - tab_h - 8);
        m_tabs[m_selected_tab].content->draw(renderer);
    }
}

void TabWidget::handle_event(const acos::input::InputEvent& event) {
    if (event.type == acos::input::InputType::Mouse) {
        i32 mx = (i32)((event.code >> 16) & 0xFFFF);
        i32 my = (i32)(event.code & 0xFFFF);
        bool pressed = (event.value & 0x01) != 0;

        if (pressed && my >= m_rect.y && my < m_rect.y + 30) {
            i32 tab_w = m_rect.w / (m_tab_count ? m_tab_count : 1);
            u32 clicked_tab = (mx - m_rect.x) / tab_w;
            select_tab(clicked_tab);
        }
    }
    if (m_selected_tab < m_tab_count) m_tabs[m_selected_tab].content->handle_event(event);
}

} // namespace acos::gui
