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

enum class ResourceKind : u32 {
    None = 0,
    Process,
    Thread,
    Channel,
    Notification,
    SharedRegion,
    GraphicsSurface,
    GraphicsWindow,
    GraphicsDisplay,
    GraphicsBuffer,
    GraphicsContext
};

namespace ResourceRights {
    static constexpr u64 Read = 1ULL << 0;
    static constexpr u64 Write = 1ULL << 1;
    static constexpr u64 Execute = 1ULL << 2;
    static constexpr u64 Map = 1ULL << 3;
    static constexpr u64 Transfer = 1ULL << 4;
    static constexpr u64 Delegate = 1ULL << 5;
    static constexpr u64 Administer = 1ULL << 6;
    static constexpr u64 Signal = 1ULL << 7;
    static constexpr u64 Wait = 1ULL << 8;
}

struct ResourceHandleEntry {
    ResourceKind kind;
    void* object;
    u64 rights;
    u64 owner_process_id;
};

struct Process {
    static constexpr usize MAX_HANDLES = 256;
    static constexpr usize MAX_FILES = 64;
    static constexpr usize MAX_SOCKETS = 32;

    u64 id;
    memory::AddressSpace* address_space;

    acos::ipc::Channel* channels[MAX_HANDLES];
    acos::ipc::SharedRegion* regions[MAX_HANDLES];
    acos::ipc::Notification* notifications[MAX_HANDLES];
    ResourceHandleEntry handles[MAX_HANDLES];

    acos::vfs::File* files[MAX_FILES];
    acos::net::Socket* sockets[MAX_SOCKETS];

    Thread* primary_thread;

    static Process* create();

    u64 register_resource(ResourceKind kind, void* object, u64 rights);
    bool close_handle(u64 handle);
    bool duplicate_handle(u64 handle, u64 rights, u64* out_handle);
    bool transfer_handle(u64 handle, Process& target, u64* out_handle);
    ResourceHandleEntry* get_handle(u64 handle);
    const ResourceHandleEntry* get_handle(u64 handle) const;

    u64 register_process(Process* process, u64 rights);
    u64 register_thread(Thread* thread, u64 rights);
    u64 register_channel(acos::ipc::Channel* chan);
    u64 register_region(acos::ipc::SharedRegion* reg);
    u64 register_notification(acos::ipc::Notification* note);

    i32 register_file(acos::vfs::File* file);
    acos::vfs::File* get_file(i32 fd);

    i32 register_socket(acos::net::Socket* socket);
    acos::net::Socket* get_socket(i32 handle);

    Process* get_process(u64 handle);
    Thread* get_thread(u64 handle);
    acos::ipc::Channel* get_channel(u64 handle);
    acos::ipc::SharedRegion* get_region(u64 handle);
    acos::ipc::Notification* get_notification(u64 handle);
};

Process* process_table_find(u64 process_id);

} // namespace acos::scheduler
