#pragma once
#include <acos/types.h>

namespace acos::shell {

class HistoryManager {
public:
    static void init();
    static void add(const char* line);
    static const char* get(int index);
    static int count();
    static void clear();

private:
    static char m_history[50][1024];
    static int m_count;
};

} // namespace acos::shell
