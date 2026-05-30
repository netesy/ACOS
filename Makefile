# ACOS Makefile

CC = clang
CXX = clang++
AS = clang
LD = ld

# UEFI Target
UEFI_CFLAGS = -target x86_64-unknown-windows-coff -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I. -Ilibs/runtime/include
# Use ld with i386pep emulation for UEFI
UEFI_LDFLAGS = -m i386pep --subsystem 10 --entry efi_main

# Kernel Target
KERNEL_CFLAGS = -fno-pic -target x86_64-pc-elf -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -mno-red-zone -I. -Ilibs/runtime/include -std=c++23 -Wall -Wextra -Werror
KERNEL_ASFLAGS = -target x86_64-pc-elf
KERNEL_LDFLAGS = -static -Wl,-no-pie -target x86_64-pc-elf -nostdlib -Wl,-Tlinker.ld

# Directories
BOOT_DIR = boot
KERNEL_DIR = kernel
HAL_DIR = $(KERNEL_DIR)/hal
ARCH_DIR = $(KERNEL_DIR)/arch/x86_64

# Files
BOOT_SRCS = $(BOOT_DIR)/main.cpp
BOOT_EFI = acos_boot.efi

KERNEL_SRCS = $(KERNEL_DIR)/ipc/notification.cpp $(KERNEL_DIR)/ipc/shared_memory.cpp libs/runtime/string.cpp $(KERNEL_DIR)/ipc/channel.cpp $(KERNEL_DIR)/capabilities/capability.cpp $(KERNEL_DIR)/security/domain.cpp $(KERNEL_DIR)/scheduler/process.cpp $(KERNEL_DIR)/scheduler/scheduler.cpp $(ARCH_DIR)/gdt.cpp $(ARCH_DIR)/idt.cpp $(KERNEL_DIR)/memory/pmm.cpp $(KERNEL_DIR)/main.cpp $(HAL_DIR)/serial.cpp $(HAL_DIR)/console.cpp
KERNEL_ASM_SRCS = $(ARCH_DIR)/switch.S $(ARCH_DIR)/boot.S
KERNEL_ELF = kernel.elf

OBJS = $(BOOT_SRCS:.cpp=.o) $(KERNEL_SRCS:.cpp=.o) $(KERNEL_ASM_SRCS:.S=.o)

all: $(BOOT_EFI) $(KERNEL_ELF)

$(BOOT_EFI): $(BOOT_DIR)/main.o
	$(LD) $(UEFI_LDFLAGS) -o $@ $^

$(BOOT_DIR)/main.o: $(BOOT_DIR)/main.cpp
	$(CXX) $(UEFI_CFLAGS) -c -o $@ $<

$(KERNEL_ELF): $(KERNEL_ASM_SRCS:.S=.o) $(KERNEL_SRCS:.cpp=.o)
	$(CXX) $(KERNEL_LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(KERNEL_CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) $(KERNEL_ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(BOOT_EFI) $(KERNEL_ELF) acos.img

.PHONY: all clean

# MinGW Cross-Compilation Support (Optional)
MINGW_CXX = x86_64-w64-mingw32-g++
MINGW_AS  = x86_64-w64-mingw32-as

mingw_all:
	$(MAKE) CXX=$(MINGW_CXX) AS=$(MINGW_AS) all
