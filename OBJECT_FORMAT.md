# OBJECT_FORMAT.md

Version: 1.0

Status: Core Standard

---

# Purpose

Defines executable and library format.

---

# Strategy

Adopt ELF64 as foundation.

Extend where necessary.

Avoid inventing a new binary format.

---

# Supported Objects

Executable

Shared Library

Kernel Module

Driver Module

Service Package

---

# Required Sections

.text

.data

.rodata

.bss

.symtab

.strtab

---

# ACOS Sections

.acos.capabilities

.acos.manifest

.acos.permissions

.acos.metadata

---

# Manifest Example

```json
{
  "name": "filesystem",
  "version": "1.0",
  "permissions": [
    "storage.read",
    "storage.write"
  ]
}
```

---

# Signing

Optional for development.

Required for production repositories.

Supported:

Ed25519

X509

Future extensions allowed.
