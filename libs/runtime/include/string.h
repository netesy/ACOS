#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* s, int c, size_t n);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
size_t strlen(const char* s);

static inline int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;
    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }
    return 0;
}

#ifdef __cplusplus
}
#endif
