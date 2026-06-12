#pragma once
#include <acos/types.h>

namespace acos::ipc {

struct Message {
    u64 sender;
    u64 receiver;
    u32 type;
    u32 flags;
    u64 size;
    void* payload;
    u64 cap_handle;
};

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

} // namespace acos::ipc

namespace acos::services {

bool register_service(const char* name, u64 channel_handle);
u64 locate_service(const char* name);

} // namespace acos::services
