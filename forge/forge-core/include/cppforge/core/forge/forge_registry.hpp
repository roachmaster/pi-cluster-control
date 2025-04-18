#ifndef CPPFORGE_CORE_FORGE_FORGE_REGISTRY_HPP
#define CPPFORGE_CORE_FORGE_FORGE_REGISTRY_HPP

/**
 * @file forge_registry.hpp
 * @brief Registers Forge instances by ForgeId.
 */

#include "forge.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Base class for ForgeRegistry-like behavior.
     *
     * Derived classes must implement:
     *   - void registerForge(
         const ForgeId& id,
         ForgeType* forge
       ) noexcept;
     */
    template<typename ForgeType>
    class ForgeRegistry
    {
    public:
        using ForgeId = std::string;

        void registerForge(
            const ForgeId& id,
            ForgeType* forge
        ) noexcept;

    protected:
        ForgeRegistry() = default;
        ForgeRegistry(const ForgeRegistry&) = delete;
        ForgeRegistry& operator=(const ForgeRegistry&) = delete;

    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_REGISTRY_HPP