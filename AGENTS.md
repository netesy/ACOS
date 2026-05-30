# AGENTS.md

## ACOS Development Constitution

Version: 1.1 (Phase 10 Update)

Status: Mandatory

Applies To:

* Human Contributors
* AI Coding Agents
* CI Systems
* Code Generators
* External Contributors

---

# Mission

ACOS exists to build a modern operating system based on:

* Capability Security
* Hybrid Microkernel Design
* Driver Isolation
* POSIX Compatibility
* Heterogeneous Compute Scheduling
* Long-Term Maintainability

---

# Prime Directive

The system must remain:

1. Secure
2. Maintainable
3. Performant
4. Observable
5. Compatible

---

# Architectural Principles

## AP-1: Kernel Minimalism
Kernel code is allowed only when required for scheduling, memory, IPC, capabilities, interrupts, security, device framework, or networking core.

## AP-2: Capability First
Every resource must be accessible through capabilities.

## AP-3: Explicit Costs
Latency and resource costs must remain visible.

## AP-4: Local First
Distributed systems supported but never assumed.

## AP-5: Isolation By Default
Subsystem failures must be contained.

## AP-6: Resource Ownership
Every resource must have an owner and explicit lifetime.

---

# Kernel Rules

## Allowed
* Scheduling
* Memory Management
* Capability Management
* IPC
* Interrupt Routing
* Core Security
* Device Framework (Control Plane)
* Networking Stack (Core Protocols)

## Forbidden
* GUI Logic
* Package Management
* Browser Components
* Application Logic

---

# AI Agent Rules

AI agents may generate code, tests, and documentation.
AI agents may not bypass architecture rules or ignore benchmarks.

---

# Final Principle

Every contributor must leave the system Safer, Simpler, More Observable, and More Maintainable than they found it.
