#ifndef CPPFORGE_CORE_FORGE_FORGEABLE_HPP
#define CPPFORGE_CORE_FORGE_FORGEABLE_HPP

/**
 * @file forgeable.hpp
 * @brief Base CRTP-style Forgeable interface for stateless execution.
 */

#include <string>

namespace cppforge::core::forge {

    using ExecutionLabel = std::string;

    /**
     * @brief CRTP base class for Forgeable-like behavior.
     *
     * Derived classes must implement:
     *   - void ExecuteImpl();
     *   - ExecutionLabel GetLabelImpl() const;
     */
    template<typename Derived>
    class Forgeable {
    public:
        void Execute() {
            return static_cast<Derived*>(this)->ExecuteImpl();
        }

        ExecutionLabel GetLabel() const {
            return static_cast<const Derived*>(this)->GetLabelImpl();
        }

    protected:
        Forgeable() = default;
        Forgeable(const Forgeable&) = delete;
        Forgeable& operator=(const Forgeable&) = delete;
    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGEABLE_HPP