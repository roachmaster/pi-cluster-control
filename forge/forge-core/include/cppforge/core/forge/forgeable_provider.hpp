#ifndef FORGEABLE_PROVIDER_HPP
#define FORGEABLE_PROVIDER_HPP

/**
 * @file forgeable_provider.hpp
 * @brief Interface for lifecycle-aware Forgeable creation.
 *
 * The ForgeableProvider resolves forges by type and id, and creates
 * Forgeable instances while handling lifecycle policy (transient, thread-local, etc.).
 */

#include "cppforge_ptr.hpp"
#include "forge_identifiers.hpp"

namespace cppforge::core::forge {

    class ForgeableProvider {
    public:
        /**
         * @brief Creates a Forgeable instance by resolving its type and id.
         *
         * This method encapsulates both forge resolution and lifecycle management.
         *
         * @param type The forge module (e.g., "goal", "dsl").
         * @param id The forge ID (e.g., "validate", "parse").
         * @return A managed pointer to the created Forgeable.
         */
        virtual ForgeablePtr provide(const ForgeType& type, const ForgeId& id) = 0;

        /**
         * @brief Virtual destructor.
         */
        virtual ~ForgeableProvider() noexcept = default;
    };

} // namespace forge

#endif // FORGEABLE_PROVIDER_HPP