#ifndef FORGE_IDENTIFIERS_HPP
#define FORGE_IDENTIFIERS_HPP

/**
 * @file forge_identifiers.hpp
 * @brief Common type aliases and default string constants for Forge type and ID handling.
 *
 * This header defines string-based type aliases used throughout the Forge system for
 * identifying modules, components, and DSL commands. It also provides standard default
 * values for unknown or missing identifiers.
 *
 * @note These definitions reside in the canonical namespace cppforge::core::forge.
 *       Use the `forge::` alias in implementation files by including forge_namespace_alias.hpp.
 */

#include <string>
#include <vector>  // ✅ Needed for ForgeKeyList

namespace cppforge::core::forge {

    /**
     * @brief Alias for the string representing a Forge module or category.
     * Example: "goal", "dsl", "config"
     */
    using ForgeType = std::string;

    /**
     * @brief Alias for the string identifier of a specific Forge instance.
     * Example: "goal.validate", "contract.parse"
     */
    using ForgeId = std::string;

    /**
     * @brief Alias for a string-formatted DSL command hint.
     * Typically generated as `${ForgeType}.${ForgeId}`.
     */
    using DslHint = std::string;

    /**
     * @brief Alias for a human-readable execution label (e.g. for testing, tracing).
     */

    /**
     * @brief Alias for a list of registered forge keys in format "type.id".
     */
    using ForgeKeyList = std::vector<std::string>;

    /**
     * @brief Default value for unknown or uninitialized Forge types.
     */
    inline constexpr const char* UNKNOWN_TYPE = "unknown";

    /**
     * @brief Default value for unknown or uninitialized Forge IDs.
     */
    inline constexpr const char* UNKNOWN_ID = "unknown";

} // namespace cppforge::core::forge

#endif // FORGE_IDENTIFIERS_HPP