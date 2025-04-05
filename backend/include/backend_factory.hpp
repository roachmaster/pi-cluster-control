#pragma once
#include <memory>
#include "backend.hpp"

std::unique_ptr<BackendApp> create_backend_app();