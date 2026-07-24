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
    ASFSFileNode() : m_is_used(false), m_fs(nullptr), m_inode_block(0), m_size(0) {
        memset(m_extents, 0, sizeof(m_extents));
    }

    void initialize(ASFSFileSystem* fs, u64 inode_block, const ASFSInode& inode) {
        m_fs = fs;
        m_inode_block = inode_block;
        m_size = inode.size;

        u64 device_total_blocks = fs->device()->capacity() / 512;

        // Copy and validate extents to ensure hardware bounds safety
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

    i32 read(u64 offset, usize size, void* buffer) override {
        if (!m_fs || !m_fs->device() || !buffer || offset >= m_size) return 0;
        usize readable = size;
        if (offset + readable > m_size) readable = (usize)(m_size - offset);

        u8 block_buf[512];
        u8* out = (u8*)buffer;
        usize copied = 0;

        while (copied < readable) {
            u64 relative_block = (offset + copied) / 512;

            // Map relative offset to physical block via extents
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

            if (!resolved) break;

            u64 total_blocks = m_fs->device()->capacity() / 512;
            if (physical_block >= total_blocks) return copied > 0 ? (i32)copied : -1;

            if (m_fs->device()->read_block(physical_block, block_buf) != 0) {
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

    i32 write(u64 offset, usize size, const void* buffer) override {
        if (!m_fs || !m_fs->device() || !buffer) return -1;

        u64 device_total_blocks = m_fs->device()->capacity() / 512;
        u64 end_byte = offset + size;
        u8 block_buf[512];
        const u8* in = (const u8*)buffer;
        usize written = 0;

        while (written < size) {
            u64 current_offset = offset + written;
            u64 relative_block = current_offset / 512;
            u64 block_offset = current_offset % 512;

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

            if (!resolved) {
                // Dynamically allocate a new physical block!
                u64 new_block = m_fs->allocate_blocks(1);
                if (new_block == 0) {
                    return written > 0 ? (i32)written : -1; // Out of space
                }

                // Append/Merge extent
                bool merged = false;
                int last_active = -1;
                for (int e = 0; e < 6; e++) {
                    if (m_extents[e].block_count > 0) {
                        last_active = e;
                    }
                }

                if (last_active >= 0) {
                    u64 last_end = m_extents[last_active].start_block + m_extents[last_active].block_count;
                    if (last_end == new_block) {
                        m_extents[last_active].block_count++;
                        merged = true;
                    }
                }

                if (!merged) {
                    int empty_slot = -1;
                    for (int e = 0; e < 6; e++) {
                        if (m_extents[e].block_count == 0) {
                            empty_slot = e;
                            break;
                        }
                    }

                    if (empty_slot >= 0) {
                        m_extents[empty_slot].start_block = new_block;
                        m_extents[empty_slot].block_count = 1;
                    } else {
                        m_fs->deallocate_blocks(new_block, 1);
                        return written > 0 ? (i32)written : -1; // Extents full
                    }
                }

                physical_block = new_block;
                // Zero out the new block on disk
                memset(block_buf, 0, 512);
                if (m_fs->device()->write_block(physical_block, block_buf) != 0) {
                    return written > 0 ? (i32)written : -1;
                }
            }

            if (physical_block >= device_total_blocks) {
                return written > 0 ? (i32)written : -1;
            }

            // Read-modify-write block
            if (m_fs->device()->read_block(physical_block, block_buf) != 0) {
                return written > 0 ? (i32)written : -1;
            }

            usize chunk = 512 - block_offset;
            if (chunk > size - written) chunk = size - written;

            memcpy(block_buf + block_offset, in + written, chunk);

            if (m_fs->device()->write_block(physical_block, block_buf) != 0) {
                return written > 0 ? (i32)written : -1;
            }

            written += chunk;
        }

        // Persist Inode updates
        m_size = (m_size > end_byte) ? m_size : end_byte;

        ASFSInode inode;
        if (m_fs->device()->read_block(m_inode_block, &inode) == 0) {
            inode.size = m_size;
            memcpy(inode.extents, m_extents, sizeof(m_extents));
            m_fs->device()->write_block(m_inode_block, &inode);
        }

        return (i32)written;
    }

    u64 size() const override { return m_size; }
    vfs::NodeType type() const override { return vfs::NodeType::File; }

    i32 read_dir(u64, vfs::DirectoryEntry*, usize) override { return -1; }

public:
    bool m_is_used;
private:
    ASFSFileSystem* m_fs;
    u64 m_inode_block;
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

vfs::Node* allocate_asfs_file_node(ASFSFileSystem* fs, u64 inode_block, const ASFSInode& inode) {
    for (int i = 0; i < 64; i++) {
        if (!g_asfs_file_nodes[i].m_is_used) {
            new (&g_asfs_file_nodes[i]) ASFSFileNode();
            g_asfs_file_nodes[i].m_is_used = true;
            g_asfs_file_nodes[i].initialize(fs, inode_block, inode);
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

bool is_path_protected(const char* path) {
    if (!path) return false;
    while (*path == '/') path++;
    if (strncmp(path, "system", 6) == 0) {
        if (path[6] == '\0' || path[6] == '/') return true;
    }
    if (strncmp(path, "vendor", 6) == 0) {
        if (path[6] == '\0' || path[6] == '/') return true;
    }
    return false;
}

ASFSFileSystem::ASFSFileSystem(BlockDevice* device) : m_device(device) {
    memset(&m_sb, 0, sizeof(m_sb));
}

vfs::Node* ASFSFileSystem::open(const char* path, u64 flags) {
    if (!path || !m_device) return nullptr;
    const char* p = path;
    while (*p == '/') p++;

    if (flags & 0x40) { // O_CREAT
        // Prevent creation inside read-only namespaces
        if (is_path_protected(path)) {
            hal::serial_print("ASFS Error: Block creation on protected partition!\n");
            return nullptr;
        }

        // Check if file already exists
        vfs::Node* existing = open_internal(m_sb.root_inode, p, 0);
        if (existing) {
            return existing;
        }

        // Create the file!
        if (!create_file(path, 0755)) {
            hal::serial_print("ASFS Error: Failed to create file!\n");
            return nullptr;
        }
    }

    return open_internal(m_sb.root_inode, p, flags);
}

vfs::Node* ASFSFileSystem::open_internal(u64 inode_block, const char* path, u64 flags [[maybe_unused]]) {
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
        return allocate_asfs_file_node(this, inode_block, inode);
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
                        return open_internal(entries[i].inode_number, remaining, flags);
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
                        return allocate_asfs_file_node(this, target_inode_block, target_inode);
                    }
                }
            }
        }
    }

    return nullptr;
}

bool ASFSFileSystem::create_file(const char* path, u64 mode) {
    char parent_path[512];
    char file_name[64];

    int last_slash = -1;
    int idx = 0;
    while (path[idx]) {
        if (path[idx] == '/') last_slash = idx;
        idx++;
    }

    if (last_slash == -1) {
        parent_path[0] = '\0';
        usize f_len = strlen(path);
        if (f_len > 63) f_len = 63;
        memcpy(file_name, path, f_len);
        file_name[f_len] = '\0';
    } else {
        memcpy(parent_path, path, last_slash);
        parent_path[last_slash] = '\0';
        const char* fname = path + last_slash + 1;
        usize f_len = strlen(fname);
        if (f_len > 63) f_len = 63;
        memcpy(file_name, fname, f_len);
        file_name[f_len] = '\0';
    }

    u64 parent_inode_block = m_sb.root_inode;
    if (parent_path[0] != '\0') {
        const char* p = parent_path;
        while (*p == '/') p++;
        parent_inode_block = find_inode_block(m_sb.root_inode, p);
        if (parent_inode_block == 0) return false;
    }

    // Allocate 1 block for the file's Inode
    u64 new_file_inode = allocate_blocks(1);
    if (new_file_inode == 0) return false;

    ASFSInode file_inode;
    memset(&file_inode, 0, sizeof(ASFSInode));
    file_inode.inode_number = (u32)new_file_inode;
    file_inode.type = 1; // File
    file_inode.size = 0;
    file_inode.permissions = (u32)mode;

    if (m_device->write_block(new_file_inode, &file_inode) != 0) {
        deallocate_blocks(new_file_inode, 1);
        return false;
    }

    if (!insert_dir_entry(parent_inode_block, file_name, 1, new_file_inode)) {
        deallocate_blocks(new_file_inode, 1);
        return false;
    }

    return true;
}

bool ASFSFileSystem::mkdir(const char* path) {
    if (!path || path[0] == '\0') return false;
    if (is_path_protected(path)) return false;

    char parent_path[512];
    char dir_name[64];

    int last_slash = -1;
    int idx = 0;
    while (path[idx]) {
        if (path[idx] == '/') last_slash = idx;
        idx++;
    }

    if (last_slash == -1) {
        parent_path[0] = '\0';
        usize f_len = strlen(path);
        if (f_len > 63) f_len = 63;
        memcpy(dir_name, path, f_len);
        dir_name[f_len] = '\0';
    } else {
        memcpy(parent_path, path, last_slash);
        parent_path[last_slash] = '\0';
        const char* fname = path + last_slash + 1;
        usize f_len = strlen(fname);
        if (f_len > 63) f_len = 63;
        memcpy(dir_name, fname, f_len);
        dir_name[f_len] = '\0';
    }

    u64 parent_inode_block = m_sb.root_inode;
    if (parent_path[0] != '\0') {
        const char* p = parent_path;
        while (*p == '/') p++;
        parent_inode_block = find_inode_block(m_sb.root_inode, p);
        if (parent_inode_block == 0) return false;
    }

    if (find_inode_block(parent_inode_block, dir_name) != 0) return false; // Duplicate name

    u64 new_dir_inode = allocate_blocks(1);
    if (new_dir_inode == 0) return false;

    u64 new_dir_data = allocate_blocks(1);
    if (new_dir_data == 0) {
        deallocate_blocks(new_dir_inode, 1);
        return false;
    }

    u8 empty_block[512] = {0};
    if (m_device->write_block(new_dir_data, empty_block) != 0) {
        deallocate_blocks(new_dir_inode, 1);
        deallocate_blocks(new_dir_data, 1);
        return false;
    }

    ASFSInode dir_inode;
    memset(&dir_inode, 0, sizeof(ASFSInode));
    dir_inode.inode_number = (u32)new_dir_inode;
    dir_inode.type = 2; // Directory
    dir_inode.size = 512;
    dir_inode.permissions = 0755;
    dir_inode.extents[0].start_block = new_dir_data;
    dir_inode.extents[0].block_count = 1;

    if (m_device->write_block(new_dir_inode, &dir_inode) != 0) {
        deallocate_blocks(new_dir_inode, 1);
        deallocate_blocks(new_dir_data, 1);
        return false;
    }

    if (!insert_dir_entry(parent_inode_block, dir_name, 2, new_dir_inode)) {
        deallocate_blocks(new_dir_inode, 1);
        deallocate_blocks(new_dir_data, 1);
        return false;
    }

    return true;
}

bool ASFSFileSystem::unlink(const char* path) {
    if (!path || path[0] == '\0') return false;
    if (is_path_protected(path)) return false;

    char parent_path[512];
    char file_name[64];

    int last_slash = -1;
    int idx = 0;
    while (path[idx]) {
        if (path[idx] == '/') last_slash = idx;
        idx++;
    }

    if (last_slash == -1) {
        parent_path[0] = '\0';
        usize f_len = strlen(path);
        if (f_len > 63) f_len = 63;
        memcpy(file_name, path, f_len);
        file_name[f_len] = '\0';
    } else {
        memcpy(parent_path, path, last_slash);
        parent_path[last_slash] = '\0';
        const char* fname = path + last_slash + 1;
        usize f_len = strlen(fname);
        if (f_len > 63) f_len = 63;
        memcpy(file_name, fname, f_len);
        file_name[f_len] = '\0';
    }

    u64 parent_inode_block = m_sb.root_inode;
    if (parent_path[0] != '\0') {
        const char* p = parent_path;
        while (*p == '/') p++;
        parent_inode_block = find_inode_block(m_sb.root_inode, p);
        if (parent_inode_block == 0) return false;
    }

    u64 file_inode_block = find_inode_block(parent_inode_block, file_name);
    if (file_inode_block == 0) return false;

    u8 inode_buf[512];
    if (m_device->read_block(file_inode_block, inode_buf) != 0) return false;
    ASFSInode file_inode;
    memcpy(&file_inode, inode_buf, sizeof(ASFSInode));

    if (file_inode.type != 1) return false; // Not a file

    // Deallocate blocks
    for (int e = 0; e < 6; e++) {
        if (file_inode.extents[e].block_count > 0) {
            deallocate_blocks(file_inode.extents[e].start_block, file_inode.extents[e].block_count);
        }
    }
    deallocate_blocks(file_inode_block, 1);

    remove_dir_entry(parent_inode_block, file_name);
    return true;
}

bool ASFSFileSystem::rmdir(const char* path) {
    if (!path || path[0] == '\0') return false;
    if (is_path_protected(path)) return false;

    char parent_path[512];
    char dir_name[64];

    int last_slash = -1;
    int idx = 0;
    while (path[idx]) {
        if (path[idx] == '/') last_slash = idx;
        idx++;
    }

    if (last_slash == -1) {
        parent_path[0] = '\0';
        usize f_len = strlen(path);
        if (f_len > 63) f_len = 63;
        memcpy(dir_name, path, f_len);
        dir_name[f_len] = '\0';
    } else {
        memcpy(parent_path, path, last_slash);
        parent_path[last_slash] = '\0';
        const char* fname = path + last_slash + 1;
        usize f_len = strlen(fname);
        if (f_len > 63) f_len = 63;
        memcpy(dir_name, fname, f_len);
        dir_name[f_len] = '\0';
    }

    u64 parent_inode_block = m_sb.root_inode;
    if (parent_path[0] != '\0') {
        const char* p = parent_path;
        while (*p == '/') p++;
        parent_inode_block = find_inode_block(m_sb.root_inode, p);
        if (parent_inode_block == 0) return false;
    }

    u64 dir_inode_block = find_inode_block(parent_inode_block, dir_name);
    if (dir_inode_block == 0 || dir_inode_block == m_sb.root_inode) return false;

    u8 inode_buf[512];
    if (m_device->read_block(dir_inode_block, inode_buf) != 0) return false;
    ASFSInode dir_inode;
    memcpy(&dir_inode, inode_buf, sizeof(ASFSInode));

    if (dir_inode.type != 2) return false;

    // Verify empty
    u8 block_buf[512];
    for (int e = 0; e < 6; e++) {
        if (dir_inode.extents[e].block_count == 0) break;
        for (u32 b = 0; b < dir_inode.extents[e].block_count; b++) {
            u64 physical_block = dir_inode.extents[e].start_block + b;
            if (m_device->read_block(physical_block, block_buf) != 0) return false;
            ASFSDirectoryEntry* entries = (ASFSDirectoryEntry*)block_buf;
            for (int i = 0; i < 8; i++) {
                if (entries[i].inode_number != 0) return false;
            }
        }
    }

    // Deallocate entries and inode
    for (int e = 0; e < 6; e++) {
        if (dir_inode.extents[e].block_count > 0) {
            deallocate_blocks(dir_inode.extents[e].start_block, dir_inode.extents[e].block_count);
        }
    }
    deallocate_blocks(dir_inode_block, 1);

    remove_dir_entry(parent_inode_block, dir_name);
    return true;
}

u64 ASFSFileSystem::find_inode_block(u64 inode_block, const char* path) {
    u64 total_blocks = m_device->capacity() / 512;
    if (inode_block == 0 || inode_block >= total_blocks) return 0;

    u8 inode_buf[512];
    if (m_device->read_block(inode_block, inode_buf) != 0) return 0;

    ASFSInode inode;
    memcpy(&inode, inode_buf, sizeof(ASFSInode));

    const char* p = path;
    while (*p == '/') p++;
    if (*p == '\0') return inode_block;

    char component[256];
    int comp_idx = 0;
    while (p[comp_idx] && p[comp_idx] != '/') {
        if (comp_idx < 255) {
            component[comp_idx] = p[comp_idx];
            comp_idx++;
        } else return 0;
    }
    component[comp_idx] = '\0';
    const char* remaining = p + comp_idx;
    while (*remaining == '/') remaining++;

    if (inode.type != 2) return 0;

    u8 dir_block_buf[512];
    for (int e = 0; e < 6; e++) {
        if (inode.extents[e].block_count == 0) break;

        for (u32 b = 0; b < inode.extents[e].block_count; b++) {
            u64 physical_block = inode.extents[e].start_block + b;
            if (physical_block >= total_blocks) return 0;

            if (m_device->read_block(physical_block, dir_block_buf) != 0) return 0;

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
                        return find_inode_block(entries[i].inode_number, remaining);
                    }
                    return entries[i].inode_number;
                }
            }
        }
    }
    return 0;
}

bool ASFSFileSystem::insert_dir_entry(u64 dir_inode_block, const char* name, u8 type, u64 target_inode_block) {
    u8 inode_buf[512];
    if (m_device->read_block(dir_inode_block, inode_buf) != 0) return false;
    ASFSInode inode;
    memcpy(&inode, inode_buf, sizeof(ASFSInode));

    u8 block_buf[512];
    for (int e = 0; e < 6; e++) {
        if (inode.extents[e].block_count == 0) {
            // Allocate a new block for directory records
            u64 new_block = allocate_blocks(1);
            if (new_block == 0) return false;
            memset(block_buf, 0, 512);
            if (m_device->write_block(new_block, block_buf) != 0) {
                deallocate_blocks(new_block, 1);
                return false;
            }

            inode.extents[e].start_block = new_block;
            inode.extents[e].block_count = 1;
            inode.size += 512;
            if (m_device->write_block(dir_inode_block, &inode) != 0) return false;
        }

        for (u32 b = 0; b < inode.extents[e].block_count; b++) {
            u64 physical_block = inode.extents[e].start_block + b;
            if (m_device->read_block(physical_block, block_buf) != 0) return false;

            ASFSDirectoryEntry* entries = (ASFSDirectoryEntry*)block_buf;
            for (int i = 0; i < 8; i++) {
                if (entries[i].inode_number == 0) {
                    // Empty slot found!
                    entries[i].inode_number = (u32)target_inode_block;
                    entries[i].type = type;
                    usize name_len = strlen(name);
                    if (name_len > 57) name_len = 57;
                    entries[i].name_len = (u8)name_len;
                    memcpy(entries[i].name, name, name_len);
                    entries[i].name[name_len] = '\0';

                    return (m_device->write_block(physical_block, block_buf) == 0);
                }
            }
        }
    }
    return false;
}

bool ASFSFileSystem::remove_dir_entry(u64 dir_inode_block, const char* name) {
    u8 inode_buf[512];
    if (m_device->read_block(dir_inode_block, inode_buf) != 0) return false;
    ASFSInode inode;
    memcpy(&inode, inode_buf, sizeof(ASFSInode));

    u8 block_buf[512];
    for (int e = 0; e < 6; e++) {
        if (inode.extents[e].block_count == 0) break;
        for (u32 b = 0; b < inode.extents[e].block_count; b++) {
            u64 physical_block = inode.extents[e].start_block + b;
            if (m_device->read_block(physical_block, block_buf) != 0) return false;

            ASFSDirectoryEntry* entries = (ASFSDirectoryEntry*)block_buf;
            for (int i = 0; i < 8; i++) {
                if (entries[i].inode_number != 0) {
                    char entry_name[64];
                    usize n_len = entries[i].name_len;
                    if (n_len > 57) n_len = 57;
                    memcpy(entry_name, entries[i].name, n_len);
                    entry_name[n_len] = '\0';

                    if (strcmp_nocase(entry_name, name) == 0) {
                        memset(&entries[i], 0, sizeof(ASFSDirectoryEntry));
                        return (m_device->write_block(physical_block, block_buf) == 0);
                    }
                }
            }
        }
    }
    return false;
}

u64 ASFSFileSystem::allocate_blocks(u32 count) {
    if (count == 0 || !m_device || m_sb.free_space_root == 0) return 0;

    u8 bitmap_buf[512];
    u64 total_blocks = m_device->capacity() / 512;
    u64 blocks_found = 0;
    u64 starting_block = 0;

    // Scan the 16 bitmap blocks starting at free_space_root
    for (u64 bm_offset = 0; bm_offset < 16; bm_offset++) {
        u64 bm_block = m_sb.free_space_root + bm_offset;
        if (m_device->read_block(bm_block, bitmap_buf) != 0) return 0;

        for (u32 byte_idx = 0; byte_idx < 512; byte_idx++) {
            u8 b = bitmap_buf[byte_idx];
            for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
                u64 block_num = (bm_offset * 512 + byte_idx) * 8 + bit_idx;
                if (block_num >= total_blocks) break;

                bool allocated = (b & (1 << bit_idx)) != 0;
                if (!allocated) {
                    if (blocks_found == 0) {
                        starting_block = block_num;
                    }
                    blocks_found++;
                    if (blocks_found == count) {
                        // Mark all blocks_found contiguous blocks as allocated (set to 1)
                        for (u64 allocated_block = starting_block; allocated_block < starting_block + count; allocated_block++) {
                            u64 chunk_bm_offset = (allocated_block / 8) / 512;
                            u32 chunk_byte_idx = (allocated_block / 8) % 512;
                            u32 chunk_bit_idx = allocated_block % 8;

                            u64 active_bm_block = m_sb.free_space_root + chunk_bm_offset;
                            u8 active_bm_buf[512];
                            if (m_device->read_block(active_bm_block, active_bm_buf) != 0) return 0;

                            active_bm_buf[chunk_byte_idx] |= (1 << chunk_bit_idx);
                            if (m_device->write_block(active_bm_block, active_bm_buf) != 0) return 0;
                        }

                        if (m_sb.free_blocks >= count) m_sb.free_blocks -= count;
                        flush_superblock();
                        return starting_block;
                    }
                } else {
                    blocks_found = 0;
                }
            }
        }
    }

    return 0; // Out of space
}

void ASFSFileSystem::deallocate_blocks(u64 start_block, u32 count) {
    if (count == 0 || !m_device || m_sb.free_space_root == 0) return;

    u8 bitmap_buf[512];
    for (u64 block_num = start_block; block_num < start_block + count; block_num++) {
        u64 chunk_bm_offset = (block_num / 8) / 512;
        u32 chunk_byte_idx = (block_num / 8) % 512;
        u32 chunk_bit_idx = block_num % 8;

        u64 active_bm_block = m_sb.free_space_root + chunk_bm_offset;
        if (m_device->read_block(active_bm_block, bitmap_buf) != 0) return;

        bitmap_buf[chunk_byte_idx] &= ~(1 << chunk_bit_idx);
        if (m_device->write_block(active_bm_block, bitmap_buf) != 0) return;
    }

    m_sb.free_blocks += count;
    flush_superblock();
}

void ASFSFileSystem::flush_superblock() {
    if (!m_device) return;
    m_device->write_block(0, &m_sb);
    u64 last_block = m_device->capacity() / 512 - 1;
    m_device->write_block(last_block, &m_sb);
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

    // Additional critical metadata validation
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
