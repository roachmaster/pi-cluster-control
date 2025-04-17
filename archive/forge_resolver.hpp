#ifndef FORGE_RESOLVER_HPP
#define FORGE_RESOLVER_HPP

/**
 * @file forge_resolver.hpp
 * @brief Interface for resolving Forgeables by type and ID at runtime.
 *
 * This interface provides a read-only abstraction for looking up Forge<T>
 * factories or executing them to create Forgeable instances. It's typically
 * used by consumers like ForgeableProvider or ForgeManager.
 */

#include <string>
#include "forge_identifiers.hpp"
#include "../forge/forge-core/include/cppforge/core/forge/cppforge_ptr.hpp"
#include "i_forge.hpp"

namespace cppforge::core::forge {

    class ForgeResolver {
    public:
        /**
         * @brief Resolves the forge factory associated with the given type and ID.
         *
         * @param type The forge module/category (e.g., "goal").
         * @param id The forge identifier (e.g., "validate").
         * @return A pointer to the IForge, or nullptr if not found.
         */
        virtual IForge* resolveForge(const ForgeType& type, const ForgeId& id) const = 0;

        /**
         * @brief Resolves and creates a Forgeable instance using the given type and ID.
         *
         * @param type The forge module/category (e.g., "goal").
         * @param id The forge identifier (e.g., "validate").
         * @return A managed ForgeablePtr, or throws if the forge is missing.
         *
         * @throws std::runtime_error if no matching forge is found.
         */
        virtual ForgeablePtr resolveAndCreate(const ForgeType& type, const ForgeId& id) const = 0;

        /**
         * @brief Virtual destructor for safe interface deletion.
         */
        virtual ~ForgeResolver() noexcept = default;
    };

} // namespace cppforge::core::forge

#endif // FORGE_RESOLVER_HPP