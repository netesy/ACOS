#include <acos/process.h>
#include <acos/runtime.h>
#include "stackwidget.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

StackWidget::StackWidget() : m_count(0), m_current_index(0) {
    m_rect = {0, 0, 100, 100};
}

StackWidget::~StackWidget() {}

Ref<RenderObject> StackWidget::create_render_object() {
    return Ref<RenderObject>();
}

void StackWidget::add_widget(Widget* widget) {
    if (m_count < 16) {
        m_pages[m_count++] = widget;
    }
}

void StackWidget::set_current_index(::acos::u32 index) {
    if (index < m_count) {
        m_current_index = index;
    }
}

} // namespace acos::gui::widgets
