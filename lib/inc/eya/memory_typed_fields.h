/**
 * @file memory_typed_fields.h
 * @brief Header defining macros for typed memory range structures with element size tracking
 *
 * This header provides the `eya_memory_typed_fields` macro which generates
 * fields for a typed memory range structure including both the range pointers
 * and element size information. The resulting structure maintains type safety
 * while providing essential memory management information.
 *
 * Key Features:
 * - Creates a typed memory range (begin/end pointers of specified type)
 * - Includes explicit element size tracking
 * - Maintains type consistency between range pointers and element type
 * - Enables bounds-checked memory operations
 */

#ifndef EYA_MEMORY_TYPED_FIELDS_H
#define EYA_MEMORY_TYPED_FIELDS_H

#include "size.h"

/**
 * @def eya_memory_typed_fields(T)
 * @brief Generates typed memory range fields with element size information
 *
 * This macro expands to two fields representing a typed memory range structure:
 * - A range field containing begin/end pointers of specified type
 * - An element size field indicating the size of individual elements
 *
 * @tparam T Type of elements in the memory range (must match range pointer types)
 *
 * Example usage:
 * @code{.c}
 * struct buffer {
 *     eya_memory_typed_fields(char);  // Creates char range{begin,end} and size_t element_size
 *     uint32_t flags;
 * };
 * @endcode
 *
 * @note The structure maintains these invariants:
 *       - range.begin <= range.end
 *       - element_size > 0
 *       - (range.end - range.begin) must be divisible by element_size
 *       - Type T must match the pointer types of the range
 *
 * @see eya_memory_range_fields() for untyped version
 */
#define eya_memory_typed_fields(T)                                                                 \
    T           range; /**< Memory range structure (type: @c T) containing begin/end pointers */   \
    eya_usize_t element_size /**< Size in bytes of each element (type: @c eya_usize_t) */

#endif // EYA_MEMORY_TYPED_FIELDS_H
