#include <acos/types.h>
#include <kernel/memory/pmm.h>

namespace acos::memory {

namespace {

constexpr usize PAGE_SIZE = 4096;

usize align_up(usize value, usize alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

} // namespace

void* kmalloc(usize size) {
    if (size == 0) return nullptr;

    const usize aligned_size = align_up(size, 16);
    const u64 pages = (aligned_size + PAGE_SIZE - 1) / PAGE_SIZE;
    const u64 addr = pmm_alloc_contiguous(pages);
    return addr ? reinterpret_cast<void*>(addr) : nullptr;
}

void kfree(void* ptr) {
    (void)ptr;
}

} // namespace acos::memory
