#include <kernel/security/domain.h>

namespace acos::security {

static u64 g_next_domain_id = 1;

Domain* Domain::create(DomainType type) {
    static Domain g_domain_pool[32];
    static u64 g_pool_index = 0;

    if (g_pool_index >= 32) return nullptr;

    Domain* d = &g_domain_pool[g_pool_index++];
    d->id = g_next_domain_id++;
    d->type = type;

    // Default security policies
    d->can_access_io = (type == DomainType::System || type == DomainType::Driver);
    d->can_access_network = (type == DomainType::System);

    return d;
}

} // namespace acos::security
