#include <boot/efi.h>
#include <acos/boot_info.h>

extern "C" efi::Status efi_main(efi::Handle imageHandle, efi::SystemTable* systemTable) {
    systemTable->conOut->outputString(systemTable->conOut, u"ACOS Bootloader Starting...\r\n");

    // 1. Get Graphics Output Protocol
    efi::GraphicsOutputProtocol* gop = nullptr;
    efi::Status status = systemTable->bootServices->handleProtocol(
        systemTable->consoleOutHandle,
        &efi::GraphicsOutputProtocolGuid,
        (void**)&gop
    );

    if (status != 0 || !gop) {
        systemTable->conOut->outputString(systemTable->conOut, u"Failed to get GOP\r\n");
        return status;
    }

    // 2. Prepare BootInfo
    static acos::BootInfo bootInfo = {};
    static acos::FramebufferInfo fbInfo = {};

    fbInfo.base = gop->mode->frameBufferBase;
    fbInfo.size = gop->mode->frameBufferSize;
    fbInfo.width = gop->mode->info->horizontalResolution;
    fbInfo.height = gop->mode->info->verticalResolution;
    fbInfo.pitch = gop->mode->info->pixelsPerScanLine;
    fbInfo.bpp = 32; // Standard for UEFI GOP

    bootInfo.framebuffer = &fbInfo;

    // 3. Get Memory Map
    acos::usize memoryMapSize = 0;
    efi::MemoryDescriptor* memoryMap = nullptr;
    acos::usize mapKey = 0;
    acos::usize descriptorSize = 0;
    acos::u32 descriptorVersion = 0;

    systemTable->bootServices->getMemoryMap(&memoryMapSize, nullptr, &mapKey, &descriptorSize, &descriptorVersion);
    memoryMapSize += 2 * descriptorSize; // Add some extra space
    systemTable->bootServices->allocatePool(efi::MemoryType::LoaderData, memoryMapSize, (void**)&memoryMap);
    systemTable->bootServices->getMemoryMap(&memoryMapSize, memoryMap, &mapKey, &descriptorSize, &descriptorVersion);

    // TODO: Convert UEFI Memory Map to ACOS Memory Map
    // For Phase 1, we just pass the raw pointer or a simplified version
    static acos::MemoryMap acosMap = {};
    bootInfo.memoryMap = &acosMap;

    systemTable->conOut->outputString(systemTable->conOut, u"Exiting Boot Services...\r\n");

    // 4. Exit Boot Services
    status = systemTable->bootServices->exitBootServices(imageHandle, mapKey);
    if (status != 0) {
        systemTable->conOut->outputString(systemTable->conOut, u"Failed to exit boot services\r\n");
        return status;
    }

    // 5. Jump to Kernel (placeholder for Phase 1)
    // In a real implementation, we would have loaded the ELF and jumped to its entry point.
    // For now, we'll assume the kernel is at a fixed location or we just halt.

    while(1) {
        __asm__("hlt");
    }

    return 0;
}
