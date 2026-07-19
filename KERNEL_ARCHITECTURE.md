# KERNEL_ARCHITECTURE.md

Version: 1.0

Status: Constitutional

---

# Purpose

This document defines the internal architecture of the ACOS kernel, which is the kernel component of the Asade operating system.

The kernel is the most privileged component of the system.

Changes to kernel architecture require formal review.

---

# Naming Convention

- **Asade**: The complete operating system
- **ACOS**: The kernel component of Asade

This document specifically describes the ACOS kernel architecture.

---

# Kernel Philosophy

The kernel exists to provide mechanisms.

Policies belong in services.

The kernel must remain:

* Small
* Auditable
* Predictable
* Secure
* Fast

---

# Kernel Responsibilities

The kernel owns only:

* Scheduling
* Memory Management
* Capability Management
* IPC
* Interrupt Management
* Security Enforcement
* Device Framework

Everything else belongs outside the kernel.

---

# Kernel Subsystems

## Scheduler

Location

/kernel/scheduler

Responsibilities

* Thread scheduling
* Core allocation
* Load balancing
* Priority enforcement
* Realtime execution
* Accelerator scheduling

Supported Classes

Interactive

Realtime

Batch

Background

Accelerator

Requirements

O(log n) or better scheduling operations.

Starvation prevention required.

---

## Memory Manager

Location

/kernel/memory

Responsibilities

* Physical Memory Management
* Virtual Memory Management
* Page Mapping
* NUMA Awareness
* Huge Pages
* Shared Memory Regions

Requirements

Zero-copy support.

Explicit ownership tracking.

No hidden allocations.

---

## Capability Manager

Location

/kernel/capabilities

Responsibilities

* Capability Creation
* Capability Validation
* Capability Transfer
* Capability Revocation
* Capability Auditing

Requirements

Capabilities must be unforgeable.

Capability checks must be constant time where possible.

---

## IPC Manager

Location

/kernel/ipc

Responsibilities

* Channel Management
* Message Delivery
* Notification Delivery
* Shared Region Registration

IPC Types

Channel IPC

Shared Memory IPC

Notification IPC

Requirements

Low-latency message delivery.

Deterministic behavior under load.

---

## Security Manager

Location

/kernel/security

Responsibilities

* Domain Enforcement
* Capability Enforcement
* Policy Hooks
* Security Auditing

Requirements

All privileged operations validated.

No implicit privilege escalation.

---

## Interrupt Manager

Location

/kernel/interrupts

Responsibilities

* Interrupt Routing
* APIC Management
* MSI/MSI-X Support
* Inter-Processor Interrupts

Requirements

Minimal interrupt latency.

Interrupt storms must be detectable.

---

## Device Framework

Location

/kernel/device

Responsibilities

* Device Discovery
* Device Enumeration
* Driver Binding
* Device Capability Creation

Requirements

Drivers remain external whenever possible.

---

# Process Model

Process

Owns:

* Address Space
* Capabilities
* Threads

---

# Thread Model

Thread states:

Created

Ready

Running

Blocked

Suspended

Terminated

---

# Domain Model

Domains are security containers.

Examples:

System Domain

Application Domain

Driver Domain

Container Domain

Guest Domain

Domains restrict:

Memory

Devices

Network Access

Filesystem Access

Capabilities

---

# Resource Handles

Every kernel-visible object has:

Resource ID

Type

Owner

Capability Set

Lifetime

Audit Metadata

---

# Kernel IPC Design

Channels

Small messages.

Shared Regions

Large data transfer.

Notifications

Events and signals.

Remote communication is not handled by the kernel.

---

# Synchronization

Allowed

Mutex

RW Lock

Semaphore

Atomic Operations

Discouraged

Global Locks

Requirements

Fine-grained locking preferred.

Lock ordering must be documented.

---

# Failure Philosophy

Kernel failures are unacceptable.

Driver failures are acceptable.

Service failures are acceptable.

Subsystem isolation is mandatory.

---

# Performance Goals

Context Switch

< 1 microsecond target

IPC Round Trip

< 2 microseconds target

Capability Validation

Near constant time

Boot Time

< 1 second target on modern hardware

---

# Kernel Size Targets

Ideal

200,000 lines

Maximum

500,000 lines

Exceeding limits requires architecture review.

---

# Architecture Review Triggers

Required when adding:

New Kernel Subsystem

New Scheduler

New Memory Manager

New Driver Tier

New Security Model

New Resource Type

New IPC Primitive
