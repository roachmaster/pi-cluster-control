#ifndef FORGE_HPP
#define FORGE_HPP

/**
 * @file forge.hpp
 * @brief Defines the templated Forge<T> interface for creating Forgeable components.
 */

#include "i_forge.hpp"
#include "cppforge_ptr.hpp"
#include "forgeable_traits.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Templated factory interface for creating Forgeable components.
     *
     * @tparam T The specific Forgeable subclass to produce.
     */
    template <typename T>
    class Forge : public IForge {
    public:
        static_assert(is_forgeable<T>, "T must be derived from Forgeable");

        /**
         * @brief Strongly-typed creation method for concrete Forgeable instances.
         *
         * @return ForgeableImplPtr<T> A pointer to a freshly created instance of T.
         */
        virtual ForgeableImplPtr<T> createImpl() = 0;

        /**
         * @brief Type-erased factory method.
         *
         * Implements IForge by calling createImpl() and converting to ForgeablePtr.
         */
        ForgeablePtr create() override {
            return ForgeablePtr(createImpl().release(), NoOpDeleter{});
        }

        ~Forge() noexcept override = default;
    };

} // namespace cppforge::core::forge

#endif // FORGE_HPP