#include <kernel/storage/ramdisk.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::storage {

RamDisk::RamDisk(void* base, usize size, usize block_size)
    : m_base(base), m_size(size), m_block_size(block_size) {}

i32 RamDisk::read_block(u64 block_id, void* buffer) {
    u64 offset = block_id * m_block_size;
    if (offset + m_block_size > m_size) return -1;
    memcpy(buffer, reinterpret_cast<u8*>(m_base) + offset, m_block_size);
    return 0;
}

i32 RamDisk::write_block(u64 block_id, const void* buffer) {
    u64 offset = block_id * m_block_size;
    if (offset + m_block_size > m_size) return -1;
    memcpy(reinterpret_cast<u8*>(m_base) + offset, buffer, m_block_size);
    return 0;
}

void RamDisk::flush() {}

} // namespace acos::storage
