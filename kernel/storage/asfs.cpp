#include <kernel/storage/asfs.h>
#include <acos/runtime.h>
#include <kernel/hal/serial.h>

namespace acos::storage {

namespace {

// Case-insensitive string comparison helper
static inline int strcmp_nocase(const char* a, const char* b) {
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

class ASFSFileNode final : public vfs::Node {
public:
    ASFSFileNode() : m_is_used(false), m_device(nullptr), m_size(0) {
        memset(m_extents, 0, sizeof(m_extents));
    }

    void initialize(BlockDevice* device, const ASFSInode& inode) {
        m_device = device;
        m_size = inode.size;

        u64 device_total_blocks = device->capacity() / 512;

        // Copy and validate extents to ensure hardware bounds safety
        for (int e = 0; e < 6; e++) {
            u64 start = inode.extents[e].start_block;
            u32 count = inode.extents[e].block_count;

            // Invariant: extent_start > 0 and extent_start + count <= device_total_blocks
            u64 end_block;
            if (count > 0 && start > 0 &&
                !__builtin_add_overflow(start, count, &end_block) &&
                end_block <= device_total_blocks) {
                m_extents[e] = inode.extents[e];
            } else {
                // Ensure malformed extents are discarded/ignored safely
                m_extents[e].start_block = 0;
                m_extents[e].block_count = 0;
            }
        }
    }

    i32 read(u64 offset, usize size, void* buffer) override {
        if (!m_device || !buffer || offset >= m_size) return 0;
        usize readable = size;
        if (offset + readable > m_size) readable = (usize)(m_size - offset);

        u8 block_buf[512];
        u8* out = (u8*)buffer;
        usize copied = 0;

        while (copied < readable) {
            u64 relative_block = (offset + copied) / 512;

            // Map the relative block offset to a physical block using our extents
            u64 physical_block = 0;
            u64 blocks_accumulated = 0;
            bool resolved = false;

            for (int e = 0; e < 6; e++) {
                if (m_extents[e].block_count == 0) break;
                if (relative_block < blocks_accumulated + m_extents[e].block_count) {
                    physical_block = m_extents[e].start_block + (relative_block - blocks_accumulated);
                    resolved = true;
                    break;
                }
                blocks_accumulated += m_extents[e].block_count;
            }

            if (!resolved) break; // Reached end of described extents

            // Hardware bounds safety check
            u64 total_blocks = m_device->capacity() / 512;
            if (physical_block >= total_blocks) return copied > 0 ? (i32)copied : -1;

            if (m_device->read_block(physical_block, block_buf) != 0) {
                return copied > 0 ? (i32)copied : -1;
            }

            u64 block_offset = (offset + copied) % 512;
            usize chunk = 512 - block_offset;
            if (chunk > readable - copied) chunk = readable - copied;

            memcpy(out + copied, block_buf + block_offset, chunk);
            copied += chunk;
        }

        return (i32)copied;
    }

    i32 write(u64, usize, const void*) override { return -1; }
    u64 size() const override { return m_size; }
    vfs::NodeType type() const override { return vfs::NodeType::File; }

    i32 read_dir(u64, vfs::DirectoryEntry*, usize) override { return -1; }

public:
    bool m_is_used;
private:
    BlockDevice* m_device;
    u64 m_size;
    ASFSExtent m_extents[6];
};

class ASFSDirNode final : public vfs::Node {
public:
    ASFSDirNode() : m_is_used(false), m_device(nullptr) {
        memset(m_extents, 0, sizeof(m_extents));
    }

    void initialize(BlockDevice* device, const ASFSInode& inode) {
        m_device = device;
        u64 device_total_blocks = device->capacity() / 512;

        for (int e = 0; e < 6; e++) {
            u64 start = inode.extents[e].start_block;
            u32 count = inode.extents[e].block_count;

            u64 end_block;
            if (count > 0 && start > 0 &&
                !__builtin_add_overflow(start, count, &end_block) &&
                end_block <= device_total_blocks) {
                m_extents[e] = inode.extents[e];
            } else {
                m_extents[e].start_block = 0;
                m_extents[e].block_count = 0;
            }
        }
    }

    i32 read(u64, usize, void*) override { return -1; }
    i32 write(u64, usize, const void*) override { return -1; }
    u64 size() const override { return 0; }
    vfs::NodeType type() const override { return vfs::NodeType::Directory; }

    i32 read_dir(u64 offset, vfs::DirectoryEntry* entries, usize max_entries) override {
        if (!m_device || !entries || max_entries == 0) return -1;

        u8 block_buf[512];
        usize count = 0;
        u64 current_offset = 0;

        for (int e = 0; e < 6; e++) {
            if (m_extents[e].block_count == 0) break;

            for (u32 b = 0; b < m_extents[e].block_count; b++) {
                u64 physical_block = m_extents[e].start_block + b;

                u64 total_blocks = m_device->capacity() / 512;
                if (physical_block >= total_blocks) return (i32)count;

                if (m_device->read_block(physical_block, block_buf) != 0) {
                    return (i32)count;
                }

                // Parse 8 entries per 512-byte block
                ASFSDirectoryEntry* dir_entries = (ASFSDirectoryEntry*)block_buf;
                for (int i = 0; i < 8; i++) {
                    if (dir_entries[i].inode_number == 0) continue;

                    if (current_offset < offset) {
                        current_offset++;
                        continue;
                    }

                    // Copy entry safely with null termination guard
                    usize n_len = dir_entries[i].name_len;
                    if (n_len > 57) n_len = 57;
                    memcpy(entries[count].name, dir_entries[i].name, n_len);
                    entries[count].name[n_len] = '\0';
                    entries[count].type = (dir_entries[i].type == 2) ? vfs::NodeType::Directory : vfs::NodeType::File;
                    entries[count].size = 0;
                    entries[count].inode_number = dir_entries[i].inode_number;

                    count++;
                    if (count >= max_entries) return (i32)count;
                }
            }
        }

        return (i32)count;
    }

public:
    bool m_is_used;
private:
    BlockDevice* m_device;
    ASFSExtent m_extents[6];
};

static ASFSFileNode g_asfs_file_nodes[64];
static ASFSDirNode g_asfs_dir_nodes[16];

vfs::Node* allocate_asfs_file_node(BlockDevice* device, const ASFSInode& inode) {
    for (int i = 0; i < 64; i++) {
        if (!g_asfs_file_nodes[i].m_is_used) {
            new (&g_asfs_file_nodes[i]) ASFSFileNode();
            g_asfs_file_nodes[i].m_is_used = true;
            g_asfs_file_nodes[i].initialize(device, inode);
            return &g_asfs_file_nodes[i];
        }
    }
    return nullptr;
}

vfs::Node* allocate_asfs_dir_node(BlockDevice* device, const ASFSInode& inode) {
    for (int i = 0; i < 16; i++) {
        if (!g_asfs_dir_nodes[i].m_is_used) {
            new (&g_asfs_dir_nodes[i]) ASFSDirNode();
            g_asfs_dir_nodes[i].m_is_used = true;
            g_asfs_dir_nodes[i].initialize(device, inode);
            return &g_asfs_dir_nodes[i];
        }
    }
    return nullptr;
}

} // namespace

ASFSFileSystem::ASFSFileSystem(BlockDevice* device) : m_device(device) {
    memset(&m_sb, 0, sizeof(m_sb));
}

vfs::Node* ASFSFileSystem::open(const char* path) {
    if (!path || !m_device) return nullptr;
    const char* p = path;
    while (*p == '/') p++;

    u64 total_blocks = m_device->capacity() / 512;
    u64 root_inode_block = m_sb.root_inode;
    if (root_inode_block == 0 || root_inode_block >= total_blocks) return nullptr;

    u8 block_buf[512];
    if (m_device->read_block(root_inode_block, block_buf) != 0) {
        return nullptr;
    }
    ASFSInode root_inode;
    memcpy(&root_inode, block_buf, sizeof(ASFSInode));

    if (*p == '\0' || strcmp(p, ".") == 0) {
        return allocate_asfs_dir_node(m_device, root_inode);
    }

    return open_internal(root_inode_block, p);
}

vfs::Node* ASFSFileSystem::open_internal(u64 inode_block, const char* path) {
    u64 total_blocks = m_device->capacity() / 512;
    if (inode_block == 0 || inode_block >= total_blocks) return nullptr;

    u8 inode_buf[512];
    if (m_device->read_block(inode_block, inode_buf) != 0) return nullptr;

    ASFSInode inode;
    memcpy(&inode, inode_buf, sizeof(ASFSInode));

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

    if (comp_idx == 0) {
        if (inode.type == 2) return allocate_asfs_dir_node(m_device, inode);
        return allocate_asfs_file_node(m_device, inode);
    }

    if (inode.type != 2) return nullptr; // Cannot look up path inside a file

    u8 dir_block_buf[512];
    for (int e = 0; e < 6; e++) {
        if (inode.extents[e].block_count == 0) break;

        for (u32 b = 0; b < inode.extents[e].block_count; b++) {
            u64 physical_block = inode.extents[e].start_block + b;
            if (physical_block >= total_blocks) return nullptr;

            if (m_device->read_block(physical_block, dir_block_buf) != 0) return nullptr;

            ASFSDirectoryEntry* entries = (ASFSDirectoryEntry*)dir_block_buf;
            for (int i = 0; i < 8; i++) {
                if (entries[i].inode_number == 0) continue;

                char entry_name[64];
                usize n_len = entries[i].name_len;
                if (n_len > 57) n_len = 57;
                memcpy(entry_name, entries[i].name, n_len);
                entry_name[n_len] = '\0';

                if (strcmp_nocase(entry_name, component) == 0) {
                    if (*remaining != '\0') {
                        return open_internal(entries[i].inode_number, remaining);
                    }

                    u64 target_inode_block = entries[i].inode_number;
                    if (target_inode_block >= total_blocks) return nullptr;

                    u8 target_inode_buf[512];
                    if (m_device->read_block(target_inode_block, target_inode_buf) != 0) return nullptr;
                    ASFSInode target_inode;
                    memcpy(&target_inode, target_inode_buf, sizeof(ASFSInode));

                    if (entries[i].type == 2) {
                        return allocate_asfs_dir_node(m_device, target_inode);
                    } else {
                        return allocate_asfs_file_node(m_device, target_inode);
                    }
                }
            }
        }
    }

    return nullptr;
}

static ASFSFileSystem g_asfs_filesystems[4];
static bool g_asfs_used[4];

bool ASFSFileSystem::probe(void* device, const char* target) {
    hal::serial_print("ASFS: probe called\n");
    if (!device) return false;
    BlockDevice* block_device = (BlockDevice*)device;
    u8 sector[512];
    if (block_device->read_block(0, sector) != 0) {
        hal::serial_print("ASFS: read block 0 failed!\n");
        return false;
    }

    ASFSSuperblock* sb = (ASFSSuperblock*)sector;
    if (sb->magic != 0x415346535F4F535FULL) { // "ASFS_OS_"
        // Try redundant superblock at block capacity() / 512 - 1
        u64 last_block = block_device->capacity() / 512 - 1;
        hal::serial_print("ASFS: Main superblock invalid. Checking redundant superblock at block: ");
        hal::serial_print_hex(last_block);
        hal::serial_print("\n");

        if (block_device->read_block(last_block, sector) != 0) {
            hal::serial_print("ASFS: Failed to read redundant superblock block.\n");
            return false;
        }

        sb = (ASFSSuperblock*)sector;
        if (sb->magic != 0x415346535F4F535FULL) {
            hal::serial_print("ASFS: invalid redundant magic number!\n");
            return false;
        }
        hal::serial_print("ASFS: Redundant superblock is valid!\n");
    }

    // Additional critical metadata validation for ASFS Probing to prevent mounting corrupted partition
    if (sb->version != 1) {
        hal::serial_print("ASFS Probe Error: Unsupported version!\n");
        return false;
    }
    if (sb->block_size != 512 && sb->block_size != 4096) {
        hal::serial_print("ASFS Probe Error: Unsupported block size!\n");
        return false;
    }
    u64 total_blocks = block_device->capacity() / 512;
    if (sb->root_inode == 0 || sb->root_inode >= total_blocks) {
        hal::serial_print("ASFS Probe Error: Out of bounds root inode block!\n");
        return false;
    }

    ASFSFileSystem* fs = nullptr;
    for (int i = 0; i < 4; i++) {
        if (!g_asfs_used[i]) {
            g_asfs_used[i] = true;
            new (&g_asfs_filesystems[i]) ASFSFileSystem(block_device);
            fs = &g_asfs_filesystems[i];
            break;
        }
    }

    if (fs) {
        if (fs->mount(target)) {
            vfs::VFS::mount(target, fs);
            hal::serial_print("ASFS: mounted successfully at ");
            hal::serial_print(target);
            hal::serial_print("!\n");
            return true;
        }
    }
    return false;
}

bool ASFSFileSystem::mount(const char* target [[maybe_unused]]) {
    u8 sector[512];
    if (m_device->read_block(0, sector) != 0) return false;
    memcpy(&m_sb, sector, sizeof(ASFSSuperblock));

    if (m_sb.magic != 0x415346535F4F535FULL) {
        // Fallback to redundant superblock
        u64 last_block = m_device->capacity() / 512 - 1;
        if (m_device->read_block(last_block, sector) != 0) return false;
        memcpy(&m_sb, sector, sizeof(ASFSSuperblock));
        if (m_sb.magic != 0x415346535F4F535FULL) return false;
    }

    if (m_sb.version != 1) return false;

    // Validate properties
    if (m_sb.block_size != 512 && m_sb.block_size != 4096) return false;
    u64 total_blocks = m_device->capacity() / 512;
    if (m_sb.root_inode == 0 || m_sb.root_inode >= total_blocks) return false;

    return true;
}

} // namespace acos::storage
