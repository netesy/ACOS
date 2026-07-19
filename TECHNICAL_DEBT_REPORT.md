# TECHNICAL_DEBT_REPORT.md - Asade Phase 20

## Critical Debt
1. **FPU Context Switching**: Threads currently do not preserve XMM/YMM registers. Required for stable floating-point apps. (STILL OPEN - `switch.S` only saves GPRs, no fxsave/fxrstor)
2. ~~**AP Trampoline**: `ap_boot.S` needs full implementation to bring secondary cores into 64-bit mode.~~ (RESOLVED - Full implementation present with real mode → protected mode → long mode transition)

## High Priority
1. **PMM Scalability**: Bitmap allocator is O(N). Needs migration to buddy allocator or similar. (STILL OPEN - `pmm.cpp` still uses bitmap)
2. **TCP State Machine**: Congestion control and retransmission logic are incomplete. (STILL OPEN - `tcp.cpp` only has basic parsing, no state machine implementation)

## Architecture Improvements
1. **Package Signatures**: SHA-256 verification is implemented; Ed25519 remains fail-closed until curve verification is available. (STILL OPEN - `signature.cpp` Ed25519 returns false)
2. **Process Resource Tracking**: Automatic cleanup of all resources (FDs, sockets) on process crash. (STILL OPEN - `ProcessTerminate` syscall exists but doesn't clean up resources)

## New Debt
1. **Inter Font Download**: `inter_data.h` contains placeholder font data. Inter TTF font needs to be downloaded from https://rsms.me/inter/ for proper UI rendering.
