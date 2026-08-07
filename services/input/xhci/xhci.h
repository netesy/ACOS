#pragma once
#include <acos/types.h>

namespace acos::drivers::usb {

struct TRB {
    u32 parameter_low;
    u32 parameter_high;
    u32 status;
    u32 control;
} __attribute__((packed));

struct EventRingSegment {
    u64 base_address;
    u32 size;
    u32 reserved;
} __attribute__((packed));

class XHCIController {
public:
    XHCIController(u64 bar0);
    bool initialize();
    bool reset();
    bool setup_rings();
    bool send_command(TRB trb);
    void discover_ports();
    void enumerate_device(u8 port_id);
    void handle_interrupt();

    // Hot-plug and Input routing
    void handle_keyboard_report(const u8* report, usize len);
    void handle_mouse_report(const u8* report, usize len);

private:
    u64 m_bar0;
    volatile u32* m_regs;
    volatile u32* m_op_regs;
    volatile u32* m_db_regs;
    volatile u32* m_rt_regs;

    // Rings (Command, Event, Transfer)
    TRB* m_cmd_ring;
    u32 m_cmd_index;
    TRB* m_event_ring;
    u32 m_event_index;
    u64* m_dcbaap;

    bool m_initialized;
};

} // namespace acos::drivers::usb
