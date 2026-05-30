#include <acos/boot_info.h>

namespace acos::hal {
    void serial_init();
    void serial_print(const char* s);
    void console_init(FramebufferInfo* fb);
    void console_clear(u32 color);
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    // 1. Initialize Serial
    acos::hal::serial_init();
    acos::hal::serial_print("ACOS Kernel Booting...\n");

    // 2. Initialize Console
    if (bootInfo && bootInfo->framebuffer) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F); // ACOS Blue
    }

    acos::hal::serial_print("ACOS Kernel Phase 1 Success.\n");

    // 3. Halt for now
    while (true) {
        __asm__("hlt");
    }
}
