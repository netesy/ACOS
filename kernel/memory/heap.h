#pragma once
#include <acos/types.h>

namespace acos::memory {
    void* kmalloc(usize size);
    void kfree(void* ptr);

    // Phase 2 Additions
    bool heap_validate();
    void heap_print_stats();
    void heap_get_stats(usize* total_size, usize* allocated, usize* free_bytes, usize* alloc_count, usize* free_count);
}
