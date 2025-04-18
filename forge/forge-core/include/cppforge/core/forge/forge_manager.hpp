#ifndef CPPFORGE_CORE_FORGE_FORGE_MANAGER_HPP
#define CPPFORGE_CORE_FORGE_FORGE_MANAGER_HPP

/**
 * @file forge_manager.hpp
 * @brief Manages Forge registration and resolution.
 */

#include "forge.hpp"
#include "forge_resolver.hpp"
#include "forge_registry.hpp"
#include "forge_cache.hpp"

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
        using CacheType = ForgeCache<ForgeType>;

        explicit ForgeManager(CacheType* cache)
            : cache_(cache)
        {
        }

        ForgeType* resolve(
            const ForgeId& id
        ) const noexcept;
        void registerForge(
            const ForgeId& id,
            ForgeType* forge
        ) noexcept;

    protected:
        ForgeManager(const ForgeManager&) = delete;
        ForgeManager& operator=(const ForgeManager&) = delete;

    private:
        CacheType* cache_;
    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_MANAGER_HPP