#pragma once
#include <acos/types.h>

namespace acos::gui {

struct Theme {
    u32 background;
    u32 foreground;
    u32 accent;
    u32 border;
    u32 text;
    u32 widget_bg;
};

extern Theme g_current_theme;

void init_default_theme();

} // namespace acos::gui
