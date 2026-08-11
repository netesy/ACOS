#pragma once
#include <acos/types.h>

namespace acos::process {

u64 get_pid();
void exit(int status);
void log(const char* msg);
void log(const char* msg, unsigned int len);
u64 create_thread(void (*entry)(void*), void* arg);
void start_thread(u64 thread_handle);

} // namespace acos::process

namespace acos::memory {

void* malloc(usize size);
void free(void* ptr);
void* realloc(void* ptr, usize size);
void* calloc(usize num, usize size);

// Compatibility
inline void* kmalloc(usize size) { return malloc(size); }
inline void kfree(void* ptr) { free(ptr); }

} // namespace acos::memory
