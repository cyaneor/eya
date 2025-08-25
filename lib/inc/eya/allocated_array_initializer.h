/**
 * @file allocated_array_initializer.h
 * @brief Macro for initializing allocated array memory ranges
 *
 * This header provides a convenience macro for initializing empty typed memory
 * ranges specifically for allocated arrays, incorporating element size information
 * and supporting variable arguments for additional initialization options.
 */

#ifndef EYA_ALLOCATED_ARRAY_INITIALIZER_H
#define EYA_ALLOCATED_ARRAY_INITIALIZER_H

#include "memory_typed_initializer.h"

/**
 * @def eya_allocated_array_initializer(element_size, ...)
 * @brief Initializes an empty typed memory range for an allocated array
 * @param element_size Size of each element in bytes
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized empty typed memory range structure
 *
 * @note This macro is a wrapper around eya_memory_typed_empty_initializer,
 *       providing an empty typed memory range with null pointers and specified
 *       element size for allocated arrays.
 *
 * Example usage:
 * @code
 * // Create an empty allocated array range for 4-byte elements
 * auto array_range = eya_allocated_array_initializer(4);
 * @endcode
 */
#define eya_allocated_array_initializer(element_size, ...)                                         \
    eya_memory_typed_empty_initializer(element_size, __VA_ARGS__)

#endif // EYA_ALLOCATED_ARRAY_INITIALIZER_H