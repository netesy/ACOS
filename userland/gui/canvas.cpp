#include "canvas.h"

namespace acos::gui {

Canvas::Canvas() : m_on_draw(nullptr), m_user_data(nullptr) {}
Canvas::~Canvas() {}

void Canvas::draw(acos::graphics::Renderer* renderer) {
    if (!is_visible() || !renderer) return;
    if (m_on_draw) m_on_draw(this, renderer);
}

} // namespace acos::gui
