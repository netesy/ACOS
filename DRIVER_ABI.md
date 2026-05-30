# DRIVER_ABI.md

Version: 1.0

Status: Stable ABI

---

# Goals

Stable driver interface.

No driver recompilation across minor releases.

---

# Driver Entry Points

```c
driverInit()

driverStart()

driverStop()

driverSuspend()

driverResume()

driverUnload()
```

---

# Driver Registration

```c
DriverDescriptor
{
    Name
    Version
    Vendor
    SupportedDevices
}
```

---

# Device Discovery

Kernel owns enumeration.

Drivers receive device handles.

Drivers never scan hardware directly.

---

# Capability Model

Drivers operate only on granted capabilities.

No unrestricted hardware access.

---

# ABI Stability

Stable across:

1.x releases

Breaking changes require:

2.x ABI
