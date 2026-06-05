#include "stackwidget.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

StackWidget::StackWidget() {
    m_rect = {0, 0, 100, 100};
}

StackWidget::~StackWidget() {}

Ref<RenderObject> StackWidget::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
