#include "master.hpp"
#include "master_factory.hpp"
#include <iostream>

class MasterAppImpl : public MasterApp {
public:
    void run() override {
        std::cout << "Running master logic..." << std::endl;
    }
};

std::unique_ptr<MasterApp> create_master_app() {
    return std::make_unique<MasterAppImpl>();
}
