#pragma once
#include <acos/types.h>
#include "color.h"

namespace acos::ui {

struct Style {
    u32 background_color = 0;
    u32 text_color = Color::White;
    i32 corner_radius = -1;
    i32 padding = -1;
    i32 margin = -1;
    i32 font_size = -1;
    bool has_background = false;
};

} // namespace acos::ui
