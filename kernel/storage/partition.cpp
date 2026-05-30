#include <kernel/storage/partition.h>

namespace acos::storage {

Partition::Partition(BlockDevice* parent, u64 start_lba, u64 sector_count)
    : m_parent(parent), m_start_lba(start_lba), m_sector_count(sector_count) {}

i32 Partition::read_block(u64 block_id, void* buffer) {
    if (block_id >= m_sector_count) return -1;
    return m_parent->read_block(m_start_lba + block_id, buffer);
}

i32 Partition::write_block(u64 block_id, const void* buffer) {
    if (block_id >= m_sector_count) return -1;
    return m_parent->write_block(m_start_lba + block_id, buffer);
}

void Partition::flush() {
    m_parent->flush();
}

void PartitionManager::enumerate(BlockDevice* device) {
    (void)device;
    // Logic to read MBR/GPT and register Partition objects
}

} // namespace acos::storage
