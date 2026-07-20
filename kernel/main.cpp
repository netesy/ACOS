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
#include <services/input/ps2/ps2.h>
#include <kernel/input/input_manager.h>
#include <kernel/input/keyboard_manager.h>
#include <kernel/input/mouse_manager.h>

namespace acos::hal { void idt_init(); }
namespace acos::memory { void vmm_init(BootInfo* bootInfo); }

extern "C" void console_push_char(char c);

extern "C" void k_handle_mouse() {
    acos::drivers::input::PS2Controller::handle_mouse_interrupt();
}

static void poll_io() {
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

    // Temporarily disabled other services to simplify debugging of cli.elf
    // spawn_service("/bin/pcie.elf");
    // if (desktop_mode) {
    //     spawn_service("/bin/display.elf");
    //     spawn_service("/bin/nvme.elf");
    //     spawn_service("/bin/ps2.elf");
    //     spawn_service("/bin/xhci.elf");
    //     spawn_service("/bin/audio.elf");
    //     spawn_service("/bin/desktop.elf");
    // }
    spawn_service("/bin/cli.elf");

    boot_thread.state = acos::scheduler::ThreadState::Ready;
    acos::scheduler::enqueue_thread(0, &boot_thread);

    // Initialize LocalApic, IoApic and route keyboard IRQ1 to vector 0x21 on BSP (Apic ID 0)
    acos::arch::x86_64::LocalApic::init();
    acos::arch::x86_64::IoApic::init(0xFEC00000);
    acos::arch::x86_64::IoApic::set_irq(1, 0x21, 0);
    acos::arch::x86_64::IoApic::unmask(1);
    acos::arch::x86_64::IoApic::set_irq(12, 0x2C, 0);
    acos::arch::x86_64::IoApic::unmask(12);

    // Initialize PS/2 Keyboard Controller to enable keyboard interrupts (IRQ1)
    acos::drivers::input::PS2Controller::init();

    acos::scheduler::schedule();

    // Enable CPU interrupts globally after the scheduler starts
    __asm__ volatile("sti");

    while (true) { poll_io(); acos::scheduler::schedule(); __asm__ volatile("hlt"); }
}

extern "C" {
    void* __dso_handle = nullptr;
    int __cxa_atexit(void (*)(void*), void*, void*) { return 0; }
    typedef unsigned long __guard;
    int __cxa_guard_acquire(__guard* g) { return *g == 0; }
    void __cxa_guard_release(__guard* g) { *g = 1; }
    void __cxa_guard_abort(__guard*) {}
}
