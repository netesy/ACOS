# AGENTS.md

## ACOS Development Constitution

Version: 1.0

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

Every change must advance these goals.

No contribution may violate them.

---

# Prime Directive

The system must remain:

1. Secure
2. Maintainable
3. Performant
4. Observable
5. Compatible

When tradeoffs exist:

Security > Correctness > Maintainability > Performance > Convenience

---

# Architectural Principles

## AP-1: Kernel Minimalism

The kernel is not a dumping ground.

Kernel code is allowed only when one of the following is true:

* Required for scheduling
* Required for memory management
* Required for IPC
* Required for capabilities
* Required for interrupts
* Required for core security
* Required for device framework operation

Everything else belongs outside the kernel.

---

## AP-2: Capability First

Every resource must be accessible through capabilities.

Never introduce:

* Global mutable state
* Implicit permissions
* Hidden privileges

Every access path must be auditable.

---

## AP-3: Explicit Costs

The system must never hide expensive operations.

Examples:

Good:

remote.open()

Bad:

open()

when network communication occurs.

Latency and resource costs must remain visible.

---

## AP-4: Local First

The operating system assumes local execution.

Distributed systems are supported but never assumed.

No subsystem may require network availability to function locally.

---

## AP-5: Isolation By Default

Subsystem failures must be contained.

Preferred failure scope:

Driver Crash
→ Driver Restart

not

Driver Crash
→ Kernel Panic

---

## AP-6: Resource Ownership

Every resource must have:

* Owner
* Lifetime
* Capability Set
* Accounting Metadata

No orphaned ownership.

---

# Repository Structure

/acos

/kernel
/memory
/scheduler
/ipc
/security
/device

/services
/filesystem
/network
/graphics
/audio

/drivers
/tier1
/tier2
/tier3

/libs
/runtime
/posix
/nativeapi

/tools
/build
/debug
/profiling

/tests

/docs

---

# Kernel Rules

## Allowed

* Scheduling
* Memory Management
* Capability Management
* IPC
* Interrupt Routing
* Core Security

## Forbidden

* GUI Logic
* Package Management
* Browser Components
* Database Logic
* Application Logic

---

# Capability Rules

Capabilities must be:

* Transferable
* Revocable
* Auditable
* Serializable

Capabilities must never:

* Grant implicit authority
* Escalate automatically
* Depend on global state

---

# Driver Rules

## Tier 1

User Space

Default destination for all new drivers.

Contributors must justify promotion.

---

## Tier 2

Protected Domains

Allowed only when:

* Performance requirements justify it
* Measured benchmarks exist

---

## Tier 3

Kernel Drivers

Require:

* Design Review
* Benchmark Evidence
* Security Review

Kernel driver additions are exceptional events.

---

# IPC Rules

Use the simplest mechanism possible.

Priority:

1. Direct Call
2. Shared Memory
3. Local IPC
4. Remote RPC

Never use Remote RPC when Local IPC suffices.

Never use IPC when a direct call is sufficient.

---

# Scheduling Rules

The scheduler owns:

* CPU Allocation
* GPU Allocation
* NPU Allocation
* Accelerator Allocation

New schedulers must provide:

* Fairness analysis
* Starvation analysis
* Complexity analysis

---

# Memory Rules

Every allocation strategy must document:

* Fragmentation impact
* NUMA impact
* Performance impact
* Failure behavior

Memory ownership must be explicit.

No hidden allocation paths.

---

# Security Rules

All code must assume hostile input.

Trust nothing.

Validate everything.

Required reviews:

* Privilege changes
* Capability changes
* IPC changes
* Driver changes

---

# Performance Rules

Performance claims require benchmarks.

Required:

* Before benchmark
* After benchmark
* Hardware specification

No benchmark.

No performance claim.

---

# API Design Rules

APIs must be:

* Explicit
* Predictable
* Versioned

Avoid:

* Hidden side effects
* Global state
* Magic behavior

Good:

ResourceHandle file

Bad:

GlobalFileManager::Current()

---

# Error Handling

Every failure must produce:

* Error Code
* Error Category
* Diagnostic Context

No silent failures.

No catch-all error suppression.

---

# Logging Rules

Logs must be:

* Structured
* Machine Readable
* Filterable

Every log requires:

* Timestamp
* Component
* Severity
* Message

---

# Testing Requirements

Every contribution must include:

* Unit Tests
* Integration Tests

Critical subsystems require:

* Fuzz Tests
* Stress Tests

Security-sensitive code requires:

* Adversarial Tests

---

# Documentation Requirements

Every subsystem must include:

* Purpose
* Design
* Data Flow
* Failure Modes
* Performance Notes

Undocumented code is incomplete code.

---

# Code Review Checklist

Reviewers must ask:

1. Does this belong in kernel space?
2. Can this be isolated further?
3. Does it introduce hidden authority?
4. Is resource ownership clear?
5. Is performance measured?
6. Is failure behavior documented?
7. Is compatibility preserved?

Any "No" blocks approval.

---

# Technical Debt Policy

Temporary solutions require:

* Justification
* Expiration Plan
* Tracking Issue

Permanent temporary fixes are forbidden.

---

# Backward Compatibility

Breaking changes require:

* Migration Plan
* Compatibility Layer
* Deprecation Window

Compatibility is a feature.

---

# AI Agent Rules

AI agents may:

* Generate code
* Generate tests
* Generate documentation

AI agents may not:

* Bypass architecture rules
* Introduce hidden dependencies
* Ignore benchmarks
* Skip tests

Generated code is held to the same standard as human code.

---

# Final Principle

Every contributor must leave the system:

Safer,
Simpler,
More Observable,
More Maintainable,

than they found it.
