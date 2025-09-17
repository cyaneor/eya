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

#include "static_cast.h"

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
 * @def eya_type_cast(T, v)
 * @brief Alias for eya_static_cast to perform a static cast operation.
 *
 * This macro is a shorthand for the @ref eya_static_cast macro,
 * allowing a static cast from the given @p value to the type @p T.
 * It supports both C and C++ compilation environments
 * by delegating to @ref eya_static_cast.
 *
 * @param T The target type to cast to.
 * @param v The value to cast.
 *
 * @return The value cast to type @p T.
 * @see eya_static_cast
 */
#define eya_type_cast(T, v) eya_static_cast(T, v)

/**
 * @def eya_type_is_signed(T)
 * @brief Determines if a given type is signed or unsigned
 *
 * This macro evaluates to a boolean expression that checks
 * whether the specified type `T` is signed (true) or unsigned (false).
 * It works by comparing the result of casting 0 and -1 to type `T`.
 *
 * @param T The type to check for signedness.
 *          Must be a fundamental arithmetic type.
 * @return int Boolean value: 1 if type is signed, 0 if unsigned.
 *
 * @note This macro relies on two's complement representation,
 *       which is standard on most modern systems.
 *       Behavior with non-arithmetic types is undefined.
 *
 * @warning Do not use with floating-point types as the behavior is undefined.
 *
 * Example usage:
 * @code
 * eya_type_is_signed(int)          // Evaluates to 1 (true)
 * eya_type_is_signed(unsigned int) // Evaluates to 0 (false)
 * eya_type_is_signed(char)         // Implementation-defined, depends if char is signed
 * @endcode
 *
 * @see eya_type_cast()
 */
#define eya_type_is_signed(T) (eya_type_cast(T, 0) > eya_type_cast(T, -1))

/**
 * @def eya_type_is_unsigned(T)
 * @brief Determines if a given type is unsigned.
 *
 * This macro is the logical inverse of `eya_type_is_signed(T)`.
 * It evaluates to a boolean expression that checks whether
 * the specified type `T` is unsigned (true) or signed (false).
 *
 * @param T The type to check. Must be a fundamental arithmetic type
 *          (e.g., int, unsigned char, uint32_t).
 *
 * @return int Boolean value:
 *             1 if the type is unsigned, 0 if it is signed.
 *
 * @note This is a convenience macro defined in terms of `eya_type_is_signed`.
 * @warning The same caveats that apply to `eya_type_is_signed` apply here.
 *          Do not use with floating-point types.
 *
 * Example usage:
 * @code
 * eya_type_is_unsigned(unsigned int) // Evaluates to 1 (true)
 * eya_type_is_unsigned(int)          // Evaluates to 0 (false)
 * @endcode
 *
 * @see eya_type_is_signed()
 */
#define eya_type_is_unsigned(T) (!eya_type_is_signed(T))

#endif // EYA_TYPE_UTIL_H