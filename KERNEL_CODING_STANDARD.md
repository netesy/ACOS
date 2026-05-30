# KERNEL_CODING_STANDARD.md

Version: 1.0

Status: Mandatory

---

# Purpose

Defines implementation rules for all kernel code.

These rules override contributor preferences.

---

# Primary Principles

1. Correctness
2. Security
3. Simplicity
4. Performance

Never sacrifice correctness for speed.

---

# Approved Languages

Core Kernel

Rust preferred

C++ permitted

---

# Forbidden Languages

Managed runtimes

Garbage-collected languages

Scripting languages

inside kernel space.

---

# Memory Allocation

Dynamic allocation is discouraged on hot paths.

Allowed:

Initialization

Setup

Rare operations

Avoid:

Interrupt handlers

Scheduler hot paths

IPC fast paths

---

# Error Handling

Every failure must be handled.

Forbidden:

Ignoring return values

Silent recovery

Empty catch blocks

---

# Logging

Required fields:

Timestamp

Subsystem

Severity

Message

---

# Assertions

Allowed:

Development builds

Testing builds

Forbidden:

Production crash-inducing assertions

Production assertions must degrade gracefully.

---

# Global State

Discouraged.

Allowed only when:

Architecturally necessary.

Must be documented.

---

# Synchronization Rules

Preferred:

Atomics

Fine-grained locks

Discouraged:

Global kernel locks

Required:

Lock hierarchy documentation.

---

# Unsafe Code

Rust:

unsafe blocks require justification comments.

C++:

manual memory operations require review.

---

# Resource Ownership

Every resource must have:

Owner

Lifetime

Cleanup path

Audit trail

---

# API Design Rules

Kernel APIs must be:

Explicit

Deterministic

Versioned

No hidden behavior.

---

# Complexity Limits

Target:

O(1)

Preferred:

O(log n)

Avoid:

O(n²)

in kernel paths.

---

# Security Rules

Never trust:

User input

Driver input

Network input

IPC input

Everything must be validated.

---

# Performance Rules

Optimizations require:

Benchmark

Comparison

Regression Test

No benchmark.

No optimization merge.

---

# Review Requirements

Required reviewers:

Architecture

Security

Performance

for critical kernel changes.

---

# Documentation Requirements

Every subsystem must include:

Purpose

Architecture

Data Flow

Failure Modes

Performance Characteristics

Undocumented code is incomplete code.
