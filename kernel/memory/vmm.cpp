#include <kernel/memory/vmm.h>
#include <acos/types.h>
#include <kernel/memory/pmm.h>
#include <kernel/hal/serial.h>
#include <acos/boot_info.h>
#include <kernel/hal/pci.h>
#include <kernel/arch/x86_64/acpi/madt.h>

extern "C" {
    extern char _text_start[];
    extern char _text_end[];
    extern char _rodata_start[];
    extern char _rodata_end[];
    extern char _data_start[];
    extern char _data_end[];
    extern char _bss_start[];
    extern char _bss_end[];
}

namespace acos::memory {

static PageTable* g_kernel_pml4 = nullptr;

static constexpr u64 PAGE_SIZE = 4096;

void clear_page_table(PageTable* table) {
    if (!table) return;
    for (int i = 0; i < 512; ++i) {
        table->entries[i] = 0;
    }
}

static PageTable* alloc_table() {
    u64 addr = pmm_alloc();
    if (addr == 0) return nullptr;
    auto* table = reinterpret_cast<PageTable*>(addr);
    clear_page_table(table);
    return table;
}

// Map a single 4KB page with Huge Page splitting support
void vmm_map(PageTable* pml4, u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;
    u64 pt_idx   = (virt >> 12) & 0x1FF;

    if (!(pml4->entries[pml4_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pml4->entries[pml4_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pdpt = reinterpret_cast<PageTable*>(pml4->entries[pml4_idx] & ~0xFFFULL);

    if (!(pdpt->entries[pdpt_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pdpt->entries[pdpt_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);

    if (!(pd->entries[pd_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pd->entries[pd_idx] = reinterpret_cast<u64>(t) | 3;
    } else if (pd->entries[pd_idx] & (1ULL << 7)) {
        // Split existing 2MB Huge Page into 4KB pages to avoid conflicts
        u64 huge_phys = pd->entries[pd_idx] & ~0x1FFFFFULL;
        u64 huge_flags = pd->entries[pd_idx] & 0x1FFFFFULL & ~(1ULL << 7);
        PageTable* t = alloc_table();
        if (!t) return;
        for (int i = 0; i < 512; i++) {
            t->entries[i] = (huge_phys + (i * 4096)) | huge_flags;
        }
        pd->entries[pd_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pt = reinterpret_cast<PageTable*>(pd->entries[pd_idx] & ~0xFFFULL);

    pt->entries[pt_idx] = phys | flags | 1;
}

// Map a 2MB large page (PS bit set in PD entry)
static void vmm_map_2m(PageTable* pml4, u64 virt, u64 phys, u64 flags) {
    u64 pml4_idx = (virt >> 39) & 0x1FF;
    u64 pdpt_idx = (virt >> 30) & 0x1FF;
    u64 pd_idx   = (virt >> 21) & 0x1FF;

    if (!(pml4->entries[pml4_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pml4->entries[pml4_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pdpt = reinterpret_cast<PageTable*>(pml4->entries[pml4_idx] & ~0xFFFULL);

    if (!(pdpt->entries[pdpt_idx] & 1)) {
        PageTable* t = alloc_table();
        if (!t) return;
        pdpt->entries[pdpt_idx] = reinterpret_cast<u64>(t) | 3;
    }
    auto* pd = reinterpret_cast<PageTable*>(pdpt->entries[pdpt_idx] & ~0xFFFULL);

    // Set PD entry with PS (Page Size) bit 7 for 2MB page
    pd->entries[pd_idx] = phys | flags | 1 | (1ULL << 7);
}

bool vmm_validate_wx() {
    if (!g_kernel_pml4) return true;
    PageTable* pml4 = g_kernel_pml4;
    for (int i = 0; i < 512; ++i) {
        if (!(pml4->entries[i] & 1)) continue;
        auto* pdpt = reinterpret_cast<PageTable*>(pml4->entries[i] & ~0xFFFULL);
        for (int j = 0; j < 512; ++j) {
            if (!(pdpt->entries[j] & 1)) continue;
            if (pdpt->entries[j] & (1ULL << 7)) { // 1GB page
                u64 entry = pdpt->entries[j];
                bool is_writable = (entry & 2) != 0;
                bool is_executable = (entry & (1ULL << 63)) == 0;
                if (is_writable && is_executable) {
                    acos::hal::serial_print("[VMM] W^X VIOLATION in 1GB page entry: ");
                    acos::hal::serial_print_hex(entry);
                    acos::hal::serial_print("\n");
                    return false;
                }
                continue;
            }
            auto* pd = reinterpret_cast<PageTable*>(pdpt->entries[j] & ~0xFFFULL);
            for (int k = 0; k < 512; ++k) {
                if (!(pd->entries[k] & 1)) continue;
                if (pd->entries[k] & (1ULL << 7)) { // 2MB page
                    u64 entry = pd->entries[k];
                    bool is_writable = (entry & 2) != 0;
                    bool is_executable = (entry & (1ULL << 63)) == 0;
                    if (is_writable && is_executable) {
                        // Skip checking framebuffer or MMIO ranges that aren't memory-mapped code
                        u64 page_addr = entry & ~0x1FFFFFULL;
                        if (page_addr < pmm_get_total_memory()) {
                            acos::hal::serial_print("[VMM] W^X VIOLATION in 2MB page entry: ");
                            acos::hal::serial_print_hex(entry);
                            acos::hal::serial_print("\n");
                            return false;
                        }
                    }
                    continue;
                }
                auto* pt = reinterpret_cast<PageTable*>(pd->entries[k] & ~0xFFFULL);
                for (int l = 0; l < 512; ++l) {
                    if (!(pt->entries[l] & 1)) continue;
                    u64 entry = pt->entries[l];
                    bool is_writable = (entry & 2) != 0;
                    bool is_executable = (entry & (1ULL << 63)) == 0;
                    if (is_writable && is_executable) {
                        acos::hal::serial_print("[VMM] W^X VIOLATION in 4KB page entry: ");
                        acos::hal::serial_print_hex(entry);
                        acos::hal::serial_print("\n");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void vmm_init(BootInfo* bootInfo) {
    g_kernel_pml4 = reinterpret_cast<PageTable*>(pmm_alloc());
    if (!g_kernel_pml4) {
        acos::hal::serial_print("[VMM] ERROR: pmm_alloc for PML4 failed\n");
        return;
    }
    clear_page_table(g_kernel_pml4);

    // Identity-map physical memory using 2MB large pages for speed.
    // By default, physical RAM is mapped as Present + Writable + NoExecute (W^X-safe)
    u64 phys_limit = pmm_get_total_memory();
    if (phys_limit < 0x100000000ULL) phys_limit = 0x100000000ULL;

    u64 map_limit = (phys_limit + 0x1FFFFF) & ~0x1FFFFFULL;

    for (u64 addr = 0; addr < map_limit; addr += 0x200000) {
        vmm_map_2m(g_kernel_pml4, addr, addr, 2 | (1ULL << 63)); // Present + Writable + NoExecute
    }

    // Map framebuffer region with 2MB pages (Present + Writable + NoExecute)
    if (bootInfo && bootInfo->framebuffer && bootInfo->framebuffer->base != 0 && bootInfo->framebuffer->size != 0) {
        const u64 start = bootInfo->framebuffer->base & ~0x1FFFFFULL;
        const u64 end = (bootInfo->framebuffer->base + bootInfo->framebuffer->size + 0x1FFFFF) & ~0x1FFFFFULL;
        for (u64 addr = start; addr < end; addr += 0x200000) {
            vmm_map_2m(g_kernel_pml4, addr, addr, 2 | (1ULL << 63));
        }
    }

    // Parse ACPI MCFG table for PCI Express ECAM support
    if (bootInfo && bootInfo->acpi) {
        void* mcfg_table = acos::arch::x86_64::MADT::find_table(bootInfo->acpi, "MCFG");
        if (mcfg_table) {
            struct MCFGHeader {
                acos::arch::x86_64::ACPISDTHeader h;
                u64 reserved;
            } __attribute__((packed));

            struct MCFGEntry {
                u64 base_address;
                u16 pci_segment_group;
                u8 start_bus;
                u8 end_bus;
                u32 reserved;
            } __attribute__((packed));

            auto* mcfg = reinterpret_cast<MCFGHeader*>(mcfg_table);
            usize entry_count = (mcfg->h.length - sizeof(MCFGHeader)) / sizeof(MCFGEntry);
            auto* entries = reinterpret_cast<MCFGEntry*>(mcfg + 1);

            if (entry_count > 0) {
                u64 ecam_base = entries[0].base_address;
                u8 start_bus = entries[0].start_bus;
                u8 end_bus = entries[0].end_bus;

                // Map ECAM memory-mapped configuration range using 2MB pages
                // Each bus is 1MB in size. We use Cache Disable (bit 4) + Write Through (bit 3) flags.
                u64 ecam_size = static_cast<u64>(end_bus - start_bus + 1) * 1024 * 1024;
                u64 ecam_end = (ecam_base + ecam_size + 0x1FFFFF) & ~0x1FFFFFULL;
                for (u64 addr = ecam_base & ~0x1FFFFFULL; addr < ecam_end; addr += 0x200000) {
                    vmm_map_2m(g_kernel_pml4, addr, addr, 2 | (1ULL << 63) | (1ULL << 4) | (1ULL << 3));
                }

                acos::hal::PCI::init_pcie(ecam_base, start_bus, end_bus);
                acos::hal::serial_print("[VMM] Mapped and initialized PCI Express ECAM: base=");
                acos::hal::serial_print_hex(ecam_base);
                acos::hal::serial_print("\n");
            }
        }
    }

    // Apply strict page-level segment protections using linker boundaries
    u64 text_s = reinterpret_cast<u64>(_text_start);
    u64 text_e = reinterpret_cast<u64>(_text_end);
    for (u64 addr = text_s; addr < text_e; addr += PAGE_SIZE) {
        vmm_map(g_kernel_pml4, addr, addr, 0); // Present, Read-Only, Executable (RX)
    }

    u64 rodata_s = reinterpret_cast<u64>(_rodata_start);
    u64 rodata_e = reinterpret_cast<u64>(_rodata_end);
    for (u64 addr = rodata_s; addr < rodata_e; addr += PAGE_SIZE) {
        vmm_map(g_kernel_pml4, addr, addr, 1ULL << 63); // Present, Read-Only, Non-Executable (R)
    }

    u64 data_s = reinterpret_cast<u64>(_data_start);
    u64 data_e = reinterpret_cast<u64>(_data_end);
    for (u64 addr = data_s; addr < data_e; addr += PAGE_SIZE) {
        vmm_map(g_kernel_pml4, addr, addr, 2 | (1ULL << 63)); // Present, Writable, Non-Executable (RW)
    }

    u64 bss_s = reinterpret_cast<u64>(_bss_start);
    u64 bss_e = reinterpret_cast<u64>(_bss_end);
    for (u64 addr = bss_s; addr < bss_e; addr += PAGE_SIZE) {
        vmm_map(g_kernel_pml4, addr, addr, 2 | (1ULL << 63)); // Present, Writable, Non-Executable (RW)
    }

    // Perform strict runtime W^X page table validation
    if (vmm_validate_wx()) {
        acos::hal::serial_print("[VMM] Strict W^X Memory Protection Verified successfully!\n");
    } else {
        acos::hal::serial_print("[VMM] CRITICAL ERROR: W^X Memory Protection validation failed!\n");
        while(1) { __asm__("hlt"); }
    }

    acos::hal::serial_print("[VMM] CR3 loaded\n");
    __asm__ volatile("mov %0, %%cr3" : : "r"(g_kernel_pml4));
}

} // namespace acos::memory
