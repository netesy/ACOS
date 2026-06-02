#include "theme.h"

namespace acos::gui {

Theme g_current_theme;

void init_synthetic_theme() {
    // ACOS Synthetic Interface - Refined Glassmorphism
    g_current_theme.background = 0xFF0A0A0B;
    g_current_theme.surface = 0xFF131314;
    g_current_theme.glass_bg = 0x991A1A1E; // 60% opacity
    
    g_current_theme.primary = 0xFF00E5FF;  // Electric Blue
    g_current_theme.secondary = 0xFFBF00FF; // Neon Purple
    g_current_theme.accent = 0xFF00E5FF;
    g_current_theme.widget_bg = 0xFF131314;
    g_current_theme.widget_bg_hover = 0xFF1C1C1E;
    g_current_theme.widget_bg_pressed = 0xFF0A0A0B;
    
    g_current_theme.border = 0x33FFFFFF;   // Subtle shimmer
    g_current_theme.foreground = 0xFFE5E2E3;
    g_current_theme.text = 0xFFE5E2E3;
    g_current_theme.text_secondary = 0xFFBAC9CC;
    
    g_current_theme.success = 0xFF00E5FF;
    g_current_theme.warning = 0xFFFFAB40;
    g_current_theme.error = 0xFFFF5252;
    g_current_theme.info = 0xFF00E5FF;
    
    g_current_theme.shadow = 0xFF00E5FF;
    g_current_theme.shadow_alpha = 40;
    
    g_current_theme.window_radius = 16;
    g_current_theme.widget_radius = 8;
    g_current_theme.border_width = 1;
}

void init_default_theme() { init_synthetic_theme(); }
void init_dark_theme() { init_synthetic_theme(); }
void init_light_theme() { init_synthetic_theme(); }

} // namespace acos::gui
