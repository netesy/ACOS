#include <acos/boot_info.h>
#include <acos/types.h>
#include <kernel/hal/serial.h>
#include <kernel/hal/spinlock.h>

extern char _kernel_end[];

namespace acos::memory {

static constexpr u64 PAGE_SIZE = 4096;

static u64* g_bitmap = nullptr;
static u16* g_page_ref_counts = nullptr;
static u8* g_page_orders = nullptr;
static u64 g_total_pages = 0;
static u64 g_used_pages = 0;
static u64 g_bitmap_size = 0;

static hal::SpinLock g_pmm_lock;

// Buddy Allocator structures
static constexpr u32 MAX_ORDER = 16;
static u64 g_buddy_free_head[MAX_ORDER + 1] = {0};

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

static inline u64 order_to_pages(u32 order) {
    return 1ULL << order;
}

static inline u32 pages_to_order(u64 pages) {
    u32 order = 0;
    while ((1ULL << order) < pages) {
        order++;
    }
    return order;
}

static void buddy_insert_to_list(u64 page_idx, u32 order) {
    u64 addr = page_idx * 4096;
    u64 old_head = g_buddy_free_head[order];
    *reinterpret_cast<u64*>(addr) = old_head; // next
    *reinterpret_cast<u64*>(addr + 8) = 0;    // prev
    if (old_head != 0) {
        *reinterpret_cast<u64*>(old_head + 8) = addr;
    }
    g_buddy_free_head[order] = addr;
    g_page_orders[page_idx] = order;
}

static void buddy_remove_from_list(u64 page_idx, u32 order) {
    u64 addr = page_idx * 4096;
    u64 next_addr = *reinterpret_cast<u64*>(addr);
    u64 prev_addr = *reinterpret_cast<u64*>(addr + 8);
    if (prev_addr != 0) {
        *reinterpret_cast<u64*>(prev_addr) = next_addr;
    } else {
        g_buddy_free_head[order] = next_addr;
    }
    if (next_addr != 0) {
        *reinterpret_cast<u64*>(next_addr + 8) = prev_addr;
    }
}

static void buddy_free_block(u64 page_idx, u32 order, bool check_processed) {
    while (order < MAX_ORDER) {
        u64 buddy_idx = page_idx ^ (1ULL << order);
        if (buddy_idx + (1ULL << order) > g_total_pages) {
            break; // Buddy is out of bounds
        }
        if (check_processed && buddy_idx > page_idx) {
            break; // Buddy not processed yet during initialization
        }
        if (bitmap_test(buddy_idx) || g_page_orders[buddy_idx] != order) {
            break; // Buddy is not free or has different order
        }
        // Coalesce! Remove buddy from its order list
        buddy_remove_from_list(buddy_idx, order);
        g_page_orders[buddy_idx] = 0xFF; // Mark buddy as merged
        if (buddy_idx < page_idx) {
            page_idx = buddy_idx;
        }
        order++;
    }
    buddy_insert_to_list(page_idx, order);
}

void pmm_init(BootInfo* bootInfo) {
    if (!bootInfo || !bootInfo->memoryMap) {
        acos::hal::serial_print("[PMM] ERROR: no bootInfo or memoryMap\n");
        return;
    }

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

    u64 kernel_end_addr = align_up(reinterpret_cast<u64>(_kernel_end), PAGE_SIZE);
    u64 bitmap_start = kernel_end_addr;
    u64 bitmap_end = bitmap_start + bitmap_bytes;
    bitmap_end = align_up(bitmap_end, PAGE_SIZE);

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
            if (start_page >= g_total_pages) continue;
            if (end_page > g_total_pages) end_page = g_total_pages;
            for (u64 page = start_page; page < end_page; ++page) {
                bitmap_clear(page);
            }
        }
    }

    // Force all reserved/non-available regions to be marked as used
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

    // Allocate reference counts array right after the bitmap
    u64 ref_counts_start = bitmap_end;
    u64 ref_counts_bytes = g_total_pages * sizeof(u16);
    u64 ref_counts_end = align_up(ref_counts_start + ref_counts_bytes, PAGE_SIZE);

    g_page_ref_counts = reinterpret_cast<u16*>(ref_counts_start);
    for (u64 i = 0; i < g_total_pages; i++) {
        g_page_ref_counts[i] = 0;
    }

    // Allocate orders array right after ref counts
    u64 orders_start = ref_counts_end;
    u64 orders_bytes = g_total_pages * sizeof(u8);
    u64 orders_end = align_up(orders_start + orders_bytes, PAGE_SIZE);

    g_page_orders = reinterpret_cast<u8*>(orders_start);
    for (u64 i = 0; i < g_total_pages; i++) {
        g_page_orders[i] = 0xFF; // Initially invalid / sentinel
    }

    // Mark bitmap's own pages as used
    u64 bitmap_start_page = bitmap_start / PAGE_SIZE;
    u64 bitmap_end_page = bitmap_end / PAGE_SIZE;
    for (u64 page = bitmap_start_page; page < bitmap_end_page; ++page) {
        bitmap_set(page);
    }

    // Mark reference counts' own pages as used
    u64 ref_start_page = ref_counts_start / PAGE_SIZE;
    u64 ref_end_page = ref_counts_end / PAGE_SIZE;
    for (u64 page = ref_start_page; page < ref_end_page; ++page) {
        bitmap_set(page);
    }

    // Mark orders' own pages as used
    u64 orders_start_page = orders_start / PAGE_SIZE;
    u64 orders_end_page = orders_end / PAGE_SIZE;
    for (u64 page = orders_start_page; page < orders_end_page; ++page) {
        bitmap_set(page);
    }

    // Mark page 0 as used (null page guard)
    bitmap_set(0);

    // Mark first 64MB of physical RAM as used/reserved to protect kernel image, PMM tables,
    // and user segment physical mappings from overlap/clobbering by page table allocations.
    u64 reserved_limit = 64 * 1024 * 1024; // 64MB
    u64 reserved_pages = reserved_limit / PAGE_SIZE;
    for (u64 page = 0; page < reserved_pages; ++page) {
        if (page < g_total_pages) {
            bitmap_set(page);
        }
    }

    // Mark kernel image pages as used
    u64 kernel_start = 0x100000; // linker.ld loads kernel at 1 MB
    for (u64 addr = kernel_start; addr < kernel_end_addr; addr += PAGE_SIZE) {
        bitmap_set(addr / PAGE_SIZE);
    }

    // Initialize all buddy lists to empty
    for (u32 o = 0; o <= MAX_ORDER; o++) {
        g_buddy_free_head[o] = 0;
    }

    // Build the buddy allocator free lists (coalescing free blocks)
    for (u64 page = 1; page < g_total_pages; page++) {
        if (!bitmap_test(page)) {
            buddy_free_block(page, 0, true);
        }
    }

    acos::hal::serial_print("[PMM] Initialized. Buddy Allocator active (orders 0-16).\n");
}

u64 pmm_alloc_contiguous(u64 page_count) {
    if (!g_bitmap || page_count == 0) return 0;

    hal::ScopedLock lock(g_pmm_lock);

    u32 order = pages_to_order(page_count);
    if (order > MAX_ORDER) {
        acos::hal::serial_print("PMM: pmm_alloc_contiguous FAILED because order exceeds MAX_ORDER\n");
        return 0;
    }

    u32 o = order;
    while (o <= MAX_ORDER && g_buddy_free_head[o] == 0) {
        o++;
    }

    if (o > MAX_ORDER) {
        return 0; // Out of memory
    }

    u64 block_addr = g_buddy_free_head[o];
    u64 next_block = *reinterpret_cast<u64*>(block_addr);
    g_buddy_free_head[o] = next_block;
    if (next_block != 0) {
        *reinterpret_cast<u64*>(next_block + 8) = 0; // prev = 0
    }

    while (o > order) {
        o--;
        u64 buddy_addr = block_addr + (order_to_pages(o) * 4096);
        buddy_insert_to_list(buddy_addr / 4096, o);
    }

    u64 start_page = block_addr / 4096;
    u64 pages_allocated = order_to_pages(order);

    for (u64 i = 0; i < pages_allocated; i++) {
        bitmap_set(start_page + i);
        if (g_page_ref_counts) {
            g_page_ref_counts[start_page + i] = 1;
        }
    }
    g_used_pages += pages_allocated;
    g_page_orders[start_page] = order;

    // Clear memory block
    for (u64 i = 0; i < (pages_allocated * 4096) / sizeof(u64); i++) {
        reinterpret_cast<u64*>(block_addr)[i] = 0;
    }

    return block_addr;
}

u64 pmm_alloc() {
    return pmm_alloc_contiguous(1);
}

void pmm_free(u64 addr) {
    if (addr == 0) return;

    hal::ScopedLock lock(g_pmm_lock);

    u64 page = addr / 4096;
    if (g_page_ref_counts && g_page_ref_counts[page] > 0) {
        g_page_ref_counts[page]--;
        if (g_page_ref_counts[page] > 0) {
            return; // Shared page, do not free yet
        }
    }

    if (bitmap_test(page)) {
        u32 order = g_page_orders[page];
        if (order > MAX_ORDER) {
            order = 0; // Fallback sanity check
        }
        u64 pages_to_free = order_to_pages(order);
        for (u64 i = 0; i < pages_to_free; i++) {
            bitmap_clear(page + i);
        }
        g_used_pages -= pages_to_free;
        buddy_free_block(page, order, false);
    }
}

u16 pmm_get_ref_count(u64 page_index) {
    if (g_page_ref_counts && page_index < g_total_pages) {
        return g_page_ref_counts[page_index];
    }
    return 0;
}

void pmm_inc_ref_count(u64 page_index) {
    hal::ScopedLock lock(g_pmm_lock);
    if (g_page_ref_counts && page_index < g_total_pages) {
        g_page_ref_counts[page_index]++;
    }
}

void pmm_dec_ref_count(u64 page_index) {
    hal::ScopedLock lock(g_pmm_lock);
    if (g_page_ref_counts && page_index < g_total_pages) {
        if (g_page_ref_counts[page_index] > 0) {
            g_page_ref_counts[page_index]--;
        }
    }
}

u64 pmm_get_total_memory() {
    return g_total_pages * 4096;
}

u64 pmm_get_used_memory() {
    return g_used_pages * 4096;
}

} // namespace acos::memory
