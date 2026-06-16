#include <acos/graphics.h>
#include <acos/syscall.h>
#include <acos/ipc.h>

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

void send_command_to_ds(const acos::abi::DisplayMsg& msg) {
    static u64 ds_channel = 0;
    if (ds_channel == 0) {
        ds_channel = syscall(sys::SyscallNum::ResourceLocate, (u64)"display_server");
    }
    if (ds_channel != 0 && ds_channel != (u64)-1) {
        acos::ipc::channel_send(ds_channel, &msg, sizeof(acos::abi::DisplayMsg));
    }
}

} // namespace acos::graphics
