#include <acos/process.h>
#include <acos/runtime.h>
#include "animation.h"

namespace acos::gui {

ScaleAnimation::ScaleAnimation(float target_scale, ::acos::u64 duration_ms)
    : m_start_scale(1.0f), m_target_scale(target_scale), m_current_scale(1.0f),
      m_duration_ms(duration_ms), m_elapsed_ms(0) {
}

void ScaleAnimation::tick(::acos::u64 delta_ms) {
    m_elapsed_ms += delta_ms;
    if (m_elapsed_ms >= m_duration_ms) {
        m_current_scale = m_target_scale;
        return;
    }
    float t = (float)m_elapsed_ms / (float)m_duration_ms;
    // Ease out cubic for smooth animation
    float eased = 1.0f - (1.0f - t) * (1.0f - t) * (1.0f - t);
    m_current_scale = m_start_scale + (m_target_scale - m_start_scale) * eased;
}

bool ScaleAnimation::is_finished() const {
    return m_elapsed_ms >= m_duration_ms;
}

void AnimationController::tick(u64 delta_ms) {
    for (::acos::usize i = 0; i < m_animations.size(); ) {
        if (m_animations[i]) {
            m_animations[i]->tick(delta_ms);
            if (m_animations[i]->is_finished()) {
                m_animations.remove_at(i);
            } else {
                i++;
            }
        } else {
            i++;
        }
    }
}

void AnimationController::add_animation(Ref<Animation> animation) {
    m_animations.push_back(animation);
}

} // namespace acos::gui
