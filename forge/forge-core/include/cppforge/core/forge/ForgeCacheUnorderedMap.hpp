#ifndef CPPFORGE_CORE_FORGE_FORGE_CACHE_UNORDERED_MAP_HPP
#define CPPFORGE_CORE_FORGE_FORGE_CACHE_UNORDERED_MAP_HPP

/**
 * @file forge_cache_unordered_map.hpp
 * @brief Simple std::unordered_map-backed implementation of ForgeCache.
 */

#include <unordered_map>
#include "forge_cache.hpp"

namespace cppforge::core::forge {

    /**
     * @brief ForgeCacheUnorderedMap provides a simple hash map-based ForgeCache.
     *
     * Template param:
     *  - ForgeableType: The type of Forgeable stored in the cache.
     */
    template<typename ForgeableType>
    class ForgeCacheUnorderedMap : public ForgeCache<ForgeCacheUnorderedMap<ForgeableType>> {
    public:
        using KeyType = typename ForgeCache<ForgeCacheUnorderedMap<ForgeableType>>::KeyType;
        using ValueType = typename ForgeCache<ForgeCacheUnorderedMap<ForgeableType>>::ValueType;
        using MapType = std::unordered_map<KeyType, ValueType>;

        using StoredType = ForgeableType;

        void insert(const KeyType& key, ValueType value) noexcept {
            cache_.emplace(key, std::move(value));
        }

        ValueType* get(const KeyType& key) noexcept {
            auto it = cache_.find(key);
            if (it != cache_.end()) {
                return &(it->second);
            }
            return nullptr;
        }

        void remove(const KeyType& key) noexcept {
            cache_.erase(key);
        }

        void clear() noexcept {
            cache_.clear();
        }

        std::size_t size() const noexcept {
            return cache_.size();
        }

    private:
        MapType cache_;
    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_CACHE_UNORDERED_MAP_HPP