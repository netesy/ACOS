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

    i32 read_blocks(u64 block_id, u64 count, void* buffer) override;
    i32 write_blocks(u64 block_id, u64 count, const void* buffer) override;
    u64 block_count() const override { return m_block_size > 0 ? (m_size / m_block_size) : 0; }
    bool is_read_only() const override { return m_read_only; }

    void set_read_only(bool ro) { m_read_only = ro; }

private:
    void* m_base;
    usize m_size;
    usize m_block_size;
    bool m_read_only;
};

} // namespace acos::storage
