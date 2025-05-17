/**
 * @file static_cast.h
 * @brief Header file for type casting macros.
 *
 * This file contains the definition of the `eya_static_cast` macro,
 * providing a unified type casting approach across C and C++ environments.
 *
 * @details The implementation varies by language:
 * - In C: Uses standard C-style cast with (T)V syntax
 * - In C++: Utilizes type-safe `static_cast` operator with compile-time checks
 *
 * This approach simplifies type conversion in cross-platform
 * and multi-language codebases while maintaining language-specific safety.
 *
 * @note The macro is particularly useful for projects requiring compatibility
 *       with both C and C++ compilers.
 */

#ifndef EYA_STATIC_CAST_H
#define EYA_STATIC_CAST_H

/**
 * @def eya_static_cast(T, V)
 * @brief Type-safe static casting macro
 * @details Performs type conversion of value @p V to type @p T using
 *          language-appropriate casting mechanism:
 *          - C++: Compile-time checked `static_cast`
 *          - C: Standard C-style cast
 *
 * @param T Target type for conversion
 * @param V Value to be converted
 *
 * Example usage:
 * @code
 * int a = 5;
 * double b = eya_static_cast(double, a);  // C++: static_cast<double>(a)
 *                                         // C: (double)a
 * @endcode
 */
#ifndef __cplusplus
#    define eya_static_cast(T, V) ((T)V) ///< C-style cast without type checks
#else
#    define eya_static_cast(T, V) static_cast<T>(V) ///< Type-safe C++ static_cast
#endif

#endif // EYA_STATIC_CAST_H