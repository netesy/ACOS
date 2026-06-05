#include "radiobutton.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

RadioButton::RadioButton() {
    m_rect = {0, 0, 100, 100};
}

RadioButton::~RadioButton() {}

Ref<RenderObject> RadioButton::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
