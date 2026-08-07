#pragma once

#include <acos/types.h>

namespace acos {

enum class MemoryRegionType : u32 {
    Available = 1,
    Reserved = 2,
    AcpiReclaimable = 3,
    AcpiNvs = 4,
    Unusable = 5,
    KernelCode = 6,
    KernelData = 7,
    Bootloader = 8,
    Framebuffer = 9,
};

struct MemoryRegion {
    u64 base;
    u64 length;
    MemoryRegionType type;
};

struct MemoryMap {
    MemoryRegion* regions;
    u64 count;
};

struct FramebufferInfo {
    u64 base;
    u64 size;
    u32 width;
    u32 height;
    u32 pitch;
    u32 bpp;
    u32 format; // 0 = RGB, 1 = BGR
};

struct CpuInfo {
    u32 cores;
};

struct AcpiInfo {
    u64 rsdp;
};

struct InitrdInfo {
    u64 base;
    u64 size;
};

struct BootInfo {
    MemoryMap* memoryMap;
    CpuInfo* cpuInfo;
    FramebufferInfo* framebuffer;
    AcpiInfo* acpi;
    InitrdInfo* initrd;
    u64 bootTime;
};

} // namespace acos
