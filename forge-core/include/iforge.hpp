#ifndef IFORGE_HPP
#define IFORGE_HPP

#include <memory>
#include "forgeable.hpp"

namespace cppforge::core::forge {

    // A no‑op deleter that does nothing.
    struct NoOpDeleter {
        // Templated call operator to work with any pointer type.
        template<typename T>
        void operator()(T* /*ptr*/) const noexcept {
            // No deletion is performed.
        }
    };

    /**
     * @brief Interface for all Forge implementations.
     *
     * IForge provides a type-erased interface for creating Forgeable
     * objects. It allows factories (Forges) to be stored and retrieved
     * without knowledge of their template parameters.
     *
     * @note Concrete implementations of IForge (via the templated Forge<T> interface)
     * should override the create() method to produce a fully initialized instance of a Forgeable.
     */
    class IForge {
    public:
        /**
         * @brief Creates an instance of a Forgeable component.
         *
         * This method should be overridden by concrete Forge implementations to
         * construct and return an instance of a Forgeable object.
         *
         * @return std::unique_ptr<Forgeable, NoOpDeleter> A unique pointer (with a no‑op deleter)
         * to the created Forgeable instance.
         */
        virtual std::unique_ptr<Forgeable, NoOpDeleter> create() = 0;

        /**
         * @brief Virtual destructor.
         *
         * Ensures that destructors for derived classes are called appropriately.
         * Marked as noexcept for exception safety.
         */
        virtual ~IForge() noexcept = default;
    };

} // namespace cppforge::core::forge

#endif // IFORGE_HPP