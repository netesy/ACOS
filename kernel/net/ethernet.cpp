#include <kernel/net/ethernet.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::net {

void Ethernet::handle_packet(NetDevice* dev, const void* data, usize size) {
    if (size < sizeof(EthernetHeader)) return;
    const EthernetHeader* header = reinterpret_cast<const EthernetHeader*>(data);
    (void)header; (void)dev;
}

bool Ethernet::send_packet(NetDevice* dev, const MACAddress& dest, u16 type, const void* data, usize size) {
    if (!dev || !data) return false;

    // Guard against a stack buffer overflow: `buffer` can only hold an
    // Ethernet header plus a standard 1500-byte MTU payload. Reject
    // anything that would overrun it instead of memcpy'ing blindly.
    static constexpr usize kMaxPayload = 1514 - sizeof(EthernetHeader);
    if (size > kMaxPayload) return false;

    u8 buffer[1514];
    EthernetHeader* header = reinterpret_cast<EthernetHeader*>(buffer);
    header->dest = dest;
    header->src = dev->mac();
    header->type = __builtin_bswap16(type);

    memcpy(buffer + sizeof(EthernetHeader), data, size);
    return dev->send_packet(buffer, size + sizeof(EthernetHeader));
}

} // namespace acos::net
