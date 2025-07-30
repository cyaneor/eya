/**
 * @file array_fields.h
 * @brief Defines the `eya_array_fields` macro
 *        for creating standard array fields in a structure.
 *
 * This header file provides the `eya_array_fields` macro,
 * which simplifies the creation of array-like structures
 * by automatically defining the `data` pointer and `size` fields.
 */

#ifndef EYA_ARRAY_FIELDS_H
#define EYA_ARRAY_FIELDS_H

#include "size.h"

/**
 * @def eya_array_fields(T)
 * @brief Macro to define standard array fields in a structure.
 * @param T Type of the array elements.
 *
 * Expands to declare two fields:
 * - `data`: Pointer to array elements of type T.
 * - `size`: Current number of elements in array (`eya_usize_t`).
 *
 * @note This macro is typically used when creating custom array types
 *       that need to maintain both the data pointer and size.
 *
 * Example usage:
 * @code{.c}
 * struct custom_array {
 *     eya_array_fields(int);  // Creates int* data and eya_usize_t size
 *     int extra_field;
 * };
 * @endcode
 *
 * @warning The containing structure must ensure proper memory management
 *          for the data pointer according to standard allocation rules.
 */
#define eya_array_fields(T)                                                                        \
    T           data;                                                                              \
    eya_usize_t size

#endif // EYA_ARRAY_FIELDS_H
