#pragma once
#include "color.h"

namespace acos::ui {

class Theme {
public:
    static Theme& instance() {
        static Theme i;
        return i;
    }

    u32 primary_color = Color::Blue;
    u32 text_color = Color::White;
    u32 background_color = 0xFF1A1A1A;
    u32 accent_color = 0xFF8B5CF6;

    i32 default_radius = 8;
    i32 default_padding = 12;

    // Added for compatibility with shell
    u32 glass_bg = 0x881A1A1A;
    u32 window_radius = 12;
    u32 border = 0x44FFFFFF;
    u32 primary = Color::Blue;
};

// Compatibility with legacy theme
extern Theme g_current_theme;
inline void init_synthetic_theme() {}

} // namespace acos::ui
