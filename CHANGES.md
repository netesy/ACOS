# CHANGES.md - ACOS Core System (Phases 1-11)

## Overview
ACOS core infrastructure is complete. The system now includes a foundational Graphics and Input subsystem, supporting multiple displays, framebuffers, and event-driven user input.

## Phase 11: Graphics and Input Foundation
- **Graphics Manager**: Orchestrates multiple \`DisplayDevice\` and \`Framebuffer\` objects.
- **Software Renderer**: Basic primitives (pixel, rect) and surface management implemented.
- **Font System**: Initial foundation for bitmap font rendering and text output.
- **Input Manager**: Established event queue for handling keyboard and mouse events.
- **Device Support**: Defined interfaces for \`KeyboardDevice\` and \`MouseDevice\`.

## Phase 10: Networking Stack
- **Full Stack**: Functional Ethernet, ARP, IPv4, ICMP, UDP, and TCP state machine foundation.
- **Sockets**: Capability-aware socket layer integrated with the process system.

## Phase 1-9 Consolidation
- **VFS & Storage**: Comprehensive filesystem abstraction and AHCI/SATA storage drivers.
- **Memory & User Mode**: 4-level paging, ELF loading, and Ring 3 transition.
- **Multitasking**: Preemptive-ready scheduler with isolation.

## Security & Architecture
- All system resources (Files, Sockets, Framebuffers, Input) are capability-managed.
- Unified build system using GCC/G++ with comprehensive subsystem coverage.

## Phase 12: Display Server and Compositor
- **Architecture**: Implemented a standalone-ready Display Server architecture.
- **Compositor**: Added a software compositor with support for surface composition, Z-ordering, and damage tracking.
- **Window System**: Established a windowing model with metadata tracking (position, size, visibility, focus).
- **Surface Manager**: Implemented off-screen surface management with double-buffering support.
- **Input Routing**: Added an Input Router to deliver keyboard and mouse events to focused windows.
- **Graphics IPC**: Defined specialized IPC channels (Graphics, Window, Surface) for client-server communication.
- **Security**: Graphical resources are managed via capabilities (CREATE_WINDOW, etc.), ensuring isolation between applications.
