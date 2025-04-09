#pragma once

class BackendApp {
public:
    virtual void run() = 0;
    virtual ~BackendApp() = default;
};
