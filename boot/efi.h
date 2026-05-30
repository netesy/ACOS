#pragma once

#include <acos/types.h>

namespace efi {

using Status = acos::usize;
using Handle = void*;
using Event = void*;

struct Guid {
    acos::u32 data1;
    acos::u16 data2;
    acos::u16 data3;
    acos::u8  data4[8];
};

struct TableHeader {
    acos::u64 signature;
    acos::u32 revision;
    acos::u32 headerSize;
    acos::u32 crc32;
    acos::u32 reserved;
};

struct SimpleTextOutputProtocol {
    void* reset;
    Status (*outputString)(SimpleTextOutputProtocol* self, const char16_t* string);
    // ... more methods omitted for brevity
};

struct MemoryDescriptor {
    acos::u32 type;
    acos::u64 physicalStart;
    acos::u64 virtualStart;
    acos::u64 numberOfPages;
    acos::u64 attribute;
};

enum class AllocateType {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
};

enum class MemoryType {
    ReservedMemoryType,
    LoaderCode,
    LoaderData,
    BootServicesCode,
    BootServicesData,
    RuntimeServicesCode,
    RuntimeServicesData,
    ConventionalMemory,
    UnusableMemory,
    ACPIReclaimMemory,
    ACPIMemoryNVS,
    MemoryMappedIO,
    MemoryMappedIOPortSpace,
    PalCode,
    PersistentMemory,
    MaxMemoryType
};

struct BootServices {
    TableHeader header;
    void* raiseTPL;
    void* restoreTPL;
    Status (*allocatePages)(AllocateType type, MemoryType memoryType, acos::usize pages, acos::u64* memory);
    Status (*freePages)(acos::u64 memory, acos::usize pages);
    Status (*getMemoryMap)(acos::usize* memoryMapSize, MemoryDescriptor* memoryMap, acos::usize* mapKey, acos::usize* descriptorSize, acos::u32* descriptorVersion);
    Status (*allocatePool)(MemoryType poolType, acos::usize size, void** buffer);
    Status (*freePool)(void* buffer);
    // ... many methods omitted
    void* createEvent;
    void* setTimer;
    void* waitForEvent;
    void* signalEvent;
    void* closeEvent;
    void* checkEvent;
    void* installProtocolInterface;
    void* reinstallProtocolInterface;
    void* uninstallProtocolInterface;
    Status (*handleProtocol)(Handle handle, const Guid* protocol, void** interface);
    void* reserved;
    void* registerProtocolNotify;
    Status (*locateHandle)(int searchType, const Guid* protocol, void* searchKey, acos::usize* bufferSize, Handle* buffer);
    void* locateDevicePath;
    void* installConfigurationTable;
    void* loadImage;
    void* startImage;
    void* exit;
    void* unloadImage;
    Status (*exitBootServices)(Handle imageHandle, acos::usize mapKey);
    // ... more methods
};

struct SystemTable {
    TableHeader header;
    char16_t* firmwareVendor;
    acos::u32 firmwareRevision;
    Handle consoleInHandle;
    void* conIn;
    Handle consoleOutHandle;
    SimpleTextOutputProtocol* conOut;
    Handle standardErrorHandle;
    SimpleTextOutputProtocol* stdErr;
    void* runtimeServices;
    BootServices* bootServices;
    acos::usize numberOfTableEntries;
    void* configurationTable;
};

// Graphics Output Protocol
struct GraphicsOutputModeInformation {
    acos::u32 version;
    acos::u32 horizontalResolution;
    acos::u32 verticalResolution;
    int pixelFormat;
    acos::u32 pixelInformation[3]; // Simplified
    acos::u32 pixelsPerScanLine;
};

struct GraphicsOutputProtocolMode {
    acos::u32 maxMode;
    acos::u32 mode;
    GraphicsOutputModeInformation* info;
    acos::usize sizeOfInfo;
    acos::u64 frameBufferBase;
    acos::usize frameBufferSize;
};

struct GraphicsOutputProtocol {
    void* queryMode;
    void* setMode;
    void* blt;
    GraphicsOutputProtocolMode* mode;
};

static constexpr Guid GraphicsOutputProtocolGuid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xde, 0x80, 0x51, 0x6a}};
static constexpr Guid LoadedImageProtocolGuid = {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
static constexpr Guid SimpleFileSystemProtocolGuid = {0x0964e5b2, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

} // namespace efi
