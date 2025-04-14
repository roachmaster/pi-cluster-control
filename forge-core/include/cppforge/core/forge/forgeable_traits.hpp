#ifndef FORGEABLE_TRAITS_HPP
#define FORGEABLE_TRAITS_HPP

#include <memory>
#include <type_traits>
#include "forgeable.hpp"
#include "no_op_deleter.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Trait to check if a type is a Forgeable.
     */
    template <typename T>
    constexpr bool is_forgeable = std::is_base_of_v<Forgeable, T>;

    /**
     * @brief Alias for a forgeable pointer of specific type T with a no-op deleter.
     *
     * Used by strongly typed Forge<T> implementations to manage concrete Forgeable lifecycles.
     */
    template <typename T>
    using ForgeableImplPtr = std::unique_ptr<T, NoOpDeleter>;

} // namespace cppforge::core::forge

#endif // FORGEABLE_TRAITS_HPP