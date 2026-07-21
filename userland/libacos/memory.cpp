#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::memory {

static u8 g_user_heap[32 * 1024 * 1024]; // 32MB static heap to prevent heap exhaustion
static usize g_heap_offset = 0;

void* malloc(usize size) {
    if (g_heap_offset + size > sizeof(g_user_heap)) {
        acos::process::log("Userland malloc Error: Heap exhausted!\n");
        return nullptr;
    }
    void* ptr = &g_user_heap[g_heap_offset];
    g_heap_offset += (size + 7) & ~7; // 8-byte alignment
    return ptr;
}

void free(void* ptr [[maybe_unused]]) {
    // No-op for this simple allocator
}

} // namespace acos::memory
