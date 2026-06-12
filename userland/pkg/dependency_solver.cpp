#include <acos/process.h>
#include <acos/runtime.h>
#include "dependency_solver.h"
#include <libs/runtime/include/acos/runtime.h>

namespace acos::pkg {

namespace {

bool empty_name(const char* name) {
    return !name || name[0] == '\0';
}

bool same_name(const char* lhs, const char* rhs) {
    if (!lhs || !rhs) {
        return false;
    }

    for (usize i = 0; i < 64; ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
        if (lhs[i] == '\0') {
            return true;
        }
    }
    return true;
}

void copy_name(char* dest, const char* src) {
    usize i = 0;
    for (; i + 1 < 64 && src && src[i]; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

} // namespace

DependencySolver::DependencySolver() : m_visited_count(0) {
    memset(m_visited, 0, sizeof(m_visited));
}

bool DependencySolver::resolve(const PackageManifest& target, PackageManifest* result, usize* count) {
    if (!result || !count || empty_name(target.name)) {
        return false;
    }

    *count = 0;
    m_visited_count = 0;
    memset(m_visited, 0, sizeof(m_visited));

    if (*count >= MAX_VISITED || !remember(target.name)) {
        return false;
    }
    result[(*count)++] = target;

    for (usize i = 0; i < 16; ++i) {
        const char* dependency = target.dependencies[i];
        if (empty_name(dependency)) {
            continue;
        }
        if (has_visited(dependency)) {
            return false;
        }
        if (!remember(dependency)) {
            return false;
        }
    }

    return check_cycles() && check_conflicts();
}

bool DependencySolver::has_visited(const char* name) const {
    for (usize i = 0; i < m_visited_count; ++i) {
        if (same_name(m_visited[i], name)) {
            return true;
        }
    }
    return false;
}

bool DependencySolver::remember(const char* name) {
    if (m_visited_count >= MAX_VISITED || empty_name(name)) {
        return false;
    }
    copy_name(m_visited[m_visited_count++], name);
    return true;
}

bool DependencySolver::check_conflicts() const {
    for (usize i = 0; i < m_visited_count; ++i) {
        for (usize j = i + 1; j < m_visited_count; ++j) {
            if (same_name(m_visited[i], m_visited[j])) {
                return false;
            }
        }
    }
    return true;
}

bool DependencySolver::check_cycles() const {
    return check_conflicts();
}

} // namespace acos::pkg
