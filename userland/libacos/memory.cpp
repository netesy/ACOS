#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::memory {

struct alignas(16) BlockHeader {
    usize size;        // Size of the usable block (excluding header)
    BlockHeader* next; // Pointer to the next block in physical memory layout
    bool is_free;      // Whether the block is currently free
    u8 padding[15];    // Explicit padding to ensure 32-byte size and alignment
};

static_assert(sizeof(BlockHeader) == 32, "BlockHeader size must be exactly 32 bytes");
static_assert(sizeof(BlockHeader) % 16 == 0, "BlockHeader size must be a multiple of 16");

alignas(16) static u8 g_user_heap[32 * 1024 * 1024]; // 32MB static heap to prevent heap exhaustion
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

    // Align size to 16-byte boundary
    usize aligned_size = (size + 15) & ~15ULL;

    if (!g_heap_initialized) {
        init_heap();
    }

    BlockHeader* current = reinterpret_cast<BlockHeader*>(g_user_heap);
    while (current != nullptr) {
        if (current->is_free && current->size >= aligned_size) {
            // Check if we can split this block
            // We need enough space for the aligned request, a new header, and at least 16 bytes of payload
            if (current->size >= aligned_size + sizeof(BlockHeader) + 16) {
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

void* realloc(void* ptr, usize size) {
    if (!ptr) return malloc(size);
    if (size == 0) {
        free(ptr);
        return nullptr;
    }

    // Align size to 16-byte boundary
    usize aligned_size = (size + 15) & ~15ULL;

    BlockHeader* block = reinterpret_cast<BlockHeader*>(ptr) - 1;
    usize old_size = block->size;
    if (old_size >= aligned_size) {
        return ptr;
    }

    void* new_ptr = malloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, old_size);
        free(ptr);
    }
    return new_ptr;
}

extern "C" void* memset(void* s, int c, acos::usize n);

void* calloc(usize num, usize size) {
    usize total = num * size;
    void* ptr = malloc(total);
    if (ptr) {
        memset(ptr, 0, total);
    }
    return ptr;
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
