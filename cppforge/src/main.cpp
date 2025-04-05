#include "cppforge_factory.hpp"

int main(int argc, char** argv) {
    auto app = create_cppforge_app();
    app->run();
    return 0;
}
