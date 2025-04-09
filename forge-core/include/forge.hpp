#ifndef FORGE_HPP
#define FORGE_HPP

#include <memory>
#include <type_traits>
#include "iforge.hpp"

namespace cppforge::core::forge {

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
        static_assert(std::is_base_of<Forgeable, T>::value, "T must be derived from Forgeable");

        /**
         * @brief Creates an instance of type T.
         *
         * Concrete implementations of Forge<T> must override this method to produce a fully
         * initialized instance of T. This method is used internally by the type-erased create()
         * method inherited from IForge.
         *
         * @return std::unique_ptr<T, NoOpDeleter> A unique pointer (with a no‑op deleter) owning the created instance.
         */
        virtual std::unique_ptr<T, NoOpDeleter> createImpl() = 0;

        /**
         * @brief Type-erased factory method.
         *
         * This method calls the templated createImpl() and returns the result as a unique
         * pointer to a Forgeable. This allows for storing and using different Forge<T> instances
         * polymorphically.
         *
         * @return std::unique_ptr<Forgeable, NoOpDeleter> A unique pointer (with a no‑op deleter) to the created Forgeable instance.
         */
        std::unique_ptr<Forgeable, NoOpDeleter> create() override {
            return createImpl();
        }

        /**
         * @brief Virtual destructor.
         *
         * Ensures proper cleanup of derived instances. Marked noexcept for exception safety.
         */
        ~Forge() noexcept override;
    };

    template <typename T>
    inline Forge<T>::~Forge() noexcept = default;

} // namespace cppforge::core::forge

#endif // FORGE_HPP