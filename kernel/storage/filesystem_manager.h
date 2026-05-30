#pragma once
#include <acos/types.h>
#include <kernel/vfs/vfs.h>
#include <kernel/storage/block_device.h>

namespace acos::storage {

class FileSystemManager {
public:
    static void register_filesystem(const char* name, vfs::FileSystem* fs);
    static void probe_and_mount(BlockDevice* device, const char* path);

private:
    struct Entry {
        char name[32];
        vfs::FileSystem* fs;
    };
    static Entry g_filesystems[8];
    static usize g_fs_count;
};

} // namespace acos::storage
