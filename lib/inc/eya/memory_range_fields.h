/**
 * @file memory_range_fields.h
 * @brief Header defining macros for typed memory range structures
 *
 * This header provides the `eya_memory_range_fields` macro which generates
 * STL-style typed memory range fields (begin/end pointers) for structures.
 * The resulting fields enable type-safe memory range operations while
 * maintaining standard iterator conventions.
 *
 * Key Features:
 * - Generates typed begin/end pointers matching the specified type
 * - Follows STL/iterator conventions for memory ranges
 * - Provides type safety for memory operations
 * - Enables range-based algorithms and bounds checking
 *
 * @see eya_memory_typed_fields() for version with additional element size tracking
 * @see eya_allocated_array_fields() for complete array management structure
 *
 * @note The memory range follows these conventions:
 *       - begin points to the first valid element (or equals end for empty ranges)
 *       - end points to one past the last valid element
 *       - The range is valid when begin <= end
 *       - The range represents [begin, end) half-open interval
 *
 * Example usage:
 * @code{.c}
 * struct vector {
 *     eya_memory_range_fields(float);
 *     size_t capacity;
 * };
 * @endcode
 *
 * @invariant Structure must maintain these constraints:
 *            - begin <= end (for non-empty ranges)
 *            - Pointers must be of matching type
 *            - Memory must be properly allocated if range is non-empty
 *            - end must point to valid memory (one past last element)
 *
 * @warning The structure does not track allocation size - for complete memory
 *          management consider using `eya_memory_typed_fields` or
 *          `eya_allocated_array_fields` instead.
 */

#ifndef EYA_MEMORY_RANGE_FIELDS_H
#define EYA_MEMORY_RANGE_FIELDS_H

/**
 * @def eya_memory_range_fields(T)
 * @brief Generates typed memory range fields for a structure.
 *
 * This macro expands to two fields representing a typed memory range:
 * - A pointer to the start of the memory block
 * - A pointer to the end (one past last element) of the memory block
 *
 * @tparam T Type of elements in the memory range (automatically deduced)
 *
 * Example usage:
 * @code{.c}
 * struct vector {
 *     eya_memory_range_fields(float);  // Creates float* begin and float* end
 *     size_t capacity;
 * };
 * @endcode
 *
 * @note The memory range follows STL-style conventions where:
 *       - begin points to the first element
 *       - end points to one past the last element
 *       - The range is valid only when begin <= end
 */
#define eya_memory_range_fields(T)                                                                 \
    T *begin; /**< Pointer to the start of the memory block */                                     \
    T *end    /**< Pointer to the first byte after the memory block */

#endif // EYA_MEMORY_RANGE_FIELDS_H
