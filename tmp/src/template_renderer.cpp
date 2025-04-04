#include "cppforge/template_renderer.hpp"
#include <iostream>

namespace cppforge {

    std::string render_template(const std::string& template_str, const std::string& json_data) {
        std::cout << "[template_renderer] Simulating rendering..." << std::endl;
        return template_str;  // Just a passthrough for now
    }

}
