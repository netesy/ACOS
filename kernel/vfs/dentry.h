#pragma once
#include <acos/types.h>
#include <kernel/vfs/inode.h>

namespace acos::vfs {

class Dentry {
public:
    Dentry(const char* name, Inode* inode, Dentry* parent = nullptr);

    const char* name() const { return m_name; }
    Inode* inode() const { return m_inode; }
    Dentry* parent() const { return m_parent; }

private:
    char m_name[256];
    Inode* m_inode;
    Dentry* m_parent;
};

} // namespace acos::vfs
