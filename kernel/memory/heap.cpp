#include <kernel/memory/heap.h>
#include <kernel/memory/pmm.h>
#include <kernel/hal/serial.h>
#include <kernel/hal/spinlock.h>
#include <acos/runtime.h>

namespace acos::memory {

namespace {

constexpr usize PAGE_SIZE = 4096;
constexpr u32 MAGIC_ALLOC = 0x414C4F43; // "ALOC"
constexpr u32 MAGIC_FREE  = 0x46524545; // "FREE"

struct BlockHeader {
    u32 magic;       // MAGIC_ALLOC or MAGIC_FREE
    bool is_free;
    usize size;      // Payload size in bytes (must be 16-byte aligned)
    BlockHeader* next;
    BlockHeader* prev;
};

// Alignment helper
usize align_up(usize value, usize alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

// Global SpinLock for thread-safe heap operations
hal::SpinLock g_heap_lock;

// Global block list pointers
BlockHeader* g_heap_first = nullptr;

// Statistics
usize g_stat_total_size = 0;
usize g_stat_allocated_bytes = 0;
usize g_stat_free_bytes = 0;
usize g_stat_allocation_count = 0;
usize g_stat_free_count = 0;
usize g_stat_arena_count = 0;

// Allocate a new arena from PMM and link it
bool expand_heap(usize minimum_payload_size) {
    // Determine how many pages we need.
    // We want to allocate at least 2MB (or aligned page size) to minimize PMM requests
    usize needed_size = minimum_payload_size + sizeof(BlockHeader);
    usize arena_size = align_up(needed_size, 2 * 1024 * 1024); // 2MB default chunk
    u64 pages = arena_size / PAGE_SIZE;

    u64 addr = pmm_alloc_contiguous(pages);
    if (!addr) {
        // Fallback: try smaller size (exact page size needed)
        arena_size = align_up(needed_size, PAGE_SIZE);
        pages = arena_size / PAGE_SIZE;
        addr = pmm_alloc_contiguous(pages);
        if (!addr) {
            hal::serial_print("[HEAP] ERROR: Out of physical memory for heap expansion!\n");
            return false;
        }
    }

    auto* new_block = reinterpret_cast<BlockHeader*>(addr);
    new_block->magic = MAGIC_FREE;
    new_block->is_free = true;
    new_block->size = arena_size - sizeof(BlockHeader);
    new_block->next = nullptr;
    new_block->prev = nullptr;

    g_stat_total_size += arena_size;
    g_stat_free_bytes += new_block->size;
    g_stat_arena_count++;

    // Insert into the global block list ordered by address
    if (!g_heap_first) {
        g_heap_first = new_block;
    } else {
        BlockHeader* curr = g_heap_first;
        if (new_block < curr) {
            new_block->next = curr;
            curr->prev = new_block;
            g_heap_first = new_block;
        } else {
            while (curr->next && curr->next < new_block) {
                curr = curr->next;
            }
            new_block->next = curr->next;
            new_block->prev = curr;
            if (curr->next) {
                curr->next->prev = new_block;
            }
            curr->next = new_block;
        }
    }

    return true;
}

// Coalesce blocks around `block`
void coalesce(BlockHeader* block) {
    if (!block || !block->is_free) return;

    // Check next block
    if (block->next && block->next->is_free) {
        u8* current_end = reinterpret_cast<u8*>(block) + sizeof(BlockHeader) + block->size;
        if (current_end == reinterpret_cast<u8*>(block->next)) {
            g_stat_free_bytes += sizeof(BlockHeader); // Header space becomes free payload
            block->size += sizeof(BlockHeader) + block->next->size;
            block->next = block->next->next;
            if (block->next) {
                block->next->prev = block;
            }
        }
    }

    // Check prev block
    if (block->prev && block->prev->is_free) {
        u8* prev_end = reinterpret_cast<u8*>(block->prev) + sizeof(BlockHeader) + block->prev->size;
        if (prev_end == reinterpret_cast<u8*>(block)) {
            g_stat_free_bytes += sizeof(BlockHeader); // Header space becomes free payload
            block->prev->size += sizeof(BlockHeader) + block->size;
            block->prev->next = block->next;
            if (block->next) {
                block->next->prev = block->prev;
            }
        }
    }
}

} // namespace

void* kmalloc(usize size) {
    if (size == 0) return nullptr;

    hal::ScopedLock lock(g_heap_lock);

    const usize aligned_size = align_up(size, 16);

    // Initial expansion if first time
    if (!g_heap_first) {
        if (!expand_heap(aligned_size)) {
            return nullptr;
        }
    }

    BlockHeader* curr = g_heap_first;
    BlockHeader* best_fit = nullptr;

    // Best-fit selection
    while (curr) {
        if (curr->magic != MAGIC_ALLOC && curr->magic != MAGIC_FREE) {
            hal::serial_print("[HEAP] CRITICAL CORRUPTION: Invalid magic detected during allocation!\n");
            while(1) { __asm__("hlt"); }
        }

        if (curr->is_free && curr->size >= aligned_size) {
            if (!best_fit || curr->size < best_fit->size) {
                best_fit = curr;
                if (curr->size == aligned_size) {
                    break;
                }
            }
        }
        curr = curr->next;
    }

    if (!best_fit) {
        if (!expand_heap(aligned_size)) {
            return nullptr;
        }
        curr = g_heap_first;
        while (curr) {
            if (curr->is_free && curr->size >= aligned_size) {
                if (!best_fit || curr->size < best_fit->size) {
                    best_fit = curr;
                    if (curr->size == aligned_size) {
                        break;
                    }
                }
            }
            curr = curr->next;
        }
    }

    if (!best_fit) {
        hal::serial_print("[HEAP] ERROR: Unable to find free block even after expansion!\n");
        return nullptr;
    }

    // Split the block if it exceeds aligned_size + sizeof(BlockHeader) + 16 (minimum payload size)
    if (best_fit->size >= aligned_size + sizeof(BlockHeader) + 16) {
        auto* split_block = reinterpret_cast<BlockHeader*>(
            reinterpret_cast<u8*>(best_fit) + sizeof(BlockHeader) + aligned_size
        );
        split_block->magic = MAGIC_FREE;
        split_block->is_free = true;
        split_block->size = best_fit->size - aligned_size - sizeof(BlockHeader);
        split_block->next = best_fit->next;
        split_block->prev = best_fit;
        if (best_fit->next) {
            best_fit->next->prev = split_block;
        }
        best_fit->next = split_block;

        best_fit->size = aligned_size;
        g_stat_free_bytes -= sizeof(BlockHeader);
    }

    best_fit->magic = MAGIC_ALLOC;
    best_fit->is_free = false;

    g_stat_allocated_bytes += best_fit->size;
    g_stat_free_bytes -= best_fit->size;
    g_stat_allocation_count++;

    return reinterpret_cast<void*>(reinterpret_cast<u8*>(best_fit) + sizeof(BlockHeader));
}

void kfree(void* ptr) {
    if (!ptr) return;

    hal::ScopedLock lock(g_heap_lock);

    if (reinterpret_cast<u64>(ptr) % 16 != 0) {
        hal::serial_print("[HEAP] kfree ERROR: Attempted to free unaligned pointer: ");
        hal::serial_print_hex(reinterpret_cast<u64>(ptr));
        hal::serial_print("\n");
        return;
    }

    auto* block = reinterpret_cast<BlockHeader*>(reinterpret_cast<u8*>(ptr) - sizeof(BlockHeader));

    if (block->magic == MAGIC_FREE || block->is_free) {
        hal::serial_print("[HEAP] kfree ERROR: Double-free detected on ptr: ");
        hal::serial_print_hex(reinterpret_cast<u64>(ptr));
        hal::serial_print("\n");
        return;
    }

    if (block->magic != MAGIC_ALLOC) {
        bool found = false;
        BlockHeader* curr = g_heap_first;
        while (curr) {
            if (curr == block) {
                found = true;
                break;
            }
            curr = curr->next;
        }

        if (!found) {
            hal::serial_print("[HEAP] kfree ERROR: Invalid free! Pointer has no matching block header: ");
            hal::serial_print_hex(reinterpret_cast<u64>(ptr));
            hal::serial_print("\n");
            return;
        }

        hal::serial_print("[HEAP] kfree ERROR: Heap corruption detected! Block header magic is invalid: ");
        hal::serial_print_hex(block->magic);
        hal::serial_print("\n");
        while(1) { __asm__("hlt"); }
    }

    block->magic = MAGIC_FREE;
    block->is_free = true;

    g_stat_allocated_bytes -= block->size;
    g_stat_free_bytes += block->size;
    g_stat_free_count++;

    coalesce(block);
}

bool heap_validate() {
    hal::ScopedLock lock(g_heap_lock);
    BlockHeader* curr = g_heap_first;
    if (!curr) return true;

    while (curr) {
        if (curr->magic != MAGIC_ALLOC && curr->magic != MAGIC_FREE) {
            hal::serial_print("[HEAP] VALIDATE FAILURE: Invalid magic in block header!\n");
            return false;
        }

        if (curr->is_free && curr->magic != MAGIC_FREE) {
            hal::serial_print("[HEAP] VALIDATE FAILURE: Free block has non-FREE magic!\n");
            return false;
        }
        if (!curr->is_free && curr->magic != MAGIC_ALLOC) {
            hal::serial_print("[HEAP] VALIDATE FAILURE: Allocated block has non-ALLOC magic!\n");
            return false;
        }

        if (curr->next) {
            if (curr->next->prev != curr) {
                hal::serial_print("[HEAP] VALIDATE FAILURE: Linkage corruption: curr->next->prev != curr\n");
                return false;
            }
        }
        curr = curr->next;
    }
    return true;
}

void heap_get_stats(usize* total_size, usize* allocated, usize* free_bytes, usize* alloc_count, usize* free_count) {
    hal::ScopedLock lock(g_heap_lock);
    if (total_size) *total_size = g_stat_total_size;
    if (allocated) *allocated = g_stat_allocated_bytes;
    if (free_bytes) *free_bytes = g_stat_free_bytes;
    if (alloc_count) *alloc_count = g_stat_allocation_count;
    if (free_count) *free_count = g_stat_free_count;
}

void heap_print_stats() {
    usize total_size = 0, allocated = 0, free_bytes = 0, alloc_count = 0, free_count = 0;
    heap_get_stats(&total_size, &allocated, &free_bytes, &alloc_count, &free_count);

    hal::serial_print("[HEAP] STATISTICS:\n");
    hal::serial_print("  Total managed space: ");
    hal::serial_print_hex(total_size);
    hal::serial_print(" bytes\n  Allocated bytes:     ");
    hal::serial_print_hex(allocated);
    hal::serial_print(" bytes\n  Free bytes:          ");
    hal::serial_print_hex(free_bytes);
    hal::serial_print(" bytes\n  Allocation count:    ");
    hal::serial_print_hex(alloc_count);
    hal::serial_print("\n  Free count:          ");
    hal::serial_print_hex(free_count);
    hal::serial_print("\n  Arena count:         ");
    hal::serial_print_hex(g_stat_arena_count);
    hal::serial_print("\n");
}

} // namespace acos::memory
