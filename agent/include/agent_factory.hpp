#pragma once
#include <memory>
#include "agent.hpp"

std::unique_ptr<AgentApp> create_agent_app();