#ifndef FORGEABLE_HPP
#define FORGEABLE_HPP

/**
 * @file forgeable.hpp
 * @brief Base interface for all executable Forgeable components.
 *
 * A Forgeable is the core unit of execution in the Forge system.
 * These objects are created by Forges and then executed to perform
 * a defined behavior (e.g., validating a goal, applying a contract, etc.).
 */

#include <string>
#include "forge_identifiers.hpp"

namespace cppforge::core::forge {

    /**
     * @brief Interface for executable Forgeable units.
     *
     * All Forgeables must implement `execute()`, which performs the
     * component's action. `executionLabel()` may optionally be used
     * for tracing, debugging, or DSL introspection.
     */
    class Forgeable {
    public:
        /**
         * @brief Returns an execution label for diagnostics or DSL tracing.
         *
         * Commonly used for logs, test descriptions, or DSL mapping.
         *
         * @return ExecutionLabel A readable label representing this component.
         */
        virtual ExecutionLabel executionLabel() const = 0;

        /**
         * @brief Executes the Forgeable's core behavior.
         *
         * This is the main entry point for triggering the logic
         * encapsulated by this component.
         */
        virtual void execute() = 0;

        /**
         * @brief Virtual destructor for safe polymorphic deletion.
         */
        virtual ~Forgeable() noexcept = default;
    };

} // namespace cppforge::core::forge

#endif // FORGEABLE_HPP