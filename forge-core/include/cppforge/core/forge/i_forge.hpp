#ifndef IFORGE_HPP
#define IFORGE_HPP

#include "forgeable.hpp"
#include "cppforge_ptr.hpp"

namespace cppforge::core::forge {

    class IForge {
    public:
        virtual ForgeablePtr create() = 0;
        virtual ~IForge() noexcept = default;
    };

} // namespace cppforge::core::forge

#endif // IFORGE_HPP