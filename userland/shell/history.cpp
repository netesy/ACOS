#include "history.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

char HistoryManager::m_history[50][1024];
int HistoryManager::m_count = 0;

void HistoryManager::init() {
    m_count = 0;
}

void HistoryManager::add(const char* line) {
    if (!line || line[0] == '\0') return;

    // Check if duplicate of last entry
    if (m_count > 0) {
        bool duplicate = true;
        for (int i = 0; line[i] || m_history[m_count - 1][i]; i++) {
            if (line[i] != m_history[m_count - 1][i]) {
                duplicate = false;
                break;
            }
        }
        if (duplicate) return;
    }

    if (m_count < 50) {
        usize len = 0;
        while (line[len] && len < 1023) {
            m_history[m_count][len] = line[len];
            len++;
        }
        m_history[m_count][len] = '\0';
        m_count++;
    } else {
        // Shift history left
        for (int i = 0; i < 49; i++) {
            memcpy(m_history[i], m_history[i+1], 1024);
        }
        usize len = 0;
        while (line[len] && len < 1023) {
            m_history[49][len] = line[len];
            len++;
        }
        m_history[49][len] = '\0';
    }
}

const char* HistoryManager::get(int index) {
    if (index < 0 || index >= m_count) return nullptr;
    return m_history[index];
}

int HistoryManager::count() {
    return m_count;
}

void HistoryManager::clear() {
    m_count = 0;
}

} // namespace acos::shell
