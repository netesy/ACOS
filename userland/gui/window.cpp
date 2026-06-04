#include "window.h"

namespace acos::ui {

Window::Window(const char* title, i32 x, i32 y, i32 w, i32 h)
    : m_title(title), m_x(x), m_y(y), m_w(w), m_h(h), m_context(2 * 1024 * 1024), m_root(Ref<Widget>::null()) {}

void Window::set_root(Ref<Widget> root) { m_root = root; m_context.build_tree(root); }
void Window::update(u64 now) {
    m_context.update(now);
    m_context.rebuild_dirty_widgets(m_root);
    m_context.perform_layout({ m_w, m_w, m_h, m_h });
}
void Window::paint(acos::graphics::Renderer* renderer) { m_context.paint(renderer); }
void Window::handle_event(UIEvent& event) {
    if (event.type == EventType::MouseDown || event.type == EventType::MouseMove || event.type == EventType::MouseUp) {
        event.mouse.x -= m_x; event.mouse.y -= m_y;
    }
    m_context.process_event(event);
}

} // namespace acos::ui
