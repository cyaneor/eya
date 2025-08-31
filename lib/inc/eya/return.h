/**
 * @file return.h
 * @brief Header file defining `eya_return_t` type and its parameters
 *
 * This file provides the definition of `eya_return_t` type used to represent
 * function return codes, along with its size limits and range values.
 *
 * The `eya_return_t` type is an alias for the integer type `eya_sint_t`,
 * allowing use of standard macros for its minimum value, maximum value, and size.
 */

#ifndef EYA_RETURN_H
#define EYA_RETURN_H

#include "numeric_types.h"

/**
 * @def EYA_RETURN_SIZE
 * @brief Size of `eya_return_t` type in bytes
 *
 * Specifies the size (in bytes) of `eya_return_t` type using
 * the value defined by `EYA_INT_SIZE` macro.
 */
#define EYA_RETURN_SIZE EYA_INT_SIZE

/**
 * @def EYA_RETURN_MIN
 * @brief Minimum value for `eya_return_t` type
 *
 * Defines the minimum possible value for `eya_return_t` type,
 * corresponding to `EYA_SINT_MIN` value.
 */
#define EYA_RETURN_MIN EYA_SINT_MIN

/**
 * @def EYA_RETURN_MAX
 * @brief Maximum value for `eya_return_t` type
 *
 * Defines the maximum possible value for `eya_return_t` type,
 * corresponding to `EYA_SINT_MAX` value.
 */
#define EYA_RETURN_MAX EYA_SINT_MAX

/**
 * @typedef eya_return_t
 * @brief Function return code type
 *
 * The `eya_return_t` type is an alias for `eya_sint_t` integer type,
 * used to represent function return codes where positive values may
 * indicate success and negative values indicate errors.
 */
typedef eya_sint_t eya_return_t;

#endif // EYA_RETURN_H