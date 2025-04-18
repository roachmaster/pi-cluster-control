#ifndef CPPFORGE_CORE_FORGE_FORGE_HPP
#define CPPFORGE_CORE_FORGE_FORGE_HPP

/**
 * @file forge.hpp
 * @brief Defines the CRTP-style Forge&lt;T, ForgeableType&gt; base for stateless factories.
 */

#include "cppforge_ptr.hpp"
#include "forgeable_traits.hpp"

namespace cppforge::core::forge {

    using ForgeId = std::string;

    /**
     * @brief CRTP base class for Forge-like behavior.
     *
     * Derived classes must implement:
     *   - ForgeablePtr createImpl();
     *   - ForgeId GetForgeIdImpl() const;
     */
    template<typename Derived, typename ForgeableType>
    class Forge {
    public:
        ForgeablePtr<ForgeableType> create() {
            return static_cast<Derived*>(this)->createImpl();
        }

        ForgeId GetForgeId() const {
            return static_cast<const Derived*>(this)->GetForgeIdImpl();
        }

    protected:
        Forge() = default;
        Forge(const Forge&) = delete;
        Forge& operator=(const Forge&) = delete;
    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_HPP