#include "spinbox.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

SpinBox::SpinBox() {
    m_rect = {0, 0, 100, 100};
}

SpinBox::~SpinBox() {}

Ref<RenderObject> SpinBox::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
