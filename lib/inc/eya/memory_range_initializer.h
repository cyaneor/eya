/**
 * @file memory_range_initializer.h
 * @brief Macros for initializing memory range structures
 *
 * This header provides convenience macros for initializing eya_memory_range_t structures.
 * The macros simplify the syntax for creating memory ranges with begin/end pointers
 * or empty ranges.
 */

#ifndef EYA_MEMORY_RANGE_INITIALIZER_H
#define EYA_MEMORY_RANGE_INITIALIZER_H

#include "initializer.h"
#include "nullptr.h"

/**
 * @def eya_memory_range_initializer(begin, end, ...)
 * @brief Initializes a memory range with specified begin and end pointers
 * @param begin Pointer to the start of the memory range
 * @param end Pointer to the end of the memory range (exclusive)
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized memory range structure
 *
 * @note This macro is a wrapper around eya_initializer that provides
 *       a more specific interface for memory ranges.
 * @warning The range should be valid (begin <= end) for proper operation
 *
 * Example usage:
 * @code
 * int array[10];
 * eya_memory_range_t range = eya_memory_range_initializer(array, array + 10);
 * @endcode
 */
#define eya_memory_range_initializer(begin, end, ...) eya_initializer(begin, end, __VA_ARGS__)

/**
 * @def eya_memory_range_empty_initializer(...)
 * @brief Initializes an empty memory range with null pointers
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized empty memory range structure
 *
 * @note This macro is a convenience wrapper around eya_memory_range_initializer
 *       that sets both begin and end pointers to nullptr, creating an empty range.
 *
 * Example usage:
 * @code
 * eya_memory_range_t empty_range = eya_memory_range_empty_initializer();
 * @endcode
 */
#define eya_memory_range_empty_initializer(...)                                                    \
    eya_memory_range_initializer(nullptr, nullptr, __VA_ARGS__)

#endif // EYA_MEMORY_RANGE_INITIALIZER_H