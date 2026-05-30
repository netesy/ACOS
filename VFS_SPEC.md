# VFS_SPEC.md

Version: 1.0

Status: Core Standard

---

# Purpose

Unified storage abstraction.

---

# Resource Types

File

Directory

Mount

Device

Pipe

Socket

---

# Path Model

```text
/
├── system
├── users
├── devices
├── services
└── mounts
```

---

# Mount Types

Local

Network

Virtual

Temporary

---

# VFS Operations

Open

Close

Read

Write

Delete

Rename

Enumerate

Query

---

# Permissions

Capability-based.

POSIX permissions optional compatibility layer.

---

# Caching

User-space cache.

Kernel fast-path optional.

---

# Journaling

Supported.

Filesystem-specific implementation.
