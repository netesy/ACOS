#pragma once
#include <acos/types.h>
#include "ref.h"
#include "list.h"

namespace acos::ui {

class UIContext;

class Animation {
public:
    virtual ~Animation() = default;
    virtual void tick(UIContext* ctx, u64 now) = 0;
    virtual bool is_finished() const = 0;
};

class AnimationManager {
public:
    AnimationManager() {}
    void update(UIContext* ctx, u64 now);
    void add_animation(UIContext* ctx, Animation* anim);
private:
    List<Animation*> m_animations;
};

} // namespace acos::ui
