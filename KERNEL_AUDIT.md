# ACOS Kernel Audit - Phase 7

## 1. Context Switching
- **Status**: VERIFIED
- **Logic**: `context_switch` (switch.S) correctly saves/restores `rbp`, `rbx`, `r12-r15`.
- **Isolation**: `switch_to` (scheduler.cpp) updates `CR3` per process, ensuring address space isolation during task switches.
- **Note**: FPU/SSE state saving not yet implemented (required for Phase 8).

## 2. Ring 3 Execution
- **Status**: PARTIAL (Infrastructure Ready)
- **GDT**: Includes Ring 3 segments (User Code/Data) and TSS foundation.
- **Syscall**: `syscall_entry` implemented with `swapgs` and stack switching.
- **Requirement**: Per-CPU `GS` base initialization is required for multi-core or robust syscall handling.

## 3. ELF Loading & Entry Points
- **Status**: VERIFIED
- **Loader**: `ElfLoader` correctly parses program headers, maps segments using VMM, and respects `PF_W`/`PF_X` flags.
- **Entry**: Entry point is captured from ELF header.
- **Refinement**: Initial thread context priming (setting RIP to entry point) is implemented in `process_loader`.

## 4. Address Space Isolation
- **Status**: VERIFIED
- **Mechanism**: Per-process PML4.
- **Enforcement**: `AddressSpace::map` applies `User` bit only to user mappings. Kernel memory identity-mapped but protected by lack of `User` bit in higher levels (future enhancement: high-half kernel).

## 5. IPC Blocking & Waking
- **Status**: VERIFIED
- **Thread Safety**: All IPC primitives (`Channel`, `Notification`) use `SpinLock` and `ScopedLock`.
- **Scheduler Integration**: `block_thread` correctly removes TCB from `g_ready_queue`. `wake_thread` re-inserts and sets state to `Ready`.
- **Wait Queues**: Primitives maintain internal waiter lists to prevent lost signals.

## Conclusion
Core infrastructure for ACOS Phase 7 is logically sound and follows the architectural specifications.
