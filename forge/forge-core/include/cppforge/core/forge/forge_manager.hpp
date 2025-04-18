#ifndef CPPFORGE_CORE_FORGE_FORGE_MANAGER_HPP
#define CPPFORGE_CORE_FORGE_FORGE_MANAGER_HPP

/**
 * @file forge_manager.hpp
 * @brief Manages Forge registration and resolution.
 */

#include <unordered_map>
#include "forge.hpp"
#include "forge_resolver.hpp"
#include "forge_registry.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Base class for ForgeManager-like behavior.
     *
     * Derived classes must implement:
     *   - ForgeType* resolve(
         const ForgeId& id
       ) const noexcept;
     *   - void registerForge(
         const ForgeId& id,
         ForgeType* forge
       ) noexcept;
     */
    template<typename ForgeType>
    class ForgeManager
    : public cppforge::core::forge::ForgeResolver<ForgeType>,
     public cppforge::core::forge::ForgeRegistry<ForgeType>    {
    public:
        using ForgeId = std::string;

        ForgeType* resolve(
            const ForgeId& id
        ) const noexcept;
        void registerForge(
            const ForgeId& id,
            ForgeType* forge
        ) noexcept;

    protected:
        ForgeManager() = default;
        ForgeManager(const ForgeManager&) = delete;
        ForgeManager& operator=(const ForgeManager&) = delete;

    private:
        std::unordered_map<ForgeId, ForgeType*> registry_;
    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_MANAGER_HPP