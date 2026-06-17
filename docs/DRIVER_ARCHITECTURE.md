# ACOS Modern Driver Architecture

Version: 1.1
Status: Implementation Specification

## 1. Vision
All ACOS drivers run in **Ring 3 (User Mode)** as isolated processes. The kernel provides only the minimal mechanisms required for hardware access:
- Memory-Mapped I/O (MMIO) windowing via capabilities.
- Interrupt-to-IPC translation.
- IOMMU-backed DMA buffer allocation.

## 2. Event Pipeline Diagram
Physical events follow a strict "Least Privilege" path.

```text
[ PHYSICAL HARDWARE ] (e.g., NVMe SSD / Wi-Fi Card)
      |
      | (PCIe Message / MSI-X)
      v
[ KERNEL (Ring 0) ]
      |
      |-- 1. Hardware Interrupt Handler (Top Half)
      |-- 2. Capability Lookup: [BDF / MSI Vector] -> [Target IPC Channel]
      |-- 3. acos::sys::InterruptDispatch()
      |-- 4. Push Lightweight IPC Notification (Header only)
      v
[ USER-SPACE DRIVER (Ring 3) ] (e.g., nvme_driver.elf)
      |
      |-- 1. Unblock from acos::ipc::NotificationWait()
      |-- 2. Access Hardware BAR (via acos::sys::DeviceMapMMIO)
      |-- 3. Update DMA Ring (acos::sys::MemoryAllocateContiguous)
      |-- 4. Notify Application via Shared Memory
      v
[ SERVICE / APP LAYER (Ring 3) ] (e.g., file_manager.elf)
```

## 3. Core Driver Subsystems

### Subsystem A: PCIe & Platform Discovery
- **`pcie_manager`**: Scans the bus, parses descriptors, and manages device ownership.
- **`acpi_daemon`**: Parses ACPI tables (MADT, FADT) and provides power/routing data.

### Subsystem B: Graphics
- **`display_server`**: Retained-mode compositor.
- **`kms_driver`**: User-space KMS for Intel/AMD mode-setting.
- **`virtio_gpu`**: Paravirtualized blitting support.

### Subsystem C: Storage
- **`nvme_driver`**: High-speed asynchronous I/O via direct SQ/CQ management.
- **`virtio_blk`**: Paravirtualized block storage.

### Subsystem D: Input
- **`xhci_manager`**: USB 3.0 controller and hub management.
- **`usb_hid`**: Class driver for USB keyboards/mice.
- **`i2c_hid`**: HID-over-I2C for internal laptop peripherals.

### Subsystem E: Connectivity
- **`network_daemon`**: Full TCP/IP stack in Ring 3.
- **`wifi_driver`**: Secure firmware loading + DMA ring management.

## 4. Implementation Roadmap

### Phase 1: Infrastructure (Critical)
- [ ] Implement `acos::sys::DeviceMapMMIO` and `acos::sys::DeviceBindInterrupt` syscalls.
- [ ] Deploy `pcie_manager.elf` as the root discovery service.

### Phase 2: Storage Migration
- [ ] Migrate `NVMe` and `AHCI` from kernel to `services/storage/`.
- [ ] Implement IOMMU-protected DMA buffers.

### Phase 3: Input & Hubs
- [ ] Migrate `xHCI` and `PS/2` to `services/input/`.
- [ ] Implement `xhci_manager` to support USB HID devices.

### Phase 4: Multimedia & Wireless
- [ ] Migrate `Intel HDA` to `services/audio/` (integrated with `audio_server`).
- [ ] Implement `wifi_driver` with user-space firmware loading.
