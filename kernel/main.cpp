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
#include <kernel/storage/asfs.h>
#include <kernel/storage/asfs_formatter.h>
#include <kernel/storage/ramdisk.h>
#include <kernel/storage/ahci.h>
#include <kernel/storage/partition.h>
#include <kernel/hal/pci.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/hal/serial.h>
#include <kernel/hal/console.h>
#include <kernel/vfs/vfs.h>
#include <kernel/vfs/file.h>
#include <kernel/vfs/dev_fs.h>
#include <kernel/smp/smp.h>
#include <kernel/smp/cpu.h>
#include <kernel/hal/gdt.h>
#include <kernel/arch/x86_64/smp/lapic.h>
#include <kernel/arch/x86_64/smp/ioapic.h>
#include <kernel/arch/x86_64/acpi/madt.h>
#include <services/input/ps2/ps2.h>
#include <kernel/input/input_manager.h>
#include <kernel/input/keyboard_manager.h>
#include <kernel/input/mouse_manager.h>

#include <kernel/memory/vmm.h>
namespace acos::hal { void idt_init(); }

extern "C" void console_push_char(char c);

extern "C" void k_handle_mouse() {
    acos::drivers::input::PS2Controller::handle_mouse_interrupt();
}

static void poll_io() {
    acos::scheduler::check_sleeping_threads();
    if (acos::hal::serial_received()) {
        char c = acos::hal::serial_read();
        __asm__ volatile("cli");
        console_push_char(c);
        __asm__ volatile("sti");
    }
}

extern "C" void k_handle_gp(acos::u64 rip, acos::u64 error_code) {
    acos::hal::serial_print("GENERAL PROTECTION FAULT at RIP: ");
    acos::hal::serial_print_hex(rip);
    acos::hal::serial_print(" Code: ");
    acos::hal::serial_print_hex(error_code);
    acos::hal::serial_print("\n");
    while(1) __asm__ volatile("hlt");
}

extern "C" void k_handle_pf(acos::u64 rip, acos::u64 error_code, acos::u64 address) {
    // Detect and resolve Copy-On-Write faults
    if ((error_code & 2) && acos::memory::vmm_handle_cow(address)) {
        return;
    }

    acos::hal::serial_print("PAGE FAULT at RIP: ");
    acos::hal::serial_print_hex(rip);
    acos::hal::serial_print(" Addr: ");
    acos::hal::serial_print_hex(address);
    acos::hal::serial_print(" Code: ");
    acos::hal::serial_print_hex(error_code);
    acos::hal::serial_print("\n");
    while(1) __asm__ volatile("hlt");
}

extern "C" void k_handle_df(acos::u64 rip, acos::u64 error_code) {
    acos::hal::serial_print("DOUBLE FAULT at RIP: ");
    acos::hal::serial_print_hex(rip);
    acos::hal::serial_print(" Code: ");
    acos::hal::serial_print_hex(error_code);
    acos::hal::serial_print("\n");
    while(1) __asm__ volatile("hlt");
}

extern "C" void k_handle_kbd() {
    acos::drivers::input::PS2Controller::handle_keyboard_interrupt();
}

extern "C" void kernelMain(acos::BootInfo* bootInfo) {
    // Enable FPU and SSE in CR0 and CR4 to prevent user-space General Protection Faults
    acos::u64 cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 &= ~(1ULL << 2); // Clear EM (bit 2)
    cr0 |= (1ULL << 1);  // Set MP (bit 1)
    __asm__ volatile("mov %0, %%cr0" : : "r"(cr0));

    acos::u64 cr4;
    __asm__ volatile("mov %%cr4, %0" : "=r"(cr4));
    cr4 |= (1ULL << 9);  // Set OSFXSR (bit 9)
    cr4 |= (1ULL << 10); // Set OSXMMEXCPT (bit 10)
    __asm__ volatile("mov %0, %%cr4" : : "r"(cr4));

    acos::hal::serial_init();
    acos::hal::console_init(nullptr);
    acos::hal::serial_print("ACOS Kernel: Initializing...\n");
    bool desktop_mode = (bootInfo && bootInfo->framebuffer != nullptr);
    if (desktop_mode) { acos::hal::console_init(bootInfo->framebuffer); acos::hal::console_clear(0x001E3A5F); }
    acos::hal::gdt_init();
    acos::smp::SmpManager::init();
    acos::hal::idt_init();
    static acos::scheduler::Thread boot_thread;
    static acos::scheduler::Process kernel_process;
    boot_thread.id = 0; boot_thread.state = acos::scheduler::ThreadState::Running;
    boot_thread.is_user = false; boot_thread.parent = &kernel_process;
    kernel_process.id = 0; acos::smp::Cpu::current()->current_thread = &boot_thread;
    acos::memory::pmm_init(bootInfo);
    static acos::vfs::DevFileSystem s_dev_fs;
    acos::vfs::VFS::mount("/dev", &s_dev_fs);
    acos::memory::vmm_init(bootInfo);
    acos::scheduler::scheduler_init();
    acos::services::init();
    acos::storage::StorageManager::init();
    static acos::storage::FAT32FileSystem fat32_proto(nullptr);
    acos::storage::FileSystemManager::register_filesystem("fat32", &fat32_proto);

    // Register ASFS and mount RAM-disk for ASFS Milestone 1
    static acos::storage::ASFSFileSystem asfs_proto(nullptr);
    acos::storage::FileSystemManager::register_filesystem("asfs", &asfs_proto);

    static acos::u8 asfs_ram_buffer[65536]; // 64KB mock RAM partition for ASFS
    static acos::storage::RamDisk asfs_ram_disk(asfs_ram_buffer, 65536);
    acos::storage::ASFSFormatter::format_ramdisk(&asfs_ram_disk);

    acos::storage::StorageManager::register_device(0x300, &asfs_ram_disk);
    acos::storage::FileSystemManager::probe_and_mount(&asfs_ram_disk, "/asfs_ram");

    acos::hal::PCIDevice ahci_dev = acos::hal::PCI::find_device(0x01, 0x06);
    if (ahci_dev.vendor_id == 0xFFFF) ahci_dev = acos::hal::PCI::find_device(0x01, 0x01);
    if (ahci_dev.vendor_id != 0xFFFF) {
        acos::hal::PCI::enable_bus_mastering(ahci_dev);
        acos::u64 bar = acos::hal::PCI::get_bar(ahci_dev, 5);
        if (bar == 0) bar = acos::hal::PCI::get_bar(ahci_dev, 0);
        static acos::storage::AHCIController ahci_ctrl(bar);
        if (ahci_ctrl.initialize()) {
            for (acos::u32 i = 0; i < ahci_ctrl.port_count(); i++) {
                acos::storage::StorageManager::register_device(i, ahci_ctrl.get_port(i));
                acos::storage::PartitionManager::enumerate(ahci_ctrl.get_port(i));
            }
        }
    }
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Filesystem, 1);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Graphics, 2);
    acos::services::ServiceManager::register_service(acos::services::ServiceId::Audio, 3);
    acos::input::InputManager::init();
    if (desktop_mode) acos::graphics::GraphicsManager::init(bootInfo->framebuffer);
    acos::audio::AudioManager::init();

    acos::hal::serial_print("Testing root filesystem...\n");
    acos::vfs::DirectoryEntry entries[16];
    int count = acos::vfs::VFS::read_dir("/", entries, 16);
    if (count >= 0) {
        acos::hal::serial_print("Root directory contents:\n");
        for (int i = 0; i < count; i++) {
            acos::hal::serial_print("  ");
            acos::hal::serial_print(entries[i].name);
            acos::hal::serial_print("\n");
        }
    } else {
        acos::hal::serial_print("Failed to read root directory\n");
    }

    // Testing ASFS Writable Core on RAM BlockDevice (mounted at /asfs_ram)
    acos::hal::serial_print("\n--- ASFS Writable RAM-Disk Test Suite ---\n");
    acos::vfs::DirectoryEntry asfs_ram_entries[16];
    int asfs_ram_count = acos::vfs::VFS::read_dir("/asfs_ram", asfs_ram_entries, 16);
    if (false && asfs_ram_count >= 0) {
        acos::hal::serial_print("RAM Disk root contents:\n");
        for (int i = 0; i < asfs_ram_count; i++) {
            acos::hal::serial_print("  ");
            acos::hal::serial_print(asfs_ram_entries[i].name);
            acos::hal::serial_print("\n");
        }

        // RAM-Disk Writable operations: create nested folder and files
        acos::hal::serial_print("Creating directory /asfs_ram/apps/test_app\n");
        if (acos::vfs::VFS::mkdir("/asfs_ram/apps/test_app", 0755) == 0) {
            acos::hal::serial_print("[SUCCESS] Created RAM-disk directory /asfs_ram/apps/test_app!\n");
        } else {
            acos::hal::serial_print("[FAIL] Failed to create RAM directory!\n");
        }

        acos::hal::serial_print("Creating and writing /asfs_ram/apps/test_app/output.txt\n");
        acos::i32 ram_fd = acos::vfs::VFS::open("/asfs_ram/apps/test_app/output.txt", 65); // O_CREAT | O_WRONLY
        if (ram_fd >= 0) {
            const char* ram_msg = "ASADE RAM disk write test success!\n";
            acos::vfs::VFS::write(ram_fd, ram_msg, strlen(ram_msg));
            acos::vfs::VFS::close(ram_fd);

            // Read back
            ram_fd = acos::vfs::VFS::open("/asfs_ram/apps/test_app/output.txt", 0);
            if (ram_fd >= 0) {
                char ram_buf[64];
                memset(ram_buf, 0, 64);
                acos::vfs::VFS::read(ram_fd, ram_buf, 63);
                acos::hal::serial_print("RAM Read Content: ");
                acos::hal::serial_print(ram_buf);
                acos::vfs::VFS::close(ram_fd);
            }
        } else {
            acos::hal::serial_print("[FAIL] Failed to write file to RAM ASFS!\n");
        }

        // Test File & Dir deletion on RAM disk
        acos::vfs::VFS::unlink("/asfs_ram/apps/test_app/output.txt");
        acos::vfs::VFS::rmdir("/asfs_ram/apps/test_app");
        acos::hal::serial_print("RAM Disk writable test cleanup complete.\n");
    } else {
        acos::hal::serial_print("Failed to access /asfs_ram directory\n");
    }

    // Testing ASFS Integration & Mount on QEMU BlockDevice (SATA/AHCI Partition 2 /system)
    acos::hal::serial_print("\n--- ASFS /system Read-Only Mount Verification ---\n");
    acos::vfs::DirectoryEntry asfs_entries[16];
    int asfs_count = acos::vfs::VFS::read_dir("/system", asfs_entries, 16);
    if (asfs_count >= 0) {
        acos::hal::serial_print("ASFS /system directory contents:\n");
        for (int i = 0; i < asfs_count; i++) {
            acos::hal::serial_print("  ");
            acos::hal::serial_print(asfs_entries[i].name);
            acos::hal::serial_print("\n");
        }

        acos::hal::serial_print("Reading '/system/bin/cli.elf' contents...\n");
        acos::i32 asfs_fd = acos::vfs::VFS::open("/system/bin/cli.elf", 0);
        if (asfs_fd >= 0) {
            char file_content[64];
            memset(file_content, 0, 64);
            acos::i32 bytes_read = acos::vfs::VFS::read(asfs_fd, file_content, 63);
            if (bytes_read >= 0) {
                acos::hal::serial_print("File content: ");
                acos::hal::serial_print(file_content);
            } else {
                acos::hal::serial_print("Failed to read file from AHCI ASFS!\n");
            }
            acos::vfs::VFS::close(asfs_fd);
        } else {
            acos::hal::serial_print("Failed to open '/system/bin/cli.elf'!\n");
        }

        // Write protection test on /system (should fail!)
        acos::hal::serial_print("Attempting to write to read-only mounted /system filesystem...\n");
        if (acos::vfs::VFS::mkdir("/system/fail_dir", 0755) != 0) {
            acos::hal::serial_print("[SUCCESS] Properly blocked writing to read-only mounted system filesystem!\n");
        } else {
            acos::hal::serial_print("[FAIL] Wrote directory to read-only mounted system filesystem!\n");
        }
    } else {
        acos::hal::serial_print("Failed to read ASFS /system directory\n");
    }

    // Testing Writable ASFS on Partition 3 (mounted at /data)
    acos::hal::serial_print("\n--- ASFS Writable Disk-backed /data Mount Verification ---\n");
    acos::vfs::DirectoryEntry data_entries[16];
    int data_count = acos::vfs::VFS::read_dir("/data", data_entries, 16);
    if (data_count >= 0) {
        acos::hal::serial_print("ASFS /data directory contents:\n");
        for (int i = 0; i < data_count; i++) {
            acos::hal::serial_print("  ");
            acos::hal::serial_print(data_entries[i].name);
            acos::hal::serial_print("\n");
        }

        // Test 1: Create nested directory
        acos::hal::serial_print("[TEST 1] Create directory /data/test_dir\n");
        if (acos::vfs::VFS::mkdir("/data/test_dir", 0755) == 0) {
            acos::hal::serial_print("[SUCCESS] Created directory /data/test_dir!\n");
        } else {
            acos::hal::serial_print("[FAIL] Failed to create /data/test_dir!\n");
        }

        // Test 2: Create file inside /data/test_dir/persist.txt
        acos::hal::serial_print("[TEST 2] Create /data/test_dir/persist.txt\n");
        acos::i32 p_fd = acos::vfs::VFS::open("/data/test_dir/persist.txt", 65); // O_CREAT | O_WRONLY
        if (p_fd >= 0) {
            const char* msg = "ASADE OS Milestone 2 persistence works across hard disk reboots!\n";
            acos::vfs::VFS::write(p_fd, msg, strlen(msg));
            acos::vfs::VFS::close(p_fd);
            acos::hal::serial_print("[SUCCESS] Wrote persistence message to file!\n");
        } else {
            acos::hal::serial_print("[FAIL] Failed to create file in /data!\n");
        }

        // Test 3: Read back file
        acos::hal::serial_print("[TEST 3] Read back and verify file contents\n");
        acos::i32 r_p_fd = acos::vfs::VFS::open("/data/test_dir/persist.txt", 0);
        if (r_p_fd >= 0) {
            char p_buf[128];
            memset(p_buf, 0, 128);
            acos::vfs::VFS::read(r_p_fd, p_buf, 127);
            acos::hal::serial_print("Verified Persistence Content: ");
            acos::hal::serial_print(p_buf);
            acos::vfs::VFS::close(r_p_fd);
        } else {
            acos::hal::serial_print("[FAIL] Failed to read back persistence file!\n");
        }
    } else {
        acos::hal::serial_print("ASFS Writable /data is currently unmounted or unavailable.\n");
    }
    acos::hal::serial_print("\n--- ASFS Verification Completed ---\n\n");

    auto spawn_service = [](const char* path) {
        acos::hal::serial_print("Main: Spawning "); acos::hal::serial_print(path); acos::hal::serial_print("\n");
        acos::i32 fd = acos::vfs::VFS::open(path, 0);
        if (fd < 0) { acos::hal::serial_print("Main: Open failed\n"); return; }
        acos::vfs::File* file = acos::scheduler::current_thread()->parent->get_file(fd);
        if (!file) { acos::vfs::VFS::close(fd); return; }
        acos::usize size = file->size();
        acos::hal::serial_print("Main: size="); acos::hal::serial_print_hex(size); acos::hal::serial_print("\n");
        void* elf_data = acos::memory::kmalloc(size);
        if (!elf_data) {
            acos::hal::serial_print("Main: kmalloc failed for ");
            acos::hal::serial_print(path);
            acos::hal::serial_print("\n");
            acos::vfs::VFS::close(fd);
            return;
        }
        file->read(elf_data, size);
        acos::hal::serial_print("Main: read done\n");
        acos::vfs::VFS::close(fd);
        acos::scheduler::Process* child = acos::loader::create_process_from_elf(path, elf_data, size);
        acos::hal::serial_print("Main: create_process child=");
        acos::hal::serial_print_hex(reinterpret_cast<acos::u64>(child));
        acos::hal::serial_print("\n");
        acos::hal::serial_print("Main: calling kfree...\n");
        acos::memory::kfree(elf_data);
        acos::hal::serial_print("Main: kfree done\n");
        if (child && child->primary_thread) {
            acos::hal::serial_print("Main: waking thread\n");
            acos::scheduler::wake_thread(child->primary_thread);
        }
        acos::hal::serial_print("Main: Spawn complete\n");
    };

    if (desktop_mode) {
        acos::i32 fd = acos::vfs::VFS::open("/system/bin/desktop.elf", 0);
        if (fd >= 0) {
            acos::vfs::VFS::close(fd);
            spawn_service("/system/bin/desktop.elf");
        } else {
            spawn_service("/bin/desktop.elf");
        }
    } else {
        acos::i32 fd = acos::vfs::VFS::open("/system/bin/cli.elf", 0);
        if (fd >= 0) {
            acos::vfs::VFS::close(fd);
            spawn_service("/system/bin/cli.elf");
        } else {
            spawn_service("/bin/cli.elf");
        }
    }

    boot_thread.state = acos::scheduler::ThreadState::Ready;
    acos::scheduler::enqueue_thread(0, &boot_thread);

    acos::u64 lapic_base = 0xFEE00000;
    acos::u64 ioapic_base = 0xFEC00000;

    if (bootInfo && bootInfo->acpi) {
        acos::hal::serial_print("[ACPI] Finding MADT table...\n");
        void* madt_table = acos::arch::x86_64::MADT::find_table(bootInfo->acpi, "APIC");
        if (madt_table) {
            acos::hal::serial_print("[ACPI] Found MADT table. Parsing...\n");
            acos::arch::x86_64::MADTHeader* madt = (acos::arch::x86_64::MADTHeader*)madt_table;
            acos::hal::serial_print("[ACPI] Dynamic LAPIC address from MADT: ");
            acos::hal::serial_print_hex(madt->lapic_addr);
            acos::hal::serial_print("\n");
            if (madt->lapic_addr != 0) {
                lapic_base = madt->lapic_addr;
            }
            // Parse for CPUs and other info
            acos::arch::x86_64::MADT::parse(madt_table);
            if (acos::arch::x86_64::MADT::ioapic_address() != 0) {
                ioapic_base = acos::arch::x86_64::MADT::ioapic_address();
                acos::hal::serial_print("[ACPI] Dynamic IOAPIC address from MADT: ");
                acos::hal::serial_print_hex(ioapic_base);
                acos::hal::serial_print("\n");
            }
        } else {
            acos::hal::serial_print("[ACPI] Warning: MADT table not found. Using defaults.\n");
        }
    } else {
        acos::hal::serial_print("[ACPI] Warning: No ACPI tables passed from bootloader. Using defaults.\n");
    }

    // Configure base dynamically
    acos::arch::x86_64::LocalApic::set_base(lapic_base);

    // Initialize LocalApic, IoApic and route keyboard IRQ1 to vector 0x21 on BSP (Apic ID 0)
    acos::arch::x86_64::LocalApic::init();
    acos::arch::x86_64::IoApic::init(ioapic_base);
    acos::arch::x86_64::IoApic::set_irq(1, 0x21, 0);
    acos::arch::x86_64::IoApic::unmask(1);
    acos::arch::x86_64::IoApic::set_irq(12, 0x2C, 0);
    acos::arch::x86_64::IoApic::unmask(12);

    // Initialize PS/2 Keyboard Controller to enable keyboard interrupts (IRQ1)
    acos::drivers::input::PS2Controller::init();

    acos::scheduler::schedule();

    // Enable CPU interrupts globally after the scheduler starts
    __asm__ volatile("sti");

    while (true) {
        poll_io();
        if (acos::scheduler::get_thread_count() == 0 && acos::scheduler::get_sleep_count() == 0) {
            __asm__ volatile("hlt");
        } else {
            acos::scheduler::schedule();
        }
    }
}

extern "C" {
    void* __dso_handle = nullptr;
    int __cxa_atexit(void (*)(void*), void*, void*) { return 0; }
    typedef unsigned long __guard;
    int __cxa_guard_acquire(__guard* g) { return *g == 0; }
    void __cxa_guard_release(__guard* g) { *g = 1; }
    void __cxa_guard_abort(__guard*) {}
}
