#!/usr/bin/env python3
import struct
import binascii
import os

# GUID Bytes matching partition.cpp
ESP_GUID = bytes([
    0x28, 0x73, 0x2A, 0xC1, 0x1F, 0xF8, 0xD2, 0x11,
    0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B
])
ASFS_GUID = bytes([
    0x53, 0x41, 0xA5, 0xA5, 0x53, 0x46, 0x53, 0x4F,
    0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5
])

def crc32_unsigned(data):
    return binascii.crc32(data) & 0xFFFFFFFF

def build_protective_mbr():
    mbr = bytearray(512)
    # Entry 1 at offset 446
    # Boot indicator: 0x00, Start CHS: 0x000200, Type: 0xEE, End CHS: 0xFFFFFF, Start LBA: 1, Size: 131071 (total blocks - 1)
    struct.pack_into("<B3sB3sII", mbr, 446, 0x00, b"\x00\x02\x00", 0xEE, b"\xff\xff\xff", 1, 131071)
    # Magic
    mbr[510] = 0x55
    mbr[511] = 0xAA
    return mbr

def build_gpt_header(current_lba, backup_lba, entries_lba, entries_crc, disk_guid):
    header = bytearray(92)
    struct.pack_into(
        "<8sIIIIQQQQ16sQIII",
        header, 0,
        b"EFI PART",       # Signature
        0x00010000,       # Revision (1.0)
        92,               # Header Size
        0,                # Header CRC (initially 0)
        0,                # Reserved
        current_lba,      # Current LBA
        backup_lba,       # Backup LBA
        34,               # First usable LBA
        131038,           # Last usable LBA
        disk_guid,        # Disk GUID
        entries_lba,      # Partition Entries LBA
        128,              # Number of partition entries
        128,              # Size of each partition entry
        entries_crc       # Partition Entries CRC
    )
    # Calculate CRC of header itself
    header_crc = crc32_unsigned(header)
    struct.pack_into("<I", header, 16, header_crc)
    # Pad to 512 bytes
    return header + bytes(512 - 92)

def build_gpt_entry(type_guid, unique_guid, start_lba, end_lba, name):
    entry = bytearray(128)
    struct.pack_into("<16s16sQQQ", entry, 0, type_guid, unique_guid, start_lba, end_lba, 0)
    # Encode partition name as UTF-16LE
    name_bytes = name.encode("utf-16le")[:72]
    entry[56:56+len(name_bytes)] = name_bytes
    return entry

def create_fat32_image():
    # Construct a minimal FAT32 filesystem (32MB, 65536 sectors)
    fat_data = bytearray(65536 * 512)

    # 1. Boot Sector (LBA 0 of partition)
    # Total sectors = 65536, Sectors per Cluster = 8, Reserved sectors = 32, Number of FATs = 2, Sectors per FAT = 64
    boot = bytearray(512)
    boot[0:3] = b"\xEB\x58\x90"
    boot[3:11] = b"MSWIN4.1"
    struct.pack_into("<HBHBHHBHHHII", boot, 11, 512, 8, 32, 2, 0, 0, 0xF8, 0, 32, 64, 2048, 65536)
    # FAT32 specific fields: Sectors per FAT = 64, Mirror flags = 0, Version = 0, Root Cluster = 2, FSInfo = 1, BackupBoot = 6
    struct.pack_into("<IHHIIH", boot, 36, 64, 0, 0, 2, 1, 6)
    # Extended bios parameters
    boot[64] = 0x80 # Drive
    boot[66] = 0x29 # Signature
    struct.pack_into("<I11s8s", boot, 67, 0x12345678, b"ACOS_BOOT  ", b"FAT32   ")
    boot[510] = 0x55
    boot[511] = 0xAA
    fat_data[0:512] = boot
    fat_data[6 * 512 : 7 * 512] = boot # Backup Boot sector

    # 2. FSInfo Sector (LBA 1 of partition)
    fsinfo = bytearray(512)
    struct.pack_into("<II480sII", fsinfo, 0, 0x41615252, 0x61417272, b"\x00" * 480, 0xFFFFFFFF, 3)
    fsinfo[510] = 0x55
    fsinfo[511] = 0xAA
    fat_data[1 * 512 : 2 * 512] = fsinfo
    fat_data[7 * 512 : 8 * 512] = fsinfo # Backup FSInfo

    # 3. File Allocation Tables (FAT 1 at sector 32, FAT 2 at sector 96)
    fat1_offset = 32 * 512
    fat2_offset = 96 * 512

    # FAT entries 0 and 1
    struct.pack_into("<II", fat_data, fat1_offset, 0x0FFFFFF8, 0x0FFFFFFF)
    struct.pack_into("<II", fat_data, fat2_offset, 0x0FFFFFF8, 0x0FFFFFFF)

    # Cluster Allocator
    current_cluster = 2

    def allocate_clusters(num_clusters):
        nonlocal current_cluster
        start = current_cluster
        for i in range(num_clusters - 1):
            struct.pack_into("<I", fat_data, fat1_offset + (current_cluster + i) * 4, current_cluster + i + 1)
            struct.pack_into("<I", fat_data, fat2_offset + (current_cluster + i) * 4, current_cluster + i + 1)
        # End of chain
        struct.pack_into("<I", fat_data, fat1_offset + (current_cluster + num_clusters - 1) * 4, 0x0FFFFFFF)
        struct.pack_into("<I", fat_data, fat2_offset + (current_cluster + num_clusters - 1) * 4, 0x0FFFFFFF)
        current_cluster += num_clusters
        return start

    def write_cluster_data(cluster, data):
        cluster_offset = (32 + 2 * 64 + (cluster - 2) * 8) * 512
        fat_data[cluster_offset : cluster_offset + len(data)] = data

    # Root Directory (Cluster 2) - 1 cluster allocated
    allocate_clusters(1)

    # Subdirectory 'EFI' (Cluster 3) - 1 cluster allocated
    efi_cluster = allocate_clusters(1)

    # Subdirectory 'BOOT' (Cluster 4) - 1 cluster allocated
    boot_cluster = allocate_clusters(1)

    # Read bootloader and kernel binaries from host dist folder
    boot_efi = b""
    if os.path.exists("acos_boot.efi"):
        with open("acos_boot.efi", "rb") as f:
            boot_efi = f.read()

    kernel_elf = b""
    if os.path.exists("kernel.elf"):
        with open("kernel.elf", "rb") as f:
            kernel_elf = f.read()

    # Allocate clusters for BOOTX64.EFI
    boot_efi_size = len(boot_efi)
    boot_efi_clusters = max(1, (boot_efi_size + 4095) // 4096)
    boot_efi_start = allocate_clusters(boot_efi_clusters)
    write_cluster_data(boot_efi_start, boot_efi)

    # Allocate clusters for kernel.elf
    kernel_size = len(kernel_elf)
    kernel_clusters = max(1, (kernel_size + 4095) // 4096)
    kernel_start = allocate_clusters(kernel_clusters)
    write_cluster_data(kernel_start, kernel_elf)

    # Populate directory entries using correct "<11sBBBHHHHHHHI" layout
    # 1. Root Directory (contains 'EFI' and 'kernel.elf')
    root_dir = bytearray(4096) # 1 cluster

    # 'EFI' entry
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        root_dir, 0,
        b"EFI        ", # name
        0x10,           # attr (directory)
        0, 0, 0, 0, 0,  # NTRes, CrtTimeTenth, CrtTime, CrtDate, LstAccDate
        (efi_cluster >> 16) & 0xFFFF, # FstClusHI
        0, 0,           # WrtTime, WrtDate
        efi_cluster & 0xFFFF, # FstClusLO
        0               # FileSize
    )

    # 'kernel.elf' entry
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        root_dir, 32,
        b"KERNEL  ELF", # name
        0x20,           # attr (archive)
        0, 0, 0, 0, 0,  # NTRes, CrtTimeTenth, CrtTime, CrtDate, LstAccDate
        (kernel_start >> 16) & 0xFFFF, # FstClusHI
        0, 0,           # WrtTime, WrtDate
        kernel_start & 0xFFFF, # FstClusLO
        kernel_size     # FileSize
    )
    write_cluster_data(2, root_dir)

    # 2. 'EFI' Directory (contains 'BOOT')
    efi_dir = bytearray(4096)
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        efi_dir, 0,
        b"BOOT       ", # name
        0x10,           # attr (directory)
        0, 0, 0, 0, 0,
        (boot_cluster >> 16) & 0xFFFF,
        0, 0,
        boot_cluster & 0xFFFF,
        0
    )
    write_cluster_data(efi_cluster, efi_dir)

    # 3. 'BOOT' Directory (contains 'BOOTX64.EFI')
    boot_dir_b = bytearray(4096)
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        boot_dir_b, 0,
        b"BOOTX64 EFI", # name
        0x20,           # attr (archive)
        0, 0, 0, 0, 0,
        (boot_efi_start >> 16) & 0xFFFF,
        0, 0,
        boot_efi_start & 0xFFFF,
        boot_efi_size
    )
    write_cluster_data(boot_cluster, boot_dir_b)

    return fat_data

def create_asfs_image():
    # Construct a production-grade ASFS filesystem (31MB, 63455 sectors)
    asfs_data = bytearray(63455 * 512)

    # Read binary files from dist folder
    cli_elf_bytes = b""
    if os.path.exists("build/dist/bin/cli.elf"):
        with open("build/dist/bin/cli.elf", "rb") as f:
            cli_elf_bytes = f.read()
    else:
        cli_elf_bytes = b"\x7fELF64_MOCK_CLI_SHELL_BINARY_FALLBACK\n"

    desktop_elf_bytes = b""
    if os.path.exists("build/dist/bin/desktop.elf"):
        with open("build/dist/bin/desktop.elf", "rb") as f:
            desktop_elf_bytes = f.read()
    else:
        desktop_elf_bytes = b"\x7fELF64_MOCK_DESKTOP_SHELL_BINARY_FALLBACK\n"

    cli_size = len(cli_elf_bytes)
    cli_blocks = (cli_size + 511) // 512

    desktop_size = len(desktop_elf_bytes)
    desktop_blocks = (desktop_size + 511) // 512

    # 1. Superblock (Block 0)
    sb = bytearray(512)
    struct.pack_into(
        "<QIIQQQQ16sQQQII",
        sb, 0,
        0x415346535F4F535F, # magic
        1,                  # version
        512,                # block_size
        63455,              # total_blocks
        60000,              # free_blocks
        1,                  # root_inode
        1,                  # transaction_id
        b"\xab" * 16,       # uuid
        0, 0, 20,           # reserved roots (free_space_root = 20)
        0,                  # feature_flags
        0x12345678          # checksum
    )
    asfs_data[0:512] = sb
    asfs_data[63454 * 512 : 63455 * 512] = sb # Redundant copy at last block

    # 2. Build and populate the initial Writable Free-Space Bitmap (Blocks 20 to 35)
    bitmap = bytearray(16 * 512)
    def mark_allocated(block_num):
        byte_idx = block_num // 8
        bit_idx = block_num % 8
        bitmap[byte_idx] |= (1 << bit_idx)

    # Superblock, Root Inode, and structural blocks 0 to 19
    for b in range(20):
        mark_allocated(b)

    # Free Space Bitmap blocks 20 to 35
    for b in range(20, 36):
        mark_allocated(b)

    # Inode blocks (15 and 17)
    mark_allocated(15)
    mark_allocated(17)

    # cli.elf data blocks
    for b in range(100, 100 + cli_blocks):
        mark_allocated(b)

    # desktop.elf data blocks
    for b in range(100 + cli_blocks, 100 + cli_blocks + desktop_blocks):
        mark_allocated(b)

    # Redundant superblock block
    mark_allocated(63454)

    # Copy free-space bitmap blocks directly into our data block allocation
    asfs_data[20 * 512 : 36 * 512] = bitmap

    # Inode layout pack string: <IIQIII (inode_number, type, size, owner_uid, group_gid, permissions) -> followed by flags (I), extents (6 * QQI), indirect_block (Q)
    def pack_inode(inode_number, type_code, size, permissions, extents):
        buf = bytearray(512)
        struct.pack_into("<IIQIII", buf, 0, inode_number, type_code, size, 0, 0, permissions)
        struct.pack_into("<I", buf, 28, 0) # flags
        for i in range(min(len(extents), 6)):
            start, count = extents[i]
            # Pack extent at 32 + i * 16
            struct.pack_into("<QII", buf, 32 + i * 16, start, count, 0)
        struct.pack_into("<Q", buf, 128, 0) # indirect block
        return buf

    def pack_dir_entry(inode, type_code, name):
        buf = bytearray(64)
        name_bytes = name.encode("ascii")[:57]
        struct.pack_into("<IBB58s", buf, 0, inode, type_code, len(name_bytes), name_bytes)
        return buf

    # Block 1: Root Inode (points to Block 2)
    asfs_data[1 * 512 : 2 * 512] = pack_inode(1, 2, 512, 0o755, [(2, 1)])

    # Block 2: Root Directory entries
    root_block = bytearray(512)
    root_block[0:64] = pack_dir_entry(3, 2, "system")
    root_block[64:128] = pack_dir_entry(5, 2, "vendor")
    root_block[128:192] = pack_dir_entry(7, 2, "apps")
    root_block[192:256] = pack_dir_entry(9, 2, "data")
    asfs_data[2 * 512 : 3 * 512] = root_block

    # Block 3: /system Inode (points to Block 4)
    asfs_data[3 * 512 : 4 * 512] = pack_inode(3, 2, 512, 0o755, [(4, 1)])

    # Block 4: /system directory entries
    sys_block = bytearray(512)
    sys_block[0:64] = pack_dir_entry(11, 2, "bin")
    sys_block[64:128] = pack_dir_entry(13, 2, "lib")
    asfs_data[4 * 512 : 5 * 512] = sys_block

    # Block 5: /vendor Inode (points to Block 6)
    asfs_data[5 * 512 : 6 * 512] = pack_inode(5, 2, 512, 0o755, [(6, 1)])
    # Block 6: /vendor empty records
    asfs_data[6 * 512 : 7 * 512] = bytearray(512)

    # Block 7: /apps Inode (points to Block 8)
    asfs_data[7 * 512 : 8 * 512] = pack_inode(7, 2, 512, 0o755, [(8, 1)])
    # Block 8: /apps empty records
    asfs_data[8 * 512 : 9 * 512] = bytearray(512)

    # Block 9: /data Inode (points to Block 10)
    asfs_data[9 * 512 : 10 * 512] = pack_inode(9, 2, 512, 0o755, [(10, 1)])
    # Block 10: /data empty records
    asfs_data[10 * 512 : 11 * 512] = bytearray(512)

    # Block 11: /system/bin Inode (points to Block 12)
    asfs_data[11 * 512 : 12 * 512] = pack_inode(11, 2, 512, 0o755, [(12, 1)])

    # Block 12: /system/bin entries
    bin_block = bytearray(512)
    bin_block[0:64] = pack_dir_entry(15, 1, "cli.elf")
    bin_block[64:128] = pack_dir_entry(17, 1, "desktop.elf")
    asfs_data[12 * 512 : 13 * 512] = bin_block

    # Block 13: /system/lib Inode (points to Block 14)
    asfs_data[13 * 512 : 14 * 512] = pack_inode(13, 2, 512, 0o755, [(14, 1)])
    # Block 14: /system/lib empty records
    asfs_data[14 * 512 : 15 * 512] = bytearray(512)

    # Block 15: /system/bin/cli.elf Inode
    asfs_data[15 * 512 : 16 * 512] = pack_inode(15, 1, cli_size, 0o755, [(100, cli_blocks)])

    # Block 17: /system/bin/desktop.elf Inode
    asfs_data[17 * 512 : 18 * 512] = pack_inode(17, 1, desktop_size, 0o755, [(100 + cli_blocks, desktop_blocks)])

    # Write binary contents
    cli_start_offset = 100 * 512
    asfs_data[cli_start_offset : cli_start_offset + cli_size] = cli_elf_bytes

    desktop_start_offset = (100 + cli_blocks) * 512
    asfs_data[desktop_start_offset : desktop_start_offset + desktop_size] = desktop_elf_bytes

    return asfs_data

def build_full_disk_image():
    # 64MB disk image = 131072 sectors
    disk = bytearray(131072 * 512)

    # 1. Protective MBR at Sector 0
    disk[0:512] = build_protective_mbr()

    # Generate partition contents
    fat32_partition_data = create_fat32_image()
    asfs_partition_data = create_asfs_image()

    # Write ASFS Partition standalone file for offline testing
    with open("asfs_test.img", "wb") as f:
        f.write(asfs_partition_data)
    print("Success: Generated standalone asfs_test.img!")

    # Write partition data to disk image
    # Partition 1 starts at LBA 2048, size = 65536 sectors
    disk[2048 * 512 : 2048 * 512 + len(fat32_partition_data)] = fat32_partition_data

    # Partition 2 starts at LBA 67584, size = 63455 sectors
    disk[67584 * 512 : 67584 * 512 + len(asfs_partition_data)] = asfs_partition_data

    # 2. Build GPT entries block (Sectors 2 to 33)
    entries = bytearray(32 * 512)
    # Entry 1: FAT32 Partition
    # Partition 1 starts at LBA 2048, ends at LBA 67583 (inclusive)
    entries[0:128] = build_gpt_entry(
        ESP_GUID,
        b"\x11" * 16,
        2048,
        67583,
        "EFI System Partition"
    )
    # Entry 2: ASFS Partition
    # Partition 2 starts at LBA 67584, ends at LBA 131038 (inclusive)
    entries[128:256] = build_gpt_entry(
        ASFS_GUID,
        b"\x22" * 16,
        67584,
        131038,
        "ASFS System"
    )

    entries_crc = crc32_unsigned(entries)
    disk[2 * 512 : 34 * 512] = entries # Primary entries table
    disk[131039 * 512 : 131071 * 512] = entries # Backup entries table (last 32 blocks before backup header)

    # 3. GPT Header at LBA 1 (and backup at LBA 131071)
    disk_guid = b"\xde\xad\xbe\xef" * 4
    primary_header = build_gpt_header(1, 131071, 2, entries_crc, disk_guid)
    disk[1 * 512 : 2 * 512] = primary_header

    backup_header = build_gpt_header(131071, 1, 131039, entries_crc, disk_guid)
    disk[131071 * 512 : 131072 * 512] = backup_header

    # Save complete GPT disk image
    with open("acos.img", "wb") as f:
        f.write(disk)
    print("Success: Generated partitioned acos.img disk image!")

if __name__ == "__main__":
    build_full_disk_image()
