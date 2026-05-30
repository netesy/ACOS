# HAL_SPEC.md

Version: 1.0

Status: Core Standard

---

# Purpose

The Hardware Abstraction Layer (HAL) isolates architecture-specific code from the rest of the kernel.

The goal is:

Write the kernel once.

Support multiple architectures.

---

# Supported Architectures

Tier 1

x86_64

ARM64 (AArch64)

Tier 2

RISC-V 64

Future architectures require HAL implementation.

---

# Design Goals

The HAL must provide:

* CPU Abstraction
* Interrupt Abstraction
* Timer Abstraction
* Memory Abstraction
* Context Switching
* Power Management

The kernel must never directly access architecture-specific instructions.

---

# HAL Layout

/kernel
/hal
/common
/x86_64
/arm64
/riscv64

---

# CPU Interface

Required functions:

```cpp
cpu_init()
cpu_id()
cpu_count()
cpu_halt()
cpu_pause()
```

---

# Context Switching Interface

Required:

```cpp
context_create()
context_switch()
context_destroy()
```

Context switching behavior must be identical across architectures.

---

# Interrupt Interface

Required:

```cpp
interrupt_enable()
interrupt_disable()
interrupt_register()
interrupt_ack()
```

---

# Timer Interface

Required:

```cpp
timer_now()
timer_sleep()
timer_frequency()
```

Resolution target:

≤ 1 microsecond

---

# Memory Interface

Required:

```cpp
page_map()
page_unmap()
page_protect()
page_query()
```

---

# Atomic Operations

Required:

```cpp
atomic_load()
atomic_store()
atomic_compare_exchange()
atomic_fetch_add()
```

---

# Synchronization Support

Required:

Mutex

RWLock

Semaphore

Spinlock

Atomics

---

# Power Management

Required:

Sleep

Suspend

Resume

Shutdown

Restart

---

# Architecture Rules

Architecture code must not:

* Implement policy
* Contain scheduler logic
* Contain security decisions

HAL provides mechanisms only.

---

# Testing Requirements

Every architecture must pass:

Boot Tests

Memory Tests

Interrupt Tests

Context Switch Tests

Stress Tests

Performance Benchmarks

before promotion to Tier 1 support.
