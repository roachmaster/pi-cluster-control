#ifndef FORGE_REGISTRY_HPP
#define FORGE_REGISTRY_HPP

/**
 * @file forge_registry.hpp
 * @brief Interface for registering and retrieving Forge<T> instances.
 *
 * This abstract interface defines how Forge factories can be stored and retrieved
 * across the Forge system. It allows systems like ForgeManager and ForgeRegistrar
 * to interact with any registry implementation, such as a singleton or scoped context.
 */

#include <memory>
#include <string>

#include "forge_identifiers.hpp"       // ForgeType, ForgeId, ForgeKeyList
#include "forgeable_traits.hpp"        // is_forgeable<T>
#include "cppforge_ptr.hpp"            // ForgePtr<T>, ForgeFactoryPtr
#include "i_forge.hpp"                 // IForge
#include "forge.hpp"                   // Forge<T>

namespace cppforge::core::forge {

    /**
     * @brief Interface for managing registration and lookup of Forge<T> factories.
     */
    class ForgeRegistry {
    public:
        /**
         * @brief Registers a Forge<T> instance under the given type and id.
         *
         * @tparam T The specific Forgeable type this forge produces.
         * @param type The forge module/category (e.g., "goal").
         * @param id The forge identifier (e.g., "validate").
         * @param forgeInstance A shared pointer to the Forge<T> factory.
         */
        template<typename T>
        void registerForge(const ForgeType& type, const ForgeId& id, ForgePtr<T> forgeInstance) {
            static_assert(is_forgeable<T>, "T must be derived from Forgeable");
            registerForgeInternal(type + "." + id, std::move(forgeInstance));
        }

        /**
         * @brief Lists all registered forge keys in "type.id" format.
         * @return A list of all registered forge identifiers.
         */
        virtual ForgeKeyList listForgeKeys() const = 0;

        /**
         * @brief Retrieves a registered forge factory by key.
         *
         * @param key The fully-qualified forge key (e.g., "goal.validate").
         * @return Pointer to the registered forge or nullptr if not found.
         */
        virtual IForge* getForgeByKey(const std::string& key) const = 0;

        /**
         * @brief Clears the entire forge registry.
         */
        virtual void clear() = 0;

        /**
         * @brief Virtual destructor for safe polymorphic deletion.
         */
        virtual ~ForgeRegistry() noexcept = default;

    protected:
        /**
         * @brief Internal method for registering type-erased forge factories.
         *
         * Called by the public templated `registerForge()` method.
         *
         * @param key The fully-qualified forge key (e.g., "goal.validate").
         * @param forgeFactory A shared pointer to the forge factory.
         */
        virtual void registerForgeInternal(const std::string& key, ForgeFactoryPtr forgeFactory) = 0;
    };

} // namespace cppforge::core::forge

#endif // FORGE_REGISTRY_HPP