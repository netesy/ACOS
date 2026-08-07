#include <kernel/drivers/net/virtio_net.h>
#include <kernel/memory/heap.h>
#include <acos/runtime.h>
#include <kernel/hal/serial.h>

namespace acos::drivers::net {

namespace {

struct VirtQueueDesc {
    u64 addr;
    u32 len;
    u16 flags;
    u16 next;
} __attribute__((packed));

struct VirtQueueAvail {
    u16 flags;
    u16 idx;
    u16 ring[256];
} __attribute__((packed));

struct VirtQueueUsedElem {
    u32 id;
    u32 len;
} __attribute__((packed));

struct VirtQueueUsed {
    u16 flags;
    u16 idx;
    VirtQueueUsedElem ring[256];
} __attribute__((packed));

struct VirtQueue {
    VirtQueueDesc* desc;
    VirtQueueAvail* avail;
    VirtQueueUsed* used;
    u16 size;
    u16 last_used_idx;
    u16 free_head;
    u16 num_free;
    u8** buffers; // Buffer pointers for recycling
};

VirtQueue g_rx_queue;
VirtQueue g_tx_queue;

void virtqueue_init(VirtQueue& q, u16 size, u8* mem) {
    q.size = size;
    q.last_used_idx = 0;
    q.free_head = 0;
    q.num_free = size;

    q.desc = reinterpret_cast<VirtQueueDesc*>(mem);
    q.avail = reinterpret_cast<VirtQueueAvail*>(mem + size * sizeof(VirtQueueDesc));
    // Pad for 4KB alignment of the Used Ring
    u64 used_offset = (size * sizeof(VirtQueueDesc) + sizeof(VirtQueueAvail) + 4095) & ~4095ULL;
    q.used = reinterpret_cast<VirtQueueUsed*>(mem + used_offset);

    // Initialize free list
    for (u16 i = 0; i < size; i++) {
        q.desc[i].addr = 0;
        q.desc[i].len = 0;
        q.desc[i].flags = 1; // NEXT
        q.desc[i].next = i + 1;
    }
    q.desc[size - 1].next = 0xFFFF; // End of list

    q.buffers = reinterpret_cast<u8**>(acos::memory::kmalloc(size * sizeof(u8*)));
    for (u16 i = 0; i < size; i++) {
        q.buffers[i] = nullptr;
    }
}

u16 virtqueue_alloc_desc(VirtQueue& q) {
    if (q.num_free == 0 || q.free_head == 0xFFFF) return 0xFFFF;
    u16 index = q.free_head;
    q.free_head = q.desc[index].next;
    q.num_free--;
    q.desc[index].flags = 0;
    return index;
}

void virtqueue_free_desc(VirtQueue& q, u16 index) {
    q.desc[index].addr = 0;
    q.desc[index].len = 0;
    q.desc[index].flags = 1; // NEXT
    q.desc[index].next = q.free_head;
    q.free_head = index;
    q.num_free++;
}

} // namespace

VirtIONet::VirtIONet(u64 pci_base) : m_pci_base(pci_base) {
<<<<<<< HEAD
    m_mac = {{0x52, 0x54, 0x00, 0x12, 0x34, 0x56}};
=======
    m_mac = {{0x52, 0x54, 0x00, 0x12, 0x34, 0x56}};
>>>>>>> 294e81b (Phase 4 implementation complete)
}

bool VirtIONet::initialize() {
    if (!m_pci_base) return false;
    
    volatile u32* device_cfg = (volatile u32*)m_pci_base;
    
    // 1. Reset device
    device_cfg[0] = 0;
    
    // 2. Set ACKNOWLEDGE status
    device_cfg[0] = 1;
    
    // 3. Set DRIVER status
    device_cfg[0] = device_cfg[0] | 2;
    
    // 4. Read device features
    u32 device_features = device_cfg[1];
    
    // 5. Negotiate features (accept all for now)
    u32 driver_features = device_features & 0x0F;
    device_cfg[1] = driver_features;
    
    // 6. Set FEATURES_OK status
    device_cfg[0] = device_cfg[0] | 8;
    
    // 7. Verify features were accepted
    if (!(device_cfg[0] & 8)) return false;
    
    // 8. Initialize RX queue (queue 0)
    device_cfg[2] = 0; // Select queue 0
    u16 rx_queue_size = (u16)device_cfg[3];
    if (rx_queue_size == 0 || rx_queue_size > 256) rx_queue_size = 256;
    
    usize rx_desc_size = rx_queue_size * sizeof(VirtQueueDesc) + sizeof(VirtQueueAvail) + 4096 + sizeof(VirtQueueUsed);
    u8* rx_mem = (u8*)acos::memory::kmalloc(rx_desc_size);
    if (!rx_mem) return false;
    
    virtqueue_init(g_rx_queue, rx_queue_size, rx_mem);

    // Populate RX queue with empty buffers for packet receiving
    for (u16 i = 0; i < rx_queue_size; i++) {
        u16 desc_idx = virtqueue_alloc_desc(g_rx_queue);
        if (desc_idx != 0xFFFF) {
            u8* buf = (u8*)acos::memory::kmalloc(1514); // MTU + Ethernet header
            g_rx_queue.buffers[desc_idx] = buf;
            g_rx_queue.desc[desc_idx].addr = reinterpret_cast<u64>(buf);
            g_rx_queue.desc[desc_idx].len = 1514;
            g_rx_queue.desc[desc_idx].flags = 2; // Write-only for device
<<<<<<< HEAD

=======

>>>>>>> 294e81b (Phase 4 implementation complete)
            g_rx_queue.avail->ring[g_rx_queue.avail->idx % rx_queue_size] = desc_idx;
            g_rx_queue.avail->idx++;
        }
    }
<<<<<<< HEAD

=======

>>>>>>> 294e81b (Phase 4 implementation complete)
    // Set queue address (physical address >> 12)
    device_cfg[4] = (u32)((u64)rx_mem >> 12);
    
    // 9. Initialize TX queue (queue 1)
    device_cfg[2] = 1; // Select queue 1
    u16 tx_queue_size = (u16)device_cfg[3];
    if (tx_queue_size == 0 || tx_queue_size > 256) tx_queue_size = 256;

    usize tx_desc_size = tx_queue_size * sizeof(VirtQueueDesc) + sizeof(VirtQueueAvail) + 4096 + sizeof(VirtQueueUsed);
    u8* tx_mem = (u8*)acos::memory::kmalloc(tx_desc_size);
    if (!tx_mem) return false;
    
    virtqueue_init(g_tx_queue, tx_queue_size, tx_mem);

    // Set queue address
    device_cfg[4] = (u32)((u64)tx_mem >> 12);
    
    // 10. Set DRIVER_OK status
    device_cfg[0] = device_cfg[0] | 4;
    
    acos::hal::serial_print("[VirtIONet] Initialized successfully. MAC: 52:54:00:12:34:56\n");

    return true;
}

bool VirtIONet::probe(device::Device* dev) {
    if (!dev) return false;
    return initialize();
}

bool VirtIONet::send_packet(const void* data, usize size) {
    if (!data || size == 0 || size > 1514) return false;
    if (!m_pci_base || !g_tx_queue.desc) return false;
    
    volatile u32* device_cfg = (volatile u32*)m_pci_base;
    
    // 1. Recycle previously used transmit descriptors/buffers to prevent OOM
    while (g_tx_queue.last_used_idx != g_tx_queue.used->idx) {
        u16 used_idx = g_tx_queue.last_used_idx % g_tx_queue.size;
        u16 desc_id = static_cast<u16>(g_tx_queue.used->ring[used_idx].id);
<<<<<<< HEAD

=======

>>>>>>> 294e81b (Phase 4 implementation complete)
        // Free/Recycle the buffer
        if (g_tx_queue.buffers[desc_id]) {
            acos::memory::kfree(g_tx_queue.buffers[desc_id]);
            g_tx_queue.buffers[desc_id] = nullptr;
        }
<<<<<<< HEAD

=======

>>>>>>> 294e81b (Phase 4 implementation complete)
        virtqueue_free_desc(g_tx_queue, desc_id);
        g_tx_queue.last_used_idx++;
    }

    // 2. Allocate a descriptor for the new transmit packet
    u16 desc_idx = virtqueue_alloc_desc(g_tx_queue);
    if (desc_idx == 0xFFFF) {
        acos::hal::serial_print("[VirtIONet] TX queue is full! Packet dropped.\n");
        return false;
    }
    
    // 3. Allocate and copy the packet buffer
    u8* tx_buffer = (u8*)acos::memory::kmalloc(size);
    if (!tx_buffer) {
        virtqueue_free_desc(g_tx_queue, desc_idx);
        return false;
    }
    memcpy(tx_buffer, data, size);
    
    // 4. Fill descriptor fields
    g_tx_queue.buffers[desc_idx] = tx_buffer;
    g_tx_queue.desc[desc_idx].addr = reinterpret_cast<u64>(tx_buffer);
    g_tx_queue.desc[desc_idx].len = size;
    g_tx_queue.desc[desc_idx].flags = 0; // Read-only for device
    
    // 5. Update available ring
    u16 avail_idx = g_tx_queue.avail->idx % g_tx_queue.size;
    g_tx_queue.avail->ring[avail_idx] = desc_idx;
    g_tx_queue.avail->idx++;
    
    // 6. Notify the device (select queue 1, notify index 1)
    device_cfg[2] = 1;
    device_cfg[4] = 1; // Doorbell trigger
    
    return true;
}

usize VirtIONet::receive_packet(void* buffer, usize max_size) {
    if (!buffer || max_size == 0) return 0;
    if (!m_pci_base || !g_rx_queue.desc) return 0;
    
    // Process received packet from the RX queue
    if (g_rx_queue.last_used_idx != g_rx_queue.used->idx) {
        u16 used_idx = g_rx_queue.last_used_idx % g_rx_queue.size;
        u16 desc_id = static_cast<u16>(g_rx_queue.used->ring[used_idx].id);
        u32 len = g_rx_queue.used->ring[used_idx].len;

        u8* packet_buf = g_rx_queue.buffers[desc_id];
        usize copied = 0;
        if (packet_buf && len > 0) {
            copied = (len < max_size) ? len : max_size;
            memcpy(buffer, packet_buf, copied);
        }

        // Recycle the receive descriptor/buffer and place it back on the available ring
        g_rx_queue.avail->ring[g_rx_queue.avail->idx % g_rx_queue.size] = desc_id;
        g_rx_queue.avail->idx++;
        g_rx_queue.last_used_idx++;

        // Notify device that RX queue has buffers available (queue 0)
        volatile u32* device_cfg = (volatile u32*)m_pci_base;
        device_cfg[2] = 0;
        device_cfg[4] = 0; // Doorbell trigger

        return copied;
    }
    
    return 0;
}

} // namespace acos::drivers::net
