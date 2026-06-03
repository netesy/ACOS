#pragma once
#include <ui/geometry.h>
#include "kernel/graphics/renderer.h"

namespace acos::ui {

class RenderObject {
public:
    RenderObject() {}
    virtual ~RenderObject() = default;

    virtual void paint(UIContext* ctx, acos::graphics::Renderer* renderer, Position offset) = 0;
    virtual bool hit_test(UIContext* ctx, Position point, Position offset) = 0;
};

} // namespace acos::ui
