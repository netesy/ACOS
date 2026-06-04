#pragma once
#include <acos/types.h>
#include <kernel/graphics/types.h>

namespace acos::gui {

class Surface {
public:
    virtual ~Surface() = default;
    virtual void* map() = 0;
    virtual void unmap() = 0;
    virtual u32 width() const = 0;
    virtual u32 height() const = 0;
};

class CompositorLayer {
public:
    virtual ~CompositorLayer() = default;
    virtual void set_position(i32 x, i32 y) = 0;
    virtual void set_opacity(float opacity) = 0;
    virtual void set_surface(Surface* surface) = 0;
    virtual void commit() = 0;
};

} // namespace acos::gui
