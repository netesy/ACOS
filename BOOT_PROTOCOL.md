# BOOT_PROTOCOL.md

Version: 1.0

Status: Core Standard

---

# Purpose

Defines how firmware transfers control to ACOS.

Supported firmware:

* UEFI 2.x
* Future ACOS Boot Protocol loaders

Legacy BIOS is not supported.

---

# Boot Stages

Stage 0

Firmware

↓

Stage 1

Boot Manager

↓

Stage 2

Kernel Loader

↓

Stage 3

Kernel Initialization

↓

Stage 4

Core Services

↓

Stage 5

System Services

↓

Stage 6

User Session

---

# Kernel Entry

Bootloader must provide:

BootInfo structure.

```c
struct BootInfo
{
    MemoryMap* memoryMap;
    CpuInfo* cpuInfo;
    FramebufferInfo* framebuffer;
    AcpiInfo* acpi;
    InitrdInfo* initrd;
    uint64_t bootTime;
};
```

Kernel receives:

```c
void kernelMain(BootInfo* info);
```

---

# Required Memory Information

Physical Memory Regions

Reserved Regions

ACPI Regions

Framebuffer Regions

Kernel Image Regions

Initrd Regions

---

# CPU Requirements

x86_64

ARM64

Future architectures supported through HAL.

---

# Early Console

Must support:

Framebuffer Text Output

Serial Output

Panic Output

before scheduler initialization.

---

# Initrd

Initial RAM disk contains:

Core Services

Driver Packages

Configuration

Recovery Tools

---

# Secure Boot

Optional but recommended.

Supported:

UEFI Secure Boot

Measured Boot

TPM Integration

---

# Boot Failure Policy

Failure must:

Display Diagnostic

Emit Serial Log

Preserve Panic Information

Never silently reboot.
