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
