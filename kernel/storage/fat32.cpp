#include <kernel/storage/fat32.h>
#include <acos/runtime.h>
#include <kernel/hal/serial.h>
#include <kernel/storage/asfs.h>

namespace acos::storage {

namespace {

static inline int strcmp_impl(const char* a, const char* b) {
    while (*a && *b) {
        char ca = *a, cb = *b;
        if (ca >= 'a' && ca <= 'z') ca -= 32;
        if (cb >= 'a' && cb <= 'z') cb -= 32;
        if (ca != cb) break;
        a++; b++;
    }
    char ca = *a, cb = *b;
    if (ca >= 'a' && ca <= 'z') ca -= 32;
    if (cb >= 'a' && cb <= 'z') cb -= 32;
    return (unsigned char)ca - (unsigned char)cb;
}

class FAT32FileNode final : public vfs::Node {
public:
    FAT32FileNode() : m_is_used(false), m_device(nullptr), m_fs(nullptr), m_first_cluster(0), m_size(0), m_fat_start(0), m_data_start(0), m_sectors_per_cluster(0), m_dir_sector(0), m_dir_offset(0) {}

    void initialize(FAT32FileSystem* fs, u32 first_cluster, u32 file_size, u32 dir_sector, u32 dir_offset) {
        m_fs = fs;
        m_device = fs->m_device;
        m_first_cluster = first_cluster;
        m_size = file_size;
        m_fat_start = fs->m_fat_start;
        m_data_start = fs->m_data_start;
        m_sectors_per_cluster = fs->m_sectors_per_cluster;
        m_dir_sector = dir_sector;
        m_dir_offset = dir_offset;
    }

    i32 read(u64 offset, usize size, void* buffer) override {
        if (!m_device || !buffer || offset >= m_size) return 0;
        usize readable = size;
        if (offset + readable > m_size) readable = (usize)(m_size - offset);
        u8 sector[512];
        u8* out = (u8*)buffer;
        usize copied = 0;
        u32 cluster = m_first_cluster;
        u64 skip = offset;
        u32 cluster_bytes = (u32)m_sectors_per_cluster * 512;
        while (cluster >= 2 && cluster < 0x0FFFFFF8 && skip >= cluster_bytes) {
            skip -= cluster_bytes;
            cluster = next_cluster(cluster);
        }
        while (copied < readable && cluster >= 2 && cluster < 0x0FFFFFF8) {
            for (u8 s = 0; s < m_sectors_per_cluster && copied < readable; ++s) {
                u32 lba = m_data_start + ((cluster - 2) * (u32)m_sectors_per_cluster) + s;
                if (m_device->read_block(lba, sector) != 0) return copied > 0 ? (i32)copied : -1;
                usize sector_offset = 0;
                if (skip >= 512) { skip -= 512; continue; }
                if (skip > 0) { sector_offset = (usize)skip; skip = 0; }
                usize chunk = 512 - sector_offset;
                if (chunk > readable - copied) chunk = readable - copied;
                memcpy(out + copied, sector + sector_offset, chunk);
                copied += chunk;
            }
            cluster = next_cluster(cluster);
        }
        return (i32)copied;
    }

    i32 write(u64 offset, usize size, const void* buffer) override {
        if (!m_device || !m_fs || !buffer) return -1;
        if (m_fs->m_read_only) {
            hal::serial_print("FAT32 Error: Attempted to write to read-only mounted filesystem!\n");
            return -1;
        }

        u64 end_byte = offset + size;
        u32 cluster_bytes = (u32)m_sectors_per_cluster * 512;

        if (m_first_cluster == 0 && end_byte > 0) {
            u32 free_cluster = 0;
            alignas(4096) u8 fat_sector[512];
            u32 total_clusters = (m_fs->m_total_sectors - m_fs->m_data_start) / m_fs->m_sectors_per_cluster;
            for (u32 c = 2; c < total_clusters + 2; c++) {
                u32 fat_offset = c * 4;
                u32 fat_block = m_fs->m_fat_start + (fat_offset / 512);
                if (m_device->read_block(fat_block, fat_sector) == 0) {
                    u32 entry_val = (*(u32*)(fat_sector + (fat_offset % 512))) & 0x0FFFFFFF;
                    if (entry_val == 0) {
                        free_cluster = c;
                        break;
                    }
                }
            }

            if (free_cluster == 0) return -1;

            if (!m_fs->write_fat_entry(free_cluster, 0x0FFFFFFF)) return -1;

            m_first_cluster = free_cluster;

            alignas(4096) u8 zero_sector[512];
            memset(zero_sector, 0, 512);
            for (u8 s = 0; s < m_sectors_per_cluster; s++) {
                u32 lba = m_data_start + ((free_cluster - 2) * (u32)m_sectors_per_cluster) + s;
                m_device->write_block(lba, zero_sector);
            }

            alignas(4096) u8 dir_sector_buf[512];
            if (m_device->read_block(m_dir_sector, dir_sector_buf) == 0) {
                u8* entry = dir_sector_buf + m_dir_offset;
                *(u16*)(entry + 26) = (u16)(free_cluster & 0xFFFF);
                *(u16*)(entry + 20) = (u16)((free_cluster >> 16) & 0xFFFF);
                m_device->write_block(m_dir_sector, dir_sector_buf);
            }
        }

        u32 current_cluster_count = (m_size + cluster_bytes - 1) / cluster_bytes;
        if (current_cluster_count == 0 && m_first_cluster != 0) current_cluster_count = 1;
        u32 needed_cluster_count = (end_byte + cluster_bytes - 1) / cluster_bytes;

        u32 last_cluster = m_first_cluster;
        if (last_cluster != 0) {
            while (true) {
                u32 next = next_cluster(last_cluster);
                if (next >= 0x0FFFFFF8 || next == 0) break;
                last_cluster = next;
            }
        }

        while (current_cluster_count < needed_cluster_count) {
            u32 free_cluster = 0;
            alignas(4096) u8 fat_sector[512];
            u32 total_clusters = (m_fs->m_total_sectors - m_fs->m_data_start) / m_fs->m_sectors_per_cluster;
            for (u32 c = 2; c < total_clusters + 2; c++) {
                u32 fat_offset = c * 4;
                u32 fat_block = m_fs->m_fat_start + (fat_offset / 512);
                if (m_device->read_block(fat_block, fat_sector) == 0) {
                    u32 entry_val = (*(u32*)(fat_sector + (fat_offset % 512))) & 0x0FFFFFFF;
                    if (entry_val == 0) {
                        free_cluster = c;
                        break;
                    }
                }
            }

            if (free_cluster == 0) return -1;

            if (!m_fs->write_fat_entry(free_cluster, 0x0FFFFFFF)) return -1;
            if (last_cluster != 0) {
                if (!m_fs->write_fat_entry(last_cluster, free_cluster)) return -1;
            }

            last_cluster = free_cluster;

            alignas(4096) u8 zero_sector[512];
            memset(zero_sector, 0, 512);
            for (u8 s = 0; s < m_sectors_per_cluster; s++) {
                u32 lba = m_data_start + ((free_cluster - 2) * (u32)m_sectors_per_cluster) + s;
                m_device->write_block(lba, zero_sector);
            }

            current_cluster_count++;
        }

        alignas(4096) u8 sector[512];
        const u8* in = (const u8*)buffer;
        usize written = 0;

        while (written < size) {
            u64 current_offset = offset + written;
            u32 target_cluster_idx = current_offset / cluster_bytes;
            u32 cluster_offset = current_offset % cluster_bytes;

            u32 cluster = m_first_cluster;
            for (u32 i = 0; i < target_cluster_idx; i++) {
                cluster = next_cluster(cluster);
            }

            u32 sector_in_cluster = cluster_offset / 512;
            u32 byte_offset_in_sector = cluster_offset % 512;

            u32 lba = m_data_start + ((cluster - 2) * (u32)m_sectors_per_cluster) + sector_in_cluster;

            if (m_device->read_block(lba, sector) != 0) {
                return written > 0 ? (i32)written : -1;
            }

            usize chunk = 512 - byte_offset_in_sector;
            if (chunk > size - written) chunk = size - written;

            memcpy(sector + byte_offset_in_sector, in + written, chunk);

            if (m_device->write_block(lba, sector) != 0) {
                return written > 0 ? (i32)written : -1;
            }

            written += chunk;
        }

        if (end_byte > m_size) {
            m_size = end_byte;

            alignas(4096) u8 dir_sector_buf[512];
            if (m_device->read_block(m_dir_sector, dir_sector_buf) == 0) {
                u8* entry = dir_sector_buf + m_dir_offset;
                *(u32*)(entry + 28) = (u32)m_size;
                m_device->write_block(m_dir_sector, dir_sector_buf);
            }
        }

        m_device->flush();
        return (i32)written;
    }

    u64 size() const override { return m_size; }
    vfs::NodeType type() const override { return vfs::NodeType::File; }

    i32 read_dir(u64, vfs::DirectoryEntry*, usize) override { return -1; }

private:
    u32 next_cluster(u32 cluster) {
        if (cluster < 2 || cluster >= 0x0FFFFFF8) return 0x0FFFFFFF;
        alignas(4096) u8 fat_sector[512];
        u32 fat_offset = cluster * 4;
        u32 fat_block = m_fat_start + (fat_offset / 512);
        if (!m_device || m_device->read_block(fat_block, fat_sector) != 0) return 0x0FFFFFFF;
        u32 next = (*(u32*)(fat_sector + (fat_offset % 512))) & 0x0FFFFFFF;
        if (next == cluster) {
            hal::serial_print("[FAT32] CRITICAL ERROR: Infinite cluster loop detected! Partition is corrupt.\n");
            return 0x0FFFFFFF;
        }
        return next;
    }

public:
    bool m_is_used;
private:
    BlockDevice* m_device;
    FAT32FileSystem* m_fs;
    u32 m_first_cluster;
    u32 m_size;
    u32 m_fat_start;
    u32 m_data_start;
    u8 m_sectors_per_cluster;
    u32 m_dir_sector;
    u32 m_dir_offset;
};

class FAT32DirNode final : public vfs::Node {
public:
    FAT32DirNode() : m_is_used(false), m_device(nullptr), m_first_cluster(0), m_fat_start(0), m_data_start(0), m_sectors_per_cluster(0) {}

    void initialize(BlockDevice* device, u32 first_cluster, u32 fat_start, u32 data_start, u8 sectors_per_cluster) {
        m_device = device; m_first_cluster = first_cluster;
        m_fat_start = fat_start; m_data_start = data_start; m_sectors_per_cluster = sectors_per_cluster;
    }

    i32 read(u64, usize, void*) override { return -1; }
    i32 write(u64, usize, const void*) override { return -1; }
    u64 size() const override { return 0; }
    vfs::NodeType type() const override { return vfs::NodeType::Directory; }

    i32 read_dir(u64 offset, vfs::DirectoryEntry* entries, usize max_entries) override {
        u8 sector[512];
        u32 cluster = m_first_cluster;
        usize count = 0;
        u64 current_offset = 0;

        while (cluster >= 2 && cluster < 0x0FFFFFF8 && count < max_entries) {
            for (u8 s = 0; s < m_sectors_per_cluster && count < max_entries; ++s) {
                u32 lba = m_data_start + ((cluster - 2) * (u32)m_sectors_per_cluster) + s;
                if (m_device->read_block(lba, sector) != 0) return (i32)count;
                for (int i = 0; i < 16; i++) {
                    u8* entry = sector + (i * 32);
                    if (entry[0] == 0) return (i32)count;
                    if (entry[0] == 0xE5 || (entry[11] & 0x08)) continue;

                    if (current_offset < offset) {
                        current_offset++;
                        continue;
                    }

                    char name[13] = {0};
                    int name_idx = 0;
                    for (int j = 0; j < 8; j++) if (entry[j] != ' ') name[name_idx++] = entry[j];
                    if (entry[8] != ' ') {
                        name[name_idx++] = '.';
                        for (int j = 8; j < 11; j++) if (entry[j] != ' ') name[name_idx++] = entry[j];
                    }
                    name[name_idx] = '\0';

                    memcpy(entries[count].name, name, name_idx + 1);
                    entries[count].type = (entry[11] & 0x10) ? vfs::NodeType::Directory : vfs::NodeType::File;
                    entries[count].size = *(u32*)(entry + 28);
                    count++;
                    if (count >= max_entries) return (i32)count;
                }
            }
            cluster = next_cluster(cluster);
        }
        return (i32)count;
    }

private:
    u32 next_cluster(u32 cluster) {
        if (cluster < 2 || cluster >= 0x0FFFFFF8) return 0x0FFFFFFF;
        u8 fat_sector[512];
        u32 fat_offset = cluster * 4;
        u32 fat_block = m_fat_start + (fat_offset / 512);
        if (!m_device || m_device->read_block(fat_block, fat_sector) != 0) return 0x0FFFFFFF;
        u32 next = (*(u32*)(fat_sector + (fat_offset % 512))) & 0x0FFFFFFF;
        if (next == cluster) {
            hal::serial_print("[FAT32] CRITICAL ERROR: Infinite cluster loop detected! Partition is corrupt.\n");
            return 0x0FFFFFFF;
        }
        return next;
    }

public:
    bool m_is_used;
private:
    BlockDevice* m_device;
    u32 m_first_cluster;
    u32 m_fat_start;
    u32 m_data_start;
    u8 m_sectors_per_cluster;
};

static FAT32FileNode g_file_nodes[64];
static FAT32DirNode g_dir_nodes[16];

vfs::Node* allocate_file_node(FAT32FileSystem* fs, u32 cluster, u32 size, u32 dir_sector, u32 dir_offset) {
    for (int i = 0; i < 64; i++) {
        if (!g_file_nodes[i].m_is_used) {
            new (&g_file_nodes[i]) FAT32FileNode();
            g_file_nodes[i].m_is_used = true;
            g_file_nodes[i].initialize(fs, cluster, size, dir_sector, dir_offset);
            return &g_file_nodes[i];
        }
    }
    return nullptr;
}

vfs::Node* allocate_dir_node(BlockDevice* device, u32 cluster, u32 fat_start, u32 data_start, u8 spc) {
    for (int i = 0; i < 16; i++) {
        if (!g_dir_nodes[i].m_is_used) {
            new (&g_dir_nodes[i]) FAT32DirNode();
            g_dir_nodes[i].m_is_used = true;
            g_dir_nodes[i].initialize(device, cluster, fat_start, data_start, spc);
            return &g_dir_nodes[i];
        }
    }
    return nullptr;
}

} // namespace

FAT32FileSystem::FAT32FileSystem(BlockDevice* device) : m_device(device) {}

vfs::Node* FAT32FileSystem::open(const char* path) {
    if (!path || !m_device) return nullptr;
    const char* p = path;
    while (*p == '/') p++;
    if (*p == '\0' || strcmp(p, ".") == 0) return allocate_dir_node(m_device, m_root_cluster, m_fat_start, m_data_start, m_sectors_per_cluster);
    return open_internal(m_root_cluster, p);
}

vfs::Node* FAT32FileSystem::open_internal(u32 cluster, const char* path) {
    alignas(4096) u8 sector[512];
    char component[256];
    int comp_idx = 0;
    while (path[comp_idx] && path[comp_idx] != '/') {
        if (comp_idx < 255) {
            component[comp_idx] = path[comp_idx];
            comp_idx++;
        } else return nullptr;
    }
    component[comp_idx] = '\0';
    const char* remaining = path + comp_idx;
    while (*remaining == '/') remaining++;

    if (comp_idx == 0) return allocate_dir_node(m_device, cluster, m_fat_start, m_data_start, m_sectors_per_cluster);

    hal::serial_print("FAT32: component='"); hal::serial_print(component);
    hal::serial_print("'\n");

    while (cluster >= 2 && cluster < 0x0FFFFFF8) {
        for (u32 s = 0; s < m_sectors_per_cluster; s++) {
            u32 lba = m_data_start + ((cluster - 2) * (u32)m_sectors_per_cluster) + s;
            if (m_device->read_block(lba, sector) != 0) return nullptr;
            for (int i = 0; i < 16; i++) {
                u8* entry = sector + (i * 32);
                if (entry[0] == 0) return nullptr;
                if (entry[0] == 0xE5 || (entry[11] & 0x08)) continue;

                char name[13] = {0};
                int name_idx = 0;
                for (int j = 0; j < 8; j++) if (entry[j] != ' ') name[name_idx++] = entry[j];
                if (entry[8] != ' ') {
                    name[name_idx++] = '.';
                    for (int j = 8; j < 11; j++) if (entry[j] != ' ') name[name_idx++] = entry[j];
                }
                name[name_idx] = '\0';

                if (strcmp_impl(name, component) == 0) {
                    u32 first_cluster = (u32)(*(u16*)(entry + 26)) | ((u32)(*(u16*)(entry + 20)) << 16);
                    if (entry[11] & 0x10) {
                        if (*remaining) return open_internal(first_cluster, remaining);
                        return allocate_dir_node(m_device, first_cluster, m_fat_start, m_data_start, m_sectors_per_cluster);
                    } else {
                        if (*remaining) return nullptr;
                        return allocate_file_node(this, first_cluster, *(u32*)(entry + 28), lba, i * 32);
                    }
                }
            }
        }
        u32 fat_offset = cluster * 4;
        u32 fat_block = m_fat_start + (fat_offset / 512);
        if (m_device->read_block(fat_block, sector) != 0) return nullptr;
        cluster = (*(u32*)(sector + (fat_offset % 512))) & 0x0FFFFFFF;
    }
    return nullptr;
}

bool FAT32FileSystem::write_fat_entry(u32 cluster, u32 value) {
    alignas(4096) u8 fat_sector[512];
    u32 fat_offset = cluster * 4;
    u32 fat_block = m_fat_start + (fat_offset / 512);
    if (!m_device || m_device->read_block(fat_block, fat_sector) != 0) return false;
    *(u32*)(fat_sector + (fat_offset % 512)) = value;
    if (m_device->write_block(fat_block, fat_sector) != 0) return false;
    for (u8 f = 1; f < m_num_fats; f++) {
        u32 backup_fat_block = fat_block + f * m_sectors_per_fat;
        m_device->write_block(backup_fat_block, fat_sector);
    }
    return true;
}

static FAT32FileSystem g_filesystems[4];
static bool g_fs_used[4];

bool FAT32FileSystem::probe(void* device, const char* target) {
    hal::serial_print("FAT32: probe called\n");
    if (!device) return false;
    BlockDevice* block_device = (BlockDevice*)device;
    alignas(4096) u8 sector[512];
    memset(sector, 0, 512);
    hal::serial_print("FAT32: reading block 0...\n");
    if (block_device->read_block(0, sector) != 0) {
        hal::serial_print("FAT32: read block 0 failed!\n");
        return false;
    }
    hal::serial_print("FAT32: block 0 read successfully\n");
    hal::serial_print("FAT32: checking magic numbers...\n");
    if (sector[510] != 0x55 || sector[511] != 0xAA) {
        hal::serial_print("FAT32: invalid magic 55 AA!\n");
        return false;
    }
    hal::serial_print("FAT32: magic numbers check passed\n");

    FAT32FileSystem* fs = nullptr;
    for (int i = 0; i < 4; i++) {
        hal::serial_print("FAT32: checking slot ");
        hal::serial_print_hex(i);
        hal::serial_print("\n");
        if (!g_fs_used[i]) {
            g_fs_used[i] = true;
            hal::serial_print("FAT32: copying filesystem instance...\n");
            new (&g_filesystems[i]) FAT32FileSystem(block_device);
            fs = &g_filesystems[i];
            hal::serial_print("FAT32: instance copied to slot\n");
            break;
        }
    }

    if (fs) {
        hal::serial_print("FAT32: calling mount...\n");
        bool m_res = fs->mount(target);
        hal::serial_print("FAT32: mount returned ");
        hal::serial_print_hex(m_res);
        hal::serial_print("\n");
        if (m_res) {
            hal::serial_print("FAT32: mounting via VFS...\n");
            vfs::VFS::mount(target, fs);
            hal::serial_print("FAT32: mounted successfully!\n");
            return true;
        }
    }
    return false;
}

bool FAT32FileSystem::mount(const char* target [[maybe_unused]]) {
    u8 sector[512];
    hal::serial_print("FAT32: mount - reading block 0...\n");
    if (m_device->read_block(0, sector) != 0) {
        hal::serial_print("FAT32: mount - read block 0 failed!\n");
        return false;
    }
    hal::serial_print("FAT32: mount - parsing values...\n");

    m_bytes_per_sector = *(u16*)(sector + 11);
    hal::serial_print("FAT32: bytes_per_sector=");
    hal::serial_print_hex(m_bytes_per_sector);
    hal::serial_print("\n");

    if (m_bytes_per_sector != 512) {
        hal::serial_print("FAT32: bytes_per_sector is not 512!\n");
        return false;
    }

    m_sectors_per_cluster = sector[13];
    hal::serial_print("FAT32: sectors_per_cluster=");
    hal::serial_print_hex(m_sectors_per_cluster);
    hal::serial_print("\n");

    m_reserved_sectors = *(u16*)(sector + 14);
    hal::serial_print("FAT32: reserved_sectors=");
    hal::serial_print_hex(m_reserved_sectors);
    hal::serial_print("\n");

    m_num_fats = sector[16];
    hal::serial_print("FAT32: num_fats=");
    hal::serial_print_hex(m_num_fats);
    hal::serial_print("\n");

    m_sectors_per_fat = *(u32*)(sector + 36);
    hal::serial_print("FAT32: sectors_per_fat=");
    hal::serial_print_hex(m_sectors_per_fat);
    hal::serial_print("\n");

    m_total_sectors = *(u32*)(sector + 32);
    hal::serial_print("FAT32: total_sectors=");
    hal::serial_print_hex(m_total_sectors);
    hal::serial_print("\n");

    m_root_cluster = *(u32*)(sector + 44);
    hal::serial_print("FAT32: root_cluster=");
    hal::serial_print_hex(m_root_cluster);
    hal::serial_print("\n");

    m_fat_start = m_reserved_sectors;
    m_data_start = m_reserved_sectors + (m_num_fats * m_sectors_per_fat);

    hal::serial_print("FAT32: m_fat_start=");
    hal::serial_print_hex(m_fat_start);
    hal::serial_print(" m_data_start=");
    hal::serial_print_hex(m_data_start);
    hal::serial_print("\n");

    m_read_only = is_path_protected(target);

    return true;
}

} // namespace acos::storage
