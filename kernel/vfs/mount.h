#pragma once
#include <acos/types.h>
#include <kernel/vfs/vfs.h>

namespace acos::vfs {

struct MountPoint {
    char path[256];
    FileSystem* fs;
    Dentry* root;
};

class MountRegistry {
public:
    static bool mount(const char* path, FileSystem* fs);
    static MountPoint* find_mount(const char* path);

private:
    static MountPoint g_mounts[16];
    static usize g_mount_count;
};

} // namespace acos::vfs
