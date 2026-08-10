#pragma once
#include <stddef.h>

#ifdef __cplusplus
namespace acos::memory {
    void* malloc(size_t size);
    void free(void* ptr);
    void* realloc(void* ptr, size_t size);
}

extern "C" {
static inline void* malloc(size_t size) { return acos::memory::malloc(size); }
static inline void free(void* ptr) { acos::memory::free(ptr); }
static inline void* realloc(void* ptr, size_t size) { return acos::memory::realloc(ptr, size); }
static inline void* calloc(size_t num, size_t size) {
    size_t total = num * size;
    void* ptr = acos::memory::malloc(total);
    if (ptr) {
        extern void* memset(void* s, int c, size_t n);
        memset(ptr, 0, total);
    }
    return ptr;
}
}
#else
void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
void* calloc(size_t num, size_t size);
#endif
