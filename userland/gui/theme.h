#pragma once
#include <acos/types.h>

namespace acos::gui {

struct Theme {
    // Base colors
    u32 background;
    u32 foreground;
    u32 accent;
    u32 accent_light;
    u32 accent_dark;
    
    // UI colors
    u32 border;
    u32 text;
    u32 text_secondary;
    u32 widget_bg;
    u32 widget_bg_hover;
    u32 widget_bg_pressed;
    
    // Status colors
    u32 success;
    u32 warning;
    u32 error;
    u32 info;
    
    // Shadows and effects
    u32 shadow;
    u8 shadow_alpha;
};

extern Theme g_current_theme;

void init_default_theme();
void init_dark_theme();
void init_light_theme();

} // namespace acos::gui
