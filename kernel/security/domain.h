#pragma once
#include <acos/types.h>

namespace acos::security {

enum class DomainType {
    System,
    Application,
    Driver,
    Container,
    Guest
};

struct Domain {
    u64 id;
    DomainType type;

    // Domain restrictions (Phase 3 foundation)
    bool can_access_io;
    bool can_access_network;

    static Domain* create(DomainType type);
};

} // namespace acos::security
