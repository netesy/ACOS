#include "animation.h"

namespace acos::gui {

Animation::Animation(u64 duration_ms, EasingFunction easing)
    : m_duration(duration_ms), m_elapsed(0), m_value(0.0f), m_easing(easing) {
}

Animation::Animation()
    : m_duration(0), m_elapsed(0), m_value(0.0f), m_easing(EasingFunction::Linear) {
}

bool Animation::update(u64 delta_ms) {
    if (m_duration == 0) {
        m_value = 1.0f;
        return true;
    }
    
    m_elapsed += delta_ms;
    if (m_elapsed >= m_duration) {
        m_elapsed = m_duration;
        m_value = 1.0f;
        return true;
    }
    
    float t = (float)m_elapsed / (float)m_duration;
    m_value = apply_easing(t);
    return false;
}

void Animation::reset() {
    m_elapsed = 0;
    m_value = 0.0f;
}

void Animation::start() {
    m_elapsed = 0;
    m_value = 0.0f;
}

float Animation::apply_easing(float t) const {
    switch (m_easing) {
        case EasingFunction::Linear:
            return t;
            
        case EasingFunction::EaseInQuad:
            return t * t;
            
        case EasingFunction::EaseOutQuad:
            return t * (2.0f - t);
            
        case EasingFunction::EaseInOutQuad:
            return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
            
        case EasingFunction::EaseInCubic:
            return t * t * t;
            
        case EasingFunction::EaseOutCubic:
            return 1.0f + (t - 1.0f) * (t - 1.0f) * (t - 1.0f);
            
        case EasingFunction::EaseInOutCubic:
            return t < 0.5f ? 4.0f * t * t * t : 1.0f + (t - 1.0f) * (2.0f * (t - 2.0f)) * (2.0f * (t - 2.0f));
            
        default:
            return t;
    }
}

} // namespace acos::gui
