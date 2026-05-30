#include <kernel/device/device.h>

namespace acos::device {

static Device* g_devices[128];
static usize g_device_count = 0;

void register_device(Device* dev) {
    if (g_device_count < 128) {
        g_devices[g_device_count++] = dev;
    }
}

} // namespace acos::device
