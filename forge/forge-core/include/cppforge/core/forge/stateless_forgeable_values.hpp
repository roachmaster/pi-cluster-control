#ifndef CPPFORGE_CORE_FORGE_STATELESS_FORGEABLE_HPP
#define CPPFORGE_CORE_FORGE_STATELESS_FORGEABLE_HPP

/**
 * @file stateless_forgeable.hpp
 * @brief CRTP-style marker interface to classify a Forgeable as stateless.
 */


namespace cppforge::core::forge {


    /**
     * @brief CRTP base class for StatelessForgeable-like behavior.
     *
     */
    template<typename Derived>
    class StatelessForgeable {
    public:

    protected:
        StatelessForgeable() = default;
        StatelessForgeable(const StatelessForgeable&) = delete;
        StatelessForgeable& operator=(const StatelessForgeable&) = delete;
    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_STATELESS_FORGEABLE_HPP