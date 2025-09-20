/**
 * @file numeric_limit.h
 * @brief Provides macros for determining the minimum and maximum values of numeric types.
 *
 * This header defines a set of macros for computing the minimum and maximum values
 * of both signed and unsigned integer types, as well as checking whether a type
 * is signed or unsigned. These macros rely on utilities defined in "bit_util.h"
 * for type casting and sign bit manipulation.
 *
 * The macros are designed to be portable and work with fundamental integer types.
 * They provide a consistent interface for querying numeric limits in a type-safe
 * manner. Floating-point types and non-arithmetic types are not supported.
 *
 * @note All macros assume that the input type `T` is a fundamental integer type.
 *       Behavior is undefined for non-integer or non-arithmetic types.
 * @warning Users must include "bit_util.h" before using these macros, as they
 *          depend on `eya_type_cast`, `eya_bit_sign_type`, `eya_type_is_signed`,
 *          `eya_type_is_unsigned`, `eya_bit_not`, `eya_type_zero_v`, and
 *          `eya_type_neg_one_v` utilities.
 */

#ifndef EYA_NUMERIC_LIMIT_H
#define EYA_NUMERIC_LIMIT_H

#include "bit_util.h"

/**
 * @def eya_numeric_limit_smin
 * @brief Returns the minimum value for a signed numeric type `T`.
 *
 * This macro computes the minimum value of a signed type `T`
 * by casting the sign bit of `T` to `T`.
 *
 * @param T The numeric type (must be a signed integer type).
 * @return The minimum value of type T.
 */
#define eya_numeric_limit_smin(T) (eya_type_cast(T, eya_bit_sign_type(T)))

/**
 * @def eya_numeric_limit_smax
 * @brief Returns the maximum value for a signed numeric type `T`.
 *
 * This macro computes the maximum value of a signed type `T`
 * by applying bitwise NOT to the type (inverts all bits).
 *
 * @param T The numeric type (must be a signed integer type).
 * @return The maximum value of type T.
 */
#define eya_numeric_limit_smax(T) eya_bit_not(T)

/**
 * @def eya_numeric_limit_umin
 * @brief Returns the minimum value for an unsigned numeric type `T`.
 *
 * This macro returns the zero value for type `T`,
 * which is the minimum value for an unsigned type.
 *
 * @param T The numeric type (must be an unsigned integer type).
 * @return The minimum value of type T (0).
 */
#define eya_numeric_limit_umin(T) eya_type_zero_v(T)

/**
 * @def eya_numeric_limit_umax
 * @brief Returns the maximum value for an unsigned numeric type `T`.
 *
 * This macro returns the maximum value of an unsigned type `T`
 * by getting the value with all bits set to 1.
 *
 * @param T The numeric type (must be an unsigned integer type).
 * @return The maximum value of type T.
 */
#define eya_numeric_limit_umax(T) eya_type_neg_one_v(T)

/**
 * @def eya_numeric_limit_is_signed
 * @brief Determines if the numeric type `T` is signed.
 *
 * This macro checks whether the type `T` is signed using
 * the underlying utility from "bit_util.h".
 *
 * @param T The numeric type to check.
 * @return `true` if `T` is a signed type, `false` if `T` is an unsigned type.
 */
#define eya_numeric_limit_is_signed(T) eya_type_is_signed(T)

/**
 * @def eya_numeric_limit_is_unsigned
 * @brief Determines if the numeric type `T` is unsigned.
 *
 * This macro checks whether the type `T` is unsigned using
 * the underlying utility from "bit_util.h".
 *
 * @param T The numeric type to check.
 *          Must be a fundamental arithmetic type.
 * @return `true` if `T` is an unsigned type, `false` if `T` is a signed type.
 *
 * @note This is an alias for `eya_type_is_unsigned(T)`
 *       and inherits all of its behavior and limitations.
 * @warning Not suitable for floating-point types or non-arithmetic types.
 */
#define eya_numeric_limit_is_unsigned(T) eya_type_is_unsigned(T)

/**
 * @def eya_numeric_limit_min
 * @brief Returns the minimum value for the numeric type `T`.
 *
 * This macro returns the minimum value of `T`, which is `eya_numeric_limit_smin(T)`
 * if `T` is a signed type, or `eya_numeric_limit_umin(T)` if `T` is an unsigned type.
 * The determination is made using `eya_numeric_limit_is_signed(T)`.
 *
 * @param T The numeric type.
 * @return The minimum value of type T.
 */
#define eya_numeric_limit_min(T)                                                                   \
    (eya_numeric_limit_is_signed(T) ? eya_numeric_limit_smin(T) : eya_numeric_limit_umin(T))

/**
 * @def eya_numeric_limit_max
 * @brief Returns the maximum value for the numeric type T.
 *
 * This macro returns the maximum value of T, which is `eya_numeric_limit_smax(T)`
 * if T is a signed type, or `eya_numeric_limit_umax(T)` if T is an unsigned type.
 * The determination is made using `eya_numeric_limit_is_signed(T)`.
 *
 * @param T The numeric type.
 * @return The maximum value of type T.
 */
#define eya_numeric_limit_max(T)                                                                   \
    (eya_numeric_limit_is_signed(T) ? eya_numeric_limit_smax(T) : eya_numeric_limit_umax(T))

#endif // EYA_NUMERIC_LIMIT_H