#pragma once
#include "observable.h"
#include <acos/types.h>

namespace acos::gui {

enum class Easing {
    Linear,
    EaseIn,
    EaseOut,
    EaseInOut
};

class Animation : public Observable<float> {
public:
    Animation(u64 duration_ms, Easing easing = Easing::Linear);

    void tick(u64 delta_ms);
    bool is_complete() const { return m_elapsed >= m_duration; }
    void reset();

private:
    float apply_easing(float t);

    u64 m_duration;
    u64 m_elapsed;
    Easing m_easing;
};

class AnimationController {
public:
    void tick(u64 delta_ms);
    void add_animation(Ref<Animation> animation);

private:
    Vector<Ref<Animation>> m_animations;
};

} // namespace acos::gui
