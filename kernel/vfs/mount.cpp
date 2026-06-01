#include <kernel/vfs/mount.h>
#include <acos/runtime.h>

namespace acos::vfs {

// Helper function for string length
static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s[len]) len++;
    return len;
}

MountPoint MountRegistry::g_mounts[16];
usize MountRegistry::g_mount_count = 0;

bool MountRegistry::mount(const char* path, FileSystem* fs) {
    if (g_mount_count >= 16) return false;

    MountPoint& mp = g_mounts[g_mount_count++];
    mp.fs = fs;

    usize i = 0;
    while (path[i] && i < 255) {
        mp.path[i] = path[i];
        i++;
    }
    mp.path[i] = '\0';

    return true;
}

MountPoint* MountRegistry::find_mount(const char* path) {
    if (!path) return nullptr;
    
    // Find the mount point that matches the longest prefix of the path
    // This allows nested mount points (e.g., /mnt/usb mounted under /mnt)
    
    MountPoint* best_match = nullptr;
    usize best_match_len = 0;
    
    for (usize i = 0; i < g_mount_count; i++) {
        const char* mount_path = g_mounts[i].path;
        usize mount_len = strlen_impl(mount_path);
        
        // Check if path starts with this mount point
        bool matches = true;
        for (usize j = 0; j < mount_len; j++) {
            if (path[j] != mount_path[j]) {
                matches = false;
                break;
            }
        }
        
        if (!matches) continue;
        
        // Check that the match is at a path boundary
        // (either end of string or followed by '/')
        if (path[mount_len] != '\0' && path[mount_len] != '/') {
            continue;
        }
        
        // This mount point matches, and it's longer than previous matches
        if (mount_len > best_match_len) {
            best_match = &g_mounts[i];
            best_match_len = mount_len;
        }
    }
    
    return best_match;
}

} // namespace acos::vfs
