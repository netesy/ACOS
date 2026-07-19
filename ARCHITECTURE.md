# ARCHITECTURE.md

Version: 1.0

Status: Constitutional

---

# Purpose

This document defines the architectural boundaries of Asade.

Any implementation detail may change.

These principles may not.

---

# Naming Convention

- **Asade**: The complete operating system
- **ACOS**: The kernel component of Asade

---

# System Vision

Asade is a capability-based hybrid microkernel operating system built on the ACOS kernel, designed for:

* Desktop Computing
* Server Computing
* Cloud Infrastructure
* Embedded Systems
* Edge Computing

The architecture prioritizes:

1. Security
2. Reliability
3. Maintainability
4. Performance
5. Compatibility

---

# Architectural Layers

Layer 0

Hardware

Layer 1

ACOS Core Kernel (Asade Kernel)

Layer 2

Protected Domains

Layer 3

System Services

Layer 4

Compatibility Layers

Layer 5

Applications

---

# Kernel Responsibilities

The kernel exists only to provide mechanisms.

The kernel does not provide policies.

Kernel responsibilities:

* Scheduling
* Memory Management
* Capability Management
* IPC
* Interrupt Management
* Security Enforcement
* Device Framework

---

# Services Responsibilities

Services provide policies.

Examples:

Filesystem Service

Network Service

Graphics Service

Audio Service

Identity Service

Container Service

---

# Resource Model

Everything is represented as a resource.

Examples:

* File
* Device
* Process
* Socket
* GPU Queue
* Memory Region
* IPC Channel

Resources are accessed through handles.

Handles are backed by capabilities.

---

# Security Boundaries

The following boundaries must always exist:

Kernel Boundary

Domain Boundary

Process Boundary

Capability Boundary

Network Boundary

No subsystem may bypass these boundaries.

---

# Driver Architecture

Tier 1

User-space Drivers

Tier 2

Protected-Domain Drivers

Tier 3

Kernel Drivers

Default destination for new drivers:

Tier 1

---

# Scheduling Model

Asade schedules:

* CPU
* GPU
* NPU
* DSP
* FPGA

as first-class resources.

Scheduling is resource-centric rather than CPU-centric.

---

# Distribution Philosophy

Asade is Local-First.

Distributed services are optional.

Network latency must remain visible.

Remote resources must never masquerade as local resources.

---

# Compatibility Philosophy

Native APIs are preferred.

POSIX compatibility is mandatory.

Linux ABI compatibility is highly desirable.

---

# Architectural Constraints

No subsystem may:

* Require global mutable state
* Require root authority
* Require network connectivity for local operation
* Depend on hidden capabilities

---

# Success Criteria

A successful Asade system:

* Survives driver crashes
* Survives service crashes
* Limits security compromise scope
* Maintains predictable performance
* Supports existing software ecosystems
