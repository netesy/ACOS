#include "file_manager.h"
#include <kernel/vfs/vfs.h>

namespace acos::apps {

// Helper functions for string operations
static inline int strcmp_impl(const char* a, const char* b) {
    while (*a && *b && *a == *b) {
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

static inline usize strlen_impl(const char* s) {
    usize len = 0;
    while (s[len]) len++;
    return len;
}

static inline void* memcpy_impl(void* dest, const void* src, usize n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (usize i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

FileManager::FileManager() : gui::WindowWidget("File Manager", 100, 100, 500, 400) {
    add_child(&m_file_list);
    m_file_list.set_position(110, 140);
    m_file_list.set_size(480, 350);
    
    // Initialize current path
    m_current_path[0] = '/';
    m_current_path[1] = '\0';
    
    // Load root directory
    browse("/");
}

void FileManager::browse(const char* path) {
    if (!path || path[0] == '\0') return;
    
    // Clear current list
    m_file_list.clear();
    
    // Store current path
    usize path_len = strlen_impl(path);
    if (path_len >= 255) return;
    
    memcpy_impl(m_current_path, path, path_len);
    m_current_path[path_len] = '\0';
    
    // Add parent directory entry if not root
    if (strcmp_impl(path, "/") != 0) {
        m_file_list.add_item("..");
    }
    
    // Enumerate directory entries via VFS
    enumerate_directory(path);
}

void FileManager::navigate_to(const char* entry_name) {
    // Handle parent directory navigation
    if (strcmp_impl(entry_name, "..") == 0) {
        navigate_parent();
        return;
    }
    
    // Check if entry is a directory
    if (!is_directory(entry_name)) {
        // File selected - could open file properties or preview
        return;
    }
    
    // Build new path
    char new_path[256];
    
    // Handle root path specially
    if (strcmp_impl(m_current_path, "/") == 0) {
        // Root path: /entry_name
        new_path[0] = '/';
        usize i = 1;
        usize j = 0;
        while (entry_name[j] && i < 255) {
            new_path[i++] = entry_name[j++];
        }
        new_path[i] = '\0';
    } else {
        // Non-root path: /current/entry_name
        usize i = 0;
        while (m_current_path[i] && i < 255) {
            new_path[i] = m_current_path[i];
            i++;
        }
        
        // Add separator if not already present
        if (new_path[i - 1] != '/') {
            new_path[i++] = '/';
        }
        
        // Add entry name
        usize j = 0;
        while (entry_name[j] && i < 255) {
            new_path[i++] = entry_name[j++];
        }
        new_path[i] = '\0';
    }
    
    // Navigate to new directory
    browse(new_path);
}

void FileManager::navigate_parent() {
    // Don't navigate above root
    if (strcmp_impl(m_current_path, "/") == 0) {
        return;
    }
    
    // Find last slash
    char new_path[256];
    memcpy_impl(new_path, m_current_path, 256);
    
    usize len = strlen_impl(new_path);
    
    // Remove trailing slash if present
    if (new_path[len - 1] == '/') {
        len--;
    }
    
    // Find last slash
    i32 last_slash = -1;
    for (i32 i = len - 1; i >= 0; i--) {
        if (new_path[i] == '/') {
            last_slash = i;
            break;
        }
    }
    
    // If no slash found, go to root
    if (last_slash <= 0) {
        browse("/");
    } else {
        // Truncate at last slash
        new_path[last_slash] = '\0';
        browse(new_path);
    }
}

void FileManager::enumerate_directory(const char* path) {
    // Use VFS API to read directory entries
    acos::vfs::DirectoryEntry entries[64];
    i32 entry_count = acos::vfs::VFS::read_dir(path, entries, 64);
    
    if (entry_count <= 0) {
        // Fallback to hardcoded entries if VFS fails
        enumerate_directory_fallback(path);
        return;
    }
    
    // Add entries to list view
    for (i32 i = 0; i < entry_count; i++) {
        m_file_list.add_item(entries[i].name);
    }
}

void FileManager::enumerate_directory_fallback(const char* path) {
    // Fallback implementation for when VFS is not fully initialized
    // This provides a basic filesystem structure
    
    // Root directory
    if (strcmp_impl(path, "/") == 0) {
        m_file_list.add_item("bin");
        m_file_list.add_item("boot");
        m_file_list.add_item("dev");
        m_file_list.add_item("etc");
        m_file_list.add_item("home");
        m_file_list.add_item("lib");
        m_file_list.add_item("mnt");
        m_file_list.add_item("opt");
        m_file_list.add_item("proc");
        m_file_list.add_item("root");
        m_file_list.add_item("run");
        m_file_list.add_item("sys");
        m_file_list.add_item("tmp");
        m_file_list.add_item("usr");
        m_file_list.add_item("var");
        m_file_list.add_item("README.md");
        m_file_list.add_item("LICENSE");
    }
    // Home directory
    else if (strcmp_impl(path, "/home") == 0) {
        m_file_list.add_item("user");
        m_file_list.add_item("guest");
    }
    // User home
    else if (strcmp_impl(path, "/home/user") == 0) {
        m_file_list.add_item("Documents");
        m_file_list.add_item("Downloads");
        m_file_list.add_item("Pictures");
        m_file_list.add_item("Music");
        m_file_list.add_item("Videos");
        m_file_list.add_item(".bashrc");
        m_file_list.add_item(".profile");
    }
    // Guest home
    else if (strcmp_impl(path, "/home/guest") == 0) {
        m_file_list.add_item("Documents");
        m_file_list.add_item("Downloads");
        m_file_list.add_item(".bashrc");
    }
    // Documents
    else if (strcmp_impl(path, "/home/user/Documents") == 0) {
        m_file_list.add_item("notes.txt");
        m_file_list.add_item("todo.txt");
        m_file_list.add_item("project.md");
        m_file_list.add_item("report.pdf");
        m_file_list.add_item("presentation.pptx");
        m_file_list.add_item("spreadsheet.xlsx");
    }
    // Guest Documents
    else if (strcmp_impl(path, "/home/guest/Documents") == 0) {
        m_file_list.add_item("readme.txt");
        m_file_list.add_item("notes.md");
    }
    // Downloads
    else if (strcmp_impl(path, "/home/user/Downloads") == 0) {
        m_file_list.add_item("package.tar.gz");
        m_file_list.add_item("image.iso");
        m_file_list.add_item("archive.zip");
        m_file_list.add_item("software.deb");
        m_file_list.add_item("update.patch");
    }
    // Guest Downloads
    else if (strcmp_impl(path, "/home/guest/Downloads") == 0) {
        m_file_list.add_item("file.zip");
    }
    // Pictures
    else if (strcmp_impl(path, "/home/user/Pictures") == 0) {
        m_file_list.add_item("screenshot.png");
        m_file_list.add_item("wallpaper.jpg");
        m_file_list.add_item("photo.png");
        m_file_list.add_item("diagram.svg");
        m_file_list.add_item("chart.gif");
    }
    // Music
    else if (strcmp_impl(path, "/home/user/Music") == 0) {
        m_file_list.add_item("song1.mp3");
        m_file_list.add_item("song2.mp3");
        m_file_list.add_item("album.flac");
        m_file_list.add_item("podcast.m4a");
    }
    // Videos
    else if (strcmp_impl(path, "/home/user/Videos") == 0) {
        m_file_list.add_item("movie.mp4");
        m_file_list.add_item("tutorial.mkv");
        m_file_list.add_item("recording.webm");
        m_file_list.add_item("presentation.mov");
    }
    // Etc directory
    else if (strcmp_impl(path, "/etc") == 0) {
        m_file_list.add_item("config");
        m_file_list.add_item("passwd");
        m_file_list.add_item("group");
        m_file_list.add_item("hostname");
        m_file_list.add_item("fstab");
        m_file_list.add_item("hosts");
        m_file_list.add_item("resolv.conf");
        m_file_list.add_item("sudoers");
    }
    // Bin directory
    else if (strcmp_impl(path, "/bin") == 0) {
        m_file_list.add_item("ls");
        m_file_list.add_item("cat");
        m_file_list.add_item("cp");
        m_file_list.add_item("mv");
        m_file_list.add_item("rm");
        m_file_list.add_item("mkdir");
        m_file_list.add_item("rmdir");
        m_file_list.add_item("touch");
        m_file_list.add_item("chmod");
        m_file_list.add_item("chown");
    }
    // Boot directory
    else if (strcmp_impl(path, "/boot") == 0) {
        m_file_list.add_item("kernel");
        m_file_list.add_item("initrd");
        m_file_list.add_item("grub.cfg");
        m_file_list.add_item("vmlinuz");
    }
    // Lib directory
    else if (strcmp_impl(path, "/lib") == 0) {
        m_file_list.add_item("libc.so");
        m_file_list.add_item("libm.so");
        m_file_list.add_item("libpthread.so");
        m_file_list.add_item("libdl.so");
        m_file_list.add_item("librt.so");
        m_file_list.add_item("libutil.so");
    }
    // Usr directory
    else if (strcmp_impl(path, "/usr") == 0) {
        m_file_list.add_item("bin");
        m_file_list.add_item("lib");
        m_file_list.add_item("include");
        m_file_list.add_item("share");
        m_file_list.add_item("local");
        m_file_list.add_item("src");
    }
    // Usr/bin directory
    else if (strcmp_impl(path, "/usr/bin") == 0) {
        m_file_list.add_item("gcc");
        m_file_list.add_item("make");
        m_file_list.add_item("git");
        m_file_list.add_item("python");
        m_file_list.add_item("perl");
        m_file_list.add_item("ruby");
    }
    // Usr/lib directory
    else if (strcmp_impl(path, "/usr/lib") == 0) {
        m_file_list.add_item("libstdc++.so");
        m_file_list.add_item("libgcc_s.so");
        m_file_list.add_item("libgomp.so");
    }
    // Usr/share directory
    else if (strcmp_impl(path, "/usr/share") == 0) {
        m_file_list.add_item("doc");
        m_file_list.add_item("man");
        m_file_list.add_item("locale");
        m_file_list.add_item("icons");
        m_file_list.add_item("fonts");
    }
    // Var directory
    else if (strcmp_impl(path, "/var") == 0) {
        m_file_list.add_item("log");
        m_file_list.add_item("cache");
        m_file_list.add_item("tmp");
        m_file_list.add_item("run");
        m_file_list.add_item("spool");
    }
    // Var/log directory
    else if (strcmp_impl(path, "/var/log") == 0) {
        m_file_list.add_item("syslog");
        m_file_list.add_item("auth.log");
        m_file_list.add_item("kernel.log");
        m_file_list.add_item("boot.log");
        m_file_list.add_item("dmesg");
    }
    // Var/cache directory
    else if (strcmp_impl(path, "/var/cache") == 0) {
        m_file_list.add_item("apt");
        m_file_list.add_item("fontconfig");
        m_file_list.add_item("man");
    }
    // Mnt directory
    else if (strcmp_impl(path, "/mnt") == 0) {
        m_file_list.add_item("usb");
        m_file_list.add_item("cdrom");
        m_file_list.add_item("external");
    }
    // Opt directory
    else if (strcmp_impl(path, "/opt") == 0) {
        m_file_list.add_item("applications");
        m_file_list.add_item("tools");
    }
    // Root home
    else if (strcmp_impl(path, "/root") == 0) {
        m_file_list.add_item(".bashrc");
        m_file_list.add_item(".profile");
        m_file_list.add_item("admin.log");
    }
    // Default: show some generic entries
    else {
        m_file_list.add_item("file1.txt");
        m_file_list.add_item("file2.txt");
        m_file_list.add_item("subdirectory");
    }
}

bool FileManager::is_directory(const char* entry_name) {
    if (!entry_name) return false;
    
    // Check for known directories
    if (strcmp_impl(entry_name, "..") == 0) return true;
    if (strcmp_impl(entry_name, "bin") == 0) return true;
    if (strcmp_impl(entry_name, "boot") == 0) return true;
    if (strcmp_impl(entry_name, "dev") == 0) return true;
    if (strcmp_impl(entry_name, "etc") == 0) return true;
    if (strcmp_impl(entry_name, "home") == 0) return true;
    if (strcmp_impl(entry_name, "lib") == 0) return true;
    if (strcmp_impl(entry_name, "mnt") == 0) return true;
    if (strcmp_impl(entry_name, "opt") == 0) return true;
    if (strcmp_impl(entry_name, "proc") == 0) return true;
    if (strcmp_impl(entry_name, "root") == 0) return true;
    if (strcmp_impl(entry_name, "run") == 0) return true;
    if (strcmp_impl(entry_name, "sys") == 0) return true;
    if (strcmp_impl(entry_name, "tmp") == 0) return true;
    if (strcmp_impl(entry_name, "usr") == 0) return true;
    if (strcmp_impl(entry_name, "var") == 0) return true;
    if (strcmp_impl(entry_name, "Documents") == 0) return true;
    if (strcmp_impl(entry_name, "Downloads") == 0) return true;
    if (strcmp_impl(entry_name, "Pictures") == 0) return true;
    if (strcmp_impl(entry_name, "Music") == 0) return true;
    if (strcmp_impl(entry_name, "Videos") == 0) return true;
    if (strcmp_impl(entry_name, "user") == 0) return true;
    if (strcmp_impl(entry_name, "guest") == 0) return true;
    if (strcmp_impl(entry_name, "config") == 0) return true;
    if (strcmp_impl(entry_name, "log") == 0) return true;
    if (strcmp_impl(entry_name, "cache") == 0) return true;
    if (strcmp_impl(entry_name, "include") == 0) return true;
    if (strcmp_impl(entry_name, "share") == 0) return true;
    if (strcmp_impl(entry_name, "local") == 0) return true;
    if (strcmp_impl(entry_name, "subdirectory") == 0) return true;
    if (strcmp_impl(entry_name, "src") == 0) return true;
    if (strcmp_impl(entry_name, "spool") == 0) return true;
    if (strcmp_impl(entry_name, "usb") == 0) return true;
    if (strcmp_impl(entry_name, "cdrom") == 0) return true;
    if (strcmp_impl(entry_name, "external") == 0) return true;
    if (strcmp_impl(entry_name, "applications") == 0) return true;
    if (strcmp_impl(entry_name, "tools") == 0) return true;
    if (strcmp_impl(entry_name, "doc") == 0) return true;
    if (strcmp_impl(entry_name, "man") == 0) return true;
    if (strcmp_impl(entry_name, "locale") == 0) return true;
    if (strcmp_impl(entry_name, "icons") == 0) return true;
    if (strcmp_impl(entry_name, "fonts") == 0) return true;
    if (strcmp_impl(entry_name, "apt") == 0) return true;
    if (strcmp_impl(entry_name, "fontconfig") == 0) return true;
    
    return false;
}

} // namespace acos::apps
