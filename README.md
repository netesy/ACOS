# Asade Operating System

Asade is a capability-based hybrid microkernel operating system built on the ACOS (Adaptive Capability Operating System) kernel.

## Naming Convention

- **Asade**: The complete operating system
- **ACOS**: The kernel component of Asade

## Overview

Asade is designed for:
- Desktop Computing
- Server Computing
- Cloud Infrastructure
- Embedded Systems
- Edge Computing

## Architecture

The system is organized into layers:

- **Layer 0**: Hardware
- **Layer 1**: ACOS Core Kernel
- **Layer 2**: Protected Domains
- **Layer 3**: System Services
- **Layer 4**: Compatibility Layers
- **Layer 5**: Applications

## Key Features

- Capability-based security model
- Hybrid microkernel architecture
- Resource-centric scheduling (CPU, GPU, NPU, DSP, FPGA)
- Local-first distribution philosophy
- POSIX compatibility
- Linux ABI compatibility (planned)

## Documentation

The architecture is defined by the following specifications:

- [AGENTS.md](AGENTS.md) - Development agent prompt and coding standards
- [ARCHITECTURE.md](ARCHITECTURE.md) - Architectural boundaries and principles
- [KERNEL_ARCHITECTURE.md](KERNEL_ARCHITECTURE.md) - Internal kernel architecture
- [SECURITY_MODEL.md](SECURITY_MODEL.md) - Security model and policies
- [DRIVER_GUIDE.md](DRIVER_GUIDE.md) - Driver development guide
- [ROADMAP.md](ROADMAP.md) - Development roadmap
- [NATIVE_API_SPEC.md](NATIVE_API_SPEC.md) - Native API specification
- [SYSTEM_CALL_SPEC.md](SYSTEM_CALL_SPEC.md) - System call specification
- [CAPABILITY_SPEC.md](CAPABILITY_SPEC.md) - Capability system specification
- [IPC_SPEC.md](IPC_SPEC.md) - IPC specification
- [VFS_SPEC.md](VFS_SPEC.md) - Virtual filesystem specification
- [SCHEDULER_SPEC.md](SCHEDULER_SPEC.md) - Scheduler specification
- [HAL_SPEC.md](HAL_SPEC.md) - Hardware abstraction layer specification
- [BOOT_PROTOCOL.md](BOOT_PROTOCOL.md) - Boot protocol specification
- [OBJECT_FORMAT.md](OBJECT_FORMAT.md) - Object format specification
- [DRIVER_ABI.md](DRIVER_ABI.md) - Driver ABI specification
- [KERNEL_CODING_STANDARD.md](KERNEL_CODING_STANDARD.md) - Kernel coding standards
- [TESTING_STANDARD.md](TESTING_STANDARD.md) - Testing standards

## Building

See the [Makefile](Makefile) for build instructions.

## License

[License information to be added]
