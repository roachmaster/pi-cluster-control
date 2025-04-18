#ifndef CPPFORGE_CORE_FORGE_FORGE_RESOLVER_HPP
#define CPPFORGE_CORE_FORGE_FORGE_RESOLVER_HPP

/**
 * @file forge_resolver.hpp
 * @brief Resolves Forge instances by ForgeId to produce Forgeables.
 */

#include "forge.hpp"

namespace cppforge::core::forge {

    /**
     * @brief base class for ForgeResolver-like behavior.
     *
     * Derived classes must implement:
     *   - ForgeType* resolve(
         const ForgeId& id
       ) const noexcept;
     */
    template<typename ForgeType>
    class ForgeResolver {
    public:
        using ForgeId = std::string;

        ForgeType* resolve(
            const ForgeId& id
        ) const noexcept;

    protected:
        ForgeResolver() = default;
        ForgeResolver(const ForgeResolver&) = delete;
        ForgeResolver& operator=(const ForgeResolver&) = delete;

    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_RESOLVER_HPP