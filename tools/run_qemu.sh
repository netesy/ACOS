#!/bin/bash

DISK_IMG="acos.img"
OVMF_PATH="/usr/share/ovmf/OVMF.fd"

echo "Building ACOS..."
make clean && make all

echo "Packaging..."
./tools/build_disk.sh

echo "Starting QEMU..."
qemu-system-x86_64 -bios "$OVMF_PATH" -drive file=$DISK_IMG,format=raw -serial stdio || qemu-system-x86_64 -drive file=$DISK_IMG,format=raw -serial stdio
