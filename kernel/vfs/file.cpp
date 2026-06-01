#include <kernel/vfs/file.h>

namespace acos::vfs {

File::File(Node* node) : m_node(node), m_offset(0) {}

i32 File::read(void* buffer, usize size) {
    if (!m_node) return -1;
    i32 bytes = m_node->read(m_offset, size, buffer);
    if (bytes > 0) m_offset += bytes;
    return bytes;
}

i32 File::write(const void* buffer, usize size) {
    if (!m_node) return -1;
    i32 bytes = m_node->write(m_offset, size, buffer);
    if (bytes > 0) m_offset += bytes;
    return bytes;
}

u64 File::seek(u64 offset) {
    m_offset = offset;
    return m_offset;
}

} // namespace acos::vfs
