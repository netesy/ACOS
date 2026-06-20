#include <kernel/vfs/mount.h>
#include <acos/runtime.h>
#include <kernel/hal/serial.h>

namespace acos::vfs {

static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s[len]) len++;
    return len;
}

MountPoint MountRegistry::g_mounts[16];
usize MountRegistry::g_mount_count = 0;

bool MountRegistry::mount(const char* path, FileSystem* fs) {
    if (g_mount_count >= 16) return false;
    for (usize i = 0; i < g_mount_count; i++) {
        if (strcmp(g_mounts[i].path, path) == 0) return false;
    }
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
    MountPoint* best_match = nullptr;
    usize best_match_len = 0;
    int root_idx = -1;

    for (usize i = 0; i < g_mount_count; i++) {
        const char* mpath = g_mounts[i].path;
        usize mlen = strlen_impl(mpath);
        
        if (mlen == 1 && mpath[0] == '/') {
            root_idx = (int)i;
            continue;
        }

        bool match = true;
        for (usize j = 0; j < mlen; j++) {
            if (path[j] != mpath[j]) { match = false; break; }
        }
        if (!match) continue;
        if (path[mlen] != '\0' && path[mlen] != '/') continue;

        if (mlen > best_match_len) {
            best_match = &g_mounts[i];
            best_match_len = mlen;
        }
    }
    if (best_match) return best_match;
    if (root_idx != -1) return &g_mounts[root_idx];
    return nullptr;
}

} // namespace acos::vfs
