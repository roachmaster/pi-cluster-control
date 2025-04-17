#ifndef CPPFORGE_CORE_FORGE_CPPFORGE_PTR_HPP
#define CPPFORGE_CORE_FORGE_CPPFORGE_PTR_HPP

#include <memory>
#include "forgeable.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Type-safe smart pointer for managing Forgeable instances.
     *
     * This alias wraps std::unique_ptr<T> and defaults to Forgeable.
     * You can specialize the alias with a different type if needed.
     */
    template<typename T = Forgeable>
    using ForgeablePtr = std::unique_ptr<T>;

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_CPPFORGE_PTR_HPP