#include "messagebox.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

MessageBox::MessageBox() {
    m_rect = {0, 0, 100, 100};
}

MessageBox::~MessageBox() {}

Ref<RenderObject> MessageBox::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
