/**
 * @file memory_typed_initializer.h
 * @brief Macros for typed memory range initialization
 *
 * This header provides macros for initializing memory ranges with type information,
 * allowing for size-aware operations on typed memory blocks.
 */

#ifndef EYA_MEMORY_TYPED_INITIALIZER_H
#define EYA_MEMORY_TYPED_INITIALIZER_H

#include "memory_range_initializer.h"

/**
 * @def eya_memory_typed_initializer(begin, end, element_size, ...)
 * @brief Initializes a typed memory range with element size information and optional arguments
 * @param begin Pointer to the first element of the range
 * @param end Pointer to one past the last element of the range
 * @param element_size Size of each element in bytes
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized typed memory range structure
 *
 * @note This macro extends eya_memory_range_initializer with element size information
 *       and supports variable arguments for additional initialization options.
 * @warning The element_size must match the actual size of elements in memory
 *
 * Example usage:
 * @code
 * int array[10];
 * // Initialize with element size (for int typically 4 bytes) and optional arguments
 * auto range = eya_memory_typed_initializer(array, array + 10, sizeof(int));
 * @endcode
 */
#define eya_memory_typed_initializer(begin, end, element_size, ...)                                \
    eya_memory_range_initializer(begin, end, element_size, __VA_ARGS__)

/**
 * @def eya_memory_typed_empty_initializer(element_size, ...)
 * @brief Creates an empty typed memory range with element size information and optional arguments
 * @param element_size Size of each element in bytes
 * @param ... Additional initialization arguments (if needed)
 * @return Empty typed memory range structure
 *
 * @note The returned range will be in uninitialized state but retains element size info
 * @see eya_memory_range_is_uninit()
 *
 * Example usage:
 * @code
 * // Create empty range for 8-byte elements with optional arguments
 * auto empty = eya_memory_typed_empty_initializer(8);
 * @endcode
 */
#define eya_memory_typed_empty_initializer(element_size, ...)                                      \
    eya_memory_typed_initializer(nullptr, nullptr, element_size, __VA_ARGS__)

#endif // EYA_MEMORY_TYPED_INITIALIZER_H