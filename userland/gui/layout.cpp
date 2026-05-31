#include "layout.h"

namespace acos::gui {

void Layout::apply_vertical(Widget* parent, Widget** children, usize count, i32 padding) {
    Rect p_rect = parent->rect();
    i32 current_y = p_rect.y + padding;
    for (usize i = 0; i < count; i++) {
        if (!children[i]) continue;
        children[i]->set_position(p_rect.x + padding, current_y);
        children[i]->set_size(p_rect.w - 2 * padding, children[i]->rect().h);
        current_y += children[i]->rect().h + padding;
    }
}

void Layout::apply_horizontal(Widget* parent, Widget** children, usize count, i32 padding) {
    Rect p_rect = parent->rect();
    i32 current_x = p_rect.x + padding;
    for (usize i = 0; i < count; i++) {
        if (!children[i]) continue;
        children[i]->set_position(current_x, p_rect.y + padding);
        children[i]->set_size(children[i]->rect().w, p_rect.h - 2 * padding);
        current_x += children[i]->rect().w + padding;
    }
}

} // namespace acos::gui
