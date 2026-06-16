#include <kernel/storage/partition.h>
#include <kernel/storage/storage_manager.h>
#include <kernel/storage/filesystem_manager.h>

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
    if (!device) return;
    
    u8 sector[512];
    if (device->read_block(0, sector) != 0) return;
    
    // Check for MBR signature
    if (sector[510] != 0x55 || sector[511] != 0xAA) return;
    
    // Parse MBR partition table
    for (int i = 0; i < 4; i++) {
        u8* entry = sector + 446 + (i * 16);
        
        u8 status [[maybe_unused]] = entry[0];
        u8 type = entry[4];
        
        if (type == 0) continue; // Empty partition
        
        u32 start_lba = *(u32*)(entry + 8);
        u32 sector_count = *(u32*)(entry + 12);
        
        // Create partition object
        Partition* part = new Partition(device, start_lba, sector_count);
        if (part) {
            // Register partition
            StorageManager::register_device(0x100 + i, part);
            // Try to mount root if not already mounted
            FileSystemManager::probe_and_mount(part, "/");
        }
    }
}

} // namespace acos::storage
