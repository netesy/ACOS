# Partial Implementation Audit

Date: 2026-06-01

## Scope

This audit tracks ACOS implementation-completeness risks found by scanning source markers and manually reviewing the affected code paths. The latest remediation pass replaced success-stubs with fail-closed behavior where a full subsystem is not yet present, connected several previously disconnected paths, and completed renderer/VFS/ELF/socket glue that had been compile-only.

## Remediated In This Pass

- Package SHA-256 verification now computes and compares a real SHA-256 digest, while Ed25519 verification fails closed instead of returning structural success.
- ELF loading exposes an `ELFLoadResult` with the loaded entry point and `create_process_from_elf()` uses that entry for the initial thread path.
- VFS `File` now wraps a concrete `Node`, and FAT32 open returns a read-only file node for 8.3 root-directory files.
- UDP receive dispatches payloads to bound sockets, and UDP send hands packets to the selected network device.
- Display input routing records routed keyboard/mouse events against the focused or hovered window instead of silently dropping them.
- GUI window/list rendering and text drawing now use renderer primitives.
- POSIX signal APIs and unsupported Linux compatibility translations fail explicitly instead of reporting successful no-ops.

## Remaining Work Requiring Hardware Or Larger Subsystems

1. x86_64 syscall entry still depends on the per-CPU GS syscall area being initialized consistently for every CPU.
2. VirtIO network transmit/receive has the high-level device status flow, but production descriptor-ring reclamation and interrupt synchronization need a dedicated driver pass.
3. VirtIO sound and audio output need PCI discovery, virtqueue setup, DMA buffers, and timer/device-driven mixer output.
4. POSIX `fork()` remains unsupported by design until copy-on-write address-space cloning exists.
5. Ed25519 package signature verification is fail-closed until a complete curve implementation is added.

## Recommended Next Fix Order

1. Per-CPU syscall/TSS initialization and tests.
2. VirtIO net descriptor-ring receive/transmit completion.
3. VirtIO sound hardware initialization and mixer output path.
4. Copy-on-write process cloning or documented removal of `fork()` from supported POSIX profile.
5. Complete Ed25519 verification.
