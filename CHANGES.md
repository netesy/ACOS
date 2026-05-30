# CHANGES.md - ACOS Core System (Phases 1-9)

## Overview
ACOS infrastructure now supports real storage device drivers (AHCI/SATA), partition management (MBR/GPT), and a Virtual File System with FAT32 support.

## Phase 9: Storage Drivers and Filesystem Foundation
- **AHCI Driver**: Implemented Host Bus Adapter and Port management foundation.
- **SATA Layer**: Added support for SATA device identification and LBA-based block access.
- **Partition Management**: Support for enumerating MBR and GPT partitions.
- **FAT32 Driver**: Implemented a functional FAT32 filesystem driver integrated with VFS.
- **VFS Integration**: Full mapping from \`VFS -> FileSystem -> BlockDevice -> Storage Controller\`.
- **Security**: Partition boundaries and filesystem metadata are treated as hostile input and validated.

## Core Highlights
- **VMM & User Mode**: Stabilized 4-level paging and user-mode process loading from ELF binaries.
- **Syscalls**: Established the system call path for user-mode applications to access VFS.
- **Multitasking**: Hardened round-robin scheduler with proper address space switching.

## Toolchain
- Unified GCC/G++ build system with comprehensive subsystem coverage.

## Verification
- Verified build for Storage, Partition, and Filesystem subsystems.
- Validated VFS structural consistency with multiple filesystem nodes.
