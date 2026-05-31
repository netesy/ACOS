CC = gcc
CXX = g++
AS = as
LD = ld

# UEFI Target
UEFI_CFLAGS = -target x86_64-unknown-windows-coff -ffreestanding -fno-stack-protector -fshort-wchar -mno-red-zone -I. -Ilibs/runtime/include
UEFI_LDFLAGS = -m i386pep --subsystem 10 --entry efi_main

# Kernel Target
KERNEL_CFLAGS = -nostdinc++ -fno-pic -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -mno-red-zone -I. -Ilibs/runtime/include -Iuserland/posix/include -std=c++23 -Wall -Wextra -Werror
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
DISPLAY_DIR = services/display
AUDIO_DIR   = services/audio
STORAGE_DIR = $(KERNEL_DIR)/storage
NET_DIR     = $(KERNEL_DIR)/net
DRIVERS_DIR = $(KERNEL_DIR)/drivers
GRAPHICS_DIR = $(KERNEL_DIR)/graphics
K_AUDIO_DIR = $(KERNEL_DIR)/audio
D_AUDIO_DIR = drivers/audio
GUI_DIR     = userland/gui
SHELL_DIR   = userland/shell
POSIX_DIR   = userland/posix/libposix
LIBC_DIR    = libc
APPS_DIR    = apps

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
	$(GRAPHICS_DIR)/graphics_manager.cpp \
	$(GRAPHICS_DIR)/framebuffer.cpp \
	$(GRAPHICS_DIR)/renderer.cpp \
	$(GRAPHICS_DIR)/surface.cpp \
	$(GRAPHICS_DIR)/font.cpp \
	$(DISPLAY_DIR)/window.cpp \
	$(DISPLAY_DIR)/surface_manager.cpp \
	$(DISPLAY_DIR)/input_router.cpp \
	$(DISPLAY_DIR)/compositor.cpp \
	$(DISPLAY_DIR)/display_server.cpp \
	$(GUI_DIR)/widget.cpp \
	$(GUI_DIR)/theme.cpp \
	$(GUI_DIR)/layout.cpp \
	$(GUI_DIR)/button.cpp \
	$(GUI_DIR)/label.cpp \
	$(GUI_DIR)/window_widget.cpp \
	$(GUI_DIR)/textbox.cpp \
	$(GUI_DIR)/listview.cpp \
	$(SHELL_DIR)/taskbar.cpp \
	$(SHELL_DIR)/launcher.cpp \
	$(SHELL_DIR)/notification_center.cpp \
	$(SHELL_DIR)/desktop_shell.cpp \
	$(SHELL_DIR)/session_manager.cpp \
	$(SHELL_DIR)/volume_indicator.cpp \
	$(APPS_DIR)/terminal/terminal.cpp \
	$(APPS_DIR)/file_manager/file_manager.cpp \
	$(APPS_DIR)/settings/settings.cpp \
	$(APPS_DIR)/settings/audio_settings.cpp \
	$(APPS_DIR)/system_monitor/system_monitor.cpp \
	$(K_AUDIO_DIR)/audio_manager.cpp \
	$(K_AUDIO_DIR)/audio_device.cpp \
	$(D_AUDIO_DIR)/virtio_sound/virtio_sound.cpp \
	$(D_AUDIO_DIR)/hda/hda.cpp \
	$(AUDIO_DIR)/audio_server.cpp \
	$(AUDIO_DIR)/audio_stream.cpp \
	$(AUDIO_DIR)/audio_mixer.cpp \
	$(AUDIO_DIR)/audio_session.cpp \
	$(POSIX_DIR)/posix.cpp \
	$(POSIX_DIR)/file.cpp \
	$(POSIX_DIR)/process.cpp \
	$(POSIX_DIR)/socket.cpp \
	$(POSIX_DIR)/thread.cpp \
	$(POSIX_DIR)/signal.cpp \
	$(POSIX_DIR)/time.cpp \
	$(LIBC_DIR)/string/string.cpp \
	$(LIBC_DIR)/memory/malloc.cpp \
	$(LIBC_DIR)/stdio/stdio.cpp \
	$(LIBC_DIR)/stdlib/stdlib.cpp

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
