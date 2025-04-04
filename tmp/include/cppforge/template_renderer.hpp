#pragma once

#include <string>

namespace cppforge {
    std::string render_template(const std::string& template_str, const std::string& json_data);
}
