#include <kernel/vfs/vfs.h>
#include <kernel/vfs/mount.h>
#include <kernel/vfs/file.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/memory/heap.h>
#include <acos/runtime.h>

namespace acos::vfs {

i32 VFS::open(const char* path, u64 flags) {
    (void)flags;
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;

    Inode* inode = nullptr;
    if (!inode) return -1;

    File* file = reinterpret_cast<File*>(memory::kmalloc(sizeof(File)));
    new (file) File(inode);

    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) return -1;
    return current->register_file(file);
}

i32 VFS::close(u64 fd) {
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) return -1;
    File* file = current->get_file(static_cast<i32>(fd));
    if (!file) return -1;

    current->files[fd] = nullptr;
    return 0;
}

i32 VFS::read(u64 fd, void* buffer, usize size) {
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) return -1;
    File* file = current->get_file(static_cast<i32>(fd));
    if (!file) return -1;
    return file->read(buffer, size);
}

i32 VFS::write(u64 fd, const void* buffer, usize size) {
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) return -1;
    File* file = current->get_file(static_cast<i32>(fd));
    if (!file) return -1;
    return file->write(buffer, size);
}

bool VFS::mount(const char* path, FileSystem* fs) {
    return MountRegistry::mount(path, fs);
}

} // namespace acos::vfs
