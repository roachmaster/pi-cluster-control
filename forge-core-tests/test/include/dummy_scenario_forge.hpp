#ifndef DUMMY_SCENARIO_FORGE_HPP
#define DUMMY_SCENARIO_FORGE_HPP

#include "forge.hpp"             // Defines cppforge::core::forge::Forge<T> and NoOpDeleter.
#include "dummy_scenario.hpp"      // Contains the DummyScenario class and its factory (if any).
#include <memory>
#include <utility>

namespace cppforge::scenarios {

// DummyScenarioForge mimics the Kotlin version pattern: it accepts a default (nullable)
// and a stub (non-null) implementation of DummyScenario, and its createImpl() method returns
// the default if available, otherwise the stub. The returned unique_ptr uses a NoOpDeleter.
    class DummyScenarioForge : public cppforge::core::forge::Forge<DummyScenario> {
    private:
        std::shared_ptr<DummyScenario> defaultImpl;  // may be null.
        std::shared_ptr<DummyScenario> stubImpl;     // must not be null.
    public:
        // Constructor accepts the two implementations.
        DummyScenarioForge(std::shared_ptr<DummyScenario> defaultImpl,
                           std::shared_ptr<DummyScenario> stubImpl)
                : defaultImpl(std::move(defaultImpl)), stubImpl(std::move(stubImpl))
        { }

        // Override of the factory method.
        // Returns a unique_ptr that borrows the instance from the shared_ptr with a NoOpDeleter.
        std::unique_ptr<DummyScenario, core::forge::NoOpDeleter> createImpl() override {
            if (defaultImpl) {
                return std::unique_ptr<DummyScenario, core::forge::NoOpDeleter>(defaultImpl.get(), core::forge::NoOpDeleter{});
            } else {
                return std::unique_ptr<DummyScenario, core::forge::NoOpDeleter>(stubImpl.get(), core::forge::NoOpDeleter{});
            }
        }
    };

} // namespace cppforge::scenarios

#endif // DUMMY_SCENARIO_FORGE_HPP