#pragma once
#include "widget.h"

namespace acos::gui::widgets {

class Layout {
public:
    static void apply_vertical(Widget* parent, Widget** children, usize count, i32 padding = 5);
    static void apply_horizontal(Widget* parent, Widget** children, usize count, i32 padding = 5);
    static void apply_grid(Widget* parent, Widget** children, usize count, u32 columns, i32 padding = 5);
};

} // namespace acos::gui::widgets
