#include <kernel/storage/storage_manager.h>
#include <kernel/storage/partition.h>
#include <kernel/storage/filesystem_manager.h>

namespace acos::storage {

StorageManager::Entry StorageManager::g_devices[16];
usize StorageManager::g_device_count = 0;

void StorageManager::register_device(u64 id, BlockDevice* device) {
    if (g_device_count < 16) {
        g_devices[g_device_count++] = {id, device};
        // Trigger partition discovery
        PartitionManager::enumerate(device);
    }
}

BlockDevice* StorageManager::get_device(u64 id) {
    for (usize i = 0; i < g_device_count; i++) {
        if (g_devices[i].id == id) return g_devices[i].device;
    }
    return nullptr;
}

void StorageManager::init() {
    // Discovery logic would trigger here
}

} // namespace acos::storage
