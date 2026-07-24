#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::memory {

struct BlockHeader {
    usize size;        // Size of the usable block (excluding header)
    BlockHeader* next; // Pointer to the next block in physical memory layout
    bool is_free;      // Whether the block is currently free
};

static u8 g_user_heap[32 * 1024 * 1024]; // 32MB static heap to prevent heap exhaustion
static bool g_heap_initialized = false;

static void init_heap() {
    BlockHeader* initial_block = reinterpret_cast<BlockHeader*>(g_user_heap);
    initial_block->size = sizeof(g_user_heap) - sizeof(BlockHeader);
    initial_block->next = nullptr;
    initial_block->is_free = true;
    g_heap_initialized = true;
}

void* malloc(usize size) {
    if (size == 0) return nullptr;

    // Align size to 8-byte boundary
    usize aligned_size = (size + 7) & ~7ULL;

    if (!g_heap_initialized) {
        init_heap();
    }

    BlockHeader* current = reinterpret_cast<BlockHeader*>(g_user_heap);
    while (current != nullptr) {
        if (current->is_free && current->size >= aligned_size) {
            // Check if we can split this block
            // We need enough space for the aligned request, a new header, and at least 8 bytes of payload
            if (current->size >= aligned_size + sizeof(BlockHeader) + 8) {
                u8* current_bytes = reinterpret_cast<u8*>(current);
                BlockHeader* next_block = reinterpret_cast<BlockHeader*>(current_bytes + sizeof(BlockHeader) + aligned_size);

                next_block->size = current->size - aligned_size - sizeof(BlockHeader);
                next_block->next = current->next;
                next_block->is_free = true;

                current->size = aligned_size;
                current->next = next_block;
            }

            current->is_free = false;
            return reinterpret_cast<void*>(current + 1);
        }
        current = current->next;
    }

    acos::process::log("Userland malloc Error: Heap exhausted!\n");
    return nullptr;
}

void free(void* ptr) {
    if (!ptr) return;

    // Verify pointer is within our heap boundaries
    u8* p = reinterpret_cast<u8*>(ptr);
    if (p < g_user_heap || p >= g_user_heap + sizeof(g_user_heap)) {
        return;
    }

    BlockHeader* block = reinterpret_cast<BlockHeader*>(ptr) - 1;
    block->is_free = true;

    // Coalesce / merge adjacent free blocks
    BlockHeader* current = reinterpret_cast<BlockHeader*>(g_user_heap);
    while (current != nullptr && current->next != nullptr) {
        if (current->is_free && current->next->is_free) {
            current->size += sizeof(BlockHeader) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

} // namespace acos::memory
