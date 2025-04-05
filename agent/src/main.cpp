#include "agent_factory.hpp"

int main(int argc, char** argv) {
    auto app = create_agent_app();
    app->run();
    return 0;
}
