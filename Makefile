CC = gcc
CXX = g++
AS = as
LD = ld

# UEFI Target (Using GCC/LD)
UEFI_CFLAGS = -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I. -Ilibs/runtime/include
UEFI_LDFLAGS = -m i386pep --subsystem 10 --entry efi_main

# Kernel Target
KERNEL_CFLAGS = -nostdinc++ -fno-pic -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -mno-red-zone -I. -Ilibs/runtime/include -std=c++23 -Wall -Wextra -Werror
KERNEL_ASFLAGS =
KERNEL_LDFLAGS = -static -z noexecstack -nostdlib -T linker.ld

# Files
BOOT_EFI   = acos_boot.efi
KERNEL_ELF = kernel.elf
DISK_IMG   = acos.img

# Directories
BOOT_DIR   = boot
KERNEL_DIR = kernel
HAL_DIR    = $(KERNEL_DIR)/hal
ARCH_DIR   = $(KERNEL_DIR)/arch/x86_64
LOADER_DIR = $(KERNEL_DIR)/loader
SYSCALL_DIR = $(KERNEL_DIR)/syscall
SERVICE_DIR = $(KERNEL_DIR)/services

# Sources
BOOT_SRCS = \
	$(BOOT_DIR)/main.cpp

KERNEL_SRCS = $(KERNEL_DIR)/storage/ahci.cpp $(KERNEL_DIR)/storage/partition.cpp $(KERNEL_DIR)/storage/filesystem_manager.cpp $(KERNEL_DIR)/storage/fat32.cpp $(KERNEL_DIR)/storage/ramdisk.cpp $(KERNEL_DIR)/storage/storage_manager.cpp \
	$(LOADER_DIR)/process_loader.cpp \
	$(LOADER_DIR)/elf_loader.cpp \
	$(LOADER_DIR)/elf.cpp \
	$(SERVICE_DIR)/service_manager.cpp \
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
	$(KERNEL_DIR)/vfs/vfs.cpp $(KERNEL_DIR)/vfs/dentry.cpp $(KERNEL_DIR)/vfs/file.cpp $(KERNEL_DIR)/vfs/mount.cpp $(KERNEL_DIR)/vfs/path.cpp \
	$(KERNEL_DIR)/main.cpp \
	$(HAL_DIR)/serial.cpp \
	$(HAL_DIR)/console.cpp \
	libs/runtime/string.cpp

KERNEL_ASM_SRCS = \
	$(ARCH_DIR)/switch.S \
	$(ARCH_DIR)/syscall.S \
	$(ARCH_DIR)/boot.S

BOOT_OBJS   = $(BOOT_SRCS:.cpp=.o)
KERNEL_OBJS = $(KERNEL_SRCS:.cpp=.o) $(KERNEL_ASM_SRCS:.S=.o)

# ----------------------------------------------------
# Build Targets
# ----------------------------------------------------

all: image

image: $(DISK_IMG)

$(BOOT_EFI): $(BOOT_OBJS)
	$(LD) $(UEFI_LDFLAGS) -o $@ $^

$(KERNEL_ELF): $(KERNEL_OBJS)
	$(CXX) $(KERNEL_LDFLAGS) -o $@ $^

# ----------------------------------------------------
# Disk Image Creation
# ----------------------------------------------------

$(DISK_IMG): $(BOOT_EFI) $(KERNEL_ELF)
	@echo "[IMG] Creating FAT32 disk image..."
	dd if=/dev/zero of=$(DISK_IMG) bs=1M count=64
	# In many headless environments, mkfs.vfat might not be available or require root.
	# Fallback or assumption that tools exist.
	mkfs.vfat -F 32 $(DISK_IMG) || true

	mmd -i $(DISK_IMG) ::/EFI || true
	mmd -i $(DISK_IMG) ::/EFI/BOOT || true

	mcopy -i $(DISK_IMG) $(BOOT_EFI) ::/EFI/BOOT/BOOTX64.EFI || true
	mcopy -i $(DISK_IMG) $(KERNEL_ELF) ::/kernel.elf || true

	@echo "[IMG] Done."

# ----------------------------------------------------
# Compilation Rules
# ----------------------------------------------------

%.o: %.cpp
	$(CXX) $(KERNEL_CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(KERNEL_CFLAGS) -c $< -o $@

$(BOOT_DIR)/main.o: $(BOOT_DIR)/main.cpp
	$(CXX) $(UEFI_CFLAGS) -c $< -o $@

# ----------------------------------------------------
# Run
# ----------------------------------------------------

run: $(DISK_IMG)
	qemu-system-x86_64 \
		-drive format=raw,file=$(DISK_IMG) \
		-bios OVMF.fd

# ----------------------------------------------------
# Clean
# ----------------------------------------------------

clean:
	rm -f $(BOOT_OBJS)
	rm -f $(KERNEL_OBJS)
	rm -f $(BOOT_EFI)
	rm -f $(KERNEL_ELF)
	rm -f $(DISK_IMG)

# ----------------------------------------------------
# MinGW Support
# ----------------------------------------------------

MINGW_CXX = x86_64-w64-mingw32-g++
MINGW_AS  = x86_64-w64-mingw32-as

mingw_all:
	$(MAKE) CXX=$(MINGW_CXX) AS=$(MINGW_AS) all

.PHONY: all image run clean mingw_all
