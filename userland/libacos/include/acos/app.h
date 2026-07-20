#pragma once
#include <acos/types.h>

namespace acos::app {

class Application {
public:
    Application();
    virtual ~Application();

    static Application& get() { return *s_instance; }

    virtual void initialize();
    virtual int run();
    virtual void quit();

private:
    static Application* s_instance;
    bool m_running;
};

} // namespace acos::app
