#include <acos/graphics.h>
#include <acos/syscall.h>

namespace acos::graphics {

u64 create_surface(u32 width, u32 height) {
    return syscall(sys::SyscallNum::GraphicsSurfaceCreate, width, height);
}

u64 create_window(u32 width, u32 height, const char* title) {
    return syscall(sys::SyscallNum::GraphicsWindowCreate, width, height, (u64)title);
}

void present(u64 handle) {
    syscall(sys::SyscallNum::GraphicsPresent, handle);
}

void* get_framebuffer() {
    return (void*)syscall(sys::SyscallNum::GraphicsGetFramebuffer);
}

bool get_framebuffer_info(FramebufferInfo* info) {
    return syscall(sys::SyscallNum::ResourceQuery, 0, (u64)info) == 0;
}

} // namespace acos::graphics
