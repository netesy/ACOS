# ASFS (ASADE File System) Specification & Architecture Report

---

## 1. Actual Storage Component Mapping & Data Flow
The ASADE storage stack is decoupled into clear layers to isolate hardware dependencies from filesystem policies and VFS abstractions. The components and their source locations are mapped below:

### Component Map
1. **Bootloader (`boot/main.cpp`)**:
   - Freestanding EFI 64-bit application that uses UEFI `SimpleFileSystem` protocols to load the kernel binary from the FAT32 EFI System Partition.
2. **EFI (`boot/efi.h`, `boot/main.cpp`)**:
   - Provides low-level interfaces for GOP framebuffers, memory maps, and file reading prior to kernel handover.
3. **Kernel (`kernel/main.cpp`)**:
   - Configures CPU architectural registers, physical/virtual memory, heaps, scheduler, interrupts, and initiates driver discovery.
4. **PCI (`kernel/hal/pci.cpp`)**:
   - Enumerates physical hardware configurations to discover the storage controller.
5. **AHCI / SATA (`kernel/storage/ahci.cpp`, `kernel/storage/ahci.h`)**:
   - Manages physical Host Bus Adapter (HBA) SATA ports to issue raw command lists to storage disks.
6. **BlockDevice (`kernel/storage/block_device.h`)**:
   - Pure abstract interface for block-level synchronous read, write, and flush requests.
7. **RAMDisk (`kernel/storage/ramdisk.cpp`, `kernel/storage/ramdisk.h`)**:
   - RAM-backed BlockDevice subclass serving as a deterministic testing backend.
8. **PartitionManager (`kernel/storage/partition.cpp`, `kernel/storage/partition.h`)**:
   - Parses GUID Partition Tables (GPT) and fallback Master Boot Records (MBR) on a physical BlockDevice to yield virtual sub-BlockDevice partitions.
9. **VFS (`kernel/vfs/vfs.cpp`, `kernel/vfs/vfs.h`)**:
   - Exposes path resolution, handles descriptors, and mounts/probes filesystem instances.
10. **FAT32 (`kernel/storage/fat32.cpp`, `kernel/storage/fat32.h`)**:
    - Parses 8.3 fat directories and cluster chains to expose boot-time assets and recovery files.
11. **ASFS (`kernel/storage/asfs.cpp`, `kernel/storage/asfs.h`)**:
    - Native, robust extent-based transactional filesystem providing metadata records and system/data security bounds.
12. **ELF Loader (`kernel/loader/elf_loader.cpp`, `kernel/loader/process_loader.cpp`)**:
    - Resolves executable formats from the VFS to create scheduling threads.

### Boot-Time Data Flow

```
+──────────────────────────────────────────────────────────────+
│                      UEFI / GPT Disk Image                   │
+──────────────────────────────────────────────────────────────+
                                │
                                ▼
+──────────────────────────────────────────────────────────────+
│                    boot/main.efi (FAT32 Boot)                │
+──────────────────────────────────────────────────────────────+
                                │  loads kernel.elf from Partition 1
                                ▼
+──────────────────────────────────────────────────────────────+
│                        kernel.elf Entry                      │
+──────────────────────────────────────────────────────────────+
                                │  PCI discovery
                                ▼
+──────────────────────────────────────────────────────────────+
│                   AHCI / SATA Storage Disk                   │
+──────────────────────────────────────────────────────────────+
                                │  enumerates partition table
                                ▼
+──────────────────────────────────────────────────────────────+
│                   PartitionManager GPT / MBR                 │
+──────────────────────────────────────────────────────────────+
         │                                       │
         ▼ (FAT32 ESP, Type ESP GUID / 0xEF)     ▼ (ASFS Partition, Type ASFS GUID / 0xAC)
+───────────────────────────────────+   +───────────────────────────────────+
│       Partition 1 BlockDevice     │   │       Partition 2 BlockDevice     │
+───────────────────────────────────+   +───────────────────────────────────+
                 │                                       │
                 ▼                                       ▼
+───────────────────────────────────+   +───────────────────────────────────+
│          FAT32 FS Probe           │   │           ASFS FS Probe           │
+───────────────────────────────────+   +───────────────────────────────────+
                 │                                       │
                 ▼ mount at /                            ▼ mount at /system
+───────────────────────────────────────────────────────────────────────────+
│                        Unified VFS Mount Registry                         │
+───────────────────────────────────────────────────────────────────────────+
                                │
                                ▼
+───────────────────────────────────────────────────────────────────────────+
│                 VFS Resolve "/system/bin/cli.elf"                         │
+───────────────────────────────────────────────────────────────────────────+
                                │
                                ▼
+───────────────────────────────────────────────────────────────────────────+
│                  ProcessLoader / ELF Loader spawn Ring 3                  │
+───────────────────────────────────────────────────────────────────────────+
```

---

## 2. Partition Type Identifiers & Identifiers Specifications
To facilitate stable dynamic mapping of system and data spaces across multiple ports, controllers, or storage types, PartitionManager uses explicit identifiers to discover volumes:

### GUID Partition Table (GPT) Identifiers
* **EFI System Partition (ESP) GUID**:
  - `C12A7328-F81F-11D2-BA4B-00A0C93EC93B`
  - Raw Little-Endian Bytes: `28 73 2A C1 1F F8 D2 11 BA 4B 00 A0 C9 3E C9 3B`
* **ASFS System Partition GUID**:
  - `A5A54153-4653-4F53-A5A5-A5A5A5A5A5A5` (equivalent to: `A5A54153-4653-4F53-A5A5-A5A5A5A5A5A5`)
  - Raw Little-Endian Bytes: `53 41 A5 A5 53 46 53 4F A5 A5 A5 A5 A5 A5 A5 A5`

### Master Boot Record (MBR) Partition Type Codes
* **EFI / FAT32 Partition Code**:
  - `0xEF` (EFI System Partition), fallback `0x0C` / `0x0E` / `0x0B`
* **ASFS Partition Code**:
  - `0xAC` (ASFS Custom)

---

## 3. On-Disk Format Specification (v2.0 - Writable Core)
An ASFS partition block layout is structured as follows:

### Sector 0: Superblock
The superblock occupies the first sector (Block 0) of the ASFS partition:

| Offset | Type | Field | Description |
| :--- | :--- | :--- | :--- |
| 0x00 | `u64` | `magic` | ASFS Magic Number (`0x415346535F4F535FULL` - "ASFS_OS_") |
| 0x08 | `u32` | `version` | Filesystem Version (currently `1`) |
| 0x0C | `u32` | `block_size` | Size of a single block in bytes (e.g., `512` or `4096`) |
| 0x10 | `u64` | `total_blocks` | Total number of blocks in the partition |
| 0x18 | `u64` | `free_blocks` | Total number of unallocated blocks |
| 0x20 | `u64` | `root_inode` | Block address of the Root Directory Inode |
| 0x28 | `u64` | `transaction_id` | Sequence number of the last committed transaction |
| 0x30 | `u8[16]` | `uuid` | Unique filesystem UUID |
| 0x40 | `u64` | `inode_tree_root` | Reserved block number for future Inode metadata B-tree |
| 0x48 | `u64` | `extent_tree_root`| Reserved block number for future Extents metadata B-tree |
| 0x50 | `u64` | `free_space_root` | Physical block number of the Free Space bitmap (starts at block `20` by default) |
| 0x58 | `u32` | `feature_flags`   | Filesystem feature flags |
| 0x5C | `u32` | `checksum` | CRC32 or Fletcher checksum of the superblock |

*To provide resilience, a redundant copy of the superblock is stored at the end of the partition.*

### ASFS Free-Space Bitmap
* **Location**: Starts at the block address specified by `free_space_root` (typically block `20`).
* **Format**: Consequent byte array where each bit maps to exactly one physical sector block:
  - `1` = allocated
  - `0` = free
* **Bounds**: Covers the complete range of partition sectors up to `total_blocks`. High-performance bitwise instructions are used to allocate contiguous segments.

### ASFS Extent Format
An extent defines a contiguous range of physical blocks:

| Offset | Type | Field | Description |
| :--- | :--- | :--- | :--- |
| 0x00 | `u64` | `start_block` | Physical block number of the extent start |
| 0x08 | `u32` | `block_count` | Number of contiguous blocks |
| 0x0C | `u32` | `reserved` | Reserved field for future extensions |

### ASFS Inode Structure
An inode represents a file or directory entry, allocating a whole block:

| Offset | Type | Field | Description |
| :--- | :--- | :--- | :--- |
| 0x00 | `u32` | `inode_number` | Unique inode index (corresponds exactly to its physical block number on disk) |
| 0x04 | `u32` | `type` | Node type (`1` File, `2` Directory, `3` Symlink) |
| 0x08 | `u64` | `size` | Size of the resource in bytes |
| 0x10 | `u32` | `owner_uid` | Owner User ID |
| 0x14 | `u32` | `group_gid` | Owner Group ID |
| 0x18 | `u32` | `permissions` | Access control permissions |
| 0x1C | `u32` | `flags` | Immutability and update flags |
| 0x20 | `ASFSExtent[6]` | `extents` | Extents describing direct data block ranges |
| 0x80 | `u64` | `indirect_block` | Pointer to single-indirect metadata block |

### ASFS Directory Entry
A directory data block contains a sequential array of directory records:

| Offset | Type | Field | Description |
| :--- | :--- | :--- | :--- |
| 0x00 | `u32` | `inode_number` | Target Inode pointer (corresponds to its physical block address) |
| 0x04 | `u8` | `type` | Node type (`1` File, `2` Directory) |
| 0x05 | `u8` | `name_len` | Length of the filename |
| 0x06 | `char[58]` | `name` | Null-terminated filename characters |

---

## 4. Hardware boundary check invariants
Every block fetch strictly verifies physical and partition boundaries to prevent underflows, overflows, or out-of-bounds corruption:
1. `block_id + block_count` does not overflow standard integer calculations.
2. `block_id + block_count <= partition_total_blocks`.
3. Every extent read satisfies `extent_start >= filesystem_data_start` and `extent_start + extent_length <= filesystem_total_blocks`.
4. System mounts reject filesystems with block sizes that are not positive powers of two, or roots pointing outside partition spaces.
5. All disk writes enforce that we never write to block 0 (superblock), block 1 (root directory), or any block outside our designated partition scope.
