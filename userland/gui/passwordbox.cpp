#include "passwordbox.h"
#include <acos/renderer.h>
#include "core/context.h"

namespace acos::gui::widgets {

PasswordBox::PasswordBox() : TextBox() {}
PasswordBox::~PasswordBox() {}

Ref<RenderObject> PasswordBox::create_render_object() {
    return UIContext::get().region().alloc<RenderPasswordBox>();
}

void PasswordBox::update_render_object(Ref<RenderObject> render_object) {
    TextBox::update_render_object(render_object);
    auto rp = static_cast<RenderPasswordBox*>(render_object.operator->());
    if (rp) {
        rp->set_text(text());
    }
}

RenderPasswordBox::RenderPasswordBox() : m_text(nullptr) {}

void RenderPasswordBox::paint(::acos::graphics::Renderer* renderer) {
    if (!renderer) return;
    renderer->fill_rect(m_rect.x, m_rect.y, m_rect.w, m_rect.h, 0xFF222222);
    if (m_text) {
        // Draw masked text with asterisks
        char masked[512];
        usize i = 0;
        while (m_text[i] && i < 511) {
            masked[i] = '*';
            i++;
        }
        masked[i] = '\0';
        renderer->draw_text(masked, m_rect.x + 4, m_rect.y + 4, 0xFFFFFFFF);
    }
}

void RenderPasswordBox::perform_layout(BoxConstraints constraints) {
    Size size = constraints.constrain({200, 32});
    m_rect.w = size.w;
    m_rect.h = size.h;
}

} // namespace acos::gui::widgets
