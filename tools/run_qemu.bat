@echo off
setlocal

set DISK_IMG=acos.img
set OVMF_PATH=C:\ovmf\OVMF.fd

echo Building ACOS...
mingw32-make mingw_all

echo Starting QEMU...
qemu-system-x86_64 -bios %OVMF_PATH% -drive file=%DISK_IMG%,format=raw -serial stdio

endlocal
