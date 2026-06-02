#include "messagebox.h"
#include "theme.h"
#include <kernel/graphics/renderer.h>

namespace acos::gui {

MessageBox::MessageBox(const char* title, const char* message)
    : WindowWidget(title, 250, 200, 300, 150),
      m_label(message), m_ok_btn("OK") {

    m_label.set_alignment(TextAlignment::Center);
    add_child(&m_label);
    add_child(&m_ok_btn);

    m_ok_btn.set_position(m_rect.x + (m_rect.w - 80) / 2, m_rect.y + m_rect.h - 50);
    m_ok_btn.set_size(80, 30);
}

MessageBox::~MessageBox() {}

void MessageBox::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;

    // Dim the background
    renderer->blend_rect(0, 0, 1920, 1080, 0x00000000, 100);

    WindowWidget::draw(renderer);
}

} // namespace acos::gui
