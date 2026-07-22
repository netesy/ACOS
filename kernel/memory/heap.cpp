#include <acos/types.h>
#include <kernel/memory/pmm.h>
#include <kernel/hal/serial.h>

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
    // Allocate 16 extra bytes for storing page count
    const u64 pages = (aligned_size + 16 + PAGE_SIZE - 1) / PAGE_SIZE;
    const u64 addr = pmm_alloc_contiguous(pages);
    if (!addr) return nullptr;

    *reinterpret_cast<u64*>(addr) = pages;

    void* ptr = reinterpret_cast<void*>(addr + 16);
    // acos::hal::serial_print("  Heap: kmalloc size=");
    // acos::hal::serial_print_hex(size);
    // acos::hal::serial_print(" pages=");
    // acos::hal::serial_print_hex(pages);
    // acos::hal::serial_print(" ptr=");
    // acos::hal::serial_print_hex(reinterpret_cast<u64>(ptr));
    // acos::hal::serial_print("\n");

    return ptr;
}

void kfree(void* ptr) {
    if (!ptr) return;
    u64 addr = reinterpret_cast<u64>(ptr) - 16;
    u64 pages = *reinterpret_cast<u64*>(addr);

    // acos::hal::serial_print("  Heap: kfree ptr=");
    // acos::hal::serial_print_hex(reinterpret_cast<u64>(ptr));
    // acos::hal::serial_print(" pages=");
    // acos::hal::serial_print_hex(pages);
    // acos::hal::serial_print("\n");

    for (u64 i = 0; i < pages; ++i) {
        pmm_free(addr + (i * PAGE_SIZE));
    }
}

} // namespace acos::memory
