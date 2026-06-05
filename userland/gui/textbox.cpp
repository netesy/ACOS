#include "textbox.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

TextBox::TextBox() {
    m_rect = {0, 0, 100, 100};
}

TextBox::~TextBox() {}

Ref<RenderObject> TextBox::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
