#ifndef CPPFORGE_CORE_FORGE_FORGEABLE_HPP
#define CPPFORGE_CORE_FORGE_FORGEABLE_HPP

/**
 * @file forgeable.hpp
 * @brief Base CRTP-style Forgeable interface for stateless execution.
 */

#include <string>

namespace cppforge::core::forge {

    /**
     * @brief Base class for Forgeable-like behavior.
     *
     * Derived classes must implement:
     *   - void execute(
       ) noexcept;
     *   - ExecutionLabel getLabel(
       ) const noexcept;
     */
    template<typename Derived>
    class Forgeable
    {
    public:
        using ExecutionLabel = std::string;


        void execute(
        ) noexcept;
        ExecutionLabel getLabel(
        ) const noexcept;

    protected:
        Forgeable() = default;
        Forgeable(const Forgeable&) = delete;
        Forgeable& operator=(const Forgeable&) = delete;

    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGEABLE_HPP