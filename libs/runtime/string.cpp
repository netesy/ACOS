#include <libs/runtime/include/acos/runtime.h>
#include <kernel/memory/heap.h>

extern "C" void* memcpy(void* dest, const void* src, acos::usize n) {
    acos::u8* d = reinterpret_cast<acos::u8*>(dest);
    const acos::u8* s = reinterpret_cast<const acos::u8*>(src);
    for (acos::usize i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

extern "C" void* memset(void* s, int c, acos::usize n) {
    acos::u8* p = reinterpret_cast<acos::u8*>(s);
    for (acos::usize i = 0; i < n; i++) {
        p[i] = static_cast<acos::u8>(c);
    }
    return s;
}

extern "C" int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

extern "C" acos::usize strlen(const char* s) {
    acos::usize len = 0;
    while (s[len]) len++;
    return len;
}

extern "C" void __cxa_pure_virtual() {
    while (1) {
        __asm__("hlt");
    }
}

void* operator new(acos::usize size) {
    // Use kernel heap allocator
    void* ptr = acos::memory::kmalloc(size);
    if (!ptr) {
        // Allocation failed - halt in freestanding environment
        while (1) {
            __asm__("hlt");
        }
    }
    return ptr;
}

void operator delete(void* ptr) noexcept {
    if (ptr) {
        acos::memory::kfree(ptr);
    }
}

void* operator new[](acos::usize size) {
    return operator new(size);
}

void operator delete[](void* ptr) noexcept {
    operator delete(ptr);
}

void operator delete(void* ptr, acos::usize size) noexcept {
    (void)size;
    if (ptr) {
        acos::memory::kfree(ptr);
    }
}
