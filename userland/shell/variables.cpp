#include "variables.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::shell {

Variable VariablesManager::m_vars[128];
usize VariablesManager::m_var_count = 0;

Alias VariablesManager::m_aliases[64];
usize VariablesManager::m_alias_count = 0;

void VariablesManager::init() {
    m_var_count = 0;
    m_alias_count = 0;

    // Set default standard environment variables
    set("PATH", "/bin:/usr/bin:/usr/local/bin", true);
    set("HOME", "/users/default", true);
    set("USER", "acos", true);
    set("PROMPT", "[\\u@acos \\W]$ ", true);
    set("?", "0", false); // Exit code of the last command
}

void VariablesManager::set(const char* name, const char* value, bool is_env) {
    if (!name || name[0] == '\0') return;

    // Search for existing variable
    for (usize i = 0; i < m_var_count; i++) {
        bool match = true;
        for (int j = 0; name[j] || m_vars[i].name[j]; j++) {
            if (name[j] != m_vars[i].name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            // Update existing
            usize len = 0;
            while (value[len] && len < 511) {
                m_vars[i].value[len] = value[len];
                len++;
            }
            m_vars[i].value[len] = '\0';
            m_vars[i].is_env = is_env;
            return;
        }
    }

    // Add new variable if we have space
    if (m_var_count < 128) {
        usize len = 0;
        while (name[len] && len < 127) {
            m_vars[m_var_count].name[len] = name[len];
            len++;
        }
        m_vars[m_var_count].name[len] = '\0';

        len = 0;
        while (value[len] && len < 511) {
            m_vars[m_var_count].value[len] = value[len];
            len++;
        }
        m_vars[m_var_count].value[len] = '\0';
        m_vars[m_var_count].is_env = is_env;
        m_var_count++;
    }
}

const char* VariablesManager::get(const char* name) {
    if (!name || name[0] == '\0') return "";

    for (usize i = 0; i < m_var_count; i++) {
        bool match = true;
        for (int j = 0; name[j] || m_vars[i].name[j]; j++) {
            if (name[j] != m_vars[i].name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return m_vars[i].value;
        }
    }
    return "";
}

void VariablesManager::remove(const char* name) {
    if (!name || name[0] == '\0') return;

    for (usize i = 0; i < m_var_count; i++) {
        bool match = true;
        for (int j = 0; name[j] || m_vars[i].name[j]; j++) {
            if (name[j] != m_vars[i].name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            // Shift remaining variables
            for (usize k = i; k < m_var_count - 1; k++) {
                m_vars[k] = m_vars[k+1];
            }
            m_var_count--;
            return;
        }
    }
}

usize VariablesManager::get_count() {
    return m_var_count;
}

const Variable* VariablesManager::get_at(usize index) {
    if (index >= m_var_count) return nullptr;
    return &m_vars[index];
}

// Alias Support
void VariablesManager::set_alias(const char* name, const char* expansion) {
    if (!name || name[0] == '\0' || !expansion) return;

    for (usize i = 0; i < m_alias_count; i++) {
        bool match = true;
        for (int j = 0; name[j] || m_aliases[i].name[j]; j++) {
            if (name[j] != m_aliases[i].name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            usize len = 0;
            while (expansion[len] && len < 511) {
                m_aliases[i].expansion[len] = expansion[len];
                len++;
            }
            m_aliases[i].expansion[len] = '\0';
            return;
        }
    }

    if (m_alias_count < 64) {
        usize len = 0;
        while (name[len] && len < 127) {
            m_aliases[m_alias_count].name[len] = name[len];
            len++;
        }
        m_aliases[m_alias_count].name[len] = '\0';

        len = 0;
        while (expansion[len] && len < 511) {
            m_aliases[m_alias_count].expansion[len] = expansion[len];
            len++;
        }
        m_aliases[m_alias_count].expansion[len] = '\0';
        m_alias_count++;
    }
}

const char* VariablesManager::get_alias(const char* name) {
    if (!name || name[0] == '\0') return nullptr;

    for (usize i = 0; i < m_alias_count; i++) {
        bool match = true;
        for (int j = 0; name[j] || m_aliases[i].name[j]; j++) {
            if (name[j] != m_aliases[i].name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return m_aliases[i].expansion;
        }
    }
    return nullptr;
}

void VariablesManager::remove_alias(const char* name) {
    if (!name || name[0] == '\0') return;

    for (usize i = 0; i < m_alias_count; i++) {
        bool match = true;
        for (int j = 0; name[j] || m_aliases[i].name[j]; j++) {
            if (name[j] != m_aliases[i].name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            for (usize k = i; k < m_alias_count - 1; k++) {
                m_aliases[k] = m_aliases[k+1];
            }
            m_alias_count--;
            return;
        }
    }
}

usize VariablesManager::get_alias_count() {
    return m_alias_count;
}

const Alias* VariablesManager::get_alias_at(usize index) {
    if (index >= m_alias_count) return nullptr;
    return &m_aliases[index];
}

} // namespace acos::shell
