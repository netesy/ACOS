#include "dialog.h"
#include "theme.h"

namespace acos::gui::widgets {

Dialog::Dialog(const char* title, i32 w, i32 h)
    : WindowWidget(title, 200, 150, w, h),
      m_accept_btn("OK"), m_cancel_btn("Cancel") {

    m_accept_btn.set_position(m_rect.x + m_rect.w - 180, m_rect.y + m_rect.h - 45);
    m_accept_btn.set_size(80, 30);
    m_cancel_btn.set_position(m_rect.x + m_rect.w - 90, m_rect.y + m_rect.h - 45);
    m_cancel_btn.set_size(80, 30);

    add_child(&m_accept_btn);
    add_child(&m_cancel_btn);
}

Dialog::~Dialog() {}


void Dialog::set_on_accept(void (*callback)(void*), void* receiver) {
    m_accept_btn.set_on_click(callback, receiver);
}

void Dialog::set_on_cancel(void (*callback)(void*), void* receiver) {
    m_cancel_btn.set_on_click(callback, receiver);
}

Ref<RenderObject> Dialog::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
