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
    if (!device || !path) return;
    
    // Try each registered filesystem
    for (usize i = 0; i < g_fs_count; i++) {
        vfs::FileSystem* fs = g_filesystems[i].fs;
        if (!fs) continue;
        
        // Try to mount with this filesystem
        if (fs->mount(path)) {
            // Successfully mounted
            acos::hal::console_print("Mounted ");
            acos::hal::console_print(g_filesystems[i].name);
            acos::hal::console_print(" at ");
            acos::hal::console_print(path);
            acos::hal::console_print("\n");
            return;
        }
    }
    
    // No filesystem could mount this device
    acos::hal::console_print("Failed to mount device at ");
    acos::hal::console_print(path);
    acos::hal::console_print("\n");
}

} // namespace acos::storage
