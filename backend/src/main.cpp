#include "backend_factory.hpp"

int main(int argc, char** argv) {
    auto app = create_backend_app();
    app->run();
    return 0;
}
