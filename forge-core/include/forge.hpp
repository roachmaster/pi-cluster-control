#ifndef FORGE_HPP
#define FORGE_HPP

#include <memory>
#include <type_traits>
#include "iforge.hpp"

namespace cppforge {
    namespace core {
        namespace forge {

/**
 * @brief Generic factory interface for creating Forgeable components.
 *
 * The Forge<T> template class provides a contract for creating objects of type T,
 * where T must inherit from Forgeable. It inherits from IForge to provide a type-erased
 * interface for factory operations.
 *
 * @tparam T The type of Forgeable component to be created.
 */
            template <typename T>
            class Forge : public IForge {
            public:
                // Ensure at compile time that T is derived from Forgeable.
                static_assert(std::is_base_of<Forgeable, T>::value, "T must be derived from Forgeable");

                /**
                 * @brief Creates an instance of type T.
                 *
                 * Concrete implementations of Forge<T> must override this method to produce a fully
                 * initialized instance of T. This method is used internally by the type-erased create()
                 * method inherited from IForge.
                 *
                 * @return std::unique_ptr<T> A unique pointer owning the created instance.
                 */
                virtual std::unique_ptr<T> createImpl() = 0;

                /**
                 * @brief Type-erased factory method.
                 *
                 * This method calls the templated createImpl() and returns the result as a unique
                 * pointer to a Forgeable. This allows for storing and using different Forge<T> instances
                 * polymorphically.
                 *
                 * @return std::unique_ptr<Forgeable> A unique pointer to the created Forgeable instance.
                 */
                std::unique_ptr<Forgeable> create() override {
                    return createImpl();
                }

                /**
                 * @brief Virtual destructor.
                 *
                 * The destructor is declared virtual and defined inline to ensure proper cleanup of derived
                 * instances. It is marked noexcept for exception safety.
                 */
                virtual ~Forge() noexcept;
            };

// Inline definition for the destructor.
// This is required because the entire template definition must be visible to users.
            template <typename T>
            inline Forge<T>::~Forge() noexcept { }

    } // namespace forge
} // namespace core
} // namespace cppforge

#endif // FORGE_HPP