#pragma once
#include <acos/types.h>

extern "C" void* memcpy(void* dest, const void* src, acos::usize n);
extern "C" void* memset(void* s, int c, acos::usize n);
extern "C" void __cxa_pure_virtual();

void operator delete(void* ptr) noexcept;
void operator delete(void* ptr, acos::usize size) noexcept;

#ifndef __GLIBCXX__
inline void* operator new(acos::usize, void* p) noexcept { return p; }
#endif
