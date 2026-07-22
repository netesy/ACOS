#pragma once
#include <acos/types.h>
#include "ref.h"
#include "vector.h"

namespace acos::gui {

class Animation {
public:
    virtual ~Animation() = default;
    virtual void tick(::acos::u64 delta_ms) = 0;
    virtual bool is_finished() const = 0;
};

class ScaleAnimation : public Animation {
public:
    ScaleAnimation(float target_scale, ::acos::u64 duration_ms);
    void tick(::acos::u64 delta_ms) override;
    bool is_finished() const override;
    float current_scale() const { return m_current_scale; }

private:
    float m_start_scale;
    float m_target_scale;
    float m_current_scale;
    ::acos::u64 m_duration_ms;
    ::acos::u64 m_elapsed_ms;
};

class AnimationController {
public:
    void tick(::acos::u64 delta_ms);
    void add_animation(Ref<Animation> animation);

private:
    ::acos::Vector<Ref<Animation>> m_animations;
};

} // namespace acos::gui
