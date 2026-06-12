#include <acos/process.h>
#include <acos/runtime.h>
#include "tabwidget.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

TabWidget::TabWidget() {
    m_rect = {0, 0, 100, 100};
}

TabWidget::~TabWidget() {}

Ref<RenderObject> TabWidget::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
