#pragma once
#include <acos/types.h>

extern "C" void* memcpy(void* dest, const void* src, acos::usize n);
extern "C" void* memset(void* s, int c, acos::usize n);
extern "C" int strcmp(const char* s1, const char* s2);
extern "C" void __cxa_pure_virtual();

void operator delete(void* ptr) noexcept;
void operator delete(void* ptr, acos::usize size) noexcept;
void* operator new[](acos::usize size);
void operator delete[](void* ptr) noexcept;

#ifndef __GLIBCXX__
inline void* operator new(acos::usize, void* p) noexcept { return p; }
#endif
