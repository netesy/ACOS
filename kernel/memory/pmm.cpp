#include <acos/boot_info.h>
#include <acos/types.h>

namespace acos::memory {

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

void pmm_init(BootInfo* bootInfo) {
    if (!bootInfo || !bootInfo->memoryMap) return;

    u64 max_addr = 0;
    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.base + region.length > max_addr) {
            max_addr = region.base + region.length;
        }
    }

    g_total_pages = max_addr / 4096;
    g_bitmap_size = (g_total_pages / 64) + 1;

    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.type == MemoryRegionType::Available && region.length >= g_bitmap_size * 8) {
            g_bitmap = reinterpret_cast<u64*>(region.base);
            break;
        }
    }

    if (!g_bitmap) return;

    for (u64 i = 0; i < g_bitmap_size; ++i) g_bitmap[i] = 0xFFFFFFFFFFFFFFFF;

    for (u64 i = 0; i < bootInfo->memoryMap->count; ++i) {
        auto& region = bootInfo->memoryMap->regions[i];
        if (region.type == MemoryRegionType::Available) {
            for (u64 page = region.base / 4096; page < (region.base + region.length) / 4096; ++page) {
                bitmap_clear(page);
            }
        }
    }

    for (u64 i = 0; i < (g_bitmap_size * 8 + 4095) / 4096; ++i) {
        bitmap_set(reinterpret_cast<uptr>(g_bitmap) / 4096 + i);
    }
}

u64 pmm_alloc() {
    for (u64 i = 0; i < g_total_pages; ++i) {
        if (!bitmap_test(i)) {
            bitmap_set(i);
            g_used_pages++;
            return i * 4096;
        }
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

} // namespace acos::memory

// Global functions for system calls
extern "C" acos::u64 pmm_get_total_memory() {
    // Return total memory in bytes
    return acos::memory::get_total_pages() * 4096;
}

extern "C" acos::u64 pmm_get_used_memory() {
    // Return used memory in bytes
    return acos::memory::get_used_pages() * 4096;
}
