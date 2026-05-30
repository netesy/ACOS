#include <kernel/vfs/dentry.h>
#include <acos/runtime.h>

namespace acos::vfs {

Dentry::Dentry(const char* name, Inode* inode, Dentry* parent)
    : m_inode(inode), m_parent(parent) {
    // simplified name copy
    usize i = 0;
    while (name[i] && i < 255) {
        m_name[i] = name[i];
        i++;
    }
    m_name[i] = '\0';
}

} // namespace acos::vfs
