#ifndef CPPFORGE_CORE_FORGE_FORGEABLE_TRAITS_HPP
#define CPPFORGE_CORE_FORGE_FORGEABLE_TRAITS_HPP

/**
 * @file forgeable_traits.hpp
 * @brief Type trait helper for validating inheritance from Forgeable.
 */

#include <type_traits>
#include <forgeable.hpp>

namespace cppforge::core::forge {

    /**
     * @brief Evaluates to true if type T inherits from Forgeable.
     */
    template <typename T>
    constexpr bool is_forgeable = std::is_base_of_v<Forgeable, T>;

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGEABLE_TRAITS_HPP