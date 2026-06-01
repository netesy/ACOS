#include "repository.h"

namespace acos::pkg {

Repository::Repository(const char* name, const char* url) : m_available_count(0) {
    // Initialize metadata
    (void)name; (void)url;
}

bool Repository::sync() {
    if (!m_metadata.url) return false;
    
    // Repository synchronization process:
    // 1. Connect to repository server via network
    // 2. Request package list/index
    // 3. Parse response (typically JSON or binary format)
    // 4. Update m_available array with available packages
    
    m_available_count = 0;
    
    // In a full implementation, this would:
    // - Use socket API to connect to repository server
    // - Send HTTP GET request for package index
    // - Parse the response
    // - Populate m_available with package metadata
    
    // For now, provide a basic implementation that:
    // - Simulates successful sync
    // - Maintains empty package list (to be populated by network layer)
    
    // Example: add a test package for demonstration
    if (m_available_count < 64) {
        PackageManifest& pkg = m_available[m_available_count++];
        acos::runtime::memset(&pkg, 0, sizeof(pkg));
        
        // Copy package name
        const char* test_name = "core-libs";
        usize i = 0;
        while (test_name[i] && i < 63) {
            pkg.name[i] = test_name[i];
            i++;
        }
        pkg.name[i] = '\0';
        
        // Copy version
        const char* test_version = "1.0.0";
        i = 0;
        while (test_version[i] && i < 31) {
            pkg.version[i] = test_version[i];
            i++;
        }
        pkg.version[i] = '\0';
        
        pkg.size = 1024 * 1024; // 1MB
    }
    
    return true;
}

const PackageManifest* Repository::get_package(usize index) const {
    if (index < m_available_count) return &m_available[index];
    return nullptr;
}

} // namespace acos::pkg
