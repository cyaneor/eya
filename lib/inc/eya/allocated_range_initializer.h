/**
 * @file allocated_range_initializer.h
 * @brief Macro for initializing allocated memory range structures
 *
 * This header provides a convenience macro for initializing eya_memory_range_t
 * structures as empty allocated ranges. It builds upon the memory range initializer
 * functionality to simplify creating empty allocated ranges.
 */

#ifndef EYA_ALLOCATED_RANGE_INITIALIZER_H
#define EYA_ALLOCATED_RANGE_INITIALIZER_H

#include "memory_range_initializer.h"

/**
 * @def eya_allocated_range_initializer(...)
 * @brief Initializes an empty allocated memory range
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized empty memory range structure
 *
 * @note This macro is a wrapper around eya_memory_range_empty_initializer,
 *       providing an empty memory range with null pointers for allocated ranges.
 *
 * Example usage:
 * @code
 * eya_memory_range_t allocated_range = eya_allocated_range_initializer();
 * @endcode
 */
#define eya_allocated_range_initializer(...) eya_memory_range_empty_initializer(__VA_ARGS__)

#endif // EYA_ALLOCATED_RANGE_INITIALIZER_H