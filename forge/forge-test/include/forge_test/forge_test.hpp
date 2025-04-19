#pragma once

#include "stateless_forgeable.hpp"
#include "forge_resolver.hpp"
#include <exception>

namespace forge_test {

/**
 * @brief Base class for running Forge-compatible tests with full lifecycle management.
 *
 * Provides structured exception handling and phase separation.
 */
    template<typename Derived, typename ForgeType>
    class ForgeTest : public cppforge::core::forge::StatelessForgeable<Derived> {
    public:
        using Resolver = cppforge::core::forge::ForgeResolver<ForgeType>;

        explicit ForgeTest(Resolver* resolver) : resolver_(resolver) {}

    protected:
        Resolver* resolver_;

        void ExecuteImpl() {
            if (!runSetupPhases()) {
                return;
            }

            auto capturedException = runExecutePhase();

            runVerifyPhase(capturedException);

            runAfterPhase();
        }

    private:
        bool runSetupPhases() {
            try {
                Derived::beforeTest(resolver_);
                Derived::setup(resolver_);
                return true;
            } catch (const std::exception& ex) {
                handleFatalTestSetupFailure(ex);
                return false;
            }
        }

        std::exception_ptr runExecutePhase() {
            try {
                Derived::executeTest(resolver_);
                return nullptr;
            } catch (...) {
                return std::current_exception();
            }
        }

        void runVerifyPhase(std::exception_ptr capturedException) {
            try {
                Derived::verify(resolver_, capturedException);
            } catch (const std::exception& ex) {
                handleFatalVerificationFailure(ex);
            }
        }

        void runAfterPhase() {
            try {
                Derived::afterTest(resolver_);
            } catch (const std::exception& ex) {
                handleFatalAfterTestFailure(ex);
            }
        }

        static void handleFatalTestSetupFailure(const std::exception& ex) noexcept {
            // TODO: Customize behavior: fail, log, abort, etc.
            std::terminate();
        }

        static void handleFatalVerificationFailure(const std::exception& ex) noexcept {
            // TODO: Customize behavior: fail verification phase.
            std::terminate();
        }

        static void handleFatalAfterTestFailure(const std::exception& ex) noexcept {
            // TODO: Customize behavior: fail if cleanup fails.
            // Not always fatal — could be a warning only.
        }
    };

} // namespace forge_test