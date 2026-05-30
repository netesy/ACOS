#include <kernel/vfs/mount.h>
#include <acos/runtime.h>

namespace acos::vfs {

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
    (void)path;
    // Simple matching for now
    if (g_mount_count > 0) return &g_mounts[0];
    return nullptr;
}

} // namespace acos::vfs
