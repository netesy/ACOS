#pragma once
#include <acos/types.h>

namespace acos::process {

u64 get_pid();
void exit(int status);
void log(const char* msg);
void log(const char* msg, unsigned int len);

} // namespace acos::process

namespace acos::memory {

void* malloc(usize size);
void free(void* ptr);

// Compatibility
inline void* kmalloc(usize size) { return malloc(size); }
inline void kfree(void* ptr) { free(ptr); }

} // namespace acos::memory
