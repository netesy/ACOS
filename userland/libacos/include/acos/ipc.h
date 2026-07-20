#pragma once
#include <acos/types.h>
#include <acos/abi/ipc.h>

namespace acos::ipc {

using Message = abi::Message;

class Channel {
public:
    Channel();
    bool send(const Message& msg);
    bool receive(Message& msg, bool block = true);
    u64 handle() const { return m_handle; }
private:
    u64 m_handle;
};

u64 channel_create();
bool channel_send(u64 handle, const void* data, usize size);
bool channel_receive(u64 handle, void* data, usize size);

class Notification {
public:
    Notification();
    ~Notification();

    void signal();
    void wait();
    u64 handle() const { return m_handle; }
private:
    u64 m_handle;
};

class SharedMemory {
public:
    SharedMemory(usize size);
    ~SharedMemory();

    void* map(u64 flags = 0);
    void unmap();
    u64 handle() const { return m_handle; }
private:
    u64 m_handle;
    void* m_ptr;
    usize m_size;
};

} // namespace acos::ipc

namespace acos::services {

bool register_service(const char* name, u64 channel_handle);
u64 locate_service(const char* name);

struct ResourceLocator {
    static u64 find(const char* name) {
        return locate_service(name);
    }
};

} // namespace acos::services
