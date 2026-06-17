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
#include <kernel/storage/storage_manager.h>
#include <kernel/storage/filesystem_manager.h>
#include <kernel/storage/fat32.h>
#include <kernel/storage/ahci.h>
#include <kernel/hal/pci.h>
#include <libs/runtime/include/acos/runtime.h>

#include <kernel/hal/serial.h>
#include <kernel/hal/console.h>
#include <kernel/vfs/vfs.h>
#include <kernel/vfs/file.h>
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

    // Initialize storage and mount root filesystem
    acos::storage::StorageManager::init();

    // Register FAT32 filesystem
    // We use a static instance for the probe, but probe_and_mount usually expects a prototype or factory.
    // Given the current FileSystemManager::register_filesystem implementation, it takes a pointer to a FileSystem instance.
    static acos::storage::FAT32FileSystem fat32_proto(nullptr);
    acos::storage::FileSystemManager::register_filesystem("fat32", &fat32_proto);

    // TODO: PCI discovery to find AHCI controller.
    // For now, we'll try a common base address or skip if not found.
    // In QEMU -device ahci, the BAR5 is typically where the registers are.
    // Without PCI scanning, this is a placeholder.
    // Usually it is something like 0xFEB00000 or 0x40000000 depending on config.
    // Let's assume for now we might have an AHCI controller at a known location if it was passed by bootloader,
    // but bootloader doesn't pass it.

    // Instead of failing, let's use the RamDisk if it was provided, or wait for PCI.
    // Given the task is to fix spawning services, and they are likely on the disk image.

    // Legacy Kernel-Mode Bootstrapping (To be migrated to pcie_manager)
    acos::hal::PCIDevice ahci_dev = acos::hal::PCI::find_device(0x01, 0x06);
    if (ahci_dev.vendor_id != 0xFFFF) {
        acos::hal::PCI::enable_bus_mastering(ahci_dev);
        acos::u64 bar5 = acos::hal::PCI::get_bar(ahci_dev, 5);
        static acos::storage::AHCIController ahci_ctrl(bar5);
        if (ahci_ctrl.initialize()) {
            for (acos::u32 i = 0; i < ahci_ctrl.port_count(); i++) {
                acos::storage::StorageManager::register_device(i, ahci_ctrl.get_port(i));
                acos::storage::FileSystemManager::probe_and_mount(ahci_ctrl.get_port(i), "/");
            }
        }
    }

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

        acos::vfs::File* file = acos::scheduler::current_thread()->parent->get_file(fd);
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

    acos::hal::serial_print("Testing root filesystem...\n");

acos::i32 fd = acos::vfs::VFS::open("/kernel.elf", 0);

if (fd >= 0)
{
    acos::hal::serial_print("Found kernel.elf\n");
    acos::vfs::VFS::close(fd);
}
else
{
    acos::hal::serial_print("Cannot find kernel.elf\n");
}

    spawn_service("/bin/pcie_manager.elf");

    if (desktop_mode) {
        spawn_service("/bin/display_server.elf");
        spawn_service("/bin/nvme_driver.elf");
        spawn_service("/bin/ps2_driver.elf");
        spawn_service("/bin/xhci_driver.elf");
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
