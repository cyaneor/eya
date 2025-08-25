/**
 * @file array_initializer.h
 * @brief Macro for initializing array structures with standard fields
 *
 * This header provides a macro for initializing structures that include
 * standard array fields (data pointer and size), as defined by the
 * eya_array_fields macro. It is designed for structures like eya_array_t,
 * which manage dynamic arrays with a data pointer and size tracking.
 */

#ifndef EYA_ARRAY_INITIALIZER_H
#define EYA_ARRAY_INITIALIZER_H

#include "initializer.h"

/**
 * @def eya_array_initializer(initializer, ...)
 * @brief Initializes an array structure with a data pointer and zero size
 * @param initializer Pointer to the array data (typically of type T* where T is the element type)
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized array structure with data set to initializer and size set to 0
 *
 * @note This macro wraps eya_initializer to set up a structure with standard
 *       array fields (data and size, as defined by eya_array_fields). The size
 *       is initialized to 0, indicating an empty array, while the data pointer
 *       is set to the provided initializer.
 *
 * Example usage:
 * @code
 * struct eya_array_t {
 *     eya_array_fields(int); // Defines int* data and eya_usize_t size
 * };
 * int data[5] = {1, 2, 3, 4, 5};
 * eya_array_t array = eya_array_initializer(data);
 * // Results in: array.data = data, array.size = 0
 * @endcode
 *
 * @warning The initializer pointer must point to valid memory, and the
 *          containing structure is responsible for proper memory management.
 *
 * @see eya_array_fields
 */
#define eya_array_initializer(initializer, ...) eya_initializer(initializer, 0, __VA_ARGS__)

#endif // EYA_ARRAY_INITIALIZER_H