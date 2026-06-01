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
    void* testString;
    void* queryMode;
    void* setMode;
    void* setAttribute;
    void* clearScreen;
    void* setCursorPosition;
    void* enableCursor;
    void* mode;
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

struct Time {
    acos::u16 year;
    acos::u8 month;
    acos::u8 day;
    acos::u8 hour;
    acos::u8 minute;
    acos::u8 second;
    acos::u8 pad1;
    acos::u32 nanosecond;
    acos::i16 timeZone;
    acos::u8 daylight;
    acos::u8 pad2;
};

struct FileProtocol {
    acos::u64 revision;
    Status (*open)(FileProtocol* self, FileProtocol** newHandle, const char16_t* fileName, acos::u64 openMode, acos::u64 attributes);
    Status (*close)(FileProtocol* self);
    Status (*deleteFile)(FileProtocol* self);
    Status (*read)(FileProtocol* self, acos::usize* bufferSize, void* buffer);
    Status (*write)(FileProtocol* self, acos::usize* bufferSize, void* buffer);
    Status (*getPosition)(FileProtocol* self, acos::u64* position);
    Status (*setPosition)(FileProtocol* self, acos::u64 position);
    Status (*getInfo)(FileProtocol* self, const Guid* informationType, acos::usize* bufferSize, void* buffer);
    Status (*setInfo)(FileProtocol* self, const Guid* informationType, acos::usize* bufferSize, void* buffer);
    Status (*flush)(FileProtocol* self);
};

struct SimpleFileSystemProtocol {
    acos::u64 revision;
    Status (*openVolume)(SimpleFileSystemProtocol* self, FileProtocol** root);
};

struct SystemTable;

struct BootServices {
    TableHeader header;
    Status (*raiseTPL)(acos::usize newTpl);
    void (*restoreTPL)(acos::usize oldTpl);
    Status (*allocatePages)(AllocateType type, MemoryType memoryType, acos::usize pages, acos::u64* memory);
    Status (*freePages)(acos::u64 memory, acos::usize pages);
    Status (*getMemoryMap)(acos::usize* memoryMapSize, MemoryDescriptor* memoryMap, acos::usize* mapKey, acos::usize* descriptorSize, acos::u32* descriptorVersion);
    Status (*allocatePool)(MemoryType poolType, acos::usize size, void** buffer);
    Status (*freePool)(void* buffer);
    Status (*createEvent)(acos::u32 type, acos::usize notifyTpl, void* notifyFunction, void* notifyContext, Event* event);
    Status (*setTimer)(Event event, int type, acos::u64 triggerTime);
    Status (*waitForEvent)(acos::usize numberOfEvents, Event* event, acos::usize* index);
    Status (*signalEvent)(Event event);
    Status (*closeEvent)(Event event);
    Status (*checkEvent)(Event event);
    Status (*installProtocolInterface)(Handle* handle, const Guid* protocol, int interfaceType, void* interface);
    Status (*reinstallProtocolInterface)(Handle handle, const Guid* protocol, void* oldInterface, void* newInterface);
    Status (*uninstallProtocolInterface)(Handle handle, const Guid* protocol, void* interface);
    Status (*handleProtocol)(Handle handle, const Guid* protocol, void** interface);
    void* reserved;
    Status (*registerProtocolNotify)(const Guid* protocol, Event event, void** registration);
    Status (*locateHandle)(int searchType, const Guid* protocol, void* searchKey, acos::usize* bufferSize, Handle* buffer);
    Status (*locateDevicePath)(const Guid* protocol, void** devicePath, Handle* device);
    Status (*installConfigurationTable)(const Guid* guid, void* table);
    Status (*loadImage)(acos::u8 bootPolicy, Handle parentImageHandle, void* devicePath, void* sourceBuffer, acos::usize sourceSize, Handle* imageHandle);
    Status (*startImage)(Handle imageHandle, acos::usize* exitDataSize, char16_t** exitData);
    Status (*exit)(Handle imageHandle, Status exitStatus, acos::usize exitDataSize, char16_t* exitData);
    Status (*unloadImage)(Handle imageHandle);
    Status (*exitBootServices)(Handle imageHandle, acos::usize mapKey);
    Status (*getNextMonotonicCount)(acos::u64* count);
    Status (*stall)(acos::usize microseconds);
    Status (*setWatchdogTimer)(acos::usize timeout, acos::u64 watchdogCode, acos::usize dataSize, char16_t* watchdogData);
    Status (*connectController)(Handle controllerHandle, Handle* driverImageHandle, void* remainingDevicePath, acos::u8 recursive);
    Status (*disconnectController)(Handle controllerHandle, Handle driverImageHandle, Handle childHandle);
    Status (*openProtocol)(Handle handle, const Guid* protocol, void** interface, Handle agentHandle, Handle controllerHandle, acos::u32 attributes);
    Status (*closeProtocol)(Handle handle, const Guid* protocol, Handle agentHandle, Handle controllerHandle);
    Status (*openProtocolInformation)(Handle handle, const Guid* protocol, void** entryBuffer, acos::usize* entryCount);
    Status (*protocolsPerHandle)(Handle handle, Guid*** protocolBuffer, acos::usize* protocolCount);
    Status (*locateHandleBuffer)(int searchType, const Guid* protocol, void* searchKey, acos::usize* noHandles, Handle** buffer);
    Status (*locateProtocol)(const Guid* protocol, void* registration, void** interface);
    Status (*installMultipleProtocolInterfaces)(Handle* handle, ...);
    Status (*uninstallMultipleProtocolInterfaces)(Handle handle, ...);
    Status (*calculateCrc32)(void* data, acos::usize dataSize, acos::u32* crc32);
    void (*copyMem)(void* destination, void* source, acos::usize length);
    void (*setMem)(void* buffer, acos::usize length, acos::u8 value);
    Status (*createEventEx)(acos::u32 type, acos::usize notifyTpl, void* notifyFunction, const void* notifyContext, const Guid* eventGroup, Event* event);
};

struct LoadedImageProtocol {
    acos::u32 revision;
    Handle parentHandle;
    SystemTable* systemTable;
    Handle deviceHandle;
    void* filePath;
    void* reserved;
    acos::u32 loadOptionsSize;
    void* loadOptions;
    void* imageBase;
    acos::u64 imageSize;
    MemoryType imageCodeType;
    MemoryType imageDataType;
    void (*unload)(Handle imageHandle);
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

enum class GraphicsPixelFormat : acos::u32 {
    PixelRedGreenBlueReserved8BitPerColor = 0,
    PixelBlueGreenRedReserved8BitPerColor = 1,
    PixelBitMask = 2,
    PixelBltOnly = 3,
    PixelFormatMax = 4,
};

struct PixelBitmask {
    acos::u32 redMask;
    acos::u32 greenMask;
    acos::u32 blueMask;
    acos::u32 reservedMask;
};

struct GraphicsOutputModeInformation {
    acos::u32 version;
    acos::u32 horizontalResolution;
    acos::u32 verticalResolution;
    GraphicsPixelFormat pixelFormat;
    PixelBitmask pixelInformation;
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

struct GraphicsOutputProtocol;

using GraphicsOutputProtocolQueryMode = Status (*)(GraphicsOutputProtocol* self,
                                                   acos::u32 modeNumber,
                                                   acos::usize* sizeOfInfo,
                                                   GraphicsOutputModeInformation** info);
using GraphicsOutputProtocolSetMode = Status (*)(GraphicsOutputProtocol* self, acos::u32 modeNumber);

struct GraphicsOutputProtocol {
    GraphicsOutputProtocolQueryMode queryMode;
    GraphicsOutputProtocolSetMode setMode;
    void* blt;
    GraphicsOutputProtocolMode* mode;
};

static constexpr Guid GraphicsOutputProtocolGuid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
static constexpr Guid LoadedImageProtocolGuid = {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
static constexpr Guid SimpleFileSystemProtocolGuid = {0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

} // namespace efi
