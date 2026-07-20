#include <acos/app.h>
#include <acos/process.h>
#include <acos/syscall.h>

namespace acos::app {

Application* Application::s_instance = nullptr;

Application::Application() : m_running(false) {
    s_instance = this;
}

Application::~Application() {
    if (s_instance == this) {
        s_instance = nullptr;
    }
}

void Application::initialize() {}

int Application::run() {
    m_running = true;
    while (m_running) {
        // Run standard loop yielding CPU
        syscall(sys::SyscallNum::Yield, 0, 0, 0, 0, 0);
    }
    return 0;
}

void Application::quit() {
    m_running = false;
}

} // namespace acos::app
