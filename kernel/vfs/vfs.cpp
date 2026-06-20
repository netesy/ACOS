#include <kernel/vfs/vfs.h>
#include <kernel/vfs/mount.h>
#include <kernel/vfs/file.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/memory/heap.h>
#include <acos/runtime.h>
#include <kernel/hal/serial.h>

namespace acos::vfs {

i32 VFS::open(const char* path, u64 flags [[maybe_unused]]) {
    if (!path || path[0] == '\0') return -1;
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;
    
    const char* relative_path = path;
    usize mlen = strlen(mp->path);
    if (mlen > 1) {
        relative_path += mlen;
        if (*relative_path == '/') relative_path++;
    }

    Node* node = mp->fs->open(relative_path);
    if (!node) return -1;
    File* file = reinterpret_cast<File*>(memory::kmalloc(sizeof(File)));
    if (!file) return -1;
    new (file) File(node);
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) { memory::kfree(file); return -1; }
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

i32 VFS::read_dir(const char* path, DirectoryEntry* entries, usize max_entries) {
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;

    const char* relative_path = path;
    usize mlen = strlen(mp->path);
    if (mlen > 1) {
        relative_path += mlen;
        if (*relative_path == '/') relative_path++;
    }

    Node* node = mp->fs->open(relative_path);
    if (!node) return -1;
    return node->read_dir(0, entries, max_entries);
}

NodeType VFS::get_node_type(const char* path) {
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return NodeType::File;

    const char* relative_path = path;
    usize mlen = strlen(mp->path);
    if (mlen > 1) {
        relative_path += mlen;
        if (*relative_path == '/') relative_path++;
    }

    Node* node = mp->fs->open(relative_path);
    if (!node) return NodeType::File;
    return node->type();
}

} // namespace acos::vfs
