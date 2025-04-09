#pragma once
#include <memory>
#include "master.hpp"

std::unique_ptr<MasterApp> create_master_app();