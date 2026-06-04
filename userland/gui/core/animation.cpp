#include "animation.h"
#include "context.h"

namespace acos::gui {

Animation::Animation(u64 duration_ms, Easing easing)
    : Observable<float>(0.0f), m_duration(duration_ms), m_elapsed(0), m_easing(easing) {}

void Animation::tick(u64 delta_ms) {
    if (is_complete()) return;

    m_elapsed += delta_ms;
    if (m_elapsed > m_duration) m_elapsed = m_duration;

    float t = (float)m_elapsed / (float)m_duration;
    set(apply_easing(t));
}

void Animation::reset() {
    m_elapsed = 0;
    set(0.0f);
}

float Animation::apply_easing(float t) {
    switch (m_easing) {
        case Easing::EaseIn: return t * t;
        case Easing::EaseOut: return t * (2 - t);
        case Easing::EaseInOut: return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
        case Easing::Linear:
        default: return t;
    }
}

void AnimationController::tick(u64 delta_ms) {
    for (u32 i = 0; i < m_animations.size(); ) {
        if (!m_animations[i]) {
            m_animations.remove_at(i);
            continue;
        }

        m_animations[i]->tick(delta_ms);

        if (m_animations[i]->is_complete()) {
            m_animations.remove_at(i);
        } else {
            i++;
        }
    }
}

void AnimationController::add_animation(Ref<Animation> animation) {
    if (animation) {
        m_animations.push_back(animation);
    }
}

} // namespace acos::gui
