#ifndef CPPFORGE_CORE_FORGE_STATEFUL_FORGEABLE_HPP
#define CPPFORGE_CORE_FORGE_STATEFUL_FORGEABLE_HPP

/**
 * @file stateful_forgeable.hpp
 * @brief CRTP-style marker interface to classify a Forgeable as stateful.
 */


namespace cppforge::core::forge {

    /**
     * @brief Base class for StatefulForgeable-like behavior.
     *
     */
    template<typename Derived>
    class StatefulForgeable
    {
    public:



    protected:
        StatefulForgeable() = default;
        StatefulForgeable(const StatefulForgeable&) = delete;
        StatefulForgeable& operator=(const StatefulForgeable&) = delete;

    };

} // namespace cppforge::core::forge

#endif // CPPFORGE_CORE_FORGE_STATEFUL_FORGEABLE_HPP