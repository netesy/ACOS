#pragma once
#include <acos/types.h>

namespace acos::hal {

struct PCIDevice {
    u8 bus;
    u8 device;
    u8 function;
    u16 vendor_id;
    u16 device_id;
    u8 class_code;
    u8 subclass;
    u8 prog_if;
};

class PCI {
public:
    static u32 read_config(u8 bus, u8 device, u8 function, u8 offset);
    static void write_config(u8 bus, u8 device, u8 function, u8 offset, u32 value);

    static PCIDevice find_device(u8 class_code, u8 subclass);
    static u64 get_bar(const PCIDevice& dev, u8 bar_index);
    static void enable_bus_mastering(const PCIDevice& dev);

    static u8 find_capability(const PCIDevice& dev, u8 cap_id);
    static void enable_msi(const PCIDevice& dev, u8 vector);
};

} // namespace acos::hal
