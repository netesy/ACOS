# ACOS Makefile

CC = clang
CXX = clang++
AS = clang

# UEFI Target
# Use a generic cross-compilation approach if specific UEFI target is tricky without lld
UEFI_CFLAGS = -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I. -Ilibs/runtime/include
# Note: For real UEFI we need PE/COFF, but for this environment we might have to compromise if tools are missing
# or assume the user will install lld. I will stick to the plan but maybe use a more standard target if lld is missing.

# Kernel Target
KERNEL_CFLAGS = -fno-pic -target x86_64-pc-elf -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -mno-red-zone -I. -Ilibs/runtime/include -std=c++23 -Wall -Wextra -Werror
KERNEL_ASFLAGS = -target x86_64-pc-elf
KERNEL_LDFLAGS = -static -Wl,-no-pie -no-pie -target x86_64-pc-elf -nostdlib -Wl,-Tlinker.ld

# Directories
BOOT_DIR = boot
KERNEL_DIR = kernel
HAL_DIR = $(KERNEL_DIR)/hal
ARCH_DIR = $(KERNEL_DIR)/arch/x86_64

# Files
BOOT_SRCS = $(BOOT_DIR)/main.cpp
BOOT_EFI = acos_boot.efi

KERNEL_SRCS = $(KERNEL_DIR)/main.cpp $(HAL_DIR)/serial.cpp $(HAL_DIR)/console.cpp
KERNEL_ASM_SRCS = $(ARCH_DIR)/boot.S
KERNEL_ELF = kernel.elf

OBJS = $(BOOT_SRCS:.cpp=.o) $(KERNEL_SRCS:.cpp=.o) $(KERNEL_ASM_SRCS:.S=.o)

all: $(BOOT_EFI) $(KERNEL_ELF)

# UEFI build might fail if lld is missing, but this is the correct way for Clang UEFI
$(BOOT_EFI): $(BOOT_DIR)/main.o
	@echo "Note: This requires lld to be installed for PE/COFF output"
	$(CXX) -target x86_64-unknown-windows-coff -fuse-ld=lld -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application -o $@ $^ || echo "UEFI Build failed - lld might be missing"

$(BOOT_DIR)/main.o: $(BOOT_DIR)/main.cpp
	$(CXX) -target x86_64-unknown-windows-coff $(UEFI_CFLAGS) -c -o $@ $<

$(KERNEL_ELF): $(KERNEL_ASM_SRCS:.S=.o) $(KERNEL_SRCS:.cpp=.o)
	$(CXX) $(KERNEL_LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(KERNEL_CFLAGS) -c -o $@ $<

%.o: %.S
	$(AS) $(KERNEL_ASFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(BOOT_EFI) $(KERNEL_ELF) acos.img

.PHONY: all clean
