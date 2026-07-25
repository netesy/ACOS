#include <acos/boot_info.h>
#include <acos/types.h>
#include <kernel/hal/serial.h>

extern char _kernel_end[];

namespace acos::memory {

static constexpr u64 PAGE_SIZE = 4096;

static u64* g_bitmap = nullptr;
static u64 g_total_pages = 0;
static u64 g_used_pages = 0;
static u64 g_bitmap_size = 0;

// O(1) Free-List Page Frame Allocator Head Pointer (Physical Address)
static u64 g_free_list_head = 0;

// Accessors for global functions
u64 get_total_pages() { return g_total_pages; }
u64 get_used_pages() { return g_used_pages; }

static inline void bitmap_set(u64 page) {
    g_bitmap[page / 64] |= (1ULL << (page % 64));
}

static inline void bitmap_clear(u64 page) {
    g_bitmap[page / 64] &= ~(1ULL << (page % 64));
}

static inline bool bitmap_test(u64 page) {
    return g_bitmap[page / 64] & (1ULL << (page % 64));
}

static u64 align_up(u64 value, u64 alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

// Rebuild the O(1) free list from the bitmap status
static void pmm_rebuild_free_list() {
    g_free_list_head = 0;
    // Walk from end to start to maintain ascending address order
    for (u64 i = g_total_pages - 1; i >= 1; --i) {
        if (!bitmap_test(i)) {
            u64 addr = i * 4096;
            *reinterpret_cast<u64*>(addr) = g_free_list_head;
            g_free_list_head = addr;
        }
    }
}

void pmm_init(BootInfo* bootInfo) {
    if (!bootInfo || !bootInfo->memoryMap) {
        acos::hal::serial_print("[PMM] ERROR: no bootInfo or memoryMap\n");
        return;
    }

    // Find maximum physical address across available (RAM) regions only.
    // This avoids counting MMIO/framebuffer gaps that inflate the bitmap.
    u64 max_addr = 0;
    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.type != MemoryRegionType::Available) continue;
        u64 end = region.base + region.length;
        if (end > max_addr) max_addr = end;
    }

    g_total_pages = max_addr / PAGE_SIZE;
    g_bitmap_size = (g_total_pages / 64) + 1;
    u64 bitmap_bytes = g_bitmap_size * sizeof(u64);

    acos::hal::serial_print("PMM: total_pages=");
    acos::hal::serial_print_hex(g_total_pages);
    acos::hal::serial_print(" max_addr=");
    acos::hal::serial_print_hex(max_addr);
    acos::hal::serial_print("\n");

    // Print all memory regions
    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        acos::hal::serial_print("PMM: Region ");
        acos::hal::serial_print_hex(i);
        acos::hal::serial_print(" base=");
        acos::hal::serial_print_hex(region.base);
        acos::hal::serial_print(" len=");
        acos::hal::serial_print_hex(region.length);
        acos::hal::serial_print(" type=");
        acos::hal::serial_print_hex(static_cast<u64>(region.type));
        acos::hal::serial_print("\n");
    }

    // Place bitmap right after the kernel image, page-aligned
    u64 kernel_end_addr = align_up(reinterpret_cast<u64>(_kernel_end), PAGE_SIZE);
    u64 bitmap_start = kernel_end_addr;
    u64 bitmap_end = bitmap_start + bitmap_bytes;
    bitmap_end = align_up(bitmap_end, PAGE_SIZE);

    // Verify the bitmap fits within an available memory region
    bool placed = false;
    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.type != MemoryRegionType::Available) continue;
        u64 region_end = region.base + region.length;
        if (bitmap_start >= region.base && bitmap_end <= region_end) {
            placed = true;
            break;
        }
    }
    if (!placed) {
        acos::hal::serial_print("[PMM] ERROR: bitmap does not fit in any available region\n");
        return;
    }

    g_bitmap = reinterpret_cast<u64*>(bitmap_start);

    // Mark all pages as used, then clear available regions
    for (u64 i = 0; i < g_bitmap_size; ++i) g_bitmap[i] = 0xFFFFFFFFFFFFFFFF;

    acos::hal::serial_print("PMM: step 1 bitmap[503]=");
    acos::hal::serial_print_hex(g_bitmap[503]);
    acos::hal::serial_print("\n");

    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.type == MemoryRegionType::Available) {
            u64 start_page = region.base / PAGE_SIZE;
            u64 end_page = (region.base + region.length) / PAGE_SIZE;
            if (start_page >= g_total_pages) continue;
            if (end_page > g_total_pages) end_page = g_total_pages;
            for (u64 page = start_page; page < end_page; ++page) {
                bitmap_clear(page);
            }
        }
    }

    acos::hal::serial_print("PMM: step 2 bitmap[503]=");
    acos::hal::serial_print_hex(g_bitmap[503]);
    acos::hal::serial_print("\n");

    // Force all reserved/non-available regions to be marked as used,
    // overriding any overlaps from other regions.
    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.type != MemoryRegionType::Available) {
            u64 start_page = region.base / PAGE_SIZE;
            u64 end_page = (region.base + region.length) / PAGE_SIZE;
            if (start_page >= g_total_pages) continue;
            if (end_page > g_total_pages) end_page = g_total_pages;
            for (u64 page = start_page; page < end_page; ++page) {
                bitmap_set(page);
            }
        }
    }

    acos::hal::serial_print("PMM: step 3 bitmap[503]=");
    acos::hal::serial_print_hex(g_bitmap[503]);
    acos::hal::serial_print("\n");

    // Mark bitmap's own pages as used
    u64 bitmap_start_page = bitmap_start / PAGE_SIZE;
    u64 bitmap_end_page = bitmap_end / PAGE_SIZE;
    for (u64 page = bitmap_start_page; page < bitmap_end_page; ++page) {
        bitmap_set(page);
    }

    // Mark page 0 as used (null page guard)
    bitmap_set(0);

    // Mark kernel image pages as used.
    u64 kernel_start = 0x100000; // linker.ld loads kernel at 1 MB
    for (u64 addr = kernel_start; addr < kernel_end_addr; addr += PAGE_SIZE) {
        bitmap_set(addr / PAGE_SIZE);
    }

    acos::hal::serial_print("PMM: page 32255 test before rebuild=");
    acos::hal::serial_print_hex(bitmap_test(32255));
    acos::hal::serial_print("\n");

    // Build the initial constant-time O(1) page frame free list
    pmm_rebuild_free_list();

    acos::hal::serial_print("[PMM] Initialized. Kernel image protected. O(1) Free List enabled.\n");
}

u64 pmm_alloc() {
    if (!g_bitmap) return 0;

    // Allocate from the fast constant-time O(1) free list
    if (g_free_list_head != 0) {
        u64 allocated_addr = g_free_list_head;
        g_free_list_head = *reinterpret_cast<u64*>(allocated_addr);

        u64 page = allocated_addr / 4096;
        bitmap_set(page);
        g_used_pages++;

        // Clear the page contents for security and safety
        for (usize i = 0; i < 4096 / sizeof(u64); i++) {
            reinterpret_cast<u64*>(allocated_addr)[i] = 0;
        }

        return allocated_addr;
    }

    // Out of memory
    return 0;
}

u64 pmm_alloc_contiguous(u64 page_count) {
    if (!g_bitmap || page_count == 0) return 0;

    const u64 limit = g_total_pages;
    for (u64 start = 1; start + page_count <= limit; ++start) {
        bool free_run = true;
        for (u64 offset = 0; offset < page_count; ++offset) {
            if (bitmap_test(start + offset)) {
                free_run = false;
                start += offset;
                break;
            }
        }
        if (!free_run) {
            continue;
        }

        for (u64 offset = 0; offset < page_count; ++offset) {
            bitmap_set(start + offset);
        }
        g_used_pages += page_count;

        // Synchronize our O(1) free list
        pmm_rebuild_free_list();

        return start * 4096;
    }
    acos::hal::serial_print("PMM: pmm_alloc_contiguous FAILED for pages=");
    acos::hal::serial_print_hex(page_count);
    acos::hal::serial_print("\n");
    return 0;
}

void pmm_free(u64 addr) {
    u64 page = addr / 4096;
    if (bitmap_test(page)) {
        bitmap_clear(page);
        g_used_pages--;

        // Push the page back onto the fast constant-time O(1) free list
        *reinterpret_cast<u64*>(addr) = g_free_list_head;
        g_free_list_head = addr;
    }
}

u64 pmm_get_total_memory() {
    return get_total_pages() * 4096;
}

u64 pmm_get_used_memory() {
    return get_used_pages() * 4096;
}

} // namespace acos::memory
