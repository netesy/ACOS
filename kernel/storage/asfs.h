#pragma once
#include <kernel/vfs/vfs.h>
#include <kernel/storage/block_device.h>

namespace acos::storage {

// ASFS Extent structure describing contiguous ranges of physical blocks
struct ASFSExtent {
    u64 start_block;        // Start of physical block address
    u32 block_count;        // Count of contiguous blocks in this extent
    u32 reserved;           // Padding/Future metadata
};

// ASFS Superblock on-disk representation
struct ASFSSuperblock {
    u64 magic;              // Magic key: "ASFS_OS_" (0x415346535F4F535FULL)
    u32 version;            // Version (1)
    u32 block_size;         // Block size (e.g. 512 or 4096)
    u64 total_blocks;       // Total blocks in this partition
    u64 free_blocks;        // Total free blocks count
    u64 root_inode;         // Root directory Inode block number
    u64 transaction_id;     // Active transaction sequence ID
    u8 uuid[16];            // Partition UUID
    u64 inode_tree_root;    // Reserved block address for future Inode B-Tree root
    u64 extent_tree_root;   // Reserved block address for future Extents B-Tree root
    u64 free_space_root;    // Reserved block address for future Free Space B-Tree root
    u32 feature_flags;      // Feature configurations mask
    u32 checksum;           // CRC32/Fletcher superblock checksum
};

// ASFS Inode structure (representing a file or directory metadata block)
struct ASFSInode {
    u32 inode_number;
    u32 type;               // 1 = File, 2 = Directory
    u64 size;               // File size in bytes
    u32 owner_uid;
    u32 group_gid;
    u32 permissions;
    u32 flags;
    ASFSExtent extents[6];  // Direct physical range extents
    u64 indirect_block;     // Indirect data blocks pointer (reserved)
};

// ASFS Directory Entry record structure (stored inside direct blocks of Directory inodes)
struct ASFSDirectoryEntry {
    u32 inode_number;       // Target Inode location
    u8 type;                // 1 = File, 2 = Directory
    u8 name_len;            // Filename character length
    char name[58];          // Null-terminated filename characters
};

class ASFSFileSystem final : public vfs::FileSystem {
public:
    ASFSFileSystem() : m_device(nullptr) {}
    ASFSFileSystem(BlockDevice* device);

    vfs::Node* open(const char* path) override;
    bool mount(const char* target) override;
    bool probe(void* device, const char* target) override;

    BlockDevice* device() const { return m_device; }
    const ASFSSuperblock& superblock() const { return m_sb; }

private:
    vfs::Node* open_internal(u64 inode_block, const char* path);

    BlockDevice* m_device;
    ASFSSuperblock m_sb;
};

} // namespace acos::storage
