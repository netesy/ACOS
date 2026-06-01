#pragma once
#include <acos/types.h>

namespace acos::pkg {

struct PackageManifest {
    char name[64];
    char version[32];
    char architecture[16];
    char publisher[64];
    char description[256];
    char license[64];

    // Capability bits requested by the package
    u64 capabilities;
    u64 size;
    char dependencies[16][64];
};

struct ACPKHeader {
    u32 magic; // 'ACPK'
    u32 version;
    u64 manifest_offset;
    u64 payload_offset;
    u64 signature_offset;
    u8 checksum[32]; // SHA-256
};

class Package {
public:
    Package(const char* path);
    Package(const PackageManifest& manifest);
    bool load();

    const PackageManifest& manifest() const { return m_manifest; }
    const char* path() const { return m_path; }

private:
    char m_path[256];
    PackageManifest m_manifest;
    ACPKHeader m_header;
};

} // namespace acos::pkg
