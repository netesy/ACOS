#include <kernel/storage/fat32.h>

namespace acos::storage {

FAT32FileSystem::FAT32FileSystem(BlockDevice* device) : m_device(device) {}

vfs::Node* FAT32FileSystem::open(const char* path) {
    (void)path;
    return nullptr;
}

bool FAT32FileSystem::mount(const char* target) {
    (void)target;
    // Logic to read BPB and verify FAT32 signature
    return true;
}

} // namespace acos::storage
