#include <acos/process.h>
#include <acos/runtime.h>
#include "scrollview.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

ScrollView::ScrollView() {
    m_rect = {0, 0, 100, 100};
}

ScrollView::~ScrollView() {}

Ref<RenderObject> ScrollView::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
