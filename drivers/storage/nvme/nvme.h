#pragma once
#include <acos/types.h>
#include <kernel/storage/block_device.h>

namespace acos::drivers::storage {

class NVMeController : public acos::storage::BlockDevice {
public:
    NVMeController(u64 bar0);
    bool initialize();

    i32 read_block(u64 block_id, void* buffer) override;
    i32 write_block(u64 block_id, const void* buffer) override;
    void flush() override;
    usize block_size() const override { return 512; }
    u64 capacity() const override { return m_capacity; }

private:
    u64 m_bar0;
    volatile u32* m_regs;
    u64 m_capacity = 0;

    struct Queue {
        u64 doorbell;
        u16 size;
        u16 head;
        u16 tail;
        void* sq_virt;
        void* cq_virt;
    };

    Queue m_admin_queue;
};

} // namespace acos::drivers::storage
