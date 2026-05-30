#pragma once
#include <kernel/storage/block_device.h>

namespace acos::storage {

class RamDisk : public BlockDevice {
public:
    RamDisk(void* base, usize size, usize block_size = 512);

    i32 read_block(u64 block_id, void* buffer) override;
    i32 write_block(u64 block_id, const void* buffer) override;
    void flush() override;
    usize block_size() const override { return m_block_size; }
    u64 capacity() const override { return m_size; }

private:
    void* m_base;
    usize m_size;
    usize m_block_size;
};

} // namespace acos::storage
