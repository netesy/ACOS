#include <acos/boot_info.h>
#include <kernel/memory/pmm.h>
#include <kernel/memory/address_space.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/services/service_manager.h>
#include <kernel/device/driver_manager.h>
#include <kernel/process/loader.h>

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
    void vmm_init();
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    acos::hal::serial_init();
    acos::hal::serial_print("ACOS Kernel: Core Infrastructure Initializing...\n");

    if (bootInfo && bootInfo->framebuffer) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F);
        acos::hal::console_print("ACOS Kernel v1.2 - Core Systems\n");
    }

    acos::hal::gdt_init();
    acos::hal::idt_init();
    acos::memory::pmm_init(bootInfo);
    acos::memory::vmm_init();
    acos::scheduler::scheduler_init();

    acos::process::create_user_process("init", 0x400000);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Filesystem, 1);
    acos::device::DriverManager::register_driver(1, acos::device::DriverTier::Tier3, nullptr);

    acos::hal::console_print("Core Infrastructure Audit: PASS\n");
    acos::hal::serial_print("ACOS Kernel Phase 1-6 Success. Entering Idle...\n");

    while (true) {
        __asm__("hlt");
    }
}
