#pragma once
#include <acos/types.h>

namespace acos::ui {

class Animation {
public:
    virtual void tick(u64 now) = 0;
};

class AnimationManager {
public:
    void update(u64 now);
};

} // namespace acos::ui
