#include <libs/runtime/include/acos/runtime.h>

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

extern "C" void __cxa_pure_virtual() {
    while (1) {
        __asm__("hlt");
    }
}

void operator delete(void* ptr) noexcept {
    (void)ptr;
}

void operator delete(void* ptr, acos::usize size) noexcept {
    (void)ptr; (void)size;
}
