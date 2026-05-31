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
#include <kernel/audio/audio_manager.h>
#include <services/display/display_server.h>
#include <services/audio/audio_server.h>
#include <userland/shell/session_manager.h>
#include <libs/runtime/include/acos/runtime.h>
#include <drivers/audio/virtio_sound/virtio_sound.h>
#include <drivers/audio/hda/hda.h>

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
acos::audio::AudioServer* g_audio_server = nullptr;
acos::shell::SessionManager* g_session_manager = nullptr;

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    acos::hal::serial_init();
    acos::hal::serial_print("ACOS Kernel: Core Infrastructure Initializing (GCC Build)...\n");

    if (bootInfo && bootInfo->framebuffer) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F);
        acos::hal::console_print("ACOS Kernel v1.4.0 - Multimedia Ready\n");
    }

    acos::hal::gdt_init();
    acos::hal::idt_init();
    acos::memory::pmm_init(bootInfo);
    acos::memory::vmm_init();
    acos::scheduler::scheduler_init();

    // Graphics and Audio initialization
    acos::graphics::GraphicsManager::init();
    acos::audio::AudioManager::init();

    // Register Services
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Filesystem, 1);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Graphics, 2);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Audio, 3);

    // Initialize Display Server
    void* ds_mem = acos::memory::kmalloc(sizeof(acos::display::DisplayServer));
    if (ds_mem) {
        g_display_server = new (ds_mem) acos::display::DisplayServer();
        if (g_display_server->initialize()) {
            acos::hal::serial_print("Display Server: Initialized\n");
        }
    }

    // Initialize Audio Subsystem and Drivers
    // Use kmalloc for drivers to avoid static initializer issues in kernelMain
    void* virtio_mem = acos::memory::kmalloc(sizeof(acos::drivers::audio::VirtIOSound));
    if (virtio_mem) {
        acos::drivers::audio::VirtIOSound* virtio_snd = new (virtio_mem) acos::drivers::audio::VirtIOSound();
        if (virtio_snd->initialize()) {
            acos::audio::AudioDevice* dev = (acos::audio::AudioDevice*)acos::memory::kmalloc(sizeof(acos::audio::AudioDevice));
            if (dev) {
                new (dev) acos::audio::AudioDevice(1, "VirtIO Sound Card", virtio_snd);
                acos::audio::AudioManager::register_device(dev);
                acos::hal::serial_print("Audio Manager: Registered VirtIO Sound Device\n");
            }
        }
    }

    // Initialize Audio Server
    void* as_mem = acos::memory::kmalloc(sizeof(acos::audio::AudioServer));
    if (as_mem) {
        g_audio_server = new (as_mem) acos::audio::AudioServer();
        if (g_audio_server->initialize()) {
            acos::hal::serial_print("Audio Server: Initialized\n");
        }
    }

    // Start Session
    void* sm_mem = acos::memory::kmalloc(sizeof(acos::shell::SessionManager));
    if (sm_mem) {
        g_session_manager = new (sm_mem) acos::shell::SessionManager();
        acos::hal::console_print("Starting Multimedia User Session...\n");
        acos::hal::serial_print("Session Manager: Starting Session for User 0\n");
    }

    acos::hal::console_print("Core System Initialization: PASS\n");
    acos::hal::serial_print("ACOS Kernel Phase 14 Success. Entering Idle Loop.\n");

    while (true) {
        __asm__("hlt");
    }
}

// Stubs to avoid link errors
extern "C" {
    void* __dso_handle = nullptr;
    int __cxa_atexit(void (*)(void*), void*, void*) { return 0; }
}
