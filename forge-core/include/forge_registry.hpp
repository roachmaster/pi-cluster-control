#ifndef FORGE_REGISTRY_HPP
#define FORGE_REGISTRY_HPP

#include <unordered_map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <typeinfo>
#include <iostream>
#include "iforge.hpp"
#include "forge.hpp"
#include "forge_log.hpp"

namespace cppforge::core::registry {
    // Bring in the forge namespace (including NoOpDeleter)
    using namespace cppforge::core::forge;

    class ForgeRegistry {
    public:
        // Returns the singleton instance.
        static ForgeRegistry &instance() {
            static ForgeRegistry instance;
            return instance;
        }

        // Registers a forge instance keyed by the fully qualified type name (from typeid(T).name()).
        template<typename T>
        void registerForge(const std::shared_ptr<Forge<T>> &forge) {
            std::string key = typeid(T).name();
            cppforge::logging::ForgeLog::info("Registering Forge for: " + std::string(typeid(T).name()));
            std::lock_guard<std::mutex> lock(mutex_);
            registry_[key] = forge;
        }

        // Retrieves a forge instance for the given type T, or returns nullptr if not registered.
        template<typename T>
        std::shared_ptr<Forge<T>> get() {
            std::string key = typeid(T).name();
            cppforge::logging::ForgeLog::debug("Fetching Forge for: " + key);
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = registry_.find(key);
            if (it != registry_.end()) {
                return std::static_pointer_cast<Forge<T>>(it->second);
            }
            return nullptr;
        }

        // Retrieves all forges whose created instance is assignable to the given base type T.
        template<typename T>
        std::vector<std::shared_ptr<Forge<T>>> getAllAssignableTo() {
            std::vector<std::shared_ptr<Forge<T>>> result;
            cppforge::logging::ForgeLog::debug("Finding all forges assignable to: " + std::string(typeid(T).name()));
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto &pair: registry_) {
                try {
                    // Updated: capture the returned pointer with its custom deleter.
                    std::unique_ptr<Forgeable, NoOpDeleter> instance = pair.second->create();
                    if (instance && dynamic_cast<T *>(instance.get()) != nullptr) {
                        result.push_back(std::static_pointer_cast<Forge<T>>(pair.second));
                    }
                } catch (const std::exception &e) {
                    cppforge::logging::ForgeLog::error("Forge creation failed during filtering: " + std::string(e.what()));
                }
            }
            return result;
        }

        // Clears all registered forges.
        void clear() {
            cppforge::logging::ForgeLog::warn("Clearing all registered forges...");
            std::lock_guard<std::mutex> lock(mutex_);
            registry_.clear();
        }

        // Lists all registered forge keys.
        std::vector<std::string> listKeys() {
            cppforge::logging::ForgeLog::debug("Listing all registered forge keys.");
            std::lock_guard<std::mutex> lock(mutex_);
            std::vector<std::string> keys;
            for (const auto &pair: registry_) {
                keys.push_back(pair.first);
            }
            return keys;
        }

    private:
        ForgeRegistry() = default;

        std::unordered_map<std::string, std::shared_ptr<IForge>> registry_;
        std::mutex mutex_;
    };
} // namespace cppforge::core::registry

#endif // FORGE_REGISTRY_HPP