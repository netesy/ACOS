#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/syscall.h>
#include <acos/ipc.h>
#include <acos/process.h>
#include <services/display/display_server.h>
#include <services/display/display_protocol.h>

using namespace acos;
using namespace acos::display;

extern "C" int main(int argc [[maybe_unused]], char** argv [[maybe_unused]]) {
    // 1. Create a channel for the Display Server
    u64 ds_channel = ipc::channel_create();
    if (!ds_channel) {
        return 1;
    }

    // 2. Register the service with the kernel
    if (!services::register_service("display_server", ds_channel)) {
        return 2;
    }

    // 3. Initialize DisplayServer instance
    // NOTE: In a real user-space DS, we need to map the framebuffer.
    // For this refactor, we'll assume DisplayServer::initialize() 
    // will eventually use a syscall to map the hardware framebuffer.
    DisplayServer ds;
    if (!ds.initialize()) {
        return 3;
    }

    // 4. Run the display server loop
    // Since we're in user-space, we can't use run_loop() as it uses __asm__("hlt")
    // and relies on internal kernel members.
    // We'll use run() or a modified version.
    ds.run();

    return 0;
}
