#include <acos/graphics.h>
#include <acos/syscall.h>
#include <acos/ipc.h>

namespace acos::graphics {

u64 create_display() {
    return syscall(sys::SyscallNum::GraphicsDisplayCreate);
}

u64 create_surface(u32 width, u32 height) {
    return syscall(sys::SyscallNum::GraphicsSurfaceCreate, width, height);
}

u64 create_window(u32 width, u32 height, const char* title) {
    return syscall(sys::SyscallNum::GraphicsWindowCreate, width, height, (u64)title);
}

u64 create_buffer(u32 size) {
    return syscall(sys::SyscallNum::GraphicsBufferCreate, size);
}

void destroy_resource(u64 handle) {
    syscall(sys::SyscallNum::GraphicsResourceDestroy, handle);
}

void present(u64 handle) {
    syscall(sys::SyscallNum::GraphicsPresent, handle);
}

void resize_resource(u64 handle, u32 width, u32 height) {
    syscall(sys::SyscallNum::GraphicsResourceResize, handle, width, height);
}

void* get_framebuffer() {
    return (void*)syscall(sys::SyscallNum::GraphicsGetFramebuffer);
}

bool get_framebuffer_info(FramebufferInfo* info) {
    return syscall(sys::SyscallNum::ResourceQuery, 0, (u64)info) == 0;
}

void send_command_to_ds(const acos::abi::DisplayMsg& msg) {
    static u64 ds_channel = 0;
    if (ds_channel == 0) {
        ds_channel = syscall(sys::SyscallNum::ResourceLocate, (u64)"display_server");
    }
    if (ds_channel != 0 && ds_channel != (u64)-1) {
        acos::ipc::channel_send(ds_channel, &msg, sizeof(acos::abi::DisplayMsg));
    }
}

// GraphicsContext Implementation
GraphicsContext::GraphicsContext(u64 handle) : m_handle(handle) {}

GraphicsContext::~GraphicsContext() {
    destroy_resource(m_handle);
}

void GraphicsContext::put_pixel(u32 x, u32 y, u32 color) {
    syscall(sys::SyscallNum::GraphicsPutPixel, m_handle, x, y, color);
}

void GraphicsContext::draw_line(u32 x1, u32 y1, u32 x2, u32 y2, u32 color) {
    u64 p1 = ((u64)x1 << 32) | y1;
    u64 p2 = ((u64)x2 << 32) | y2;
    syscall(sys::SyscallNum::GraphicsDrawLine, m_handle, p1, p2, color);
}

void GraphicsContext::draw_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    u64 pos = ((u64)x << 32) | y;
    u64 size = ((u64)w << 32) | h;
    syscall(sys::SyscallNum::GraphicsDrawRect, m_handle, pos, size, color);
}

void GraphicsContext::fill_rect(u32 x, u32 y, u32 w, u32 h, u32 color) {
    u64 pos = ((u64)x << 32) | y;
    u64 size = ((u64)w << 32) | h;
    syscall(sys::SyscallNum::GraphicsFillRect, m_handle, pos, size, color);
}

void GraphicsContext::draw_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    u64 center = ((u64)cx << 32) | cy;
    syscall(sys::SyscallNum::GraphicsDrawCircle, m_handle, center, radius, color);
}

void GraphicsContext::fill_circle(u32 cx, u32 cy, u32 radius, u32 color) {
    u64 center = ((u64)cx << 32) | cy;
    syscall(sys::SyscallNum::GraphicsFillCircle, m_handle, center, radius, color);
}

void GraphicsContext::blit(u32 dx, u32 dy, u64 src_surface_handle, u32 sx, u32 sy, u32 sw, u32 sh) {
    u64 dest = ((u64)dx << 32) | dy;
    u64 src_pos = ((u64)sx << 32) | sy;
    u64 src_size = ((u64)sw << 32) | sh;
    syscall(sys::SyscallNum::GraphicsBlit, m_handle, dest, src_surface_handle, src_pos, src_size);
}

void GraphicsContext::clear(u32 color) {
    syscall(sys::SyscallNum::GraphicsClear, m_handle, color);
}

void GraphicsContext::copy_rect(u32 dx, u32 dy, u32 sx, u32 sy, u32 w, u32 h) {
    u64 dest = ((u64)dx << 32) | dy;
    u64 src = ((u64)sx << 32) | sy;
    u64 size = ((u64)w << 32) | h;
    syscall(sys::SyscallNum::GraphicsCopyRect, m_handle, dest, src, size);
}

u64 create_graphics_context(u64 target_handle, u32 target_type) {
    return syscall(sys::SyscallNum::GraphicsContextCreate, target_handle, target_type);
}

} // namespace acos::graphics
