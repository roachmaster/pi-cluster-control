#ifndef FORGE_MANAGER_HPP
#define FORGE_MANAGER_HPP

/**
 * @file forge_manager.hpp
 * @brief Unified component for Forge registration and resolution.
 *
 * ForgeManager acts as the centralized interface for managing Forge<T> instances.
 * It implements both ForgeRegistry and ForgeResolver, enabling both registration
 * and resolution of forge components through a type-safe and thread-safe API.
 */

#include <unordered_map>
#include <memory>
#include <mutex>
#include <string>
#include <stdexcept>

#include "forge_registry.hpp"         // Provides registerForge<T>()
#include "forge_resolver.hpp"         // Provides resolveForge(), resolveAndCreate()
#include "forge_identifiers.hpp"      // ForgeType, ForgeId, ForgeKeyList
#include "cppforge_ptr.hpp"           // ForgePtr<T>, ForgeFactoryPtr
#include "i_forge.hpp"                // IForge

namespace cppforge::core::forge {

    class ForgeManager : public ForgeRegistry, public ForgeResolver {
    public:
        /**
         * @brief Resolves a Forgeable-producing factory by type and id.
         */
        IForge* resolveForge(const ForgeType& type, const ForgeId& id) const override {
            const std::string key = type + "." + id;
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = registry_.find(key);
            return (it != registry_.end()) ? it->second.get() : nullptr;
        }

        /**
         * @brief Resolves and returns a ForgeablePtr by type and id.
         */
        ForgeablePtr resolveAndCreate(const ForgeType& type, const ForgeId& id) const override {
            IForge* forge = resolveForge(type, id);
            if (!forge) {
                throw std::runtime_error("ForgeManager: No forge found for key: " + type + "." + id);
            }
            return forge->create();  // ✅ must return ForgeablePtr
        }

        /**
         * @brief Lists all registered forge keys in "type.id" format.
         */
        ForgeKeyList listForgeKeys() const override {
            std::lock_guard<std::mutex> lock(mutex_);
            ForgeKeyList keys;
            for (const auto& pair : registry_) {
                keys.push_back(pair.first);
            }
            return keys;
        }

        /**
         * @brief Clears all registered forges (used for tests or reset).
         */
        void clear() override {
            std::lock_guard<std::mutex> lock(mutex_);
            registry_.clear();
        }

    protected:
        /**
         * @brief Internal implementation of type-erased forge registration.
         *
         * Called by the template method `ForgeRegistry::registerForge<T>()`.
         */
        void registerForgeInternal(const std::string& key, ForgeFactoryPtr forgeFactory) override {
            std::lock_guard<std::mutex> lock(mutex_);
            if (registry_.find(key) != registry_.end()) {  // ✅ compatible with C++17
                throw std::runtime_error("ForgeManager: Duplicate forge key: " + key);
            }
            registry_[key] = std::move(forgeFactory);
        }

    private:
        std::unordered_map<std::string, ForgeFactoryPtr> registry_;
        mutable std::mutex mutex_;
    };

} // namespace cppforge::core::forge

#endif // FORGE_MANAGER_HPP