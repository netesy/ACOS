#include "messagebox.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

MessageBox::MessageBox(const char* title, const char* message) : WindowWidget(title, 200, 200, 300, 150) {
    (void)message;
}

MessageBox::~MessageBox() {}

Ref<RenderObject> MessageBox::create_render_object() {
    return Ref<RenderObject>();
}

} // namespace acos::gui::widgets
