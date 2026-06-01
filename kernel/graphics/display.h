#pragma once
#include <acos/types.h>
#include <kernel/graphics/types.h>
#include <kernel/graphics/framebuffer.h>

namespace acos::graphics {

class DisplayDevice {
public:
    virtual ~DisplayDevice() = default;
    virtual bool initialize() = 0;
    virtual Framebuffer* get_framebuffer() = 0;
    virtual u32 width() const = 0;
    virtual u32 height() const = 0;
};

} // namespace acos::graphics
