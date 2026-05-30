# SYSTEM_CALL_SPEC.md

Version: 1.0

Status: Core Standard

---

# Syscall Philosophy

Minimal syscall surface.

Prefer capability operations.

---

# Categories

Process

Thread

Memory

IPC

Capabilities

Devices

Time

Scheduling

---

# Examples

Process

```c
sys_process_create()
sys_process_exit()
```

Thread

```c
sys_thread_create()
sys_thread_join()
```

Memory

```c
sys_memory_map()
sys_memory_unmap()
```

IPC

```c
sys_channel_send()
sys_channel_receive()
```

Capability

```c
sys_cap_create()
sys_cap_transfer()
sys_cap_revoke()
```

---

# Design Rules

Every syscall:

Validates capabilities

Returns Result code

Provides audit hooks

No hidden side effects.
