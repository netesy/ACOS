#pragma once
#include <acos/types.h>
#include <kernel/storage/block_device.h>

namespace acos::storage {

struct PartitionInfo {
    u64 start_lba;
    u64 sector_count;
    u8 type_guid[16];
    char name[36];
};

class Partition : public BlockDevice {
public:
    Partition(BlockDevice* parent, u64 start_lba, u64 sector_count);

    i32 read_block(u64 block_id, void* buffer) override;
    i32 write_block(u64 block_id, const void* buffer) override;
    void flush() override;
    usize block_size() const override { return m_parent->block_size(); }
    u64 capacity() const override { return m_sector_count * block_size(); }

private:
    BlockDevice* m_parent;
    u64 m_start_lba;
    u64 m_sector_count;
};

class PartitionManager {
public:
    static void enumerate(BlockDevice* device);
};

} // namespace acos::storage
