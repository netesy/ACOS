#include <kernel/memory/heap.h>
#include <acos/types.h>

extern "C" {

void* malloc(acos::usize size) {
    return acos::memory::kmalloc(size);
}

void free(void* ptr) {
    acos::memory::kfree(ptr);
}

void* calloc(acos::usize nmemb, acos::usize size) {
    acos::usize total = nmemb * size;
    void* p = malloc(total);
    if (p) {
        acos::u8* q = (acos::u8*)p;
        for (acos::usize i = 0; i < total; i++) q[i] = 0;
    }
    return p;
}

}

void operator delete(void* ptr) noexcept {
    acos::memory::kfree(ptr);
}

void operator delete(void* ptr, acos::usize size) noexcept {
    (void)size;
    acos::memory::kfree(ptr);
}

void* operator new(acos::usize size) {
    return acos::memory::kmalloc(size);
}

void* operator new[](acos::usize size) {
    return acos::memory::kmalloc(size);
}

void operator delete[](void* ptr) noexcept {
    acos::memory::kfree(ptr);
}

void operator delete[](void* ptr, acos::usize size) noexcept {
    (void)size;
    acos::memory::kfree(ptr);
}
