#pragma once
#include <acos/types.h>

namespace acos::hal {

class SpinLock {
public:
    void lock() {
        while (__atomic_test_and_set(&m_locked, __ATOMIC_ACQUIRE)) {
            __asm__("pause");
        }
    }

    void unlock() {
        __atomic_clear(&m_locked, __ATOMIC_RELEASE);
    }

private:
    bool m_locked = false;
};

class ScopedLock {
public:
    ScopedLock(SpinLock& lock) : m_lock(lock) { m_lock.lock(); }
    ~ScopedLock() { m_lock.unlock(); }
private:
    SpinLock& m_lock;
};

} // namespace acos::hal
