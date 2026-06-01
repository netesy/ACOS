#include <kernel/vfs/vfs.h>
#include <kernel/vfs/mount.h>
#include <kernel/vfs/file.h>
#include <kernel/scheduler/scheduler.h>
#include <kernel/scheduler/process.h>
#include <kernel/memory/heap.h>
#include <acos/runtime.h>

namespace acos::vfs {

i32 VFS::open(const char* path, u64 flags [[maybe_unused]]) {
    if (!path || path[0] == '\0') return -1;
    
    // Validate path - prevent directory traversal attacks
    const char* p = path;
    while (*p) {
        // Check for null bytes
        if (*p == '\0') break;
        
        // Check for excessive path depth
        if (p - path > 4096) return -1;
        
        p++;
    }
    
    // Find appropriate mount point
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;
    
    // Open file through filesystem
    vfs::Node* node = mp->fs->open(path);
    if (!node) return -1;
    
    // Create file descriptor
    File* file = reinterpret_cast<File*>(memory::kmalloc(sizeof(File)));
    if (!file) return -1;
    
    // For now, pass nullptr as we don't have a proper Inode yet
    // TODO: Convert Node to Inode or create wrapper
    new (file) File(nullptr);
    
    // Register with process
    scheduler::Process* current = scheduler::current_thread()->parent;
    if (!current) {
        memory::kfree(file);
        return -1;
    }
    
    i32 fd = current->register_file(file);
    if (fd < 0) {
        memory::kfree(file);
        return -1;
    }
    
    return fd;
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
    if (!path || !entries || max_entries == 0) return -1;
    
    // Find appropriate mount point
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return -1;
    
    // Open directory through filesystem
    vfs::Node* node = mp->fs->open(path);
    if (!node) return -1;
    
    // Check if it's a directory
    if (node->type() != NodeType::Directory) {
        return -1;
    }
    
    // Read directory entries
    i32 count = node->read_dir(0, entries, max_entries);
    
    return count;
}

NodeType VFS::get_node_type(const char* path) {
    if (!path) return NodeType::File;
    
    // Find appropriate mount point
    MountPoint* mp = MountRegistry::find_mount(path);
    if (!mp || !mp->fs) return NodeType::File;
    
    // Open node through filesystem
    vfs::Node* node = mp->fs->open(path);
    if (!node) return NodeType::File;
    
    return node->type();
}

} // namespace acos::vfs
