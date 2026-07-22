#include <acos/process.h>
#include <acos/runtime.h>
#include "theme.h"

namespace acos::gui::widgets {

Theme g_current_theme;

void init_synthetic_theme() {
    g_current_theme.background = 0xFF0A0A0B;
    g_current_theme.surface = 0xFF131314;
    g_current_theme.glass_bg = 0xCC131314;  // Increased alpha for stronger glass effect
    g_current_theme.primary = 0xFF00E5FF;
    g_current_theme.secondary = 0xFFBF00FF;
    g_current_theme.border = 0xFF555555;  // Slightly brighter for better visibility
    g_current_theme.text = 0xFFE5E2E3;
    g_current_theme.foreground = 0xFFE5E2E3;
    g_current_theme.text_secondary = 0xFF888888;
    g_current_theme.accent = 0xFF00E5FF;
    g_current_theme.info = 0xFF00E5FF;
    g_current_theme.success = 0xFF00C853;
    g_current_theme.warning = 0xFFFFD600;
    g_current_theme.error = 0xFFFF1744;
    g_current_theme.widget_bg = 0x22FFFFFF;  // More subtle widget background
    g_current_theme.widget_bg_hover = 0x44FFFFFF;
    g_current_theme.widget_bg_pressed = 0x66FFFFFF;
    g_current_theme.shadow = 0xFF000000;
    g_current_theme.shadow_alpha = 180;  // Increased for deeper shadows
    g_current_theme.glass_alpha = 200;  // Increased for stronger glass
    g_current_theme.hover_alpha = 85;  // Increased hover visibility
    g_current_theme.pressed_alpha = 120;  // Increased pressed visibility
    g_current_theme.active_alpha = 100;  // Increased active visibility
    g_current_theme.window_radius = 16;
    g_current_theme.widget_radius = 10;  // Slightly larger for softer look
    g_current_theme.border_width = 1;
    g_current_theme.dock_radius = 24;  // More rounded dock
    g_current_theme.dock_elevation = 16;  // Higher dock elevation for depth
    g_current_theme.window_elevation = 12;  // Higher window elevation
}

void init_default_theme() { init_synthetic_theme(); }
void init_dark_theme() { init_synthetic_theme(); }
void init_light_theme() { init_synthetic_theme(); }

} // namespace acos::gui::widgets
