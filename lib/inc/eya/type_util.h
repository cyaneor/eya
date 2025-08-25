/**
 * @file type_util.h
 * @brief Type utility macros for cross-platform development
 *
 * This header provides a set of utility macros for working with data types in
 * a cross-platform and cross-language (C/C++) compatible way.
 *
 * The macros offer:
 * - Type size calculations
 * - Bit size determination
 * - Type casting with language-appropriate implementations
 *
 * The implementation automatically adapts to C or C++ compilation environments
 * to provide the most appropriate behavior for each language while maintaining
 * source compatibility.
 */

#ifndef EYA_TYPE_UTIL_H
#define EYA_TYPE_UTIL_H

#include "compiler.h"

/**
 * @def eya_type_size(T)
 * @brief Calculates type size in bytes (C implementation)
 * @param T Data type to determine size of
 * @return Size of type T in bytes via sizeof operator
 *
 * Example of use:
 * @code
 * size_t s = eya_type_size(double); // sizeof(double)
 * @endcode
 */
#define eya_type_size(T) sizeof(T)

/**
 * @def eya_type_bits(T)
 * @brief Calculates bit size of type T
 *
 * @param T Data type to determine bit size of
 * @return Number of bits in type T (sizeof(T) * 8)
 *
 * Usage example:
 * @code
 * int bits = eya_type_bits(int); // Returns 32 for 32-bit int
 * @endcode
 */
#define eya_type_bits(T) (eya_type_size(T) * 8)

/**
 * @def eya_type_cast(T, V)
 * @brief Casts value V to type T
 *
 * @details Depending on the programming language, it uses:
 *          - In C: Standard C-style cast
 *          - In C++: Type-safe static_cast
 *
 * @param T Target type to cast to
 * @param V Value to be cast
 *
 * @return Result of casting V to type T
 *
 * @note In C++, using this macro is preferred over direct static_cast usage
 *       to maintain code compatibility with C if needed.
 * @warning In C, this macro doesn't provide compile-time type checking,
 *          unlike the C++ version.
 *
 * Example:
 * @code
 * int x = 10;
 * double y = eya_type_cast(double, x); // Cast int to double
 * @endcode
 */
#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
#    define eya_type_cast(T, V) static_cast<T>(V) ///< Type-safe C++ static_cast
#else
#    define eya_type_cast(T, V) ((T)V) ///< C-style cast without type checks
#endif

#endif // EYA_TYPE_UTIL_H