#include "button.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Button::Button() {
    m_rect = {0, 0, 100, 100};
}

Button::~Button() {}

Ref<RenderObject> Button::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
