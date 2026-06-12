#include <acos/process.h>
#include <acos/runtime.h>
#include "layout.h"

namespace acos::gui::widgets {

void Layout::apply_vertical(Widget* parent, Widget** children, ::acos::usize count, ::acos::i32 padding) {
    if (!parent) return;
    ::acos::i32 cur_y = 0;
    for (::acos::usize i = 0; i < count; i++) {
        if (children[i]) {
            children[i]->set_position(0, cur_y);
            cur_y += children[i]->rect().h + padding;
        }
    }
}

void Layout::apply_horizontal(Widget* parent, Widget** children, ::acos::usize count, ::acos::i32 padding) {
    if (!parent) return;
    ::acos::i32 cur_x = 0;
    for (::acos::usize i = 0; i < count; i++) {
        if (children[i]) {
            children[i]->set_position(cur_x, 0);
            cur_x += children[i]->rect().w + padding;
        }
    }
}

void Layout::apply_grid(Widget* parent, Widget** children, ::acos::usize count, ::acos::u32 columns, ::acos::i32 padding) {
    (void)parent; (void)children; (void)count; (void)columns; (void)padding;
}

} // namespace acos::gui::widgets
