#ifndef FORGE_REGISTRAR_HPP
#define FORGE_REGISTRAR_HPP

#include <memory>
#include "forge_registry.hpp"
#include "forge_bench.hpp"  // This header should define the ForgeBench class.

namespace cppforge {
    namespace core {
        namespace registry {

/**
 * @brief The ForgeRegistrar is responsible for initializing the
 * ForgeRegistry with forges from the provided ForgeBench.
 *
 * This class acts as a bridge between the scenario bench and the global
 * forge registry. Its initialize() method should register all available
 * forges from the ForgeBench instance.
 *
 * @note Ensure that the ForgeBench contains and properly creates all
 * desired Forgeable components before calling initialize().
 */
            class ForgeRegistrar {
            public:
                /**
                 * @brief Initializes the global forge registry.
                 *
                 * Registers forges from the given ForgeBench into the global registry.
                 *
                 * @param bench A shared pointer to the ForgeBench instance containing the available forges.
                 */
                static void initialize(const std::shared_ptr<cppforge::scenarios::ForgeBench>& bench);
            };

        } // namespace registry
    } // namespace core
} // namespace cppforge

#endif // FORGE_REGISTRAR_HPP