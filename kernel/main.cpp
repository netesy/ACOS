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
#include <services/display/display_protocol.h>
#include <services/display/terminal_window.h>
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
acos::audio::AudioServer* g_audio_server = nullptr;
acos::shell::SessionManager* g_session_manager = nullptr;
acos::shell::DesktopShell* g_desktop_shell = nullptr;

// Boot mode: detected from framebuffer presence.
// Server mode = CLI only over serial (make run-s, -nographic).
// Desktop mode = full GUI with display server (make run, SDL).
static bool g_desktop_mode = false;

static void* cli_thread_entry(void*) {
    void* cli_mem = acos::memory::kmalloc(sizeof(acos::shell::CLIShell));
    if (cli_mem) {
        acos::shell::CLIShell* cli_shell = new (cli_mem) acos::shell::CLIShell();
        cli_shell->run();
    } else {
        acos::hal::serial_print("CLI_THREAD: ERROR failed to allocate memory for shell\n");
    }
    for (;;) { __asm__ volatile("hlt"); }
    return nullptr;
}

// Display Server thread: owns the compositor, processes IPC commands.
static void* ds_thread_entry(void* arg) {
    auto* ds = static_cast<acos::display::DisplayServer*>(arg);
    ds->run_loop();
    for (;;) { __asm__ volatile("hlt"); }
    return nullptr;
}

// Desktop Shell thread: UI event processing, sends commands to DS via IPC.
static void* desktop_shell_thread_entry(void* arg) {
    auto* shell = static_cast<acos::shell::DesktopShell*>(arg);
    shell->run_loop();
    for (;;) { __asm__ volatile("hlt"); }
    return nullptr;
}

static void desktop_draw_callback(acos::graphics::Renderer* renderer) {
    if (g_desktop_shell) {
        g_desktop_shell->draw(renderer);
    }
}

// I/O polling: check for serial input and wake any thread
// blocked on console reads.
static void poll_io() {
    acos::scheduler::Thread* blocked = acos::scheduler::get_console_blocked();
    if (blocked && acos::hal::serial_received()) {
        acos::scheduler::wake_thread(blocked);
    }
}

// ----------------------------------------------------------------
// Desktop mode: init graphics, display server, desktop shell, audio
// ----------------------------------------------------------------
static void init_desktop_services(acos::BootInfo* bootInfo) {
    // Graphics subsystem
    acos::graphics::GraphicsManager::init(bootInfo->framebuffer);

    // Display server + terminal window
    void* ds_mem = acos::memory::kmalloc(sizeof(acos::display::DisplayServer));
    if (ds_mem) {
        g_display_server = new (ds_mem) acos::display::DisplayServer();
        if (g_display_server->initialize()) {
            acos::hal::serial_print("Display Server: Initialized\n");

            // Terminal window inside the display
            static acos::display::TerminalWindow s_terminal_window;
            if (s_terminal_window.initialize(g_display_server)) {
                acos::display::g_terminal_window = &s_terminal_window;
                acos::hal::serial_print("Terminal Window: Initialized\n");
            }

            // Desktop shell (taskbar, top bar, dock)
            static acos::shell::DesktopShell s_desktop_shell;
            s_desktop_shell.set_display_server(g_display_server);
            s_desktop_shell.initialize();
            g_desktop_shell = &s_desktop_shell;
            g_display_server->set_desktop_draw(desktop_draw_callback);
            acos::hal::serial_print("Desktop Shell: Initialized\n");
        }
    }

    // Audio subsystem
    acos::audio::AudioManager::init();
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
    void* as_mem = acos::memory::kmalloc(sizeof(acos::audio::AudioServer));
    if (as_mem) {
        g_audio_server = new (as_mem) acos::audio::AudioServer();
        if (g_audio_server->initialize()) {
            acos::hal::serial_print("Audio Server: Initialized\n");
        }
    }
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    // ============================================================
    // PHASE 1: Core init (both modes)
    // ============================================================
    acos::hal::serial_init();
    acos::hal::console_init(nullptr);
    acos::hal::serial_print("ACOS Kernel: Core Infrastructure Initializing...\n");

    // Detect boot mode from framebuffer presence
    g_desktop_mode = (bootInfo && bootInfo->framebuffer != nullptr);

    if (g_desktop_mode) {
        acos::hal::console_init(bootInfo->framebuffer);
        acos::hal::console_clear(0x001E3A5F);
        acos::hal::console_print("ACOS Kernel v1.0.0 - Desktop Mode\n");
        acos::hal::serial_print("[MODE] Desktop (GUI)\n");
    } else {
        acos::hal::serial_print("[MODE] Server (CLI)\n");
    }

    acos::hal::gdt_init();
    acos::smp::SmpManager::init();
    acos::hal::idt_init();

    // Register boot thread
    static acos::scheduler::Thread boot_thread;
    static acos::scheduler::Process kernel_process;

    boot_thread.id = 0;
    boot_thread.state = acos::scheduler::ThreadState::Running;
    boot_thread.is_user = false;
    boot_thread.parent = &kernel_process;
    kernel_process.id = 0;
    acos::smp::Cpu::current()->current_thread = &boot_thread;

    // Memory management
    acos::memory::pmm_init(bootInfo);

    // VFS
    static acos::vfs::DevFileSystem s_dev_fs;
    acos::vfs::VFS::mount("/dev", &s_dev_fs);
    acos::i32 test_fd = acos::vfs::VFS::open("/dev/console", 0);
    if (test_fd >= 0) {
        acos::hal::serial_print("VFS: /dev/console mounted and verified\n");
        acos::vfs::VFS::close(test_fd);
    } else {
        acos::hal::serial_print("VFS: ERROR failed to mount /dev/console\n");
    }

    acos::memory::vmm_init(bootInfo);
    acos::scheduler::scheduler_init();

    // Register kernel services
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Filesystem, 1);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Graphics, 2);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Audio, 3);

    // ============================================================
    // PHASE 2: Mode-specific services
    // ============================================================
    if (g_desktop_mode) {
        init_desktop_services(bootInfo);
    } else {
        // Server mode: no graphics, no display, no audio
        // Audio manager still needs basic init for stubs
        acos::audio::AudioManager::init();
    }

    // ============================================================
    // PHASE 3: Create service threads
    // ============================================================

    // Helper: create a kernel thread with its own process
    auto create_service_thread = [](const char* name,
                                    acos::scheduler::ThreadEntry entry,
                                    void* arg) -> acos::scheduler::Thread* {
        acos::scheduler::Thread* thread = acos::scheduler::create_thread(entry, arg);
        if (!thread) {
            acos::hal::serial_print("Main: ERROR failed to create thread: ");
            acos::hal::serial_print(name);
            acos::hal::serial_print("\n");
            return nullptr;
        }
        acos::scheduler::Process* proc = acos::scheduler::Process::create();
        if (!proc) {
            acos::hal::serial_print("Main: ERROR Process::create() for ");
            acos::hal::serial_print(name);
            acos::hal::serial_print("\n");
            return nullptr;
        }
        thread->parent = proc;
        thread->is_user = false;
        proc->primary_thread = thread;
        acos::scheduler::wake_thread(thread);
        return thread;
    };

    if (g_desktop_mode) {
        // Thread 1: Display Server (compositor + IPC handler)
        create_service_thread("display_server", ds_thread_entry, g_display_server);
        acos::hal::serial_print("Main: Display Server thread created\n");

        // Thread 2: Desktop Shell (UI event loop)
        create_service_thread("desktop_shell", desktop_shell_thread_entry, g_desktop_shell);
        acos::hal::serial_print("Main: Desktop Shell thread created\n");
    }

    // Thread 3: CLI Shell (user interaction — both modes)
    create_service_thread("cli_shell", cli_thread_entry, nullptr);
    acos::hal::serial_print("Main: CLI Shell thread created\n");

    // Re-enqueue boot thread so the idle loop can run
    boot_thread.state = acos::scheduler::ThreadState::Ready;
    acos::scheduler::enqueue_thread(0, &boot_thread);

    // Switch to the first ready service thread
    acos::scheduler::schedule();

    // ============================================================
    // PHASE 4: Boot thread idle loop
    // ============================================================
    // The boot thread is now the idle/scheduler thread.
    // It drives I/O polling and triggers display recomposition
    // by sending damage notifications to the DS thread via IPC.
    acos::hal::serial_print("ACOS Kernel Boot Success. Entering Idle Loop.\n");

    while (true) {
        if (g_desktop_mode && g_display_server) {
            // Trigger recomposition: the DS thread composes when
            // it receives damage or has pending IPC commands.
            acos::display::DisplayMsg cmd{};
            cmd.type = acos::display::DisplayMsgType::DamageNotify;
            g_display_server->send_command(cmd);
        }

        // Poll serial I/O and wake blocked threads
        poll_io();

        // Drive scheduler
        acos::scheduler::schedule();

        // Yield CPU until next event
        __asm__ volatile("hlt");
    }
}

// Stubs to avoid link errors
extern "C" {
    void* __dso_handle = nullptr;
    int __cxa_atexit(void (*)(void*), void*, void*) { return 0; }

    // Static local variable guards (freestanding, single-threaded)
    typedef unsigned long __guard;
    int __cxa_guard_acquire(__guard* g) {
        return *g == 0;
    }
    void __cxa_guard_release(__guard* g) {
        *g = 1;
    }
    void __cxa_guard_abort(__guard*) {}
}
