#include <kernel/storage/filesystem_manager.h>
#include <acos/runtime.h>
#include <kernel/hal/console.h>
#include <kernel/hal/serial.h>

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
    
    for (usize i = 0; i < g_fs_count; i++) {
        vfs::FileSystem* fs = g_filesystems[i].fs;
        if (!fs) continue;
        
        if (fs->probe(device, path)) {
            hal::serial_print("FileSystem: Mounted ");
            hal::serial_print(g_filesystems[i].name);
            hal::serial_print(" at ");
            hal::serial_print(path);
            hal::serial_print("\n");
            return;
        }
    }
    
    hal::serial_print("FileSystem: Failed to mount device at ");
    hal::serial_print(path);
    hal::serial_print("\n");
}

} // namespace acos::storage
