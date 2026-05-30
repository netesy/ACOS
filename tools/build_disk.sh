#!/bin/bash

DISK_IMG="acos.img"
BOOT_EFI="acos_boot.efi"
KERNEL_ELF="kernel.elf"

if [ ! -f "$BOOT_EFI" ]; then
    echo "Error: $BOOT_EFI not found."
    exit 1
fi

dd if=/dev/zero of=$DISK_IMG bs=1M count=64
mkfs.vfat -F 32 $DISK_IMG
mmd -i $DISK_IMG ::/EFI
mmd -i $DISK_IMG ::/EFI/BOOT
mcopy -i $DISK_IMG $BOOT_EFI ::/EFI/BOOT/BOOTX64.EFI
mcopy -i $DISK_IMG $KERNEL_ELF ::/kernel.elf
echo "Success."
