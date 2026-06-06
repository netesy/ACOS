#pragma once
#include <acos/types.h>

namespace acos::gui::widgets {

struct Theme {
    u32 background;
    u32 surface;
    u32 glass_bg;
    u32 primary;
    u32 secondary;
    u32 border;
    u32 foreground;
    u32 text;
    u32 text_secondary;
    u32 success;
    u32 warning;
    u32 error;
    u32 accent;
    u32 widget_bg;
    u32 widget_bg_hover;
    u32 widget_bg_pressed;
    u32 info;
    u32 shadow;
    u8 shadow_alpha;
    u32 window_radius;
    u32 widget_radius;
    u32 border_width;
};

extern Theme g_current_theme;

void init_synthetic_theme();
void init_default_theme();
void init_dark_theme();
void init_light_theme();

} // namespace acos::gui::widgets

namespace acos::gui {
    using widgets::g_current_theme;
}
