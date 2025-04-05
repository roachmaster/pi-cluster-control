#include "backend.hpp"
#include "backend_factory.hpp"
#include <iostream>

class BackendAppImpl : public BackendApp {
public:
    void run() override {
        std::cout << "Running backend logic..." << std::endl;
    }
};

std::unique_ptr<BackendApp> create_backend_app() {
    return std::make_unique<BackendAppImpl>();
}
