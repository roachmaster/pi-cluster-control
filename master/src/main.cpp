#include "master_factory.hpp"

int main(int argc, char** argv) {
    auto app = create_master_app();
    app->run();
    return 0;
}
