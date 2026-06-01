# TECHNICAL_DEBT_REPORT.md - ACOS Phase 20

## Critical Debt
1. **FPU Context Switching**: Threads currently do not preserve XMM/YMM registers. Required for stable floating-point apps.
2. **AP Trampoline**: `ap_boot.S` needs full implementation to bring secondary cores into 64-bit mode.

## High Priority
1. **PMM Scalability**: Bitmap allocator is O(N). Needs migration to buddy allocator or similar.
2. **TCP State Machine**: Congestion control and retransmission logic are incomplete.

## Architecture Improvements
1. **Package Signatures**: `SignatureVerifier` is currently a success-stub.
2. **Process Resource Tracking**: Automatic cleanup of all resources (FDs, sockets) on process crash.
