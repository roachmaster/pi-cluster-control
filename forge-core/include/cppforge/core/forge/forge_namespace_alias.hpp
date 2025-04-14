#ifndef CPPFORGE_CORE_FORGE_NAMESPACE_ALIAS_HPP
#define CPPFORGE_CORE_FORGE_NAMESPACE_ALIAS_HPP

/**
 * @file forge_namespace_alias.hpp
 * @brief Provides namespace aliasing for the cppforge::core::forge module.
 *
 * This header defines a short-form alias `forge` for the full namespace
 * `cppforge::core::forge`. It is intended for use in implementation files (.cpp)
 * and internal utilities to improve readability and reduce verbosity.
 *
 * @note This header should NOT be included or used inside public headers.
 *       Always define types and classes in their canonical namespace
 *       (i.e., cppforge::core::forge) to maintain proper namespace scoping.
 */

// Base alias for the forge module namespace
namespace forge = cppforge::core::forge;

#endif // CPPFORGE_CORE_FORGE_NAMESPACE_ALIAS_HPP