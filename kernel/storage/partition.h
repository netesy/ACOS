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

    u64 block_count() const override { return m_sector_count; }
    bool is_read_only() const override { return m_parent->is_read_only(); }

private:
    BlockDevice* m_parent;
    u64 m_start_lba;
    u64 m_sector_count;
};

// GPT layout structures
struct GPTHeader {
    u64 signature;              // "EFI PART" (0x5452415020494645ULL)
    u32 revision;
    u32 header_size;
    u32 header_crc;
    u32 reserved;
    u64 current_lba;
    u64 backup_lba;
    u64 first_usable_lba;
    u64 last_usable_lba;
    u8 disk_guid[16];
    u64 partition_entries_lba;
    u32 num_partition_entries;
    u32 partition_entry_size;
    u32 entries_crc;
};

struct GPTPartitionEntry {
    u8 type_guid[16];
    u8 unique_guid[16];
    u64 starting_lba;
    u64 ending_lba;             // Inclusive
    u64 attributes;
    u16 name[36];               // UTF-16 characters
};

class PartitionManager {
public:
    static void enumerate(BlockDevice* device);
};

} // namespace acos::storage
