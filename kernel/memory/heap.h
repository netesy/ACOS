#pragma once
#include <acos/types.h>

namespace acos::memory {
    void* kmalloc(usize size);
    void kfree(void* ptr);
}
