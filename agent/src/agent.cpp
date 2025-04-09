#include "agent.hpp"
#include "agent_factory.hpp"
#include <iostream>

class AgentAppImpl : public AgentApp {
public:
    void run() override {
        std::cout << "Running agent logic..." << std::endl;
    }
};

std::unique_ptr<AgentApp> create_agent_app() {
    return std::make_unique<AgentAppImpl>();
}
