# CHANGES.md - ACOS Core System (Phases 1-6)

## Overview
ACOS core infrastructure is fully implemented, transitioning from a basic bootloader to a microkernel capable of managing isolated user-mode services and drivers.

## New Subsystems

### 1. Virtual Memory Management (Phase 5A)
- **AddressSpace**: Manages per-process PML4 page tables.
- **Paging**: 4-level x86_64 paging with user/kernel isolation.
- **VMM**: Kernel-wide identity mapping and address space switching support.

### 2. User Mode & Syscalls (Phase 5B)
- **User Segments**: GDT updated with Ring 3 code/data segments and TSS for stack switching.
- **Syscall Infrastructure**: implemented \`SYSCALL\` entry in assembly and C++ dispatcher for \`GET_PID\`, \`YIELD\`, and IPC.
- **Loader**: Functional user process creation and initial stack setup.

### 3. Service & Driver Framework (Phase 6)
- **Service Manager**: Registry and lifecycle management for system services (FS, Network, etc.).
- **Driver Manager**: Infrastructure for tracking and managing driver states (Loaded, Running, Failed).
- **Resource Integration**: Services and drivers are now first-class kernel resources.

## Implementation Standards
- **Freestanding C++23**: Pure kernel implementation with custom runtime support.
- **Thread Safety**: SpinLocks applied to all shared kernel structures.
- **Build System**: Makefile updated to support Linux/Windows cross-builds with unified targets.

## Verification
- Clean build for kernel and bootloader.
- Successful audit of core initialization sequence in \`kernelMain\`.
