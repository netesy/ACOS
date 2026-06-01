#include "pkg.h"
#include <libs/runtime/include/acos/runtime.h>
#include <userland/posix/include/unistd.h>
#include <userland/posix/include/fcntl.h>

namespace acos::pkg {

Package::Package(const char* path) {
    if (!path) {
        m_path[0] = '\0';
        return;
    }
    
    usize i = 0;
    while (path[i] && i < 255) {
        m_path[i] = path[i];
        i++;
    }
    m_path[i] = '\0';
    
    // Initialize manifest
    memset(&m_manifest, 0, sizeof(m_manifest));
    memset(&m_header, 0, sizeof(m_header));
}

bool Package::load() {
    if (m_path[0] == '\0') return false;
    
    // Open package file
    int fd = open(m_path, O_RDONLY);
    if (fd < 0) return false;
    
    // Read ACPK header
    if (read(fd, &m_header, sizeof(ACPKHeader)) != sizeof(ACPKHeader)) {
        close(fd);
        return false;
    }
    
    // Verify magic number
    if (m_header.magic != 0x4B504341) { // 'ACPK' in little-endian
        close(fd);
        return false;
    }
    
    // Verify version
    if (m_header.version != 1) {
        close(fd);
        return false;
    }
    
    // Seek to manifest offset
    lseek(fd, m_header.manifest_offset, 0); // 0 = SEEK_SET
    
    // Read manifest
    if (read(fd, &m_manifest, sizeof(PackageManifest)) != sizeof(PackageManifest)) {
        close(fd);
        return false;
    }
    
    // Validate manifest
    if (m_manifest.name[0] == '\0') {
        close(fd);
        return false;
    }
    
    // Null-terminate strings
    m_manifest.name[63] = '\0';
    m_manifest.version[31] = '\0';
    m_manifest.architecture[15] = '\0';
    m_manifest.publisher[63] = '\0';
    m_manifest.description[255] = '\0';
    m_manifest.license[63] = '\0';
    
    close(fd);
    return true;
}

} // namespace acos::pkg
