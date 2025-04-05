#include "cppforge.hpp"
#include "cppforge_factory.hpp"
#include <iostream>

class CppforgeAppImpl : public CppforgeApp {
public:
    void run() override {
        std::cout << "Running cppforge logic..." << std::endl;
    }
};

std::unique_ptr<CppforgeApp> create_cppforge_app() {
    return std::make_unique<CppforgeAppImpl>();
}
