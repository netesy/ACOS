#include <kernel/scheduler/process.h>
#include <kernel/memory/heap.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/vfs/file.h>
#include <kernel/net/socket.h>

namespace acos::scheduler {

static u64 g_next_process_id = 1;
static Process* g_process_table[256];
static usize g_process_count = 0;

Process* Process::create() {
    Process* p = reinterpret_cast<Process*>(acos::memory::kmalloc(sizeof(Process)));
    if (!p) return nullptr;

    p->id = g_next_process_id++;
    p->address_space = reinterpret_cast<memory::AddressSpace*>(acos::memory::kmalloc(sizeof(memory::AddressSpace)));
    new (p->address_space) memory::AddressSpace();

    for (usize i = 0; i < MAX_HANDLES; i++) {
        p->channels[i] = nullptr;
        p->regions[i] = nullptr;
        p->notifications[i] = nullptr;
        p->handles[i] = {ResourceKind::None, nullptr, 0, p->id};
    }

    for (usize i = 0; i < MAX_FILES; i++) {
        p->files[i] = nullptr;
    }

    for (usize i = 0; i < MAX_SOCKETS; i++) {
        p->sockets[i] = nullptr;
    }

    if (g_process_count < 256) {
        g_process_table[g_process_count++] = p;
    }

    return p;
}


u64 Process::register_resource(ResourceKind kind, void* object, u64 rights) {
    if (kind == ResourceKind::None || !object) {
        return 0;
    }
    for (usize i = 1; i < MAX_HANDLES; ++i) {
        if (handles[i].kind == ResourceKind::None) {
            handles[i] = {kind, object, rights, id};
            return i;
        }
    }
    return 0;
}

bool Process::close_handle(u64 handle) {
    if (handle == 0 || handle >= MAX_HANDLES || handles[handle].kind == ResourceKind::None) {
        return false;
    }
    handles[handle] = {ResourceKind::None, nullptr, 0, id};
    channels[handle] = nullptr;
    regions[handle] = nullptr;
    notifications[handle] = nullptr;
    return true;
}

bool Process::duplicate_handle(u64 handle, u64 rights, u64* out_handle) {
    ResourceHandleEntry* source = get_handle(handle);
    if (!source || !out_handle || (rights & ~source->rights) != 0 || (source->rights & ResourceRights::Delegate) == 0) {
        return false;
    }
    const u64 duplicate = register_resource(source->kind, source->object, rights);
    if (!duplicate) {
        return false;
    }
    *out_handle = duplicate;
    return true;
}

bool Process::transfer_handle(u64 handle, Process& target, u64* out_handle) {
    ResourceHandleEntry* source = get_handle(handle);
    if (!source || !out_handle || (source->rights & ResourceRights::Transfer) == 0) {
        return false;
    }
    const u64 transferred = target.register_resource(source->kind, source->object, source->rights);
    if (!transferred) {
        return false;
    }
    close_handle(handle);
    *out_handle = transferred;
    return true;
}

ResourceHandleEntry* Process::get_handle(u64 handle) {
    if (handle == 0 || handle >= MAX_HANDLES || handles[handle].kind == ResourceKind::None) {
        return nullptr;
    }
    return &handles[handle];
}

const ResourceHandleEntry* Process::get_handle(u64 handle) const {
    if (handle == 0 || handle >= MAX_HANDLES || handles[handle].kind == ResourceKind::None) {
        return nullptr;
    }
    return &handles[handle];
}

u64 Process::register_process(Process* process, u64 rights) {
    return register_resource(ResourceKind::Process, process, rights);
}

u64 Process::register_thread(Thread* thread, u64 rights) {
    return register_resource(ResourceKind::Thread, thread, rights);
}

i32 Process::register_file(acos::vfs::File* file) {
    for (usize i = 0; i < MAX_FILES; i++) {
        if (!files[i]) {
            files[i] = file;
            return static_cast<i32>(i);
        }
    }
    return -1;
}

acos::vfs::File* Process::get_file(i32 fd) {
    if (fd < 0 || static_cast<usize>(fd) >= MAX_FILES) return nullptr;
    return files[fd];
}

i32 Process::register_socket(acos::net::Socket* socket) {
    for (usize i = 0; i < MAX_SOCKETS; i++) {
        if (!sockets[i]) {
            sockets[i] = socket;
            return static_cast<i32>(i);
        }
    }
    return -1;
}

acos::net::Socket* Process::get_socket(i32 handle) {
    if (handle < 0 || static_cast<usize>(handle) >= MAX_SOCKETS) return nullptr;
    return sockets[handle];
}

u64 Process::register_channel(acos::ipc::Channel* chan) {
    const u64 handle = register_resource(ResourceKind::Channel, chan, ResourceRights::Read | ResourceRights::Write | ResourceRights::Transfer | ResourceRights::Delegate);
    if (handle) {
        channels[handle] = chan;
    }
    return handle;
}

Process* Process::get_process(u64 handle) {
    ResourceHandleEntry* entry = get_handle(handle);
    if (!entry || entry->kind != ResourceKind::Process) return nullptr;
    return static_cast<Process*>(entry->object);
}

Thread* Process::get_thread(u64 handle) {
    ResourceHandleEntry* entry = get_handle(handle);
    if (!entry || entry->kind != ResourceKind::Thread) return nullptr;
    return static_cast<Thread*>(entry->object);
}

acos::ipc::Channel* Process::get_channel(u64 handle) {
    ResourceHandleEntry* entry = get_handle(handle);
    if (!entry || entry->kind != ResourceKind::Channel || (entry->rights & ResourceRights::Read) == 0) return nullptr;
    return static_cast<acos::ipc::Channel*>(entry->object);
}

u64 Process::register_region(acos::ipc::SharedRegion* reg) {
    const u64 handle = register_resource(ResourceKind::SharedRegion, reg, ResourceRights::Read | ResourceRights::Write | ResourceRights::Map | ResourceRights::Transfer | ResourceRights::Delegate);
    if (handle) {
        regions[handle] = reg;
    }
    return handle;
}

acos::ipc::SharedRegion* Process::get_region(u64 handle) {
    ResourceHandleEntry* entry = get_handle(handle);
    if (!entry || entry->kind != ResourceKind::SharedRegion) return nullptr;
    return static_cast<acos::ipc::SharedRegion*>(entry->object);
}

u64 Process::register_notification(acos::ipc::Notification* note) {
    const u64 handle = register_resource(ResourceKind::Notification, note, ResourceRights::Signal | ResourceRights::Wait | ResourceRights::Transfer | ResourceRights::Delegate);
    if (handle) {
        notifications[handle] = note;
    }
    return handle;
}

acos::ipc::Notification* Process::get_notification(u64 handle) {
    ResourceHandleEntry* entry = get_handle(handle);
    if (!entry || entry->kind != ResourceKind::Notification) return nullptr;
    return static_cast<acos::ipc::Notification*>(entry->object);
}


Process* process_table_find(u64 process_id) {
    for (usize i = 0; i < g_process_count; ++i) {
        if (g_process_table[i] && g_process_table[i]->id == process_id) {
            return g_process_table[i];
        }
    }
    return nullptr;
}

} // namespace acos::scheduler
