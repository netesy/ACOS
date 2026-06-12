#include <acos/process.h>
#include <acos/runtime.h>
#include <userland/pkg/package_manager.h>
#include <libc/stdio/stdio.cpp>

using namespace acos::pkg;

int main(int argc, char** argv) {
    if (argc < 2) {
        // printf("Usage: pkg [install|remove|upgrade|verify] <package>\n");
        return 1;
    }

    PackageManager pm;
    // Basic CLI dispatch
    return 0;
}
