#!/usr/bin/env python3
import os
import shutil
import subprocess

def build_full_disk_image():
    # Construct a raw unpartitioned FAT32 disk image (64MB)
    disk_img = "acos.img"
    print("[IMG] Creating unpartitioned raw FAT32 disk image...")

    # Create 64MB zeroed image file
    with open(disk_img, "wb") as f:
        f.write(b"\x00" * (64 * 1024 * 1024))

    # Format as FAT32
    print("[IMG] Formatting with mkfs.vfat...")
    subprocess.run(["mkfs.vfat", "-F", "32", disk_img], check=True)

    # Create directories using mtools
    print("[IMG] Populating directories...")
    subprocess.run(["mmd", "-i", disk_img, "::/EFI"], check=True)
    subprocess.run(["mmd", "-i", disk_img, "::/EFI/BOOT"], check=True)
    subprocess.run(["mmd", "-i", disk_img, "::/bin"], check=True)

    # Copy bootloader and kernel
    boot_path = "build/dist/EFI/BOOT/BOOTX64.EFI" if os.path.exists("build/dist/EFI/BOOT/BOOTX64.EFI") else "acos_boot.efi"
    subprocess.run(["mcopy", "-i", disk_img, boot_path, "::/EFI/BOOT/BOOTX64.EFI"], check=True)

    kernel_path = "build/dist/kernel.elf" if os.path.exists("build/dist/kernel.elf") else "kernel.elf"
    subprocess.run(["mcopy", "-i", disk_img, kernel_path, "::/kernel.elf"], check=True)

    if os.path.exists("README.TXT"):
        subprocess.run(["mcopy", "-i", disk_img, "README.TXT", "::/README.TXT"], check=True)

    # Create and copy startup.nsh
    startup_path = "startup_temp.nsh"
    with open(startup_path, "w") as f:
        f.write("fs0:\\EFI\\BOOT\\BOOTX64.EFI\r\n")
    subprocess.run(["mcopy", "-i", disk_img, startup_path, "::/startup.nsh"], check=True)
    os.remove(startup_path)

    # Copy bin files
    bin_dir = "build/dist/bin"
    if os.path.exists(bin_dir):
        for fname in os.listdir(bin_dir):
            fpath = os.path.join(bin_dir, fname)
            if os.path.isfile(fpath) and fname.endswith(".elf"):
                subprocess.run(["mcopy", "-i", disk_img, fpath, f"::/bin/{fname}"], check=True)

    print("Success: Generated raw unpartitioned acos.img disk image!")

if __name__ == "__main__":
    build_full_disk_image()
