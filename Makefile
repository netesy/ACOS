CC = gcc
CXX = g++
AS = as
LD = ld

# UEFI Target
UEFI_CFLAGS = -target x86_64-unknown-windows-coff -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I. -Ilibs/runtime/include
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
STORAGE_DIR = $(KERNEL_DIR)/storage
NET_DIR     = $(KERNEL_DIR)/net
DRIVERS_DIR = $(KERNEL_DIR)/drivers

# Sources
BOOT_SRCS = $(BOOT_DIR)/main.cpp

KERNEL_SRCS = \
	$(NET_DIR)/net_device.cpp \
	$(NET_DIR)/ethernet.cpp \
	$(NET_DIR)/arp.cpp \
	$(NET_DIR)/ipv4.cpp \
	$(NET_DIR)/icmp.cpp \
	$(NET_DIR)/udp.cpp \
	$(NET_DIR)/tcp.cpp \
	$(NET_DIR)/socket.cpp \
	$(DRIVERS_DIR)/net/virtio_net.cpp \
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

all: $(KERNEL_ELF)

$(BOOT_EFI): $(BOOT_OBJS)
	$(LD) $(UEFI_LDFLAGS) -o $@ $^

$(KERNEL_ELF): $(KERNEL_OBJS)
	$(CXX) $(KERNEL_LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(KERNEL_CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(KERNEL_CFLAGS) -c $< -o $@

$(BOOT_DIR)/main.o: $(BOOT_DIR)/main.cpp
	$(CXX) $(UEFI_CFLAGS) -c $< -o $@

clean:
	find . -name "*.o" -type f -delete
	rm -f $(BOOT_EFI) $(KERNEL_ELF) $(DISK_IMG)

.PHONY: all clean
