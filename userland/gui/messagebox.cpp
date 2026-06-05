#include "messagebox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui::widgets {

MessageBox::MessageBox(const char* title, const char* message)
    : WindowWidget(title, 250, 200, 300, 150),
      m_label(message), m_ok_btn("OK") {

    m_elevation = 24;
    m_label.set_alignment(TextAlignment::Center);
    add_child(&m_label);
    add_child(&m_ok_btn);

    m_ok_btn.set_position(m_rect.x + (m_rect.w - 80) / 2, m_rect.y + m_rect.h - 50);
    m_ok_btn.set_size(80, 30);
}

MessageBox::~MessageBox() {}


Ref<RenderObject> Messagebox::create_render_object() { return Ref<RenderObject>(); }
Ref<RenderObject> MessageBox::create_render_object() { return Ref<RenderObject>(); }
} // namespace acos::gui::widgets
