#pragma once
#include <acos/types.h>

namespace acos::gui {

// Easing functions for animations
enum class EasingFunction {
    Linear,
    EaseInQuad,
    EaseOutQuad,
    EaseInOutQuad,
    EaseInCubic,
    EaseOutCubic,
    EaseInOutCubic,
};

// Simple animation class for property interpolation
class Animation {
public:
    Animation(u64 duration_ms, EasingFunction easing = EasingFunction::EaseOutQuad);
    Animation();  // Default: no animation
    
    // Update animation, returns true if complete
    bool update(u64 delta_ms);
    
    // Get current interpolated value (0.0 to 1.0)
    float get_value() const { return m_value; }
    
    // Check if animation is complete
    bool is_complete() const { return m_elapsed >= m_duration; }
    
    // Reset animation
    void reset();
    
    // Start animation
    void start();
    
    // Set duration
    void set_duration(u64 duration_ms) { m_duration = duration_ms; }
    
private:
    u64 m_duration;
    u64 m_elapsed;
    float m_value;
    EasingFunction m_easing;
    
    float apply_easing(float t) const;
};

// Color interpolation helper
inline u32 lerp_color(u32 from, u32 to, float t) {
    if (t <= 0.0f) return from;
    if (t >= 1.0f) return to;
    
    // Extract ARGB components
    u8 from_a = (from >> 24) & 0xFF;
    u8 from_r = (from >> 16) & 0xFF;
    u8 from_g = (from >> 8) & 0xFF;
    u8 from_b = from & 0xFF;
    
    u8 to_a = (to >> 24) & 0xFF;
    u8 to_r = (to >> 16) & 0xFF;
    u8 to_g = (to >> 8) & 0xFF;
    u8 to_b = to & 0xFF;
    
    // Interpolate each component
    u8 a = from_a + (u8)((i32)to_a - (i32)from_a) * t;
    u8 r = from_r + (u8)((i32)to_r - (i32)from_r) * t;
    u8 g = from_g + (u8)((i32)to_g - (i32)from_g) * t;
    u8 b = from_b + (u8)((i32)to_b - (i32)from_b) * t;
    
    return (a << 24) | (r << 16) | (g << 8) | b;
}

// Float interpolation helper
inline float lerp(float from, float to, float t) {
    if (t <= 0.0f) return from;
    if (t >= 1.0f) return to;
    return from + (to - from) * t;
}

} // namespace acos::gui
