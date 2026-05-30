# CHANGES.md - ACOS Core System (Phases 1-10)

## Overview
ACOS infrastructure now includes a foundational Networking Stack, real storage drivers, and a robust microkernel core. The system is capability-managed and supports isolated user-mode processes.

## Phase 10: Networking Stack Foundation
- **NetDevice Layer**: Defined abstract network device interface with MAC/MTU support.
- **VirtIO-Net Driver**: Implemented early VirtIO-Net support for QEMU environments.
- **Ethernet**: Added frame parsing and construction logic.
- **ARP**: Established address resolution protocol foundation.
- **IPv4 & ICMP**: Implemented IPv4 header handling and ICMP echo (ping) support.
- **UDP & TCP**: Implemented functional transport layers with socket dispatching and state machine foundation.
- **Socket Layer**: Functional socket abstraction with UDPSocket and TCPSocket implementations.
- **Network Manager**: Unified packet dispatching and device coordination.

## Subsystems (Phase 1-9 Consolidation)
- **VFS & Storage**: Advanced filesystem abstraction and AHCI/SATA storage support.
- **Process System**: ELF64 loading and user-mode runtime foundation.
- **Multitasking**: Round-robin scheduler with proper isolation.

## Toolchain & Build
- Migrated to GCC/G++ build system with unified Makefile targets.
- Updated AGENTS.md for Phase 10 standards.

## Verification
- Verified full networking stack build.
- Successful audit of socket management and packet dispatch logic.
