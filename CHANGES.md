# CHANGES.md - ACOS Core System (Phases 1-8)

## Overview
ACOS infrastructure now includes a Virtual File System (VFS) and a Storage Framework. The system supports abstracted file operations across different filesystem implementations and a memory-backed RAM disk.

## Phase 8: VFS and Storage Framework
- **VFS Architecture**: Implemented \`Inode\`, \`Dentry\`, and \`File\` abstractions.
- **Mount System**: Global \`MountRegistry\` for managing multiple filesystems.
- **Path Resolution**: Support for absolute path normalization and directory traversal foundation.
- **File Descriptors**: Per-process descriptor tables for tracking open files.
- **Storage Abstraction**: Defined \`BlockDevice\` interface and implemented a functional \`RamDisk\`.
- **Security**: Files integrated as capability-managed resources with access right enforcement.

## Subsystem Highlights
- **VMM**: 4-level paging with isolated per-process address spaces.
- **User Mode**: Ring 3 transition support via GDT/TSS and SYSCALL infrastructure.
- **Process System**: ELF64 loading and runtime process initialization.
- **IPC**: Hardened thread-safe communication primitives.

## Toolchain and build
- Fully switched to GCC/G++ toolchain.
- Makefile updated with comprehensive subsystem targets.

## Verification
- Verified build for VFS and Storage components.
- Successful audit of kernel-to-user transition and IPC blocking logic.
