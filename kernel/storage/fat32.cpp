#include <kernel/storage/fat32.h>
#include <acos/runtime.h>

namespace acos::storage {

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
    
    // Parse BPB to get root directory cluster
    u32 root_cluster = *(u32*)(sector + 44);
    u32 sectors_per_cluster = sector[13];
    u32 bytes_per_sector = *(u16*)(sector + 11);
    
    if (sectors_per_cluster == 0 || bytes_per_sector != 512) return nullptr;
    
    // Search for file in root directory
    u32 cluster = root_cluster;
    u32 entries_per_sector = 512 / 32;
    
    while (cluster < 0x0FFFFFF8) {
        if (m_device->read_block(cluster, sector) != 0) return nullptr;
        
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
                // Create a simple file node wrapper
                // For now, return nullptr as we need a proper File implementation
                // This will be completed when File class is fully defined
                return nullptr;
            }
        }
        
        // Move to next cluster in FAT chain
        u32 fat_sector = 1; // FAT starts at sector 1
        u32 fat_offset = cluster * 4;
        u32 fat_block = fat_sector + (fat_offset / 512);
        
        if (m_device->read_block(fat_block, sector) != 0) return nullptr;
        
        cluster = *(u32*)(sector + (fat_offset % 512));
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
