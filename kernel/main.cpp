#include <acos/boot_info.h>

namespace acos::hal {
    void serial_init();
    void serial_print(const char* s);
    void console_init(FramebufferInfo* fb);
    void console_clear(u32 color);
    void console_print(const char* s, u32 color = 0xFFFFFFFF);
    void gdt_init();
    void idt_init();
}

namespace acos::memory {
    void pmm_init(BootInfo* bootInfo);
}

namespace acos::scheduler {
    void scheduler_init();
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    acos::hal::serial_init();
    acos::hal::serial_print("ACOS Kernel Phase 2: Core Kernel Starting...\n");

    if (bootInfo && bootInfo->framebuffer) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F);
        acos::hal::console_print("ACOS Kernel Phase 2 - Core Kernel\n");
    }

    acos::hal::gdt_init();
    acos::hal::idt_init();
    acos::hal::console_print("CPU Setup Complete.\n");

    acos::memory::pmm_init(bootInfo);
    acos::hal::console_print("Memory Management Operational.\n");

    acos::scheduler::scheduler_init();
    acos::hal::console_print("Scheduler Initialized.\n");

    acos::hal::serial_print("ACOS Kernel Phase 2 Successful. Multitasking Ready.\n");

    while (true) {
        __asm__("hlt");
    }
}
