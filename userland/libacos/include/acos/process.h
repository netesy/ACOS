#pragma once
#include <acos/types.h>

namespace acos::process {

class Thread {
public:
    Thread(void (*entry)(void*), void* arg);
    void start();
    void join();
    void terminate();
    u64 handle() const { return m_handle; }
private:
    u64 m_handle;
};

class Process {
public:
    Process(const char* path);
    void start();
    void terminate();
    u64 handle() const { return m_handle; }
private:
    u64 m_handle;
};

u64 get_pid();
void exit(int status);
void log(const char* msg);
void log(const char* msg, unsigned int len);
u64 create_thread(void (*entry)(void*), void* arg);
void start_thread(u64 thread_handle);

void sleep(u64 ms);
void yield();
int args_count();
const char* get_arg(int index);

} // namespace acos::process

namespace acos::memory {

void* malloc(usize size);
void free(void* ptr);

// Compatibility
inline void* kmalloc(usize size) { return malloc(size); }
inline void kfree(void* ptr) { free(ptr); }

} // namespace acos::memory
