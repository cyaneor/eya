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
 * by inverting the bits of the minimum signed value.
 *
 * @param T The numeric type (must be a signed integer type).
 * @return The maximum value of type T.
 */
#define eya_numeric_limit_smax(T) (~eya_numeric_limit_smin(T))

/**
 * @def eya_numeric_limit_umin
 * @brief Returns the minimum value for an unsigned numeric type `T`.
 *
 * This macro returns 0,
 * which is the minimum value for an unsigned type `T`.
 *
 * @param T The numeric type (must be an unsigned integer type).
 * @return The minimum value of type T (0).
 */
#define eya_numeric_limit_umin(T) (eya_type_cast(T, 0))

/**
 * @def eya_numeric_limit_umax
 * @brief Returns the maximum value for an unsigned numeric type `T`.
 *
 * This macro returns the maximum value
 * of an unsigned type `T` by casting `-1` to `T`,
 * which sets all bits to 1.
 *
 * @param T The numeric type (must be an unsigned integer type).
 * @return The maximum value of type T.
 */
#define eya_numeric_limit_umax(T) (eya_type_cast(T, -1))

/**
 * @def eya_numeric_limit_is_signed
 * @brief Determines if the numeric type `T` is signed.
 *
 * This macro checks if casting `0` and `-1` to `T`
 * results in `0` being greater than the cast result of `-1`.
 *
 * For signed types, `(T)-1` is -1, so `0 > (T)-1` returns `true`.
 * For unsigned types, `(T)-1` is the maximum value, so `0 > (T)-1` returns `false`.
 *
 * @param T The numeric type to check.
 * @return `true` if `T` is a signed type, `false` if `T` is an unsigned type.
 */
#define eya_numeric_limit_is_signed(T) (eya_type_cast(T, 0) > eya_type_cast(T, -1))

/**
 * @def eya_numeric_limit_min
 * @brief Returns the minimum value for the numeric type `T`.
 *
 * This macro returns the minimum value of `T`, which is `eya_numeric_limit_smin(T)`
 * if `T` is a signed type, or `eya_numeric_limit_umin()` if `T` is an unsigned type.
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
 * if T is a signed type, or eya_numeric_limit_umax(T) if T is an unsigned type.
 * The determination is made using `eya_numeric_limit_is_signed(T)`.
 *
 * @param T The numeric type.
 * @return The maximum value of type T.
 */
#define eya_numeric_limit_max(T)                                                                   \
    (eya_numeric_limit_is_signed(T) ? eya_numeric_limit_smax(T) : eya_numeric_limit_umax(T))

#endif // EYA_NUMERIC_LIMIT_H