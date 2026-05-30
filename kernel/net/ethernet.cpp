#include <kernel/net/ethernet.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::net {

void Ethernet::handle_packet(NetDevice* dev, const void* data, usize size) {
    if (size < sizeof(EthernetHeader)) return;
    const EthernetHeader* header = reinterpret_cast<const EthernetHeader*>(data);
    (void)header; (void)dev;
}

bool Ethernet::send_packet(NetDevice* dev, const MACAddress& dest, u16 type, const void* data, usize size) {
    u8 buffer[1514];
    EthernetHeader* header = reinterpret_cast<EthernetHeader*>(buffer);
    header->dest = dest;
    header->src = dev->mac();
    header->type = __builtin_bswap16(type);

    memcpy(buffer + sizeof(EthernetHeader), data, size);
    return dev->send_packet(buffer, size + sizeof(EthernetHeader));
}

} // namespace acos::net
