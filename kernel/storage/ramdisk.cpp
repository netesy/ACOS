#include <kernel/storage/ramdisk.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::storage {

RamDisk::RamDisk(void* base, usize size, usize block_size)
    : m_base(base), m_size(size), m_block_size(block_size), m_read_only(false) {}

i32 RamDisk::read_block(u64 block_id, void* buffer) {
    return read_blocks(block_id, 1, buffer);
}

i32 RamDisk::write_block(u64 block_id, const void* buffer) {
    return write_blocks(block_id, 1, buffer);
}

void RamDisk::flush() {}

i32 RamDisk::read_blocks(u64 block_id, u64 count, void* buffer) {
    if (!m_base || !buffer) return -1;
    if (count == 0) return -1;

    u64 total_b = block_count();

    // Guard against u64 overflows
    if (block_id >= total_b) return -1;
    u64 end_block;
    if (__builtin_add_overflow(block_id, count, &end_block)) return -1;
    if (end_block > total_b) return -1;

    u64 offset = block_id * m_block_size;
    u64 read_size = count * m_block_size;

    // Check bounds against total allocation capacity
    if (offset + read_size > m_size) return -1;

    memcpy(buffer, reinterpret_cast<u8*>(m_base) + offset, read_size);
    return 0;
}

i32 RamDisk::write_blocks(u64 block_id, u64 count, const void* buffer) {
    if (m_read_only) return -1;
    if (!m_base || !buffer) return -1;
    if (count == 0) return -1;

    u64 total_b = block_count();

    // Guard against u64 overflows
    if (block_id >= total_b) return -1;
    u64 end_block;
    if (__builtin_add_overflow(block_id, count, &end_block)) return -1;
    if (end_block > total_b) return -1;

    u64 offset = block_id * m_block_size;
    u64 write_size = count * m_block_size;

    // Check bounds against total allocation capacity
    if (offset + write_size > m_size) return -1;

    memcpy(reinterpret_cast<u8*>(m_base) + offset, buffer, write_size);
    return 0;
}

} // namespace acos::storage
