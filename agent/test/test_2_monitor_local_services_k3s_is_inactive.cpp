#include <gtest/gtest.h>
#include <iostream>
#include <memory>

// Step Interface
class scn_2_monitor_local_services_k3s_is_inactive {
public:
    virtual void given_k3s_is_not_running() {
        FAIL() << "[STEP NOT IMPLEMENTED] Given k3s is not running";
    }
    virtual void when_the_agent_checks_for_running_services() {
        FAIL() << "[STEP NOT IMPLEMENTED] When the agent checks for running services";
    }
    virtual void then_it_should_report_k3s_as_inactive() {
        FAIL() << "[STEP NOT IMPLEMENTED] Then it should report k3s as inactive";
    }

    virtual ~scn_2_monitor_local_services_k3s_is_inactive() = default;
};

// Stub Implementation (throws failures)
class stub_scn_2_monitor_local_services_k3s_is_inactive : public scn_2_monitor_local_services_k3s_is_inactive {
    // No overrides – just uses FAIL() behavior from base class
};

#ifdef HAS_IMPL_scn_2_monitor_local_services_k3s_is_inactive
static std::unique_ptr<scn_2_monitor_local_services_k3s_is_inactive> forge_bdd_steps() {
    return std::make_unique<impl_scn_2_monitor_local_services_k3s_is_inactive>();
}
#else
static std::unique_ptr<scn_2_monitor_local_services_k3s_is_inactive> forge_bdd_steps() {
    return std::make_unique<stub_scn_2_monitor_local_services_k3s_is_inactive>();
}
#endif

// Test Case
TEST(scn_2_monitor_local_services_k3s_is_inactive_test, executes_scenario) {
    auto steps = forge_bdd_steps();

    std::cout << "[GIVEN] Given k3s is not running" << std::endl;
    steps->given_k3s_is_not_running();
    std::cout << "[WHEN] When the agent checks for running services" << std::endl;
    steps->when_the_agent_checks_for_running_services();
    std::cout << "[THEN] Then it should report k3s as inactive" << std::endl;
    steps->then_it_should_report_k3s_as_inactive();
}
