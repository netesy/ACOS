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

## Phase 13: Desktop Shell and Native GUI Framework
- **GUI Toolkit**: Implemented a native, lightweight GUI toolkit in `userland/gui/`.
  - Base `Widget` class with event handling and drawing abstractions.
  - Basic widgets: `Button`, `Label`, `TextBox`, `ListView`, and `WindowWidget`.
  - Layout system with support for Vertical and Horizontal stacking.
  - Theme system for consistent visual styling across applications.
- **Desktop Shell**: Created the ACOS desktop environment in `userland/shell/`.
  - `Taskbar` for running applications and system status.
  - `Launcher` for application discovery and startup.
  - `NotificationCenter` for system and application notifications.
  - `SessionManager` to manage user session lifecycles.
- **System Applications**: Developed core native applications using the GUI toolkit.
  - `Terminal`: Basic command-line interface.
  - `File Manager`: VFS-integrated directory and file browser.
  - `Settings`: Interface for system and theme configuration.
  - `System Monitor`: Real-time display of system resources (CPU, Memory, Processes).
- **Security**: Established application isolation; apps communicate through the toolkit and window system, maintaining kernel and display server security boundaries.

## Phase 14: Audio System and Multimedia Foundation
- **Audio Architecture**: Implemented a comprehensive audio stack including drivers, kernel management, and a user-space audio service.
- **Audio Service**: Created `AudioServer` in `services/audio/` to handle client requests, stream management, and mixing.
- **Audio Mixer**: Developed a software mixer supporting multiple concurrent streams, per-stream volume, and master volume control.
- **Kernel Audio**: Established `AudioManager` and `AudioDevice` in `kernel/audio/` for hardware abstraction and enumeration.
- **Drivers**:
  - `VirtIO Sound`: Initial driver implementation for QEMU-based audio playback.
  - `Intel HD Audio (HDA)`: Foundation for PCI-based audio controller discovery and codec enumeration.
- **Capability Model**: Integrated audio operations into the ACOS capability system (`AUDIO_PLAYBACK`, `AUDIO_RECORD`, etc.).
- **GUI Integration**:
  - Added Audio Settings to the Settings application.
  - Implemented a Volume Indicator in the Taskbar for quick volume control and status.
- **Performance**: Architecture supports shared-memory ring buffers for low-latency audio processing.

## Phase 15: POSIX Compatibility Layer
- **POSIX Runtime**: Implemented `libposix` providing source compatibility for POSIX-compliant applications.
- **Process API**: Added support for `execve`, `waitpid`, `getpid`, etc., mapping to the ACOS Process Manager.
- **File API**: Integrated `open`, `read`, `write`, and `lseek` with the ACOS VFS.
- **Socket API**: Mapped POSIX socket calls to the ACOS Networking Stack, maintaining capability enforcement.
- **Thread API**: Provided `pthread_create` and `pthread_join` as wrappers for the native ACOS threading model.
- **Signal API**: Implemented basic signal handling (`SIGINT`, `SIGKILL`, etc.) using ACOS event delivery.
- **Memory API**: Added `mmap` and `munmap` support mapping to ACOS address space management.
- **Libc Foundation**: Developed a native `libc` providing essential string, memory, and stdio functions.
- **Security**: Ensured all POSIX wrappers respect ACOS capabilities, domains, and security boundaries.
