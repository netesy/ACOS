#include <kernel/hal/pci.h>

namespace acos::hal {

static constexpr u16 PCI_CONFIG_ADDRESS = 0xCF8;
static constexpr u16 PCI_CONFIG_DATA    = 0xCFC;

u32 PCI::read_config(u8 bus, u8 device, u8 function, u8 offset) {
    u32 address = (u32)((u32)bus << 16) | ((u32)device << 11) |
                  ((u32)function << 8) | (offset & 0xFC) | ((u32)0x80000000);
    __asm__ volatile("outl %0, %1" : : "a"(address), "Nd"(PCI_CONFIG_ADDRESS));
    u32 data;
    __asm__ volatile("inl %1, %0" : "=a"(data) : "Nd"(PCI_CONFIG_DATA));
    return data;
}

void PCI::write_config(u8 bus, u8 device, u8 function, u8 offset, u32 value) {
    u32 address = (u32)((u32)bus << 16) | ((u32)device << 11) |
                  ((u32)function << 8) | (offset & 0xFC) | ((u32)0x80000000);
    __asm__ volatile("outl %0, %1" : : "a"(address), "Nd"(PCI_CONFIG_ADDRESS));
    __asm__ volatile("outl %0, %1" : : "a"(value), "Nd"(PCI_CONFIG_DATA));
}

PCIDevice PCI::find_device(u8 class_code, u8 subclass) {
    for (u16 bus = 0; bus < 256; bus++) {
        for (u8 device = 0; device < 32; device++) {
            u32 reg0 = read_config((u8)bus, device, 0, 0);
            if ((reg0 & 0xFFFF) == 0xFFFF) continue;

            u32 reg2 = read_config((u8)bus, device, 0, 0x08);
            u8 dev_class = (reg2 >> 24) & 0xFF;
            u8 dev_subclass = (reg2 >> 16) & 0xFF;

            if (dev_class == class_code && dev_subclass == subclass) {
                return {(u8)bus, device, 0, (u16)(reg0 & 0xFFFF), (u16)(reg0 >> 16), dev_class, dev_subclass, (u8)((reg2 >> 8) & 0xFF)};
            }
        }
    }
    return {0, 0, 0, 0xFFFF, 0xFFFF, 0, 0, 0};
}

u64 PCI::get_bar(const PCIDevice& dev, u8 bar_index) {
    u32 bar = read_config(dev.bus, dev.device, dev.function, 0x10 + (bar_index * 4));
    if (bar & 1) return 0; // I/O Space not supported here

    u64 address = bar & 0xFFFFFFF0;
    if ((bar >> 1) & 0x03) { // 64-bit
        u32 bar_high = read_config(dev.bus, dev.device, dev.function, 0x10 + (bar_index * 4) + 4);
        address |= ((u64)bar_high << 32);
    }
    return address;
}

void PCI::enable_bus_mastering(const PCIDevice& dev) {
    u32 command = read_config(dev.bus, dev.device, dev.function, 0x04);
    command |= 0x06; // Bus Master (bit 2) + Memory Space (bit 1)
    write_config(dev.bus, dev.device, dev.function, 0x04, command);
}

u8 PCI::find_capability(const PCIDevice& dev, u8 cap_id) {
    u32 status = read_config(dev.bus, dev.device, dev.function, 0x06);
    if (!(status & (1 << 4))) return 0; // Capabilities List bit

    u8 ptr = (u8)read_config(dev.bus, dev.device, dev.function, 0x34);
    while (ptr) {
        u32 cap = read_config(dev.bus, dev.device, dev.function, ptr);
        if ((cap & 0xFF) == cap_id) return ptr;
        ptr = (u8)((cap >> 8) & 0xFF);
    }
    return 0;
}

void PCI::enable_msi(const PCIDevice& dev, u8 vector) {
    u8 msi_ptr = find_capability(dev, 0x05); // MSI Capability ID
    if (!msi_ptr) return;

    // Local APIC ID (simplified, assuming BSP)
    u32 message_addr = 0xFEE00000;
    u32 message_data = vector;

    write_config(dev.bus, dev.device, dev.function, msi_ptr + 4, message_addr);

    u32 ctrl = read_config(dev.bus, dev.device, dev.function, msi_ptr);
    if (ctrl & (1 << 23)) { // 64-bit support
        write_config(dev.bus, dev.device, dev.function, msi_ptr + 8, 0); // Upper address
        write_config(dev.bus, dev.device, dev.function, msi_ptr + 12, message_data);
    } else {
        write_config(dev.bus, dev.device, dev.function, msi_ptr + 8, message_data);
    }

    ctrl |= (1 << 16); // MSI Enable bit
    write_config(dev.bus, dev.device, dev.function, msi_ptr, ctrl);
}

} // namespace acos::hal
