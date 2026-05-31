#include "session_manager.h"
#include "desktop_shell.h"
#include <kernel/memory/heap.h>
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

SessionManager::SessionManager() : m_current_user(0), m_active(false) {}

void SessionManager::start_session(u64 user_id) {
    m_current_user = user_id;
    m_active = true;

    // Launch Desktop Shell using placement new from runtime.h
    void* shell_mem = acos::memory::kmalloc(sizeof(DesktopShell));
    if (shell_mem) {
        DesktopShell* shell = new (shell_mem) DesktopShell();
        shell->initialize();
        shell->run();
    }
}

void SessionManager::end_session() {
    m_active = false;
}

} // namespace acos::shell
