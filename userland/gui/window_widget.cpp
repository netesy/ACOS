#include "window_widget.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

WindowWidget::WindowWidget() {
    m_rect = {0, 0, 100, 100};
}

WindowWidget::~WindowWidget() {}

Ref<RenderObject> WindowWidget::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
