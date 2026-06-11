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
#include <userland/shell/desktop_shell.h>
#include <userland/shell/cli_shell.h>
#include <libs/runtime/include/acos/runtime.h>
#include <drivers/audio/virtio_sound/virtio_sound.h>
#include <drivers/audio/hda/hda.h>

#include <kernel/hal/serial.h>
#include <kernel/hal/console.h>
#include <kernel/vfs/vfs.h>
#include <kernel/vfs/dev_fs.h>
#include <kernel/smp/smp.h>
#include <kernel/smp/cpu.h>

namespace acos::hal {
    void gdt_init();
    void idt_init();
}

namespace acos::memory {
    void vmm_init(BootInfo* bootInfo);
}

// Global instances
acos::display::DisplayServer* g_display_server = nullptr;

static void* cli_thread_entry(void*) {
    void* cli_mem = acos::memory::kmalloc(sizeof(acos::shell::CLIShell));
    if (cli_mem) {
        acos::shell::CLIShell* cli_shell = new (cli_mem) acos::shell::CLIShell();
        cli_shell->run();
    } else {
        acos::hal::serial_print("CLI_THREAD: ERROR failed to allocate memory for shell\n");
    }

    // Safety: never return to a garbage address. Block forever.
    for (;;) { __asm__ volatile("hlt"); }
    return nullptr;
}
acos::audio::AudioServer* g_audio_server = nullptr;
acos::shell::SessionManager* g_session_manager = nullptr;
acos::shell::DesktopShell* g_desktop_shell = nullptr;

[[maybe_unused]] static void desktop_draw_callback(acos::graphics::Renderer* renderer) {
    if (g_desktop_shell) {
        g_desktop_shell->draw(renderer);
    }
}

// I/O polling: check for serial input and wake any thread
// blocked on console reads. Called from the idle loop since
// we don't yet have interrupt-driven serial.
static void poll_io() {
    acos::scheduler::Thread* blocked = acos::scheduler::get_console_blocked();
    if (blocked && acos::hal::serial_received()) {
        acos::scheduler::wake_thread(blocked);
    }
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    acos::hal::serial_init();
    acos::hal::console_init(nullptr);
    acos::hal::serial_print("ACOS Kernel: Core Infrastructure Initializing (GCC Build)...\n");

    if (bootInfo && bootInfo->framebuffer) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F);
        acos::hal::console_print("ACOS Kernel v1.0.0 - Multimedia Ready\n");
    }

    acos::hal::gdt_init();
    acos::smp::SmpManager::init();
    acos::hal::idt_init();

    // Register the current boot thread as the initial thread for CPU 0
    static acos::scheduler::Thread boot_thread;
    static acos::scheduler::Process kernel_process;

    boot_thread.id = 0;
    boot_thread.state = acos::scheduler::ThreadState::Running;
    boot_thread.is_user = false;
    boot_thread.parent = &kernel_process;

    kernel_process.id = 0;

    acos::smp::Cpu::current()->current_thread = &boot_thread;

    acos::memory::pmm_init(bootInfo);

    // Initialize DevFS and mount /dev/console
    static acos::vfs::DevFileSystem s_dev_fs;
    acos::vfs::VFS::mount("/dev", &s_dev_fs);

    // Explicit debug to confirm /dev/console is resolvable
    acos::i32 test_fd = acos::vfs::VFS::open("/dev/console", 0);
    if (test_fd >= 0) {
        acos::hal::serial_print("VFS: /dev/console mounted and verified\n");
        acos::vfs::VFS::close(test_fd);
    } else {
        acos::hal::serial_print("VFS: ERROR failed to mount /dev/console\n");
    }
    acos::memory::vmm_init(bootInfo);
    acos::scheduler::scheduler_init();

    // Graphics and Audio initialization
    acos::graphics::GraphicsManager::init(bootInfo ? bootInfo->framebuffer : nullptr);
    acos::audio::AudioManager::init();

    // Register Services
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Filesystem, 1);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Graphics, 2);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Audio, 3);

    // Initialize Display Server
    [[maybe_unused]] bool display_ready = false;
    void* ds_mem = acos::memory::kmalloc(sizeof(acos::display::DisplayServer));
    if (ds_mem) {
        g_display_server = new (ds_mem) acos::display::DisplayServer();
        if (g_display_server->initialize()) {
            display_ready = true;
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

    // CLI Shell Initialization - Start as a separate thread to avoid blocking kernelMain
    acos::hal::serial_print("Main: Creating shell thread...\n");
    acos::scheduler::Thread* cli_thread = acos::scheduler::create_thread(cli_thread_entry, nullptr);
    if (cli_thread) {
        // Create a process for the shell
        acos::scheduler::Process* cli_process = acos::scheduler::Process::create();
        if (!cli_process) {
            acos::hal::serial_print("Main: ERROR Process::create() returned null\n");
        } else {
            cli_thread->parent = cli_process;
            cli_thread->is_user = false; // Run in kernel mode for now since it's linked in
            cli_process->primary_thread = cli_thread;
            acos::scheduler::wake_thread(cli_thread);
            // Switch to the shell thread
            acos::scheduler::schedule();
        }
    } else {
        acos::hal::serial_print("Main: ERROR failed to create shell thread\n");
    }

    acos::hal::console_print("Core System Initialization: PASS\n");
    acos::hal::serial_print("ACOS Kernel Boot Success. Entering Idle Loop.\n");

    // Kernel idle loop: drive display compositing, I/O polling,
    // and the scheduler each tick.
    while (true) {
        if (g_display_server) {
            g_display_server->run_tick();
        }

        // Poll for I/O and wake blocked threads BEFORE scheduling,
        // so newly-woken threads are visible to the scheduler.
        poll_io();

        // Drive scheduler
        acos::scheduler::schedule();

        // Halt CPU until next hardware event. This yields the host
        // CPU in QEMU/TCG, preventing a 100% spin that starves the
        // main loop of cycles needed to deliver serial/keyboard I/O.
        // On real hardware, PIT IRQ0 wakes us periodically.
        __asm__ volatile("hlt");
    }
}

// Stubs to avoid link errors
extern "C" {
    void* __dso_handle = nullptr;
    int __cxa_atexit(void (*)(void*), void*, void*) { return 0; }
}
