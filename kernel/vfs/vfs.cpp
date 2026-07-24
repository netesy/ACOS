#include <kernel/hal/serial.h>
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
    acos::hal::serial_print("  VFS: open called for ");
    acos::hal::serial_print(path ? path : "null");
    acos::hal::serial_print("\n");
    if (!path || path[0] == '\0') return -1;
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) {
        acos::hal::serial_print("  VFS: find_mount failed\n");
        return -1;
    }
    
    const char* relative_path = path;
    usize mlen = strlen(mp->path);
    if (mlen > 1) {
        relative_path += mlen;
        if (*relative_path == '/') relative_path++;
    }
    acos::hal::serial_print("  VFS: relative_path: ");
    acos::hal::serial_print(relative_path);
    acos::hal::serial_print("\n");

    Node* node = mp->fs->open(relative_path, flags);
    if (!node) {
        acos::hal::serial_print("  VFS: fs->open failed\n");
        return -1;
    }
    File* file = reinterpret_cast<File*>(memory::kmalloc(sizeof(File)));
    if (!file) return -1;
    new (file) File(node);
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) { memory::kfree(file); return -1; }
    i32 fd = current->register_file(file);
    acos::hal::serial_print("  VFS: register_file fd=");
    acos::hal::serial_print_hex(fd);
    acos::hal::serial_print("\n");
    return fd;
}

i32 VFS::close(u64 fd) {
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) return -1;
    File* file = current->get_file(static_cast<i32>(fd));
    if (!file) return -1;
    current->files[fd] = nullptr;
    file->~File();
    memory::kfree(file);
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

i32 VFS::dup2(u64 old_fd, u64 new_fd) {
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) return -1;
    File* file = current->get_file(static_cast<i32>(old_fd));
    if (!file) return -1;
    if (new_fd >= scheduler::Process::MAX_FILES) return -1;

    if (current->files[new_fd]) {
        VFS::close(new_fd);
    }

    Node* node = file->node();
    node->add_ref();

    File* new_file = reinterpret_cast<File*>(memory::kmalloc(sizeof(File)));
    if (!new_file) {
        node->close_node();
        return -1;
    }
    new (new_file) File(node);
    current->files[new_fd] = new_file;
    return static_cast<i32>(new_fd);
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

i32 VFS::mkdir(const char* path, u64 mode [[maybe_unused]]) {
    if (!path || path[0] == '\0') return -1;
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;

    const char* relative_path = path;
    usize mlen = strlen(mp->path);
    if (mlen > 1) {
        relative_path += mlen;
        if (*relative_path == '/') relative_path++;
    }
    return mp->fs->mkdir(relative_path) ? 0 : -1;
}

i32 VFS::unlink(const char* path) {
    if (!path || path[0] == '\0') return -1;
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;

    const char* relative_path = path;
    usize mlen = strlen(mp->path);
    if (mlen > 1) {
        relative_path += mlen;
        if (*relative_path == '/') relative_path++;
    }
    return mp->fs->unlink(relative_path) ? 0 : -1;
}

i32 VFS::rmdir(const char* path) {
    if (!path || path[0] == '\0') return -1;
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;

    const char* relative_path = path;
    usize mlen = strlen(mp->path);
    if (mlen > 1) {
        relative_path += mlen;
        if (*relative_path == '/') relative_path++;
    }
    return mp->fs->rmdir(relative_path) ? 0 : -1;
}

} // namespace acos::vfs
