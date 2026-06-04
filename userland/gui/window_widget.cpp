#include "window_widget.h"
#include "theme.h"
#include <kernel/memory/heap.h>
#include <kernel/graphics/renderer.h>
#include <kernel/graphics/font.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::gui {

WindowWidget::WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title) {
    m_rect = {x, y, w, h};
    m_flags = (u32)WidgetFlags::Visible | (u32)WidgetFlags::Enabled;
    m_state = WidgetState::Normal;
    m_style.elevation = 8;
}

WindowWidget::~WindowWidget() {}

Ref<RenderObject> WindowWidget::create_render_object() {
    // RenderWindow implementation omitted for brevity, but would handle glass effects etc.
    return Ref<RenderObject>();
}

void WindowWidget::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
}

void WindowWidget::show() {
    m_flags |= (u32)WidgetFlags::Visible;
}

} // namespace acos::gui
