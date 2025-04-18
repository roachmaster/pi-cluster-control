#ifndef CPPFORGE_CORE_FORGE_FORGE_CACHE_HPP
#define CPPFORGE_CORE_FORGE_FORGE_CACHE_HPP

/**
 * @file forge_cache.hpp
 * @brief Base CRTP-style ForgeCache interface for stateful, key-value ForgeablePtr management.
 */

#include <string>
#include "forgeable.hpp"
#include "stateful_forgeable.hpp"
#include "cppforge_ptr.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Base class for ForgeCache-like behavior.
     *
     * Derived classes must implement:
     *   - void insert(const KeyType& key,ValueType value) noexcept;
     *   - ValueType* get(const KeyType& key) noexcept;
     *   - void remove(const KeyType& key) noexcept;
     *   - void clear() noexcept;
     *   - std::size_t size() const noexcept;
     */
    template<typename Derived>
    class ForgeCache
    {
    public:
        using KeyType = std::string;
        using ValueType = ForgeablePtr<typename Derived::StoredType>;

        void insert(
            const KeyType& key,
            ValueType value
        ) noexcept;
        ValueType* get(
            const KeyType& key
        ) noexcept;
        void remove(
            const KeyType& key
        ) noexcept;
        void clear(
        ) noexcept;
        std::size_t size(
        ) const noexcept;

    protected:
        ForgeCache() = default;
        ForgeCache(const ForgeCache&) = delete;
        ForgeCache& operator=(const ForgeCache&) = delete;

    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_CACHE_HPP