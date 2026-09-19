# OS Language (Aurora Systems Language) Stage Evaluation Report

## Executive Summary
This document provides an architectural and strategic evaluation of whether the current project milestone is the appropriate stage to introduce the OS language (**Aurora Systems Language**) for building the Asade operating system userland.

Based on strict adherence to project specifications (`AGENTS.md`), current roadmap maturity (`ROADMAP.md` Phase 11), Native C++23 ABI stability, and runtime toolchain dependencies, the conclusion is:

**NO, this is NOT yet the appropriate stage to introduce Aurora Systems Language.**

Userland development should remain focused on C++23 (supported by `libacos` and freestanding runtime libraries) through Phase 11–14 until Native C++ API/ABI boundaries reach full v1.0 release freeze.

---

## Evaluation Criteria & Analysis

### 1. AGENTS.md Directives & Development Rules
* **Rule**: "Never jump ahead of roadmap phases."
* **Rule**: "Never skip reasoning."
* **Language Specifications**:
  - **Primary Language**: C++23
  - **Secondary Language**: x86_64 Assembly, AArch64 Assembly
  - **Future Language**: Aurora Systems Language (not implemented yet)
* **Analysis**: `AGENTS.md` explicitly designates Aurora Systems Language as a *Future Language* that is not implemented yet. Introducing an unwritten compiler/toolchain at this point directly violates the core directive to strictly follow roadmap phases without skipping ahead.

### 2. Roadmap Maturity (Current Phase: Phase 11)
* **Current Phase**: Phase 11 — Graphics and Input Foundation (Display Server, Compositor, Input Manager, Window System, GUI Framework).
* **Next Phases**:
  - Phase 12: Security Hardening & Capability Auditing
  - Phase 13: Virtualization & Guest Isolation
  - Phase 14: System-wide Optimization & Performance Leadership
* **Analysis**: Asade is actively completing Phase 11. Userland services (e.g., `services/display`, `services/audio`, `userland/shell`, `userland/gui`, `apps/terminal`, `apps/file_manager`, `apps/settings`) are actively being written, refined, and tested in C++20/C++23 using `libacos`. Introducing a custom language before completing desktop/graphics foundation and security hardening would fragment userland development and stall roadmap progress.

### 3. Native API & ABI Stability
* **Native Specs**: `NATIVE_API_SPEC.md`, `SYSTEM_CALL_SPEC.md`, `DRIVER_ABI.md`, `CAPABILITY_SPEC.md`.
* **Freestanding Runtime**: `libs/runtime` provides `acos::Vector`, `acos::String`, `acos::Expected`, `acos::Optional`, `acos::Span`, `acos::Mutex`, etc.
* **Analysis**:
  - Any custom systems language intended for building userland must bind to a stable Native System Call ABI and C-compatible/C++ capability interface.
  - The C++ Native API and capability handle model (`Process`, `Thread`, `Channel`, `Notification`, `SharedRegion`) are currently being refined and stabilized.
  - Attempting to target an unstable Native ABI with a new language compiler creates a moving target, leading to fragile bindings and technical debt.

### 4. Compiler Toolchain & Freestanding Environment
* **Toolchain Requirements**:
  - The kernel and userland build with Clang/GCC targeting `x86_64-unknown-elf` and `x86_64-unknown-windows-coff` (UEFI) using standard Makefile rules.
  - A new OS language requires a specification, standard library, lexer/parser, LLVM code generator or native assembler backend, freestanding runtime support, and integration into the Makefile build system.
  - Diverting engineering resources to compiler development at Phase 11 would distract from core operating system features (graphics, input, VFS, networking).

---

## Strategic Recommendation & Transition Plan

1. **Phase 11–14 (Short/Medium Term)**:
   - Continue building and stabilizing all core userland applications, shell, desktop environment, and system services in C++23 and Assembly.
   - Maintain strict conformance with `AGENTS.md` and `NATIVE_API_SPEC.md`.

2. **Post-Version 1.0 Release (Phase 15 / Future Stage)**:
   - Once Version 1.0 Release Criteria are met (Stable Kernel, Stable APIs, Stable Driver Framework, Security Review Complete):
     - Draft the formal language specification for Aurora Systems Language.
     - Build an LLVM-based compiler for Aurora Systems Language targeting `x86_64-unknown-elf` and `aarch64-unknown-elf`.
     - Create foreign function interface (FFI) bindings for `libacos` and Native Capability Syscalls.
     - Begin porting non-critical userland utilities to Aurora Systems Language incrementally.

---

## Conclusion
Including Aurora Systems Language at this stage is premature and counterproductive to system stability. The project must complete Phase 11–14 in C++23 before initiating custom OS language compiler integration.
