#ifndef CPPFORGE_PTR_HPP
#define CPPFORGE_PTR_HPP

#include <memory>
#include "forgeable.hpp"
#include "forge.hpp"
#include "no_op_deleter.hpp"

namespace cppforge::core::forge {

    /**
     * @brief The standard smart pointer used for managing Forgeable instances.
     */
    using ForgeablePtr = std::unique_ptr<Forgeable, NoOpDeleter>;

    /**
     * @brief Type-erased pointer to any registered Forge factory.
     */
    using ForgeFactoryPtr = std::shared_ptr<IForge>;

    /**
     * @brief Strongly typed pointer to a Forge<T> instance.
     */
    template <typename T>
    using ForgePtr = std::shared_ptr<Forge<T>>;

} // namespace cppforge::core::forge

#endif // CPPFORGE_PTR_HPP