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
 * - Type value constants
 * - Type trait detection
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
 * @brief Calculates type size in bytes
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
 * @def eya_type_cast(T, expr)
 * @brief Performs type casting with language-appropriate implementation
 *
 * This macro provides a portable type casting mechanism that automatically
 * uses the appropriate casting method based on the compilation environment.
 *
 * In C++ mode, it uses `static_cast<T>(expr)` for type-safe casting with
 * compile-time checks. In C mode, it falls back to traditional C-style
 * casting `((T)(expr))`.
 *
 * @param T The target type to cast to
 * @param expr The expression or value to be cast
 * @return The expression cast to type T using appropriate casting semantics
 *
 * @note This macro leverages `eya_static_cast` internally, which provides
 *       the language-specific implementation details.
 *
 * Example usage:
 * @code
 * int x = 42;
 * double y = eya_type_cast(double, x); // Cast int to double
 * void* ptr = eya_type_cast(void*, &x); // Cast pointer to void*
 * @endcode
 *
 * @see eya_static_cast()
 */
#define eya_type_cast(T, expr) eya_static_cast(T, expr)

/**
 * @def eya_type_zero_v(T)
 * @brief Provides the zero value for the specified type
 *
 * This macro generates a zero value properly cast to the target type T.
 * It ensures type-safe zero initialization across different data types.
 *
 * @param T The target type for which to generate zero value
 * @return Zero value appropriately cast to type T
 *
 * Example usage:
 * @code
 * int zero_int = eya_type_zero_v(int);        // 0
 * float zero_float = eya_type_zero_v(float);  // 0.0f
 * void* null_ptr = eya_type_zero_v(void*);    // null pointer
 * @endcode
 */
#define eya_type_zero_v(T) eya_type_cast(T, 0)

/**
 * @def eya_type_one_v(T)
 * @brief Provides the unit value (1) for the specified type
 *
 * This macro generates a unit value (1) properly cast to the target type T.
 * Useful for initializations and arithmetic operations requiring type-specific unit values.
 *
 * @param T The target type for which to generate unit value
 * @return Unit value (1) appropriately cast to type T
 *
 * Example usage:
 * @code
 * int one_int = eya_type_one_v(int);          // 1
 * float one_float = eya_type_one_v(float);    // 1.0f
 * double one_double = eya_type_one_v(double); // 1.0
 * @endcode
 */
#define eya_type_one_v(T) eya_type_cast(T, 1)

/**
 * @def eya_type_neg_one_v(T)
 * @brief Provides the negative unit value (-1) for the specified type
 *
 * This macro generates a negative unit value (-1) properly cast to the target type T.
 * Particularly useful for signedness detection and boundary value testing.
 *
 * @param T The target type for which to generate negative unit value
 * @return Negative unit value (-1) appropriately cast to type T
 *
 * Example usage:
 * @code
 * int neg_one_int = eya_type_neg_one_v(int);          // -1
 * signed char neg_char = eya_type_neg_one_v(signed char); // -1
 * @endcode
 *
 * @note For unsigned types, this will result in the maximum value due to wrap-around
 * @see eya_type_is_signed()
 */
#define eya_type_neg_one_v(T) eya_type_cast(T, -1)

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
#define eya_type_is_signed(T) (eya_type_zero_v(T) > eya_type_neg_one_v(T))

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