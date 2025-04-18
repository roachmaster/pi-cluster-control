#ifndef CPPFORGE_CORE_FORGE_CPPFORGE_PTR_HPP
#define CPPFORGE_CORE_FORGE_CPPFORGE_PTR_HPP

#include <memory>
#include "forgeable_traits.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Type-safe smart pointer for managing Forgeable-derived instances.
     *
     * This alias wraps std::unique_ptr<T> and enforces that T is a valid Forgeable type.
     */
    template<typename T>
    struct ForgeablePtr_helper {
        static_assert(is_forgeable<T>, "ForgeablePtr must wrap a Forgeable-derived type.");
        using type = std::unique_ptr<T>;
    };

    template<typename T>
    using ForgeablePtr = typename ForgeablePtr_helper<T>::type;

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_CPPFORGE_PTR_HPP