#pragma once
#include <acos/types.h>

namespace acos::process {

u64 get_pid();
void exit(int status);
void log(const char* msg);
void log(const char* msg, unsigned int len);

} // namespace acos::process

namespace acos::memory {

void* kmalloc(usize size);
void kfree(void* ptr);

} // namespace acos::memory
