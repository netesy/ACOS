#include <acos/process.h>
#include <acos/runtime.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::memory {

static u8 g_user_heap[1024 * 1024]; // 1MB static heap for now
static usize g_heap_offset = 0;

void* kmalloc(usize size) {
    if (g_heap_offset + size > sizeof(g_user_heap)) return nullptr;
    void* ptr = &g_user_heap[g_heap_offset];
    g_heap_offset += (size + 7) & ~7; // 8-byte alignment
    return ptr;
}

void kfree(void* ptr [[maybe_unused]]) {
    // No-op for this simple allocator
}

} // namespace acos::memory
