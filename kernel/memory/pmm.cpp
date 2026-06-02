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

    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.type == MemoryRegionType::Available) {
            u64 start_page = region.base / PAGE_SIZE;
            u64 end_page = (region.base + region.length) / PAGE_SIZE;
            for (u64 page = start_page; page < end_page; ++page) {
                bitmap_clear(page);
            }
        }
    }

    // Mark bitmap's own pages as used
    u64 bitmap_start_page = bitmap_start / PAGE_SIZE;
    u64 bitmap_end_page = bitmap_end / PAGE_SIZE;
    for (u64 page = bitmap_start_page; page < bitmap_end_page; ++page) {
        bitmap_set(page);
    }

    // Mark page 0 as used (null page guard)
    bitmap_set(0);
}

u64 pmm_alloc() {
    if (!g_bitmap) return 0;
    for (u64 i = 1; i < g_total_pages; ++i) {
        if (!bitmap_test(i)) {
            bitmap_set(i);
            g_used_pages++;
            return i * 4096;
        }
    }
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
        return start * 4096;
    }
    return 0;
}


void pmm_free(u64 addr) {
    u64 page = addr / 4096;
    if (bitmap_test(page)) {
        bitmap_clear(page);
        g_used_pages--;
    }
}

u64 pmm_get_total_memory() {
    return get_total_pages() * 4096;
}

u64 pmm_get_used_memory() {
    return get_used_pages() * 4096;
}

} // namespace acos::memory
