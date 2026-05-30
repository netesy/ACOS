#include <kernel/scheduler/process.h>
#include <kernel/memory/heap.h>
#include <libs/runtime/include/acos/runtime.h>
#include <kernel/vfs/file.h>

namespace acos::scheduler {

static u64 g_next_process_id = 1;

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
    }

    for (usize i = 0; i < MAX_FILES; i++) {
        p->files[i] = nullptr;
    }

    return p;
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

u64 Process::register_channel(acos::ipc::Channel* chan) {
    for (usize i = 1; i < MAX_HANDLES; i++) {
        if (!channels[i]) {
            channels[i] = chan;
            return i;
        }
    }
    return 0;
}

acos::ipc::Channel* Process::get_channel(u64 handle) {
    if (handle >= MAX_HANDLES) return nullptr;
    return channels[handle];
}

u64 Process::register_region(acos::ipc::SharedRegion* reg) {
    for (usize i = 1; i < MAX_HANDLES; i++) {
        if (!regions[i]) {
            regions[i] = reg;
            return i;
        }
    }
    return 0;
}

acos::ipc::SharedRegion* Process::get_region(u64 handle) {
    if (handle >= MAX_HANDLES) return nullptr;
    return regions[handle];
}

u64 Process::register_notification(acos::ipc::Notification* note) {
    for (usize i = 1; i < MAX_HANDLES; i++) {
        if (!notifications[i]) {
            notifications[i] = note;
            return i;
        }
    }
    return 0;
}

acos::ipc::Notification* Process::get_notification(u64 handle) {
    if (handle >= MAX_HANDLES) return nullptr;
    return notifications[handle];
}

} // namespace acos::scheduler
