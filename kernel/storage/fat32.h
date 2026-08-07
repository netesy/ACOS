#pragma once
#include <kernel/vfs/vfs.h>
#include <kernel/storage/block_device.h>

namespace acos::storage {

class FAT32FileSystem : public vfs::FileSystem {
public:
    FAT32FileSystem() : m_device(nullptr) {}
    FAT32FileSystem(BlockDevice* device);

    vfs::Node* open(const char* path) override;
    bool mount(const char* target) override;
    bool probe(void* device, const char* target) override;

    bool write_fat_entry(u32 cluster, u32 value);

    vfs::Node* open_internal(u32 cluster, const char* path);

    bool is_read_only() const { return m_read_only; }

    BlockDevice* m_device;
    bool m_read_only = false;
    u16 m_bytes_per_sector;
    u8 m_sectors_per_cluster;
    u16 m_reserved_sectors;
    u8 m_num_fats;
    u32 m_sectors_per_fat;
    u32 m_total_sectors;
    u32 m_root_cluster;
    u32 m_fat_start;
    u32 m_data_start;

    // FSInfo fields for free-space management
    u16 m_fsinfo_sector = 1;
    u32 m_free_clusters = 0xFFFFFFFF;
    u32 m_next_free_cluster_hint = 0xFFFFFFFF;

    void update_fsinfo(u32 free_clusters, u32 next_free_hint);
};

} // namespace acos::storage
