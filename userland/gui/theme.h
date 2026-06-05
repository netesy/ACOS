#pragma once
#include <acos/types.h>

namespace acos::gui::widgets {

struct Theme {
    // ACOS Synthetic Interface colors
    u32 background;       // Level 0: #0A0A0B
    u32 surface;          // Level 1: #131314
    u32 glass_bg;         // 60% opaque charcoal
    u32 primary;          // Electric Blue: #00E5FF
    u32 secondary;        // Neon Purple: #BF00FF
    
    u32 border;           // 1px shimmering edge
    u32 foreground;       // Primary text
    u32 text;             // #E5E2E3 (same as foreground)
    u32 text_secondary;   // #BAC9CC
    
    u32 success;          // Electric Blue
    u32 warning;          // Vibrant Orange
    u32 error;            // Neon Pink/Red
    u32 accent;           // For compatibility
    u32 widget_bg;        // For compatibility
    u32 widget_bg_hover;  // For compatibility
    u32 widget_bg_pressed;// For compatibility
    u32 info;             // For compatibility
    
    u32 shadow;           // Glow effect color
    u8 shadow_alpha;

    // Shape properties
    u32 window_radius;    // 16px
    u32 widget_radius;    // 8px
    u32 border_width;     // 1px
};

extern Theme g_current_theme;

void init_synthetic_theme();
void init_default_theme();
void init_dark_theme();
void init_light_theme();

} // namespace acos::gui::widgets
