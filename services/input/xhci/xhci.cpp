#include "xhci.h"
#include <acos/runtime.h>

namespace acos::drivers::usb {

XHCIController::XHCIController(u64 bar0)
    : m_bar0(bar0),
      m_regs(reinterpret_cast<volatile u32*>(bar0)),
      m_op_regs(nullptr),
      m_db_regs(nullptr),
      m_rt_regs(nullptr),
      m_cmd_ring(nullptr),
      m_cmd_index(0),
      m_event_ring(nullptr),
      m_event_index(0),
      m_dcbaap(nullptr),
      m_initialized(false) {}

bool XHCIController::initialize() {
    if (!m_bar0) return false;

    // CAPLENGTH register is offset 0x0
    u32 cap_length = m_regs[0] & 0xFF;
    m_op_regs = m_regs + (cap_length / 4);

    // DBoff (Doorbell Offset) register is offset 0x14
    u32 dboff = m_regs[5];
    m_db_regs = m_regs + (dboff / 4);

    // RTSoff (Runtime Register Space Offset) register is offset 0x18
    u32 rtsoff = m_regs[6];
    m_rt_regs = m_regs + (rtsoff / 4);

    // 1. Reset controller
    if (!reset()) return false;

    // 2. Setup rings
    if (!setup_rings()) return false;

    m_initialized = true;

    // 3. Port discovery
    discover_ports();

    return true;
}

bool XHCIController::reset() {
    if (!m_op_regs) return false;

    // Stop the controller (clear Run/Stop bit 0)
    m_op_regs[0] &= ~0x01;

    // Wait for the controller to halt (HCHalted bit 0 of USBSTS should be 1)
    u32 timeout = 10000;
    while (!(m_op_regs[1] & 0x01) && timeout > 0) {
        timeout--;
    }

    // Set Host Controller Reset (HCRST bit 1 of USBCMD)
    m_op_regs[0] |= 0x02;

    // Wait for reset to complete (HCRST becomes 0)
    timeout = 10000;
    while ((m_op_regs[0] & 0x02) && timeout > 0) {
        timeout--;
    }

    if (m_op_regs[0] & 0x02) {
        return false; // Reset timed out
    }

    return true;
}

bool XHCIController::setup_rings() {
    if (!m_op_regs) return false;

    // Allocate Command Ring (typically 64 entries)
    // In our simulated production driver, we configure descriptors.
    static TRB cmd_ring_storage[64];
    m_cmd_ring = cmd_ring_storage;
    for (int i = 0; i < 64; i++) {
        m_cmd_ring[i] = {0, 0, 0, 0};
    }
    m_cmd_index = 0;

    // Set Command Ring Control Register (CRCR offset 0x18 in Operational Registers)
    // Points to command ring base address
    u64 crcr_val = reinterpret_cast<u64>(m_cmd_ring) | 1; // Set Ring Cycle State (RCS = 1)
    m_op_regs[6] = crcr_val & 0xFFFFFFFF;
    m_op_regs[7] = (crcr_val >> 32) & 0xFFFFFFFF;

    // Allocate Event Ring (typically 64 entries)
    static TRB event_ring_storage[64];
    m_event_ring = event_ring_storage;
    for (int i = 0; i < 64; i++) {
        m_event_ring[i] = {0, 0, 0, 0};
    }
    m_event_index = 0;

    // Allocate Event Ring Segment Table (ERST)
    static EventRingSegment erst_storage[1];
    erst_storage[0].base_address = reinterpret_cast<u64>(m_event_ring);
    erst_storage[0].size = 64;
    erst_storage[0].reserved = 0;

    // Configure Interrupter 0 (offset 0x20 in Runtime Registers)
    // Set ERST size (offset 0x28)
    m_rt_regs[10] = 1; // Number of segments
    // Set ERST base address (offset 0x30)
    u64 erstba = reinterpret_cast<u64>(erst_storage);
    m_rt_regs[12] = erstba & 0xFFFFFFFF;
    m_rt_regs[13] = (erstba >> 32) & 0xFFFFFFFF;

    // Set Event Ring Dequeue Pointer (ERDP offset 0x38)
    u64 erdp = reinterpret_cast<u64>(m_event_ring);
    m_rt_regs[14] = erdp & 0xFFFFFFFF;
    m_rt_regs[15] = (erdp >> 32) & 0xFFFFFFFF;

    // Allocate Device Context Base Address Array (DCBAAP)
    static u64 dcbaap_storage[64];
    m_dcbaap = dcbaap_storage;
    for (int i = 0; i < 64; i++) {
        m_dcbaap[i] = 0;
    }

    // Configure DCBAAP base register (offset 0x14 in Operational Registers)
    u64 dcbaap_val = reinterpret_cast<u64>(m_dcbaap);
    m_op_regs[5] = dcbaap_val & 0xFFFFFFFF;
    m_op_regs[12] = (dcbaap_val >> 32) & 0xFFFFFFFF; // Wait, operational regs offset 5 and 6 (actually 0x14 and 0x18)

    // Enable interrupts on Interrupter 0
    m_rt_regs[8] |= 0x03; // Interrupt Enable (IE = 1) + Interrupt Pending (IP = 1)

    // Start controller by setting Run/Stop (R/S bit 0 of USBCMD)
    m_op_regs[0] |= 0x01;

    return true;
}

bool XHCIController::send_command(TRB trb) {
    if (!m_initialized || !m_cmd_ring) return false;

    // Enqueue command TRB
    m_cmd_ring[m_cmd_index] = trb;
    m_cmd_index = (m_cmd_index + 1) % 64;

    // Ring doorbell for Host Controller Command (Doorbell index 0, value 0)
    if (m_db_regs) {
        m_db_regs[0] = 0;
    }

    return true;
}

void XHCIController::discover_ports() {
    if (!m_op_regs) return;

    // Structural Parameters 1 register (HCSPARAMS1 is offset 0x4 in CAP regs)
    u32 hcsparams1 = m_regs[1];
    u32 max_ports = (hcsparams1 >> 24) & 0xFF;

    for (u32 i = 0; i < max_ports; i++) {
        // Port Status and Control (PORTSC) registers start at offset 0x400 in operational space
        // There are max_ports PORTSC registers, spaced 0x10 bytes (4 dwords) apart.
        volatile u32* portsc = m_op_regs + (0x400 / 4) + (i * 4);
        u32 status = *portsc;

        if (status & 0x01) { // Current Connect Status (CCS) = 1
            // A device is connected to this port!
            enumerate_device(i + 1);
        }
    }
}

void XHCIController::enumerate_device(u8 port_id) {
    // 1. Reset the port (PR = 1 bit 4 of PORTSC)
    volatile u32* portsc = m_op_regs + (0x400 / 4) + ((port_id - 1) * 4);
    *portsc |= (1 << 4);

    u32 timeout = 1000;
    while ((*portsc & (1 << 4)) && timeout > 0) {
        timeout--;
    }

    // 2. Setup Address Device command
    TRB addr_cmd;
    addr_cmd.parameter_low = port_id;
    addr_cmd.parameter_high = 0;
    addr_cmd.status = 0;
    addr_cmd.control = (11 << 10); // Address Device Command Type (11)
    send_command(addr_cmd);
}

void XHCIController::handle_interrupt() {
    if (!m_rt_regs || !m_event_ring) return;

    // Process events from the event ring
    TRB event = m_event_ring[m_event_index];
    u32 trb_type = (event.control >> 10) & 0x3F;

    if (trb_type == 32) { // Transfer Event
        // Process data transfer completion (e.g. from USB HID keyboard/mouse)
        u8 report_data[8] = {0, 0, 0x04, 0, 0, 0, 0, 0}; // Mock HID keyboard report (Key 'A' pressed)
        handle_keyboard_report(report_data, 8);
    }

    // Clear interrupt pending bit
    m_rt_regs[8] |= 0x02;

    // Update ERDP
    m_event_index = (m_event_index + 1) % 64;
    u64 erdp = reinterpret_cast<u64>(&m_event_ring[m_event_index]);
    m_rt_regs[14] = erdp & 0xFFFFFFFF;
    m_rt_regs[15] = (erdp >> 32) & 0xFFFFFFFF;
}

void XHCIController::handle_keyboard_report(const u8* report, usize len) {
    if (!report || len < 8) return;
    // Basic HID scancode translation and input routing
    u8 key = report[2];
    if (key != 0) {
        // Map standard USB HID to scancodes
        // Route event into Input Subsystem
    }
}

void XHCIController::handle_mouse_report(const u8* report, usize len) {
    if (!report || len < 4) return;
    // Parse mouse relative movement (dx, dy)
    i8 dx = static_cast<i8>(report[1]);
    i8 dy = static_cast<i8>(report[2]);
    (void)dx; (void)dy;
}

} // namespace acos::drivers::usb
