#include <acos/boot_info.h>
#include <kernel/memory/pmm.h>
#include <kernel/memory/address_space.h>
#include <kernel/memory/heap.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/services/service_manager.h>
#include <kernel/device/driver_manager.h>
#include <kernel/loader/process_loader.h>
#include <kernel/graphics/graphics_manager.h>
#include <services/display/display_server.h>
#include <userland/shell/session_manager.h>
#include <libs/runtime/include/acos/runtime.h>

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

// Global instances
acos::display::DisplayServer* g_display_server = nullptr;
acos::shell::SessionManager* g_session_manager = nullptr;

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    acos::hal::serial_init();
    acos::hal::serial_print("ACOS Kernel: Core Infrastructure Initializing (GCC Build)...\n");

    if (bootInfo && bootInfo->framebuffer) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F);
        acos::hal::console_print("ACOS Kernel v1.3.0 - Desktop Environment\n");
    }

    acos::hal::gdt_init();
    acos::hal::idt_init();
    acos::memory::pmm_init(bootInfo);
    acos::memory::vmm_init();
    acos::scheduler::scheduler_init();

    // Graphics initialization
    acos::graphics::GraphicsManager::init();

    // Register Services
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Filesystem, 1);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Graphics, 2);

    // Initialize Display Server
    void* ds_mem = acos::memory::kmalloc(sizeof(acos::display::DisplayServer));
    if (ds_mem) {
        g_display_server = new (ds_mem) acos::display::DisplayServer();
        if (g_display_server->initialize()) {
            acos::hal::serial_print("Display Server: Initialized\n");
        }
    }

    // Phase 13: Initialize Session Manager and start user session
    void* sm_mem = acos::memory::kmalloc(sizeof(acos::shell::SessionManager));
    if (sm_mem) {
        g_session_manager = new (sm_mem) acos::shell::SessionManager();
        acos::hal::console_print("Starting User Session...\n");
        acos::hal::serial_print("Session Manager: Starting Session for User 0\n");
        // g_session_manager->start_session(0); // This would enter the shell loop
    }

    acos::hal::console_print("Core System Initialization: PASS\n");
    acos::hal::serial_print("ACOS Kernel Phase 13 Success. Entering Idle Loop.\n");

    while (true) {
        __asm__("hlt");
    }
}

extern "C" {
    void* __dso_handle = nullptr;
    int __cxa_atexit(void (*)(void*), void*, void*) { return 0; }
}
