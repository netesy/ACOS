#include <acos/types.h>

extern "C" {

void* memcpy(void* dest, const void* src, acos::usize n) {
    acos::u8* d = (acos::u8*)dest;
    const acos::u8* s = (const acos::u8*)src;
    while (n--) *d++ = *s++;
    return dest;
}

void* memset(void* s, int c, acos::usize n) {
    acos::u8* p = (acos::u8*)s;
    while (n--) *p++ = (acos::u8)c;
    return s;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

acos::usize strlen(const char* s) {
    acos::usize len = 0;
    while (*s++) len++;
    return len;
}

char* strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++));
    return dest;
}

}
