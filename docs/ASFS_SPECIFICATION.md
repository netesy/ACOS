# ASFS (ASADE File System) Specification & Architecture Report

---

## 1. Current Storage Architecture
Currently, ASADE OS boots from an EFI System Partition formatted in FAT32. The bootloader loads the `kernel.elf` executable, which initializes the ACOS kernel. On boot, the kernel:
1. Enumerates the PCI bus to find SATA/AHCI storage controllers.
2. Registers block devices corresponding to physical ports.
3. Performs basic partition discovery (supporting MBR partition tables).
4. Probes and mounts partition block devices using the virtual filesystem (VFS) layer.
5. The VFS layer abstracts storage using a custom `FileSystem` interface, and is currently registered with a FAT32 filesystem implementation.
6. The FAT32 filesystem parses the 8.3 filename layout and returns read-only directory and file `Node` instances.
7. Processes in userspace open files, which returns file descriptors mapping to kernel-allocated `vfs::File` objects.

### Current Architectural Limitations
* **Coupling & Risk**: Writes in FAT32 are unsafe, incomplete, and lack transactional guarantees. Direct modifications on real physical hardware can result in complete FAT chain or directory tree corruption.
* **Lack of Isolation**: FAT32 contains no concept of owner UID, security groups, application-level isolation, or capability boundaries. Any process can read or modify any file on a mounted FAT32 volume.
* **No Immutability**: Critical system utilities in `/bin` can be directly overwritten by standard applications, lacking split system/data immutability.

---

## 2. Proposed ASFS Architecture
The native ASADE File System (ASFS) introduces a modern, secure, and crash-resilient storage design, structured as:

```
                         ASADE Applications
                                │
                         ASADE File API
                                │
                      Capability Authorization
                                │
                               VFS
                                │
                    ┌───────────┴───────────┐
                    │                       │
              Protected Namespaces     Writable Namespaces
                    │                       │
            /system /vendor             /data /apps
                    │                       │
                    └───────────┬───────────┘
                                │
                           ASFS VFS
                                │
                      Transaction Manager
                                │
                     Metadata / Extent Trees
                                │
                       Block Allocation
                                │
                         Block Device API
                         /       |       \
                      AHCI      NVMe      USB
                         \       |       /
                              Storage
```

### Key Principles of ASFS
* **Capability Separation**: Capabilities sit strictly above ASFS (at VFS / System Call boundary). ASFS provides the low-level security metadata (UIDs, GIDs, permissions, capability-mapping blocks) which the higher capability authorization layer queries and enforces.
* **Separation of Concerns**: Fully decoupled from physical storage drivers. Functions on top of any `BlockDevice` interface.
* **System/Data Separation**: The `/system` path is mounted read-only during normal operation, ensuring the OS base components are protected. Writable storage is designated under `/data`.
* **Application Sandboxing**: Paths under `/data/apps/<app-id>` are sandbox-protected. Processes only receive capabilities to access their own designated sandboxed folders.
* **Transactional Integrity**: Employs a Copy-on-Write (CoW) metadata mechanism and transactional commit sequence to prevent metadata corruption during crashes or power losses.

---

## 3. On-Disk Format Specification (v1 - Extent Based)
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
| 0x50 | `u64` | `free_space_root` | Reserved block number for future Free Space metadata B-tree |
| 0x58 | `u32` | `feature_flags`   | Filesystem feature flags |
| 0x5C | `u32` | `checksum` | CRC32 or Fletcher checksum of the superblock |

*To provide resilience, a redundant copy of the superblock is stored at the end of the partition.*

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
| 0x00 | `u32` | `inode_number` | Unique inode index |
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
| 0x00 | `u32` | `inode_number` | Target Inode pointer |
| 0x04 | `u8` | `type` | Node type (`1` File, `2` Directory) |
| 0x05 | `u8` | `name_len` | Length of the filename |
| 0x06 | `char[58]` | `name` | Null-terminated filename characters |

---

## 4. VFS Integration Plan
ASFS mounts seamlessly to the existing ACOS VFS framework:
1. Create `ASFSFileSystem` implementing `vfs::FileSystem`.
2. Define `ASFSFileNode` and `ASFSDirNode` implementing `vfs::Node`.
3. Read the superblock on mount, validating magic numbers, checksums, and version tags. Also validate the redundant copy if needed.
4. Open directories and files via inode lookup, resolving the components of a path recursively.
5. Coordinate with `FileSystemManager` to probe partition block devices and register ASFS.

---

## 5. Capability & Sandbox Integration Plan
1. Integration with the ACOS `ResourceHandleTable`: Every open ASFS resource is assigned a kernel `File` capability.
2. Secure Path Resolution: Path resolutions verify that a process can only access `/data/apps/<app-id>` matching its own application ID.
3. Access Control checks POSIX-like owner rights, but maps directly to security domain policies defined in the capability manager.

---

## 6. Boot & Partition Layout
A standard ASADE storage layout on real hardware consists of:
* **Partition 1 (FAT32)**: EFI System Partition containing `\EFI\BOOT\BOOTX64.EFI`, `kernel.elf`, and configuration files.
* **Partition 2 (ASFS)**: The native ASADE system and user data storage.
  * `/system`: Read-Only operating system binaries (`/bin`, `/lib`, `/drivers`).
  * `/data`: Writable private and user applications data.

---

## 7. Migration Plan
* **Milestone 1**: Read-only core. RAM block device, ASFS image layout, mounting and path traversal / nested file reading validation.
* **Milestone 2**: Inode and directory hierarchy writable support.
* **Milestone 3**: B-Tree metadata trees, extent trees, and allocator integration.
* **Milestone 4**: Transaction committing, atomic Commits, Copy-On-Write metadata, and Crash Recovery validation.

---

## 8. Test Strategy
* **Format & Mount Validation**: Test boot loader and kernel mounting consistency on startup.
* **Read Integrity**: Verify that nested paths (e.g., `/asfs/system/bin/cli.elf`) are resolved and read correctly.
* **Path Separation**: Ensure read-only restrictions are strictly enforced.

---

## 9. Risk Assessment
* **Data Loss Risk**: Low. FAT32 boot mechanism remains untouched; ASFS is developed isolatedly.
* **Memory Limits**: The design must avoid heavy runtime overheads given ACOS's freestanding kernel requirements.

---

## 10. Implementation Plan (Milestone 1)
1. Write ASFS specifications and specifications report.
2. Implement superblock validation, file system structures, and file/directory node reading logic.
3. Integrate with the VFS framework.
4. Spawn a mock RAM-Backed Block Device and format it dynamically with an ASFS partition containing basic files to verify Milestone 1.
