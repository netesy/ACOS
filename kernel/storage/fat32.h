#pragma once
#include <kernel/vfs/vfs.h>
#include <kernel/storage/block_device.h>

namespace acos::storage {

class FAT32FileSystem : public vfs::FileSystem {
public:
    FAT32FileSystem(BlockDevice* device);

    vfs::Node* open(const char* path) override;
    bool mount(const char* target) override;

private:
    BlockDevice* m_device;
};

} // namespace acos::storage
