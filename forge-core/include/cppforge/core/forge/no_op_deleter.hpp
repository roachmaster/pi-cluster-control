#ifndef FORGE_NO_OP_DELETER_HPP
#define FORGE_NO_OP_DELETER_HPP

namespace cppforge::core::forge {

    /**
     * @brief A no‑op deleter that does nothing.
     *
     * Useful when you want a std::unique_ptr to manage a pointer without
     * actually deleting it. Typically used when the lifecycle is managed elsewhere.
     */
    struct NoOpDeleter {
        /**
         * @brief Templated call operator to work with any pointer type.
         * @tparam T The type of the object the pointer refers to.
         * @param ptr The pointer to the object (unused).
         */
        template<typename T>
        void operator()(T* /*ptr*/) const noexcept {
            // No deletion is performed.
        }
    };

} // namespace cppforge::core::forge

#endif // FORGE_NO_OP_DELETER_HPP