# CAPABILITY_SPEC.md

Version: 1.0

Status: Core Standard

---

# Purpose

Defines authority management.

---

# Capability Structure

```c
struct Capability
{
    uint128_t id;
    uint64_t objectId;
    uint64_t owner;
    uint64_t rights;
    uint64_t expiration;
};
```

---

# Rights

Read

Write

Execute

Map

Transfer

Delegate

Administer

---

# Properties

Unforgeable

Revocable

Transferable

Auditable

---

# Delegation

Delegated capability may:

Reduce rights

Limit lifetime

Limit scope

Never increase authority.

---

# Revocation

Must support:

Immediate Revocation

Cascading Revocation

Domain Revocation

---

# Capability Lookup

Target complexity:

O(1)

using kernel-managed capability tables.

---

# Audit Events

Create

Transfer

Delegate

Revoke

Expire

All events logged.
