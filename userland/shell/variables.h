#pragma once
#include <acos/types.h>

namespace acos::shell {

struct Variable {
    char name[128];
    char value[512];
    bool is_env;
};

struct Alias {
    char name[128];
    char expansion[512];
};

class VariablesManager {
public:
    static void init();
    static void set(const char* name, const char* value, bool is_env = false);
    static const char* get(const char* name);
    static void remove(const char* name);

    static usize get_count();
    static const Variable* get_at(usize index);

    // Alias Support
    static void set_alias(const char* name, const char* expansion);
    static const char* get_alias(const char* name);
    static void remove_alias(const char* name);
    static usize get_alias_count();
    static const Alias* get_alias_at(usize index);

private:
    static Variable m_vars[128];
    static usize m_var_count;

    static Alias m_aliases[64];
    static usize m_alias_count;
};

} // namespace acos::shell
