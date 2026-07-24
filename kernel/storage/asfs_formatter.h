#pragma once
#include <kernel/storage/asfs.h>
#include <kernel/storage/ramdisk.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::storage {

class ASFSFormatter {
public:
    static bool format_ramdisk(RamDisk* disk) {
        if (!disk) return false;

        u8 block_buf[512];

        // 1. Superblock (Block 0)
        memset(block_buf, 0, 512);
        ASFSSuperblock* sb = (ASFSSuperblock*)block_buf;
        sb->magic = 0x415346535F4F535FULL;
        sb->version = 1;
        sb->block_size = 512;
        sb->total_blocks = disk->capacity() / 512;
        sb->free_blocks = sb->total_blocks - 100;
        sb->root_inode = 1; // Root directory inode is in Block 1
        sb->transaction_id = 1;
        memset(sb->uuid, 0xAB, 16);
        sb->inode_tree_root = 0;   // Reserved
        sb->extent_tree_root = 0;  // Reserved
        sb->free_space_root = 20;  // Writable Free Space Bitmap starts at Block 20!
        sb->feature_flags = 0;
        sb->checksum = 0x12345678;

        if (disk->write_block(0, block_buf) != 0) return false;

        // Write Redundant Superblock copy at the very last block of the device
        u64 last_block = disk->capacity() / 512 - 1;
        if (disk->write_block(last_block, block_buf) != 0) return false;

        // 2. Root Directory Inode (Block 1)
        memset(block_buf, 0, 512);
        ASFSInode* root_inode = (ASFSInode*)block_buf;
        root_inode->inode_number = 1;
        root_inode->type = 2; // Directory
        root_inode->size = 512;
        root_inode->owner_uid = 0;
        root_inode->group_gid = 0;
        root_inode->permissions = 0755;
        root_inode->extents[0].start_block = 2; // Directory entry contents reside in Block 2
        root_inode->extents[0].block_count = 1;

        if (disk->write_block(1, block_buf) != 0) return false;

        // 3. Root Directory entries block (Block 2)
        // Configure writable structure:
        // - apps (Directory, Inode in Block 3)
        // - users (Directory, Inode in Block 5)
        // - shared (Directory, Inode in Block 7)
        memset(block_buf, 0, 512);
        ASFSDirectoryEntry* root_entries = (ASFSDirectoryEntry*)block_buf;

        // "apps" entry
        root_entries[0].inode_number = 3;
        root_entries[0].type = 2;
        root_entries[0].name_len = 4;
        memcpy(root_entries[0].name, "apps", 4);

        // "users" entry
        root_entries[1].inode_number = 5;
        root_entries[1].type = 2;
        root_entries[1].name_len = 5;
        memcpy(root_entries[1].name, "users", 5);

        // "shared" entry
        root_entries[2].inode_number = 7;
        root_entries[2].type = 2;
        root_entries[2].name_len = 6;
        memcpy(root_entries[2].name, "shared", 6);

        if (disk->write_block(2, block_buf) != 0) return false;

        // 4. apps Inode (Block 3)
        memset(block_buf, 0, 512);
        ASFSInode* apps_inode = (ASFSInode*)block_buf;
        apps_inode->inode_number = 3;
        apps_inode->type = 2;
        apps_inode->size = 512;
        apps_inode->permissions = 0755;
        apps_inode->extents[0].start_block = 4;
        apps_inode->extents[0].block_count = 1;

        if (disk->write_block(3, block_buf) != 0) return false;

        // 5. apps entries (Block 4) - empty
        memset(block_buf, 0, 512);
        if (disk->write_block(4, block_buf) != 0) return false;

        // 6. users Inode (Block 5)
        memset(block_buf, 0, 512);
        ASFSInode* users_inode = (ASFSInode*)block_buf;
        users_inode->inode_number = 5;
        users_inode->type = 2;
        users_inode->size = 512;
        users_inode->permissions = 0755;
        users_inode->extents[0].start_block = 6;
        users_inode->extents[0].block_count = 1;

        if (disk->write_block(5, block_buf) != 0) return false;

        // 7. users entries (Block 6) - empty
        memset(block_buf, 0, 512);
        if (disk->write_block(6, block_buf) != 0) return false;

        // 8. shared Inode (Block 7)
        memset(block_buf, 0, 512);
        ASFSInode* shared_inode = (ASFSInode*)block_buf;
        shared_inode->inode_number = 7;
        shared_inode->type = 2;
        shared_inode->size = 512;
        shared_inode->permissions = 0755;
        shared_inode->extents[0].start_block = 8;
        shared_inode->extents[0].block_count = 1;

        if (disk->write_block(7, block_buf) != 0) return false;

        // 9. shared entries (Block 8) - empty
        memset(block_buf, 0, 512);
        if (disk->write_block(8, block_buf) != 0) return false;

        // 10. Write Free-space Bitmap (Blocks 20 to 35)
        memset(block_buf, 0, 512);
        // Mark blocks 0 to 35 as allocated (bits set to 1)
        // In block 20 (first bitmap block), bytes 0 to 4 have bits set
        block_buf[0] = 0xFF; // blocks 0-7
        block_buf[1] = 0xFF; // blocks 8-15
        block_buf[2] = 0xFF; // blocks 16-23
        block_buf[3] = 0xFF; // blocks 24-31
        block_buf[4] = 0x0F; // blocks 32-35 (0b00001111)

        // Write bitmap block 20
        if (disk->write_block(20, block_buf) != 0) return false;

        // Reset buffer and write remaining empty bitmap blocks 21 to 35
        memset(block_buf, 0, 512);
        for (u64 b = 21; b < 36; b++) {
            if (disk->write_block(b, block_buf) != 0) return false;
        }

        return true;
    }
};

} // namespace acos::storage
