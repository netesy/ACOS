#include <kernel/storage/filesystem_manager.h>
#include <acos/runtime.h>

namespace acos::storage {

FileSystemManager::Entry FileSystemManager::g_filesystems[8];
usize FileSystemManager::g_fs_count = 0;

void FileSystemManager::register_filesystem(const char* name, vfs::FileSystem* fs) {
    if (g_fs_count < 8) {
        usize i = 0;
        while (name[i] && i < 31) {
            g_filesystems[g_fs_count].name[i] = name[i];
            i++;
        }
        g_filesystems[g_fs_count].name[i] = '\0';
        g_filesystems[g_fs_count].fs = fs;
        g_fs_count++;
    }
}

void FileSystemManager::probe_and_mount(BlockDevice* device, const char* path) {
    (void)device; (void)path;
    // Logic to iterate registered filesystems and call mount() if successful probe
}

} // namespace acos::storage
