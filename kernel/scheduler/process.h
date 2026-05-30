#pragma once
#include <acos/types.h>
#include <kernel/scheduler/thread.h>
#include <kernel/ipc/channel.h>
#include <kernel/ipc/shared_memory.h>
#include <kernel/ipc/notification.h>
#include <kernel/memory/address_space.h>

namespace acos::vfs { class File; }
namespace acos::net { class Socket; }

namespace acos::scheduler {

struct Process {
    static constexpr usize MAX_HANDLES = 256;
    static constexpr usize MAX_FILES = 64;
    static constexpr usize MAX_SOCKETS = 32;

    u64 id;
    memory::AddressSpace* address_space;

    acos::ipc::Channel* channels[MAX_HANDLES];
    acos::ipc::SharedRegion* regions[MAX_HANDLES];
    acos::ipc::Notification* notifications[MAX_HANDLES];

    acos::vfs::File* files[MAX_FILES];
    acos::net::Socket* sockets[MAX_SOCKETS];

    static Process* create();

    u64 register_channel(acos::ipc::Channel* chan);
    u64 register_region(acos::ipc::SharedRegion* reg);
    u64 register_notification(acos::ipc::Notification* note);

    i32 register_file(acos::vfs::File* file);
    acos::vfs::File* get_file(i32 fd);

    i32 register_socket(acos::net::Socket* socket);
    acos::net::Socket* get_socket(i32 handle);

    acos::ipc::Channel* get_channel(u64 handle);
    acos::ipc::SharedRegion* get_region(u64 handle);
    acos::ipc::Notification* get_notification(u64 handle);
};

} // namespace acos::scheduler
