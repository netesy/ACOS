# NATIVE_API_SPEC.md

Version: 1.0

Status: Stable Foundation

---

# Purpose

Define the primary ACOS application interface.

Applications should target this API before POSIX.

---

# Design Goals

The Native API must be:

* Explicit
* Capability-Based
* Resource-Oriented
* Async-Friendly
* Language Neutral

---

# Core Concepts

Everything is a Resource.

Resources are accessed through Handles.

Handles are backed by Capabilities.

---

# Namespace Layout

acos::resource

acos::process

acos::thread

acos::memory

acos::ipc

acos::device

acos::network

acos::graphics

acos::audio

acos::storage

---

# Resource Handle

Example

```cpp
ResourceHandle file;
```

Properties

Type

ID

Capabilities

State

Owner

---

# Resource Operations

Supported by all resources

open()

close()

query()

duplicate()

transfer()

revoke()

---

# Process API

Create Process

```cpp
Process p = Process::create();
```

Capabilities

grant()

revoke()

transfer()

Lifecycle

start()

suspend()

resume()

terminate()

---

# Thread API

Create

```cpp
Thread t = p.createThread(entry);
```

Operations

start()

yield()

sleep()

join()

terminate()

---

# Domain API

Create

```cpp
Domain d = Domain::create();
```

Operations

attachProcess()

detachProcess()

grantCapability()

revokeCapability()

setQuota()

---

# Memory API

Allocate

```cpp
MemoryRegion r =
Memory::allocate(size);
```

Operations

map()

unmap()

share()

protect()

Capabilities

Read

Write

Execute

Map

---

# IPC API

Channel

```cpp
Channel c;
```

Operations

send()

receive()

reply()

close()

---

# Shared Region API

```cpp
SharedRegion s;
```

Operations

map()

unmap()

share()

synchronize()

---

# Notification API

```cpp
Notification n;
```

Operations

signal()

wait()

reset()

---

# Device API

Enumerate

```cpp
Device::enumerate();
```

Operations

open()

close()

query()

Capabilities required.

---

# Storage API

Open

```cpp
Storage::open(path);
```

Operations

read()

write()

flush()

resize()

sync()

---

# Network API

Create Endpoint

```cpp
Endpoint e;
```

Operations

bind()

connect()

listen()

send()

receive()

close()

Remote operations must be explicit.

---

# Graphics API

Resources

Display

Surface

Window

Buffer

Operations

create()

destroy()

present()

resize()

---

# Audio API

Resources

OutputDevice

InputDevice

AudioStream

Operations

start()

stop()

pause()

resume()

write()

read()

---

# Error Model

Every operation returns:

Result<T>

Example

```cpp
auto result =
Storage::open("data.bin");

if (!result)
{
    log(result.error());
}
```

No exceptions in the core API.

---

# Asynchronous Model

Every blocking operation must have:

sync version

async version

Example

```cpp
read()
readAsync()
```

---

# Capability Enforcement

Every API call validates capabilities.

Unauthorized access returns:

PermissionDenied

No implicit escalation exists.

---

# Resource Discovery

Applications never access global objects directly.

Example

```cpp
ResourceLocator::find();
```

Resources are acquired through capability-aware discovery.

---

# Language Bindings

Official Bindings

C

C++

Rust

Zig

Fyra

Luminar

Additional bindings generated from IDL.

---

# IDL System

All APIs defined through Interface Definition Language.

Example

interface Storage
{
read();
write();
flush();
}

Generated automatically for all supported languages.

---

# Versioning

Every interface is versioned.

Example

Storage.v1

Storage.v2

Breaking changes require new versions.

---

# Stability Rules

Stable APIs may never change behavior.

New functionality requires:

Extension

New Interface

New Version

Compatibility is mandatory.
