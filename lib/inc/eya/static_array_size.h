/**
 * @file static_array_size.h
 * @brief Header for static array element count calculation macro
 *
 * Defines the `eya_static_array_size` macro/function for determining
 * the number of elements in statically allocated arrays.
 *
 * Implementation differs between C and C++ environments:
 * - C++ uses template-based compile-time calculation
 * - C uses sizeof-based preprocessor macro
 */

#ifndef EYA_STATIC_ARRAY_SIZE_H
#define EYA_STATIC_ARRAY_SIZE_H

/**
 * @def eya_static_array_size
 * @brief Calculates static array element count
 *
 * Macro that computes array element count by dividing total array size
 * by individual element size. Only works with actual arrays, not pointers.
 *
 * @param x Array variable name
 * @return Number of elements as size_t
 *
 * @warning Do not use with pointers - will produce invalid results
 * @note Safe for stack-allocated arrays and global arrays
 */
#define eya_static_array_size(x) (sizeof(x) / sizeof(x[0]))

#endif // EYA_STATIC_ARRAY_SIZE_H