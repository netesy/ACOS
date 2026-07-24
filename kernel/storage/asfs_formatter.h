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
        sb->free_blocks = sb->total_blocks - 100; // Mock free blocks count
        sb->root_inode = 1; // Root directory inode is in Block 1
        sb->transaction_id = 1;
        memset(sb->uuid, 0xAB, 16);
        sb->inode_tree_root = 0;   // Reserved
        sb->extent_tree_root = 0;  // Reserved
        sb->free_space_root = 0;   // Reserved
        sb->feature_flags = 0;     // Initial features
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
        // Let's configure directory layout:
        // - system (Directory, Inode in Block 3)
        // - data (Directory, Inode in Block 5)
        memset(block_buf, 0, 512);
        ASFSDirectoryEntry* root_entries = (ASFSDirectoryEntry*)block_buf;

        // "system" entry
        root_entries[0].inode_number = 3;
        root_entries[0].type = 2; // Directory
        root_entries[0].name_len = 6;
        memcpy(root_entries[0].name, "system", 6);

        // "data" entry
        root_entries[1].inode_number = 5;
        root_entries[1].type = 2; // Directory
        root_entries[1].name_len = 4;
        memcpy(root_entries[1].name, "data", 4);

        if (disk->write_block(2, block_buf) != 0) return false;

        // 4. system Inode (Block 3)
        memset(block_buf, 0, 512);
        ASFSInode* system_inode = (ASFSInode*)block_buf;
        system_inode->inode_number = 3;
        system_inode->type = 2; // Directory
        system_inode->size = 512;
        system_inode->permissions = 0755;
        system_inode->extents[0].start_block = 4; // Directory entry contents in Block 4
        system_inode->extents[0].block_count = 1;

        if (disk->write_block(3, block_buf) != 0) return false;

        // 5. system entries block (Block 4)
        // Let's configure "system" entries:
        // - bin (Directory, Inode in Block 9)
        memset(block_buf, 0, 512);
        ASFSDirectoryEntry* system_entries = (ASFSDirectoryEntry*)block_buf;

        system_entries[0].inode_number = 9;
        system_entries[0].type = 2; // Directory
        system_entries[0].name_len = 3;
        memcpy(system_entries[0].name, "bin", 3);

        if (disk->write_block(4, block_buf) != 0) return false;

        // 6. data Inode (Block 5)
        memset(block_buf, 0, 512);
        ASFSInode* data_inode = (ASFSInode*)block_buf;
        data_inode->inode_number = 5;
        data_inode->type = 2; // Directory
        data_inode->size = 512;
        data_inode->permissions = 0755;
        data_inode->extents[0].start_block = 6; // Directory entry contents in Block 6
        data_inode->extents[0].block_count = 1;

        if (disk->write_block(5, block_buf) != 0) return false;

        // 7. data entries block (Block 6)
        // Let's configure "data" entries:
        // - apps (Directory, Inode in Block 11)
        memset(block_buf, 0, 512);
        ASFSDirectoryEntry* data_entries = (ASFSDirectoryEntry*)block_buf;

        data_entries[0].inode_number = 11;
        data_entries[0].type = 2; // Directory
        data_entries[0].name_len = 4;
        memcpy(data_entries[0].name, "apps", 4);

        if (disk->write_block(6, block_buf) != 0) return false;

        // 8. system/bin Inode (Block 9)
        memset(block_buf, 0, 512);
        ASFSInode* bin_inode = (ASFSInode*)block_buf;
        bin_inode->inode_number = 9;
        bin_inode->type = 2; // Directory
        bin_inode->size = 512;
        bin_inode->permissions = 0755;
        bin_inode->extents[0].start_block = 10; // Directory entries block 10
        bin_inode->extents[0].block_count = 1;

        if (disk->write_block(9, block_buf) != 0) return false;

        // 9. system/bin entries block (Block 10)
        // Let's add "cli.elf" as a nested file inside "/system/bin/cli.elf":
        // - cli.elf (File, Inode in Block 13)
        memset(block_buf, 0, 512);
        ASFSDirectoryEntry* bin_entries = (ASFSDirectoryEntry*)block_buf;

        bin_entries[0].inode_number = 13;
        bin_entries[0].type = 1; // File
        bin_entries[0].name_len = 7;
        memcpy(bin_entries[0].name, "cli.elf", 7);

        if (disk->write_block(10, block_buf) != 0) return false;

        // 10. data/apps Inode (Block 11)
        memset(block_buf, 0, 512);
        ASFSInode* apps_inode = (ASFSInode*)block_buf;
        apps_inode->inode_number = 11;
        apps_inode->type = 2; // Directory
        apps_inode->size = 512;
        apps_inode->permissions = 0755;
        apps_inode->extents[0].start_block = 12; // Directory entries block 12
        apps_inode->extents[0].block_count = 1;

        if (disk->write_block(11, block_buf) != 0) return false;

        // 11. data/apps entries block (Block 12) - empty for now
        memset(block_buf, 0, 512);
        if (disk->write_block(12, block_buf) != 0) return false;

        // 12. system/bin/cli.elf Inode (Block 13)
        memset(block_buf, 0, 512);
        ASFSInode* cli_inode = (ASFSInode*)block_buf;
        cli_inode->inode_number = 13;
        cli_inode->type = 1; // File
        cli_inode->size = 35; // Correct ELF headers mock size
        cli_inode->permissions = 0755;
        cli_inode->extents[0].start_block = 14; // File contents reside in Block 14
        cli_inode->extents[0].block_count = 1;

        if (disk->write_block(13, block_buf) != 0) return false;

        // 13. system/bin/cli.elf content data block (Block 14)
        // Store standard ELF executable format magic string (\x7fELF)
        memset(block_buf, 0, 512);
        const char* elf_mock = "\x7f" "ELF64_MOCK_EXECUTABLE_ASFS_STABLE\n";
        memcpy(block_buf, elf_mock, 35);

        if (disk->write_block(14, block_buf) != 0) return false;

        return true;
    }
};

} // namespace acos::storage
