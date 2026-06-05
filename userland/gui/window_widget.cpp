#include "window_widget.h"
#include "core/render_object.h"
#include "core/render_widgets.h"
#include "core/context.h"

namespace acos::gui {

WindowWidget::WindowWidget(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title), m_window_handle(0) {
    m_rect = {x, y, w, h};
}

WindowWidget::~WindowWidget() {}

Ref<RenderObject> WindowWidget::create_render_object() {
    return UIContext::get().region().alloc<widgets::RenderPanel>();
}

void WindowWidget::update_render_object(Ref<RenderObject> render_object) {
    Widget::update_render_object(render_object);
}

void WindowWidget::show() {
    set_visible(true);
}

} // namespace acos::gui
