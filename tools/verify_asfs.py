#!/usr/bin/env python3
import struct
import binascii
import sys

def crc32_unsigned(data):
    return binascii.crc32(data) & 0xFFFFFFFF

def calculate_sb_checksum(sb_block):
    # The superblock struct is the first 96 bytes
    sb_struct = bytearray(sb_block[:96])
    # Clear checksum (last 4 bytes of the 96-byte struct)
    sb_struct[92:96] = b"\x00\x00\x00\x00"
    return crc32_unsigned(sb_struct)

def verify_acos_image():
    img_path = "acos.img"
    try:
        with open(img_path, "rb") as f:
            disk = f.read()
    except Exception as e:
        print(f"Error: Could not open {img_path}: {e}")
        return False

    print(f"Successfully loaded {img_path} ({len(disk)} bytes)")

    # 1. Verify Protective MBR at Sector 0
    mbr = disk[0:512]
    if mbr[510] != 0x55 or mbr[511] != 0xAA:
        print("FAIL: Invalid Protective MBR Magic")
        return False
    print("PASS: Protective MBR signature verified (0xAA55)")

    # 2. Verify GPT Header at Sector 1
    gpt_header = disk[512:1024]
    signature, revision, header_size, header_crc, reserved, current_lba, backup_lba, first_usable, last_usable, disk_guid, partition_lba, num_entries, entry_size, entries_crc = struct.unpack_from(
        "<8sIIIIQQQQ16sQIII", gpt_header, 0
    )

    if signature != b"EFI PART":
        print(f"FAIL: Invalid GPT signature: {signature}")
        return False
    print("PASS: GPT Header Signature is 'EFI PART'")

    # 3. Read GPT entries
    entries_offset = partition_lba * 512
    entries_data = disk[entries_offset : entries_offset + num_entries * entry_size]

    computed_entries_crc = crc32_unsigned(entries_data)
    if computed_entries_crc != entries_crc:
        print(f"FAIL: GPT Entries CRC mismatch (Header: {entries_crc}, Computed: {computed_entries_crc})")
        return False
    print("PASS: GPT Partition Entries CRC is valid")

    partitions = []
    for i in range(num_entries):
        offset = i * entry_size
        entry = entries_data[offset : offset + entry_size]
        type_guid = entry[0:16]
        uniq_guid = entry[16:32]
        start_lba, end_lba, attributes = struct.unpack_from("<QQQ", entry, 32)
        name_bytes = entry[56:128]
        name = name_bytes.decode("utf-16le").split("\x00")[0]
        if start_lba != 0 or end_lba != 0:
            partitions.append({
                "index": i + 1,
                "type_guid": type_guid,
                "uniq_guid": uniq_guid,
                "start_lba": start_lba,
                "end_lba": end_lba,
                "name": name
            })

    print(f"Discovered {len(partitions)} active partition(s):")
    for p in partitions:
        print(f"  Partition {p['index']}: '{p['name']}' (LBA {p['start_lba']} - {p['end_lba']})")

    if len(partitions) < 3:
        print("FAIL: Expected at least 3 partitions (ESP, ASFS System, ASFS Data)")
        return False

    p1, p2, p3 = partitions[0], partitions[1], partitions[2]

    # Verify Partition 2: ASFS System
    print("\nVerifying Partition 2 (ASFS Read-Only System)...")
    p2_start_bytes = p2["start_lba"] * 512
    p2_data = disk[p2_start_bytes : (p2["end_lba"] + 1) * 512]

    # Superblock is at block 0 of Partition 2
    p2_sb = p2_data[0:512]
    magic, version, block_size, total_blocks, free_blocks, free_space_root, transaction_id, uuid, root_inode, journal_start, journal_blocks, version_minor, checksum = struct.unpack_from(
        "<QIIQQQQ16sQQQII", p2_sb, 0
    )

    if magic != 0x415346535F4F535f:
        print(f"FAIL: Invalid ASFS magic in Partition 2: {hex(magic)}")
        return False
    if version != 1:
        print(f"FAIL: Unsupported version in Partition 2: {version}")
        return False

    # Verify CRC32 checksum of superblock
    computed_sb2_checksum = calculate_sb_checksum(p2_sb)
    if computed_sb2_checksum != checksum:
        print(f"FAIL: Partition 2 Superblock CRC32 corrupt! Superblock: {hex(checksum)}, Computed: {hex(computed_sb2_checksum)}")
        return False

    print(f"PASS: Superblock Magic verified ({hex(magic)})")
    print(f"PASS: Superblock version: {version}")
    print(f"PASS: Block size: {block_size}, Total blocks: {total_blocks}")
    print(f"PASS: Superblock CRC32 checksum is valid: {hex(checksum)}")

    # Check root inode block (block 1)
    p2_root_inode_block = p2_data[1*512 : 2*512]
    inode_num, type_code, size, _, _, permissions = struct.unpack_from("<IIQIII", p2_root_inode_block, 0)
    if inode_num != 1 or type_code != 2:
        print(f"FAIL: Invalid root inode header in Partition 2. Inode: {inode_num}, Type: {type_code}")
        return False
    print("PASS: Root directory inode is valid")

    # Verify Partition 3: ASFS Writable Data
    print("\nVerifying Partition 3 (ASFS Writable Data)...")
    p3_start_bytes = p3["start_lba"] * 512
    p3_data = disk[p3_start_bytes : (p3["end_lba"] + 1) * 512]

    p3_sb = p3_data[0:512]
    magic3, version3, block_size3, total_blocks3, free_blocks3, free_space_root3, transaction_id3, uuid3, root_inode3, journal_start3, journal_blocks3, version_minor3, checksum3 = struct.unpack_from(
        "<QIIQQQQ16sQQQII", p3_sb, 0
    )

    if magic3 != 0x415346535F4F535f:
        print(f"FAIL: Invalid ASFS magic in Partition 3: {hex(magic3)}")
        return False

    computed_sb3_checksum = calculate_sb_checksum(p3_sb)
    if computed_sb3_checksum != checksum3:
        print(f"FAIL: Partition 3 Superblock CRC32 corrupt! Superblock: {hex(checksum3)}, Computed: {hex(computed_sb3_checksum)}")
        return False

    print(f"PASS: Partition 3 Superblock Magic verified ({hex(magic3)})")
    print(f"PASS: Partition 3 total blocks: {total_blocks3}")
    print(f"PASS: Partition 3 Superblock CRC32 checksum is valid: {hex(checksum3)}")

    # Verify that structural subdirectories '/apps', '/users', '/shared' exist on Data Partition 3
    # Inode 1 points to directory entries block 2
    p3_dir_block = p3_data[2*512 : 3*512]
    entries = []
    for i in range(8):
        offset = i * 64
        entry = p3_dir_block[offset : offset + 64]
        inode, type_code, name_len = struct.unpack_from("<IBB", entry, 0)
        if inode != 0:
            name = entry[6:6+name_len].decode("ascii")
            entries.append((inode, type_code, name))

    print(f"Found Partition 3 root directory entries: {entries}")
    entry_names = [e[2] for e in entries]
    for expected in ["apps", "users", "shared"]:
        if expected not in entry_names:
            print(f"FAIL: Missing expected subdirectory '{expected}' in Partition 3")
            return False
        print(f"PASS: Found on-disk subdirectory '/{expected}'")

    print("\n=== ALL STATIC VERIFICATIONS PASS SUCCESSFULLY! ===")
    return True

if __name__ == "__main__":
    if not verify_acos_image():
        sys.exit(1)
