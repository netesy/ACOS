#include "dialog.h"
#include "core/render_object.h"
#include "core/context.h"

namespace acos::gui::widgets {

Dialog::Dialog(const char* title, ::acos::i32 w, ::acos::i32 h) : WindowWidget(title, 200, 200, w, h) {
}

Dialog::~Dialog() {}

Ref<RenderObject> Dialog::create_render_object() {
    return Ref<RenderObject>();
}

void Dialog::set_on_accept(void (*callback)(void*), void* receiver) {
    (void)callback; (void)receiver;
}

void Dialog::set_on_cancel(void (*callback)(void*), void* receiver) {
    (void)callback; (void)receiver;
}

} // namespace acos::gui::widgets
