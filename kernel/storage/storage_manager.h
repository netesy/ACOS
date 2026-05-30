#pragma once
#include <kernel/storage/block_device.h>

namespace acos::storage {

class StorageManager {
public:
    static void register_device(u64 id, BlockDevice* device);
    static BlockDevice* get_device(u64 id);
    static void init();

private:
    struct Entry {
        u64 id;
        BlockDevice* device;
    };
    static Entry g_devices[16];
    static usize g_device_count;
};

} // namespace acos::storage
