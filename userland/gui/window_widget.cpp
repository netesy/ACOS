#include "window_widget.h"
#include "theme.h"
#include <kernel/memory/heap.h>
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::gui {

WindowWidget::WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title), m_child_count(0), m_window_handle(0) {
    m_rect = {x, y, w, h};
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled;
    m_state = WidgetState::Normal;
    m_elevation = 8;
}

WindowWidget::~WindowWidget() {}

void WindowWidget::add_child(Widget* child) {
    if (m_child_count < 32) {
        m_children[m_child_count++] = child;
        child->set_parent(this);
    }
}

void WindowWidget::draw(acos::graphics::Renderer* renderer) {
    if (!(m_flags & (u32)WidgetFlags::Visible) || !renderer) return;

    draw_shadow(renderer);

    u8 glass_alpha = (u8)((g_current_theme.glass_bg >> 24) & 0xFF);

    renderer->blend_rect(static_cast<u32>(m_rect.x), static_cast<u32>(m_rect.y),
                         static_cast<u32>(m_rect.w), static_cast<u32>(m_rect.h),
                         g_current_theme.glass_bg, glass_alpha);

    renderer->blend_rect(static_cast<u32>(m_rect.x), static_cast<u32>(m_rect.y),
                         static_cast<u32>(m_rect.w), 30, g_current_theme.glass_bg, 200);

    renderer->draw_rounded_rect(static_cast<u32>(m_rect.x), static_cast<u32>(m_rect.y),
                                static_cast<u32>(m_rect.w), static_cast<u32>(m_rect.h),
                                g_current_theme.window_radius, g_current_theme.border);

    renderer->draw_text(m_title, static_cast<u32>(m_rect.x + 12),
                        static_cast<u32>(m_rect.y + 10), g_current_theme.text,
                        acos::graphics::Font::Alignment::Left, acos::graphics::Font::Style::Bold);

    for (usize i = 0; i < m_child_count; ++i) {
        if (m_children[i] && m_children[i]->is_visible()) {
            m_children[i]->draw(renderer);
        }
    }
}

void WindowWidget::draw_to_buffer(u32* buffer [[maybe_unused]], u32 pitch [[maybe_unused]]) {}

void WindowWidget::show() {
    m_flags |= (u32)WidgetFlags::Visible;
}

} // namespace acos::gui
