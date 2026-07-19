#pragma once
#include <acos/types.h>
#include <acos/abi/display.h>
#include <acos/graphics_types.h>

namespace acos::graphics {

struct FramebufferInfo {
    u64 base;
    u64 size;
    u32 width;
    u32 height;
    u32 pitch;
    u32 bpp;
};

using DisplayMsg = abi::DisplayMsg;
using DisplayMsgType = abi::DisplayMsgType;

// Resource Management
u64 create_display();
u64 create_surface(u32 width, u32 height);
u64 create_window(u32 width, u32 height, const char* title);
u64 create_buffer(u32 size);

void destroy_resource(u64 handle);
void present(u64 handle);
void resize_resource(u64 handle, u32 width, u32 height);

void* get_framebuffer();
bool get_framebuffer_info(FramebufferInfo* info);
void send_command_to_ds(const DisplayMsg& msg);

// Graphics Context Proxy
class GraphicsContext {
public:
    GraphicsContext(u64 handle);
    ~GraphicsContext();

    u64 handle() const { return m_handle; }

    void put_pixel(u32 x, u32 y, u32 color);
    void draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color);
    void draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color);
    void draw_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void fill_circle(u32 cx, u32 cy, u32 radius, u32 color);
    void blit(u32 dx, u32 dy, u64 src_surface_handle, u32 sx, u32 sy, u32 sw, u32 sh);
    void clear(u32 color);
    void copy_rect(u32 dx, u32 dy, u32 sx, u32 sy, u32 w, u32 h);

private:
    u64 m_handle;
};

u64 create_graphics_context(u64 target_handle, u32 target_type);

} // namespace acos::graphics
