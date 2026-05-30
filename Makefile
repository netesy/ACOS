CC = clang
CXX = clang++
AS = clang
LD = ld

# UEFI Target
UEFI_CFLAGS = -target x86_64-unknown-windows-coff -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I. -Ilibs/runtime/include
UEFI_LDFLAGS = -m i386pep --subsystem 10 --entry efi_main

# Kernel Target
KERNEL_CFLAGS = -fno-pic -target x86_64-pc-elf \
	-ffreestanding \
	-fno-stack-protector \
	-fno-exceptions \
	-fno-rtti \
	-mno-red-zone \
	-I. \
	-Ilibs/runtime/include \
	-std=c++23 \
	-Wall \
	-Wextra \
	-Werror

KERNEL_ASFLAGS = -target x86_64-pc-elf
KERNEL_LDFLAGS = -static -Wl,-no-pie -target x86_64-pc-elf -nostdlib -Wl,-Tlinker.ld

# Files
BOOT_EFI   = acos_boot.efi
KERNEL_ELF = kernel.elf
DISK_IMG   = acos.img

# Directories
BOOT_DIR   = boot
KERNEL_DIR = kernel
HAL_DIR    = $(KERNEL_DIR)/hal
ARCH_DIR   = $(KERNEL_DIR)/arch/x86_64

# Sources
BOOT_SRCS = \
	$(BOOT_DIR)/main.cpp

KERNEL_SRCS = $(KERNEL_DIR)/services/service_manager.cpp $(KERNEL_DIR)/device/driver_manager.cpp $(KERNEL_DIR)/process/loader.cpp $(KERNEL_DIR)/syscall/syscall.cpp \
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
	$(KERNEL_DIR)/main.cpp \
	$(HAL_DIR)/serial.cpp \
	$(HAL_DIR)/console.cpp \
	libs/runtime/string.cpp

KERNEL_ASM_SRCS = $(ARCH_DIR)/syscall.S \
	$(ARCH_DIR)/switch.S \
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
	mkfs.vfat -F 32 $(DISK_IMG)

	mmd -i $(DISK_IMG) ::/EFI
	mmd -i $(DISK_IMG) ::/EFI/BOOT

	mcopy -i $(DISK_IMG) $(BOOT_EFI) ::/EFI/BOOT/BOOTX64.EFI
	mcopy -i $(DISK_IMG) $(KERNEL_ELF) ::/kernel.elf

	@echo "[IMG] Done."

# ----------------------------------------------------
# Compilation Rules
# ----------------------------------------------------

%.o: %.cpp
	$(CXX) $(KERNEL_CFLAGS) -c $< -o $@

%.o: %.S
	$(AS) $(KERNEL_ASFLAGS) -c $< -o $@

$(BOOT_DIR)/main.o: $(BOOT_DIR)/main.cpp
	$(CXX) $(UEFI_CFLAGS) -c $< -o $@

# ----------------------------------------------------
# Run
# ----------------------------------------------------

run: $(DISK_IMG)
	qemu-system-x86_64 \
		-drive format=raw,file=$(DISK_IMG) \
		-bios OVMF.fd

# Windows QEMU
run-win: $(DISK_IMG)
	qemu-system-x86_64.exe \
		-L "C:/Program Files/qemu" \
		-drive format=raw,file=$(DISK_IMG)

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

.PHONY: all image run run-win clean mingw_all
