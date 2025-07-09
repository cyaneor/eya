/**
 * @file memory_view_fields.h
 * @brief Header providing a macro for defining memory view structures.
 *
 * This file defines a utility macro for creating structures that represent contiguous memory
 * regions. The macro generates standard begin/end pointer fields with consistent naming and
 * semantics.
 *
 * Key features:
 * - Type-safe pointer declarations
 * - Consistent naming convention
 * - Semantically clear documentation
 * - Interoperable with range-based algorithms
 *
 * Typical use cases include:
 * - Wrapping raw memory buffers
 * - Implementing custom containers
 * - Passing memory regions between functions
 * - Interfacing with C APIs that work with pointer ranges
 *
 * @warning The memory region represented must remain valid while in use.
 *          This is a lightweight wrapper and does not manage memory ownership.
 *
 * @see https://en.cppreference.com/w/cpp/iterator/begin
 * @see https://en.cppreference.com/w/cpp/iterator/end
 */

#ifndef EYA_MEMORY_VIEW_FIELDS_H
#define EYA_MEMORY_VIEW_FIELDS_H

/**
 * @def eya_memory_view_fields(T)
 * @brief Defines the standard fields for a memory view structure.
 *
 * This macro expands to declare two pointer fields that represent a contiguous memory region:
 * a beginning pointer and an end pointer (exclusive).
 *
 * @tparam T The type of elements in the memory view.
 *
 * The macro generates the following fields:
 * @code
 * {
 *     T *begin;
 *     T *end;
 * }
 * @endcode
 *
 * @note The memory region is considered to be [begin, end) - inclusive of begin,
 *       but exclusive of end.
 *
 * Example usage:
 * @code
 * struct IntArray {
 *     eya_memory_view_fields(int);
 * };
 * @endcode
 */
#define eya_memory_view_fields(T)                                                                  \
    T *begin; /**< Pointer to the start of the memory region. */                                   \
    T *end    /**< Pointer to the end of the memory region (exclusive). */

#endif // EYA_MEMORY_VIEW_FIELDS_H
