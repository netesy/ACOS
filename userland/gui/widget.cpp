#include "widget.h"

namespace acos::gui {

Widget::Widget() : m_rect{0, 0, 0, 0}, m_parent(nullptr), m_visible(true) {}
Widget::~Widget() {}

void Widget::handle_event(const acos::input::InputEvent& event) {
    (void)event;
}

} // namespace acos::gui
