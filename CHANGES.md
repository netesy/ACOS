# CHANGES.md - ACOS Phase 1: Boot System

## Overview
Implemented the foundational components to boot ACOS on x86_64 UEFI.

## Added Components

### 1. Bootloader (/boot)
- **efi.h**: UEFI definitions for GOP, Memory Map, and Boot Services.
- **main.cpp**: Initialises GOP, collects memory map, prepares `BootInfo`, and transitions to the kernel.

### 2. Kernel (/kernel)
- **arch/x86_64/boot.S**: Assembly entry point, sets up the kernel stack.
- **main.cpp**: `kernelMain` entry point.
- **hal/serial.cpp**: COM1 serial driver for debug logging.
- **hal/console.cpp**: Framebuffer-based early console.

### 3. Runtime Library (/libs/runtime)
- **acos/types.h**: Standard ACOS integer and pointer types.
- **acos/boot_info.h**: Definition of the `BootInfo` structure passed from bootloader to kernel.

### 4. Build System
- **Makefile**: Root makefile using `clang` and `ld` (with i386pep for UEFI).
- **linker.ld**: Linker script for the ELF64 kernel.

### 5. Tools (/tools)
- **build_disk.sh**: Linux script to package the bootloader and kernel into a FAT32 image.
- **run_qemu.sh**: Linux script to build and run in QEMU.
- **run_qemu.bat**: Windows batch script to build and run in QEMU (using MinGW).

## Usage

### Linux
```bash
./tools/run_qemu.sh
```

### Windows
```cmd
tools\run_qemu.bat
```

## Phase 2: Core Kernel Advancements

### 1. Enhanced HAL
- **efi.h**: Full UEFI protocol and service definitions.
- **console.cpp**: Added bitmap font support (8x8) and `console_print` with basic overflow handling.

### 2. Memory Management
- **pmm.cpp**: Implemented Physical Memory Manager using a bitmap allocator.
- Integrated PMM into `kernelMain` using `BootInfo` memory map.

### 3. CPU Setup
- **gdt.cpp**: Implemented Global Descriptor Table for x86_64.
- **idt.cpp**: Implemented Interrupt Descriptor Table foundation.

### 4. Scheduling
- **scheduler.cpp**: Established minimal thread structure and scheduler initialization.

### 5. Build Improvements
- Makefile updated to include all new subsystems.
- Linker script and boot assembly refined for Phase 2 entry.

## Phase 3: Process System

### 1. Scheduler and Processes
- **thread.h**: Defined Thread Control Block (TCB) with state management.
- **process.h/cpp**: Implemented Process Control Block (PCB) and process creation logic.
- **switch.S**: Implemented x86_64 context switching assembly.

### 2. Security and Domains
- **domain.h/cpp**: Implemented security Domains for isolating system, drivers, and applications.
- Established default domain policies for I/O and network access.

### 3. Capability Management
- **capability.h/cpp**: Implemented core capability structures and transfer/revocation mechanisms.

### 4. System Integration
- Updated `kernelMain` to initialize the Process and Domain managers.
- Verified compilation of the isolated process model.

## Phase 4: IPC and System Service Infrastructure

### 1. IPC Primitives
- **Channel IPC**: Implemented `Channel` class with FIFO ring buffer. Supports structured `Message` delivery with future capability attachment.
- **Notifications**: Implemented `Notification` class for lightweight event signaling. integrated with scheduler for future blocking/waking.
- **Shared Memory**: Implemented `SharedRegion` for zero-copy physical page sharing between address spaces.

### 2. Process and Scheduler Extensions
- Extended Process Control Block (PCB) with handle tables for IPC objects.
- Implemented handle-based lookup and resource registration.
- Added `block_thread` and `wake_thread` logic to the scheduler to support IPC blocking operations.

### 3. Security and Performance
- All IPC objects are managed as kernel resources with integer handles to prevent direct pointer access.
- Fast-path IPC operations (enqueue/dequeue) are O(1) and avoid heap allocation.
- Minimal `memcpy` and `memset` implemented for freestanding kernel environment.

## Phase 4 & 5: IPC Hardening and Device Infrastructure

### 1. IPC Audit and Hardening
- **SpinLock**: Implemented `acos::hal::SpinLock` and `ScopedLock` for thread-safe kernel operations.
- **Blocking IPC**: Refactored `Channel` and `Notification` to correctly interact with the scheduler. Blocked threads are now removed from the ready queue, and wakeups re-insert them.
- **Wait Queues**: Added internal wait queues to IPC primitives to handle multiple concurrent waiters.
- **Shared Memory**: Clarified `SharedRegion` as a physical memory tracking mechanism for future VMM mapping.

### 2. Device Framework (Phase 5 Foundation)
- **Device/Driver Base**: Defined core classes for hardware management.
- **Device Registry**: Implemented basic tracking for discovered hardware.
- **Driver Tiers**: Established infrastructure for Tier 1 (user-space) and Tier 3 (kernel) driver isolation.

### 3. Build and Runtime
- Unified Makefile with new subsystems.
- Addressed linker warnings and sign-comparison errors.
