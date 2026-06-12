#include <acos/boot_info.h>
#include <kernel/memory/pmm.h>
#include <kernel/memory/address_space.h>
#include <kernel/memory/heap.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/services/service_manager.h>
#include <kernel/services/service_registry.h>
#include <kernel/device/driver_manager.h>
#include <kernel/loader/process_loader.h>
#include <kernel/graphics/graphics_manager.h>
#include <kernel/audio/audio_manager.h>
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


// I/O polling: check for serial input and wake any thread
// blocked on console reads.
static void poll_io() {
    acos::scheduler::Thread* blocked = acos::scheduler::get_console_blocked();
    if (blocked && acos::hal::serial_received()) {
        acos::scheduler::wake_thread(blocked);
    }
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    // ============================================================
    // PHASE 1: Core init (both modes)
    // ============================================================
    acos::hal::serial_init();
    acos::hal::console_init(nullptr);
    acos::hal::serial_print("ACOS Kernel: Core Infrastructure Initializing...\n");

    bool desktop_mode = (bootInfo && bootInfo->framebuffer != nullptr);

    if (desktop_mode) {
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
    acos::services::init();

    // Register kernel services
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Filesystem, 1);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Graphics, 2);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Audio, 3);

    // ============================================================
    // PHASE 2: Mode-specific services
    // ============================================================
    if (desktop_mode) {
         acos::graphics::GraphicsManager::init(bootInfo->framebuffer);
    }
    acos::audio::AudioManager::init();

    // ============================================================
    // PHASE 3: Spawn user-space services
    // ============================================================

    auto spawn_service = [](const char* path) {
        acos::hal::serial_print("Main: Spawning service ");
        acos::hal::serial_print(path);
        acos::hal::serial_print("\n");
        
        acos::i32 fd = acos::vfs::VFS::open(path, 0);
        if (fd < 0) {
            acos::hal::serial_print("Main: ERROR failed to open ");
            acos::hal::serial_print(path);
            acos::hal::serial_print("\n");
            return;
        }

        acos::vfs::File* file = acos::scheduler::process_table_find(0)->get_file(fd);
        if (!file) {
            acos::vfs::VFS::close(fd);
            return;
        }

        acos::usize size = file->size();
        void* elf_data = acos::memory::kmalloc(size);
        file->read(elf_data, size);
        acos::vfs::VFS::close(fd);

        acos::scheduler::Process* child = acos::loader::create_process_from_elf(path, elf_data, size);
        acos::memory::kfree(elf_data);

        if (child && child->primary_thread) {
            acos::scheduler::wake_thread(child->primary_thread);
        } else {
            acos::hal::serial_print("Main: ERROR failed to load ");
            acos::hal::serial_print(path);
            acos::hal::serial_print("\n");
        }
    };

    if (desktop_mode) {
        spawn_service("/bin/display_server.elf");
        spawn_service("/bin/audio_server.elf");
        spawn_service("/bin/desktop_shell.elf");
    }
    spawn_service("/bin/cli_shell.elf");

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
