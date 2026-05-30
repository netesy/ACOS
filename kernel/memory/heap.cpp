#include <acos/types.h>
#include <kernel/memory/pmm.h>
#include <kernel/hal/spinlock.h>

namespace acos::memory {

static hal::SpinLock g_heap_lock;
static u64 g_heap_end = 0x10000000;

void* kmalloc(usize size) {
    hal::ScopedLock lock(g_heap_lock);

    u64 addr = g_heap_end;
    g_heap_end += (size + 15) & ~15ULL;

    return reinterpret_cast<void*>(addr);
}

void kfree(void* ptr) {
    (void)ptr;
}

} // namespace acos::memory
