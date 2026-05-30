# CHANGES.md - ACOS Core System (Phases 1-7)

## Overview
ACOS core infrastructure is fully implemented, transitioning from a basic bootloader to a microkernel capable of managing isolated user-mode services and drivers. The build system has been migrated to the GNU GCC/G++ toolchain.

## Phase 7: ELF Loader and Process Runtime
- **ELF64 Support**: Implemented parsing and validation for 64-bit ELF binaries.
- **Segment Loading**: Enabled mapping of ELF segments into user address spaces with appropriate permissions.
- **Process Runtime**: Orchestrated process creation and initial thread setup from ELF data.
- **User Stack**: Initialized user-mode stacks with future POSIX metadata support.
- **Audit**: Verified context switching, address space isolation, and IPC signaling logic (see KERNEL_AUDIT.md).

## Key Subsystems

### 1. Virtual Memory Management (Phase 5A)
- **AddressSpace**: Manages per-process PML4 page tables.
- **Paging**: 4-level x86_64 paging with user/kernel isolation.

### 2. User Mode & Syscalls (Phase 5B)
- **User Segments**: GDT updated with Ring 3 code/data segments and TSS foundation.
- **Syscall Infrastructure**: implemented \`SYSCALL\` entry in assembly and C++ dispatcher for kernel services.

### 3. Service & Driver Framework (Phase 6)
- **Service Manager**: Registry and lifecycle management for system services (FS, Network, etc.).
- **Driver Manager**: Infrastructure for tracking and managing driver states.

## Toolchain Migration
- Migrated Makefile from Clang/LLD to GCC/LD.
- Resolved freestanding C++ runtime conflicts between libgcc/libstdc++ and custom ACOS headers.

## Verification
- Clean build for kernel and bootloader using \`gcc\` and \`ld\`.
- Successful audit of core initialization sequence in \`kernelMain\`.
