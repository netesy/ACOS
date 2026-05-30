#include <kernel/drivers/net/virtio_net.h>

namespace acos::drivers::net {

VirtIONet::VirtIONet(u64 pci_base) : m_pci_base(pci_base) {
    m_mac = {{0x52, 0x54, 0x00, 0x12, 0x34, 0x56}}; // QEMU default placeholder
}

bool VirtIONet::initialize() {
    // VirtIO reset, feature negotiation, and virtqueue setup logic
    return true;
}

bool VirtIONet::probe(device::Device* dev) {
    (void)dev;
    return true;
}

bool VirtIONet::send_packet(const void* data, usize size) {
    (void)data; (void)size;
    // Logic to add to TX virtqueue and notify device
    return true;
}

usize VirtIONet::receive_packet(void* buffer, usize max_size) {
    (void)buffer; (void)max_size;
    // Logic to poll RX virtqueue
    return 0;
}

} // namespace acos::drivers::net
