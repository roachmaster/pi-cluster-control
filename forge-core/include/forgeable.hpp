#ifndef FORGEABLE_HPP
#define FORGEABLE_HPP

#include <string>

namespace cppforge::core::forge {

/**
 * @brief The Forgeable interface.
 *
 * This interface represents a component that can be "forged" or created via a factory.
 * Classes implementing this interface are required to provide a scenario name and implement
 * the "smelt" operation, which defines the component's behavior.
 *
 * @note Derived classes must override the pure virtual functions to provide their
 * specific behavior.
 */
    class Forgeable {
    public:
        /**
         * @brief Retrieves the scenario name.
         *
         * This method should return a descriptive name for the scenario or component.
         *
         * @return std::string The scenario name.
         */
        virtual std::string scenarioName() const = 0;

        /**
         * @brief Performs the "smelt" operation.
         *
         * This method should implement the core behavior of the component.
         * Essentially, it "smelts" the component, which is a metaphor for creating or processing
         * the component's functionality.
         */
        virtual void smelt() = 0;

        /**
         * @brief Virtual destructor.
         *
         * Ensures that derived class destructors are called properly. Marked noexcept for safety.
         */
        virtual ~Forgeable() noexcept = default;
    };

} // namespace cppforge

#endif // FORGEABLE_HPP