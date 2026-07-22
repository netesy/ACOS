CC = clang
CXX = clang++
UEFI_CXX = clang++
AS = clang
LD = ld

# UEFI Target
UEFI_CFLAGS = -target x86_64-unknown-windows-coff -ffreestanding -fcf-protection=none -fno-stack-protector -fshort-wchar -mno-red-zone -I. -Ilibs/runtime/include -Ilibs/abi/include
UEFI_LDFLAGS = -m i386pep --subsystem 10 --entry efi_main

# Kernel Target
KERNEL_CFLAGS = -target x86_64-unknown-elf -nostdinc++ -fno-pic -ffreestanding -fcf-protection=none -fno-stack-protector -fno-exceptions -fno-rtti -mno-red-zone -O2 -I. -Ilibs/runtime/include -Ilibs/abi/include -Iuserland/posix/include -std=c++20 -Wall -Wextra -Werror -D_KERNEL
KERNEL_ASFLAGS = -target x86_64-unknown-elf
KERNEL_LDFLAGS = -target x86_64-unknown-elf -fuse-ld=lld -nostdlib -Wl,-T,linker.ld -Wl,--no-undefined

# Userland Build Flags
USER_CFLAGS = -target x86_64-unknown-elf -fno-pic -nostdinc++ -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -mno-red-zone -O2 -I. -Ilibs/runtime/include -Ilibs/abi/include -Iuserland/libacos/include -std=c++20 -Wall -Wextra -Werror
USER_LDFLAGS = -target x86_64-unknown-elf -nostdlib -Wl,-static -Wl,-no-pie

# Files
BOOT_EFI   = acos_boot.efi
KERNEL_ELF = kernel.elf
DISK_IMG   = acos.img
BUILD_DIR  = build
DIST_DIR   = $(BUILD_DIR)/dist
QEMU       ?= qemu-system-x86_64
QEMU_DISPLAY ?= sdl
QEMU_FIRMWARE ?= $(firstword $(wildcard OVMF.fd /usr/share/ovmf/OVMF.fd /usr/share/qemu/OVMF.fd /usr/share/OVMF/OVMF_CODE.fd /usr/share/OVMF/OVMF_CODE_4M.fd))
MKFS_VFAT  ?= $(firstword $(shell command -v mkfs.vfat 2>/dev/null) $(wildcard /usr/sbin/mkfs.vfat /sbin/mkfs.vfat))
MMD        ?= $(shell command -v mmd 2>/dev/null)
MCOPY      ?= $(shell command -v mcopy 2>/dev/null)

# Directories
BOOT_DIR   = boot
KERNEL_DIR = kernel
HAL_DIR    = $(KERNEL_DIR)/hal
ARCH_DIR   = $(KERNEL_DIR)/arch/x86_64
LOADER_DIR = $(KERNEL_DIR)/loader
SYSCALL_DIR = $(KERNEL_DIR)/syscall
SERVICE_DIR = $(KERNEL_DIR)/services
DISPLAY_DIR = services/display
AUDIO_DIR   = services/audio
STORAGE_DIR = $(KERNEL_DIR)/storage
NET_DIR     = $(KERNEL_DIR)/net
DRIVERS_DIR = $(KERNEL_DIR)/drivers
GRAPHICS_DIR = $(KERNEL_DIR)/graphics
K_AUDIO_DIR = $(KERNEL_DIR)/audio
D_AUDIO_DIR = drivers/audio
SMP_DIR     = $(KERNEL_DIR)/smp
ACPI_DIR    = $(ARCH_DIR)/acpi
ARCH_SMP_DIR = $(ARCH_DIR)/smp

# Kernel Sources
KERNEL_SRCS = \
	libs/runtime/string.cpp \
	$(STORAGE_DIR)/ahci.cpp \
	$(STORAGE_DIR)/partition.cpp \
	$(STORAGE_DIR)/filesystem_manager.cpp \
	$(STORAGE_DIR)/fat32.cpp \
	$(STORAGE_DIR)/ramdisk.cpp \
	$(STORAGE_DIR)/storage_manager.cpp \
	$(LOADER_DIR)/process_loader.cpp \
	$(LOADER_DIR)/elf_loader.cpp \
	$(LOADER_DIR)/elf.cpp \
	$(SERVICE_DIR)/service_manager.cpp \
	$(SERVICE_DIR)/service_registry.cpp \
	$(KERNEL_DIR)/device/driver_manager.cpp \
	$(SYSCALL_DIR)/syscall.cpp \
	$(KERNEL_DIR)/capabilities/capability.cpp \
	$(KERNEL_DIR)/security/domain.cpp \
	$(KERNEL_DIR)/scheduler/process.cpp \
	$(KERNEL_DIR)/scheduler/scheduler.cpp \
	$(ARCH_DIR)/gdt.cpp \
	$(ARCH_DIR)/idt.cpp \
	$(KERNEL_DIR)/memory/pmm.cpp \
	$(KERNEL_DIR)/memory/vmm.cpp \
	$(KERNEL_DIR)/memory/address_space.cpp \
	$(KERNEL_DIR)/memory/heap.cpp \
	$(KERNEL_DIR)/ipc/channel.cpp \
	$(KERNEL_DIR)/ipc/notification.cpp \
	$(KERNEL_DIR)/ipc/shared_memory.cpp \
	$(KERNEL_DIR)/vfs/vfs.cpp \
	$(KERNEL_DIR)/vfs/dentry.cpp \
	$(KERNEL_DIR)/vfs/file.cpp \
	$(KERNEL_DIR)/vfs/mount.cpp \
	$(KERNEL_DIR)/vfs/path.cpp \
	$(KERNEL_DIR)/vfs/console_node.cpp \
	$(KERNEL_DIR)/main.cpp \
	$(HAL_DIR)/serial.cpp \
	$(HAL_DIR)/console.cpp \
	$(HAL_DIR)/pci.cpp \
	services/input/ps2/ps2.cpp \
	$(GRAPHICS_DIR)/graphics_manager.cpp \
	$(GRAPHICS_DIR)/framebuffer.cpp \
	$(GRAPHICS_DIR)/renderer.cpp \
	$(GRAPHICS_DIR)/surface.cpp \
	$(GRAPHICS_DIR)/clipping.cpp \
	$(GRAPHICS_DIR)/dirty_region.cpp \
	$(GRAPHICS_DIR)/context.cpp \
	$(GRAPHICS_DIR)/font.cpp \
	$(GRAPHICS_DIR)/font_manager.cpp \
	$(KERNEL_DIR)/input/input_manager.cpp \
	$(KERNEL_DIR)/input/input_queue.cpp \
	$(KERNEL_DIR)/input/keyboard_manager.cpp \
	$(KERNEL_DIR)/input/mouse_manager.cpp \
	$(K_AUDIO_DIR)/audio_manager.cpp \
	$(K_AUDIO_DIR)/audio_device.cpp \
	$(D_AUDIO_DIR)/virtio_sound/virtio_sound.cpp \
	$(SMP_DIR)/smp.cpp \
	$(SMP_DIR)/cpu.cpp \
	$(SMP_DIR)/ipi.cpp \
	$(SMP_DIR)/load_balancer.cpp \
	$(ACPI_DIR)/madt.cpp \
	$(ARCH_SMP_DIR)/lapic.cpp \
	$(ARCH_SMP_DIR)/ioapic.cpp

KERNEL_ASM_SRCS = \
	$(ARCH_DIR)/switch.S \
	$(ARCH_DIR)/syscall.S \
	$(ARCH_DIR)/boot.S

# Userland Library (libacos)
LIBACOS_SRCS = \
	userland/libacos/syscall.cpp \
	userland/libacos/process.cpp \
	userland/libacos/memory.cpp \
	userland/libacos/ipc.cpp \
	userland/libacos/graphics.cpp \
	userland/libacos/vfs.cpp \
	userland/libacos/framebuffer.cpp \
	userland/libacos/renderer.cpp \
	userland/libacos/font.cpp \
	userland/libacos/font_manager.cpp \
	userland/libacos/string.cpp \
	userland/libacos/input.cpp

GUI_SRCS = $(wildcard userland/gui/*.cpp) $(wildcard userland/gui/core/*.cpp)

LIBACOS_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(LIBACOS_SRCS))
GUI_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(GUI_SRCS))

# Services
DISPLAY_SERVER_SRCS = \
	services/display/main.cpp \
	services/display/display_server.cpp \
	services/display/compositor.cpp \
	services/display/surface_manager.cpp \
	services/display/input_router.cpp \
	services/display/window.cpp \
	services/display/terminal_window.cpp

AUDIO_SERVER_SRCS = \
	services/audio/main.cpp \
	services/audio/audio_server.cpp \
	services/audio/audio_stream.cpp \
	services/audio/audio_mixer.cpp \
	services/audio/audio_session.cpp \
	services/audio/hda/hda.cpp

PCIE_MANAGER_SRCS = services/pcie_manager/main.cpp

NVME_DRIVER_SRCS = services/storage/nvme/nvme.cpp services/storage/nvme/main.cpp

PS2_DRIVER_SRCS = services/input/ps2/ps2.cpp services/input/ps2/main.cpp

XHCI_DRIVER_SRCS = services/input/xhci/xhci.cpp services/input/xhci/main.cpp

DESKTOP_SHELL_SRCS = \
	userland/shell/desktop_shell.cpp \
	userland/shell/taskbar.cpp \
	userland/shell/launcher.cpp \
	userland/shell/notification_center.cpp \
	userland/shell/session_manager.cpp \
	userland/shell/volume_indicator.cpp \
	userland/shell/shortcut_manager.cpp \
	userland/shell/shortcut_widget.cpp \
	userland/shell/telemetry_widgets.cpp \
	userland/shell/desktop_main.cpp

APP_SRCS = \
	apps/terminal/terminal.cpp \
	apps/terminal/terminal_buffer.cpp \
	apps/terminal/terminal_parser.cpp \
	apps/terminal/terminal_session.cpp \
	apps/terminal/terminal_view.cpp \
	apps/file_manager/file_manager.cpp \
	apps/settings/settings.cpp \
	apps/settings/audio_settings.cpp

CLI_SHELL_SRCS = \
	userland/shell/cli_shell.cpp \
	userland/shell/cli_main.cpp \
	userland/shell/variables.cpp \
	userland/shell/parser.cpp \
	userland/shell/executor.cpp \
	userland/shell/console_reader.cpp \
	userland/shell/history.cpp \
	userland/shell/completion.cpp

# Objects
BOOT_OBJS   = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(BOOT_DIR)/main.cpp)
KERNEL_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(KERNEL_SRCS)) \
              $(patsubst %.S, $(BUILD_DIR)/%.o, $(KERNEL_ASM_SRCS))

# Binaries
DISPLAY_SERVER_BIN = $(DIST_DIR)/bin/display.elf
AUDIO_SERVER_BIN   = $(DIST_DIR)/bin/audio.elf
PCIE_MANAGER_BIN   = $(DIST_DIR)/bin/pcie.elf
NVME_DRIVER_BIN    = $(DIST_DIR)/bin/nvme.elf
PS2_DRIVER_BIN     = $(DIST_DIR)/bin/ps2.elf
XHCI_DRIVER_BIN    = $(DIST_DIR)/bin/xhci.elf
DESKTOP_SHELL_BIN  = $(DIST_DIR)/bin/desktop.elf
CLI_SHELL_BIN      = $(DIST_DIR)/bin/cli.elf

DISPLAY_SERVER_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(DISPLAY_SERVER_SRCS))
AUDIO_SERVER_OBJS   = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(AUDIO_SERVER_SRCS))
PCIE_MANAGER_OBJS   = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(PCIE_MANAGER_SRCS))
NVME_DRIVER_OBJS    = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(NVME_DRIVER_SRCS))
PS2_DRIVER_OBJS     = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(PS2_DRIVER_SRCS))
XHCI_DRIVER_OBJS    = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(XHCI_DRIVER_SRCS))
DESKTOP_SHELL_OBJS  = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(DESKTOP_SHELL_SRCS))
APP_OBJS            = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(APP_SRCS))
CLI_SHELL_OBJS      = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CLI_SHELL_SRCS))

SERVICES_BINS = $(DISPLAY_SERVER_BIN) $(AUDIO_SERVER_BIN) $(PCIE_MANAGER_BIN) $(NVME_DRIVER_BIN) $(PS2_DRIVER_BIN) $(XHCI_DRIVER_BIN) $(DESKTOP_SHELL_BIN) $(CLI_SHELL_BIN)

# ----------------------------------------------------
# Build Targets
# ----------------------------------------------------

all: image

image: $(DISK_IMG)

$(BOOT_EFI): $(BOOT_OBJS)
	@mkdir -p $(@D)
	$(LD) $(UEFI_LDFLAGS) -o $@ $^

$(KERNEL_ELF): $(KERNEL_OBJS)
	@mkdir -p $(@D)
	ld -T linker.ld -o $@ $^

# Userland linking rules
$(DISPLAY_SERVER_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(DISPLAY_SERVER_OBJS) $(LIBACOS_OBJS) $(GUI_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

$(AUDIO_SERVER_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(AUDIO_SERVER_OBJS) $(LIBACOS_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

$(PCIE_MANAGER_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(PCIE_MANAGER_OBJS) $(LIBACOS_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

$(NVME_DRIVER_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(NVME_DRIVER_OBJS) $(LIBACOS_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

$(PS2_DRIVER_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(PS2_DRIVER_OBJS) $(LIBACOS_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

$(XHCI_DRIVER_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(XHCI_DRIVER_OBJS) $(LIBACOS_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

$(DESKTOP_SHELL_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(DESKTOP_SHELL_OBJS) $(APP_OBJS) $(LIBACOS_OBJS) $(GUI_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

$(CLI_SHELL_BIN): $(BUILD_DIR)/userland/libacos/crt0.o $(CLI_SHELL_OBJS) $(LIBACOS_OBJS)
	@mkdir -p $(@D)
	$(CXX) $(USER_LDFLAGS) -o $@ $^

# ----------------------------------------------------
# Disk Image Creation
# ----------------------------------------------------

$(DISK_IMG): dist
	@echo "[IMG] Creating FAT32 disk image..."
	dd if=/dev/zero of=$(DISK_IMG) bs=1M count=64
	@if [ -n "$(MKFS_VFAT)" ]; then \
		$(MKFS_VFAT) -F 32 $(DISK_IMG); \
	else \
		echo "[IMG] Warning: mkfs.vfat not found; leaving unformatted raw image."; \
	fi
	@if [ -n "$(MMD)" ] && [ -n "$(MCOPY)" ] && [ -n "$(MKFS_VFAT)" ]; then \
		$(MMD) -i $(DISK_IMG) ::/EFI; \
		$(MMD) -i $(DISK_IMG) ::/EFI/BOOT; \
		$(MCOPY) -i $(DISK_IMG) $(DIST_DIR)/EFI/BOOT/BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI; \
		$(MCOPY) -i $(DISK_IMG) $(DIST_DIR)/kernel.elf ::/kernel.elf; \
		$(MCOPY) -i $(DISK_IMG) README.TXT ::/README.TXT; \
		echo "fs0:\\EFI\\BOOT\\BOOTX64.EFI" > startup.nsh; \
		$(MCOPY) -i $(DISK_IMG) startup.nsh ::/startup.nsh; \
		$(MMD) -i $(DISK_IMG) ::/bin; \
		for bin in $(SERVICES_BINS); do \
			$(MCOPY) -v -i $(DISK_IMG) $$bin ::/bin/$$(basename $$bin); \
		done \
	else \
		echo "[IMG] Warning: mtools and mkfs.vfat are required to populate the FAT32 image."; \
	fi
	@echo "[IMG] Done."

# ----------------------------------------------------
# Compilation Rules
# ----------------------------------------------------

$(BUILD_DIR)/kernel/%.o: kernel/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(KERNEL_CFLAGS) -c $< -o $@

$(BUILD_DIR)/drivers/%.o: drivers/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(KERNEL_CFLAGS) -c $< -o $@

$(BUILD_DIR)/libs/%.o: libs/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(KERNEL_CFLAGS) -c $< -o $@

$(BUILD_DIR)/userland/libs/%.o: libs/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(USER_CFLAGS) -c $< -o $@

$(BUILD_DIR)/userland/libacos/%.o: userland/libacos/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(USER_CFLAGS) -c $< -o $@

$(BUILD_DIR)/userland/libacos/%.o: userland/libacos/%.S
	@mkdir -p $(@D)
	$(AS) $(KERNEL_ASFLAGS) -c $< -o $@

$(BUILD_DIR)/services/%.o: services/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(USER_CFLAGS) -Iservices/display/include -Iservices/audio/include -c $< -o $@

$(BUILD_DIR)/userland/shell/%.o: userland/shell/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(USER_CFLAGS) -c $< -o $@

$(BUILD_DIR)/userland/gui/%.o: userland/gui/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(USER_CFLAGS) -c $< -o $@

$(BUILD_DIR)/apps/%.o: apps/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(USER_CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(@D)
	$(AS) $(KERNEL_ASFLAGS) -c $< -o $@

$(BUILD_DIR)/$(BOOT_DIR)/main.o: $(BOOT_DIR)/main.cpp
	@mkdir -p $(@D)
	$(UEFI_CXX) $(UEFI_CFLAGS) -c $< -o $@

# ----------------------------------------------------
# Run
# ----------------------------------------------------

dist: $(BOOT_EFI) $(KERNEL_ELF) $(SERVICES_BINS)
	mkdir -p $(DIST_DIR)/EFI/BOOT
	cp $(BOOT_EFI) $(DIST_DIR)/EFI/BOOT/BOOTX64.EFI
	cp $(KERNEL_ELF) $(DIST_DIR)/kernel.elf

run: $(DISK_IMG)
	@if command -v $(QEMU) >/dev/null 2>&1; then \
		if [ -n "$(QEMU_FIRMWARE)" ]; then \
			echo "[DESKTOP] Launching ACOS..."; \
			$(QEMU) \
				-m 512M \
				-machine q35 \
				-drive if=pflash,format=raw,readonly=on,file="$(QEMU_FIRMWARE)" \
				-device ahci,id=ahci \
				-drive file=$(DISK_IMG),format=raw,if=none,id=drive0 \
				-device ide-hd,drive=drive0,bus=ahci.0 \
				-usb -device usb-tablet \
				-vga std \
				-display $(QEMU_DISPLAY) \
				-serial stdio; \
		else \
			echo "[DESKTOP] Warning: OVMF firmware not found; cannot launch UEFI VM."; \
			exit 1; \
		fi; \
	else \
		echo "[DESKTOP] Warning: $(QEMU) not found; skipping VM launch."; \
		exit 1; \
	fi

clean:
	rm -f $(BOOT_EFI) $(KERNEL_ELF) $(DISK_IMG)
	rm -rf $(BUILD_DIR) $(DIST_DIR)

.PHONY: all image run clean
