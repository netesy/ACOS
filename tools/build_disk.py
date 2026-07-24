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
ASFS_DATA_GUID = bytes([
    0x53, 0x41, 0xDA, 0xDA, 0x53, 0x46, 0x53, 0x4F,
    0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA, 0xDA
])

def crc32_unsigned(data):
    return binascii.crc32(data) & 0xFFFFFFFF

def calculate_sb_checksum(sb_block):
    # The superblock struct is the first 96 bytes
    sb_struct = bytearray(sb_block[:96])
    # Clear checksum (last 4 bytes of the 96-byte struct)
    sb_struct[92:96] = b"\x00\x00\x00\x00"
    return crc32_unsigned(sb_struct)

def build_protective_mbr(total_sectors):
    mbr = bytearray(512)
    # Entry 1 at offset 446
    size_lba = total_sectors - 1
    if size_lba > 0xFFFFFFFF:
        size_lba = 0xFFFFFFFF
    struct.pack_into("<B3sB3sII", mbr, 446, 0x00, b"\x00\x02\x00", 0xEE, b"\xff\xff\xff", 1, size_lba)
    mbr[510] = 0x55
    mbr[511] = 0xAA
    return mbr

def build_gpt_header(current_lba, backup_lba, entries_lba, entries_crc, disk_guid, total_sectors):
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
        total_sectors - 34, # Last usable LBA
        disk_guid,        # Disk GUID
        entries_lba,      # Partition Entries LBA
        128,              # Number of partition entries
        128,              # Size of each partition entry
        entries_crc       # Partition Entries CRC
    )
    header_crc = crc32_unsigned(header)
    struct.pack_into("<I", header, 16, header_crc)
    return header + bytes(512 - 92)

def build_gpt_entry(type_guid, unique_guid, start_lba, end_lba, name):
    entry = bytearray(128)
    struct.pack_into("<16s16sQQQ", entry, 0, type_guid, unique_guid, start_lba, end_lba, 0)
    name_bytes = name.encode("utf-16le")[:72]
    entry[56:56+len(name_bytes)] = name_bytes
    return entry

def create_fat32_image():
    fat_data = bytearray(65536 * 512)

    boot = bytearray(512)
    boot[0:3] = b"\xEB\x58\x90"
    boot[3:11] = b"MSWIN4.1"
    struct.pack_into("<HBHBHHBHHHII", boot, 11, 512, 8, 32, 2, 0, 0, 0xF8, 0, 32, 64, 2048, 65536)
    struct.pack_into("<IHHIIH", boot, 36, 64, 0, 0, 2, 1, 6)
    boot[64] = 0x80
    boot[66] = 0x29
    struct.pack_into("<I11s8s", boot, 67, 0x12345678, b"ACOS_BOOT  ", b"FAT32   ")
    boot[510] = 0x55
    boot[511] = 0xAA
    fat_data[0:512] = boot
    fat_data[6 * 512 : 7 * 512] = boot

    fsinfo = bytearray(512)
    struct.pack_into("<II480sII", fsinfo, 0, 0x41615252, 0x61417272, b"\x00" * 480, 0xFFFFFFFF, 3)
    fsinfo[510] = 0x55
    fsinfo[511] = 0xAA
    fat_data[1 * 512 : 2 * 512] = fsinfo
    fat_data[7 * 512 : 8 * 512] = fsinfo

    fat1_offset = 32 * 512
    fat2_offset = 96 * 512
    struct.pack_into("<II", fat_data, fat1_offset, 0x0FFFFFF8, 0x0FFFFFFF)
    struct.pack_into("<II", fat_data, fat2_offset, 0x0FFFFFF8, 0x0FFFFFFF)

    current_cluster = 2

    def allocate_clusters(num_clusters):
        nonlocal current_cluster
        start = current_cluster
        for i in range(num_clusters - 1):
            struct.pack_into("<I", fat_data, fat1_offset + (current_cluster + i) * 4, current_cluster + i + 1)
            struct.pack_into("<I", fat_data, fat2_offset + (current_cluster + i) * 4, current_cluster + i + 1)
        struct.pack_into("<I", fat_data, fat1_offset + (current_cluster + num_clusters - 1) * 4, 0x0FFFFFFF)
        struct.pack_into("<I", fat_data, fat2_offset + (current_cluster + num_clusters - 1) * 4, 0x0FFFFFFF)
        current_cluster += num_clusters
        return start

    def write_cluster_data(cluster, data):
        cluster_offset = (32 + 2 * 64 + (cluster - 2) * 8) * 512
        fat_data[cluster_offset : cluster_offset + len(data)] = data

    allocate_clusters(1)
    efi_cluster = allocate_clusters(1)
    boot_cluster = allocate_clusters(1)

    boot_efi = b""
    if os.path.exists("acos_boot.efi"):
        with open("acos_boot.efi", "rb") as f:
            boot_efi = f.read()

    kernel_elf = b""
    if os.path.exists("kernel.elf"):
        with open("kernel.elf", "rb") as f:
            kernel_elf = f.read()

    boot_efi_size = len(boot_efi)
    boot_efi_clusters = max(1, (boot_efi_size + 4095) // 4096)
    boot_efi_start = allocate_clusters(boot_efi_clusters)
    write_cluster_data(boot_efi_start, boot_efi)

    kernel_size = len(kernel_elf)
    kernel_clusters = max(1, (kernel_size + 4095) // 4096)
    kernel_start = allocate_clusters(kernel_clusters)
    write_cluster_data(kernel_start, kernel_elf)

    root_dir = bytearray(4096)
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        root_dir, 0,
        b"EFI        ", 0x10,
        0, 0, 0, 0, 0,
        (efi_cluster >> 16) & 0xFFFF,
        0, 0,
        efi_cluster & 0xFFFF,
        0
    )
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        root_dir, 32,
        b"KERNEL  ELF", 0x20,
        0, 0, 0, 0, 0,
        (kernel_start >> 16) & 0xFFFF,
        0, 0,
        kernel_start & 0xFFFF,
        kernel_size
    )
    write_cluster_data(2, root_dir)

    efi_dir = bytearray(4096)
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        efi_dir, 0,
        b"BOOT       ", 0x10,
        0, 0, 0, 0, 0,
        (boot_cluster >> 16) & 0xFFFF,
        0, 0,
        boot_cluster & 0xFFFF,
        0
    )
    write_cluster_data(efi_cluster, efi_dir)

    boot_dir_b = bytearray(4096)
    struct.pack_into(
        "<11sBBBHHHHHHHI",
        boot_dir_b, 0,
        b"BOOTX64 EFI", 0x20,
        0, 0, 0, 0, 0,
        (boot_efi_start >> 16) & 0xFFFF,
        0, 0,
        boot_efi_start & 0xFFFF,
        boot_efi_size
    )
    write_cluster_data(boot_cluster, boot_dir_b)

    return fat_data

def pack_inode(inode_number, type_code, size, permissions, extents):
    buf = bytearray(512)
    struct.pack_into("<IIQIII", buf, 0, inode_number, type_code, size, 0, 0, permissions)
    struct.pack_into("<I", buf, 28, 0)
    for i in range(min(len(extents), 6)):
        start, count = extents[i]
        struct.pack_into("<QII", buf, 32 + i * 16, start, count, 0)
    struct.pack_into("<Q", buf, 128, 0)
    return buf

def pack_dir_entry(inode, type_code, name):
    buf = bytearray(64)
    name_bytes = name.encode("ascii")[:57]
    struct.pack_into("<IBB58s", buf, 0, inode, type_code, len(name_bytes), name_bytes)
    return buf

def create_asfs_system_image():
    asfs_data = bytearray(63455 * 512)

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
        0x415346535F4F535F, 1, 512, 63455, 60000, 1, 1,
        b"\xab" * 16, 0, 0, 20, 0, 0
    )
    checksum = calculate_sb_checksum(sb)
    struct.pack_into("<I", sb, 92, checksum)
    asfs_data[0:512] = sb
    asfs_data[63454 * 512 : 63455 * 512] = sb

    bitmap = bytearray(16 * 512)
    def mark_allocated(block_num):
        byte_idx = block_num // 8
        bit_idx = block_num % 8
        bitmap[byte_idx] |= (1 << bit_idx)

    for b in range(36):
        mark_allocated(b)
    mark_allocated(15)
    mark_allocated(17)
    for b in range(100, 100 + cli_blocks + desktop_blocks):
        mark_allocated(b)
    mark_allocated(63454)
    asfs_data[20 * 512 : 36 * 512] = bitmap

    asfs_data[1 * 512 : 2 * 512] = pack_inode(1, 2, 512, 0o755, [(2, 1)])

    root_block = bytearray(512)
    root_block[0:64] = pack_dir_entry(11, 2, "bin")
    root_block[64:128] = pack_dir_entry(13, 2, "lib")
    asfs_data[2 * 512 : 3 * 512] = root_block

    asfs_data[11 * 512 : 12 * 512] = pack_inode(11, 2, 512, 0o755, [(12, 1)])

    bin_block = bytearray(512)
    bin_block[0:64] = pack_dir_entry(15, 1, "cli.elf")
    bin_block[64:128] = pack_dir_entry(17, 1, "desktop.elf")
    asfs_data[12 * 512 : 13 * 512] = bin_block

    asfs_data[13 * 512 : 14 * 512] = pack_inode(13, 2, 512, 0o755, [(14, 1)])
    asfs_data[14 * 512 : 15 * 512] = bytearray(512)

    asfs_data[15 * 512 : 16 * 512] = pack_inode(15, 1, cli_size, 0o755, [(100, cli_blocks)])
    asfs_data[17 * 512 : 18 * 512] = pack_inode(17, 1, desktop_size, 0o755, [(100 + cli_blocks, desktop_blocks)])

    cli_start_offset = 100 * 512
    asfs_data[cli_start_offset : cli_start_offset + cli_size] = cli_elf_bytes

    desktop_start_offset = (100 + cli_blocks) * 512
    asfs_data[desktop_start_offset : desktop_start_offset + desktop_size] = desktop_elf_bytes

    return asfs_data

def create_asfs_data_image():
    asfs_data = bytearray(129024 * 512)

    # 1. Superblock (Block 0)
    sb = bytearray(512)
    struct.pack_into(
        "<QIIQQQQ16sQQQII",
        sb, 0,
        0x415346535F4F535F, 1, 512, 129024, 120000, 1, 1,
        b"\xcd" * 16, 0, 0, 20, 0, 0
    )
    checksum = calculate_sb_checksum(sb)
    struct.pack_into("<I", sb, 92, checksum)
    asfs_data[0:512] = sb
    asfs_data[129023 * 512 : 129024 * 512] = sb

    bitmap = bytearray(32 * 512)
    def mark_allocated(block_num):
        byte_idx = block_num // 8
        bit_idx = block_num % 8
        bitmap[byte_idx] |= (1 << bit_idx)

    for b in range(20):
        mark_allocated(b)
    for b in range(20, 52):
        mark_allocated(b)
    mark_allocated(129023)
    asfs_data[20 * 512 : 52 * 512] = bitmap

    asfs_data[1 * 512 : 2 * 512] = pack_inode(1, 2, 512, 0o755, [(2, 1)])

    root_block = bytearray(512)
    root_block[0:64] = pack_dir_entry(3, 2, "apps")
    root_block[64:128] = pack_dir_entry(5, 2, "users")
    root_block[128:192] = pack_dir_entry(7, 2, "shared")
    asfs_data[2 * 512 : 3 * 512] = root_block

    asfs_data[3 * 512 : 4 * 512] = pack_inode(3, 2, 512, 0o755, [(4, 1)])
    asfs_data[4 * 512 : 5 * 512] = bytearray(512)

    asfs_data[5 * 512 : 6 * 512] = pack_inode(5, 2, 512, 0o755, [(6, 1)])
    asfs_data[6 * 512 : 7 * 512] = bytearray(512)

    asfs_data[7 * 512 : 8 * 512] = pack_inode(7, 2, 512, 0o755, [(8, 1)])
    asfs_data[8 * 512 : 9 * 512] = bytearray(512)

    return asfs_data

def build_full_disk_image():
    total_sectors = 262144
    disk = bytearray(total_sectors * 512)

    disk[0:512] = build_protective_mbr(total_sectors)

    fat32_partition_data = b""
    if os.path.exists("acos_fat32.img") and os.path.getsize("acos_fat32.img") == 65536 * 512:
        with open("acos_fat32.img", "rb") as f:
            fat32_partition_data = f.read()
        print("Success: Merged host-generated FAT32 partition 1!")
    else:
        fat32_partition_data = create_fat32_image()

    asfs_sys_data = create_asfs_system_image()
    asfs_data_data = create_asfs_data_image()

    with open("asfs_test.img", "wb") as f:
        f.write(asfs_sys_data)
    print("Success: Generated standalone asfs_test.img (ASFS system)!")

    disk[2048 * 512 : 2048 * 512 + len(fat32_partition_data)] = fat32_partition_data
    disk[67584 * 512 : 67584 * 512 + len(asfs_sys_data)] = asfs_sys_data
    disk[131072 * 512 : 131072 * 512 + len(asfs_data_data)] = asfs_data_data

    entries = bytearray(32 * 512)
    entries[0:128] = build_gpt_entry(ESP_GUID, b"\x11" * 16, 2048, 67583, "EFI System Partition")
    entries[128:256] = build_gpt_entry(ASFS_GUID, b"\x22" * 16, 67584, 131038, "ASFS System")
    entries[256:384] = build_gpt_entry(ASFS_DATA_GUID, b"\x33" * 16, 131072, 260095, "ASFS Data")

    entries_crc = crc32_unsigned(entries)
    disk[2 * 512 : 34 * 512] = entries
    disk[(total_sectors - 33) * 512 : (total_sectors - 1) * 512] = entries

    disk_guid = b"\xde\xad\xbe\xef" * 4
    primary_header = build_gpt_header(1, total_sectors - 1, 2, entries_crc, disk_guid, total_sectors)
    disk[1 * 512 : 2 * 512] = primary_header

    backup_header = build_gpt_header(total_sectors - 1, 1, total_sectors - 33, entries_crc, disk_guid, total_sectors)
    disk[(total_sectors - 1) * 512 : total_sectors * 512] = backup_header

    with open("acos.img", "wb") as f:
        f.write(disk)
    print("Success: Generated partitioned acos.img disk image!")

if __name__ == "__main__":
    build_full_disk_image()
