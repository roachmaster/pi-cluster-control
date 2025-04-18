#ifndef CPPFORGE_CORE_FORGE_FORGE_HPP
#define CPPFORGE_CORE_FORGE_FORGE_HPP

/**
 * @file forge.hpp
 * @brief Defines the CRTP-style Forge&lt;T, ForgeableType&gt; base for stateless factories.
 */

#include "cppforge_ptr.hpp"
#include "forgeable_traits.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Base class for Forge-like behavior.
     *
     * Derived classes must implement:
     *   - ForgeablePtr&lt;ForgeableType&gt; create(
       ) noexcept;
     *   - ForgeId getForgeId(
       ) const noexcept;
     */
    template<typename Derived, typename ForgeableType>
    class Forge
    {
    public:
        using ForgeId = std::string;


        ForgeablePtr<ForgeableType> create(
        ) noexcept;
        ForgeId getForgeId(
        ) const noexcept;

    protected:
        Forge() = default;
        Forge(const Forge&) = delete;
        Forge& operator=(const Forge&) = delete;

    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_FORGE_HPP