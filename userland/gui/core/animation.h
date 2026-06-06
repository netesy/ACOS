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

class AnimationController {
public:
    void tick(::acos::u64 delta_ms);
    void add_animation(Ref<Animation> animation);

private:
    ::acos::Vector<Ref<Animation>> m_animations;
};

} // namespace acos::gui
