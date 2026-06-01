#include <kernel/storage/fat32.h>
#include <acos/runtime.h>

namespace acos::storage {

namespace {

class FAT32FileNode final : public vfs::Node {
public:
    FAT32FileNode() : m_device(nullptr), m_first_cluster(0), m_size(0), m_fat_start(0), m_data_start(0), m_sectors_per_cluster(0) {}

    void initialize(BlockDevice* device, u32 first_cluster, u32 file_size, u32 fat_start, u32 data_start, u8 sectors_per_cluster) {
        m_device = device;
        m_first_cluster = first_cluster;
        m_size = file_size;
        m_fat_start = fat_start;
        m_data_start = data_start;
        m_sectors_per_cluster = sectors_per_cluster;
    }

    i32 read(u64 offset, usize size, void* buffer) override {
        if (!m_device || !buffer || offset >= m_size) {
            return 0;
        }

        usize readable = size;
        if (offset + readable > m_size) {
            readable = static_cast<usize>(m_size - offset);
        }

        u8 sector[512];
        u8* out = static_cast<u8*>(buffer);
        usize copied = 0;
        u32 cluster = m_first_cluster;
        u64 skip = offset;
        const u32 cluster_bytes = static_cast<u32>(m_sectors_per_cluster) * 512;

        while (cluster >= 2 && cluster < 0x0FFFFFF8 && skip >= cluster_bytes) {
            skip -= cluster_bytes;
            cluster = next_cluster(cluster);
        }

        while (copied < readable && cluster >= 2 && cluster < 0x0FFFFFF8) {
            for (u8 s = 0; s < m_sectors_per_cluster && copied < readable; ++s) {
                const u32 lba = m_data_start + ((cluster - 2) * m_sectors_per_cluster) + s;
                if (m_device->read_block(lba, sector) != 0) {
                    return copied > 0 ? static_cast<i32>(copied) : -1;
                }

                usize sector_offset = 0;
                if (skip >= 512) {
                    skip -= 512;
                    continue;
                }
                if (skip > 0) {
                    sector_offset = static_cast<usize>(skip);
                    skip = 0;
                }

                usize chunk = 512 - sector_offset;
                if (chunk > readable - copied) {
                    chunk = readable - copied;
                }
                memcpy(out + copied, sector + sector_offset, chunk);
                copied += chunk;
            }
            cluster = next_cluster(cluster);
        }

        return static_cast<i32>(copied);
    }

    i32 write(u64, usize, const void*) override { return -1; }
    u64 size() const override { return m_size; }
    vfs::NodeType type() const override { return vfs::NodeType::File; }

private:
    u32 next_cluster(u32 cluster) {
        u8 fat_sector[512];
        const u32 fat_offset = cluster * 4;
        const u32 fat_block = m_fat_start + (fat_offset / 512);
        if (!m_device || m_device->read_block(fat_block, fat_sector) != 0) {
            return 0x0FFFFFFF;
        }
        return (*(u32*)(fat_sector + (fat_offset % 512))) & 0x0FFFFFFF;
    }

    BlockDevice* m_device;
    u32 m_first_cluster;
    u32 m_size;
    u32 m_fat_start;
    u32 m_data_start;
    u8 m_sectors_per_cluster;
};

static FAT32FileNode g_fat32_nodes[64];
static bool g_fat32_node_used[64];

FAT32FileNode* allocate_node() {
    for (usize i = 0; i < 64; ++i) {
        if (!g_fat32_node_used[i]) {
            g_fat32_node_used[i] = true;
            return &g_fat32_nodes[i];
        }
    }
    return nullptr;
}

} // namespace

// Helper function for string comparison
static inline int strcmp_impl(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

FAT32FileSystem::FAT32FileSystem(BlockDevice* device) : m_device(device) {}

vfs::Node* FAT32FileSystem::open(const char* path) {
    if (!path || !m_device) return nullptr;
    
    u8 sector[512];
    if (m_device->read_block(0, sector) != 0) return nullptr;
    
    const u32 root_cluster = *(u32*)(sector + 44);
    const u32 sectors_per_cluster = sector[13];
    const u32 bytes_per_sector = *(u16*)(sector + 11);
    const u32 reserved = *(u16*)(sector + 14);
    const u32 fats = sector[16];
    const u32 sectors_per_fat = *(u32*)(sector + 36);
    const u32 fat_start = reserved;
    const u32 data_start = reserved + (fats * sectors_per_fat);
    
    if (sectors_per_cluster == 0 || bytes_per_sector != 512) return nullptr;
    
    u32 cluster = root_cluster;
    u32 entries_per_sector = 512 / 32;
    
    while (cluster < 0x0FFFFFF8) {
        const u32 dir_lba = data_start + ((cluster - 2) * sectors_per_cluster);
        if (m_device->read_block(dir_lba, sector) != 0) return nullptr;
        
        for (u32 i = 0; i < entries_per_sector; i++) {
            u8* entry = sector + (i * 32);
            
            // Check for end of directory
            if (entry[0] == 0) return nullptr;
            
            // Skip deleted entries
            if (entry[0] == 0xE5) continue;
            
            // Skip volume labels and directories
            if (entry[11] & 0x10) continue;
            
            // Extract filename (8.3 format)
            char name[13] = {0};
            int name_idx = 0;
            
            // Copy base name (8 chars)
            for (int j = 0; j < 8; j++) {
                if (entry[j] != ' ') {
                    name[name_idx++] = entry[j];
                }
            }
            
            // Add dot and extension
            if (entry[8] != ' ') {
                name[name_idx++] = '.';
                for (int j = 8; j < 11; j++) {
                    if (entry[j] != ' ') {
                        name[name_idx++] = entry[j];
                    }
                }
            }
            name[name_idx] = '\0';
            
            // Compare with requested path
            if (strcmp_impl(name, path) == 0) {
                FAT32FileNode* node = allocate_node();
                if (!node) return nullptr;
                const u32 first_cluster = (static_cast<u32>(*(u16*)(entry + 20)) << 16) | *(u16*)(entry + 26);
                const u32 file_size = *(u32*)(entry + 28);
                node->initialize(m_device, first_cluster, file_size, fat_start, data_start, static_cast<u8>(sectors_per_cluster));
                return node;
            }
        }
        
        // Move to next cluster in FAT chain
        u32 fat_offset = cluster * 4;
        u32 fat_block = fat_start + (fat_offset / 512);
        
        if (m_device->read_block(fat_block, sector) != 0) return nullptr;
        
        cluster = (*(u32*)(sector + (fat_offset % 512))) & 0x0FFFFFFF;
    }
    
    return nullptr;
}

bool FAT32FileSystem::mount(const char* target [[maybe_unused]]) {
    if (!m_device) return false;
    
    u8 sector[512];
    if (m_device->read_block(0, sector) != 0) return false;
    
    // Verify boot sector signature
    if (sector[510] != 0x55 || sector[511] != 0xAA) return false;
    
    // Verify FAT32 signature at offset 82
    if (sector[82] != 0x28 && sector[82] != 0x29) return false;
    
    // Parse BPB
    u16 bytes_per_sector = *(u16*)(sector + 11);
    u8 sectors_per_cluster = sector[13];
    u16 reserved_sectors = *(u16*)(sector + 14);
    u8 num_fats = sector[16];
    u32 total_sectors = *(u32*)(sector + 32);
    u32 sectors_per_fat = *(u32*)(sector + 36);
    u32 root_cluster = *(u32*)(sector + 44);
    
    // Validate parameters
    if (bytes_per_sector != 512) return false;
    if (sectors_per_cluster == 0 || (sectors_per_cluster & (sectors_per_cluster - 1))) return false;
    if (num_fats == 0 || num_fats > 2) return false;
    if (total_sectors == 0) return false;
    if (sectors_per_fat == 0) return false;
    if (root_cluster < 2) return false;
    
    // Store parameters
    m_bytes_per_sector = bytes_per_sector;
    m_sectors_per_cluster = sectors_per_cluster;
    m_reserved_sectors = reserved_sectors;
    m_num_fats = num_fats;
    m_sectors_per_fat = sectors_per_fat;
    m_total_sectors = total_sectors;
    m_root_cluster = root_cluster;
    
    // Calculate data area start
    m_fat_start = reserved_sectors;
    m_data_start = reserved_sectors + (num_fats * sectors_per_fat);
    
    return true;
}

} // namespace acos::storage
