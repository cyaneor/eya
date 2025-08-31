/**
 * @file error_code.h
 * @brief Header file defining the `eya_error_code_t` type
 *        and related macros.
 *
 * This file provides the definition of the `eya_error_code_t` type
 * used to represent error codes returned by functions,
 * along with macros related to its size and value range.
 *
 * Serves as a foundation for unified error code handling,
 * allowing developers to use standardized values
 * to indicate errors and successful states.
 */

#ifndef EYA_ERROR_CODE_H
#define EYA_ERROR_CODE_H

#include "return.h"

/**
 * @def EYA_ERROR_CODE_SIZE
 * @brief Size of the `eya_error_code_t` type in bytes.
 *
 * The `EYA_ERROR_CODE_SIZE` macro defines the size (in bytes) of the `eya_error_code_t` type,
 * using the value set for `EYA_RETURN_SIZE`.
 */
#define EYA_ERROR_CODE_SIZE EYA_RETURN_SIZE

/**
 * @def EYA_ERROR_CODE_MIN
 * @brief Minimum value that `eya_error_code_t` can hold.
 *
 * The `EYA_ERROR_CODE_MIN` macro defines the minimum possible value
 * for the `eya_error_code_t` type, using `EYA_RETURN_MIN`.
 */
#define EYA_ERROR_CODE_MIN EYA_RETURN_MIN

/**
 * @def EYA_ERROR_CODE_MAX
 * @brief Maximum value that `eya_error_code_t` can hold.
 *
 * The `EYA_ERROR_CODE_MAX` macro defines the maximum possible value
 * for the `eya_error_code_t` type, using `EYA_RETURN_MAX`.
 */
#define EYA_ERROR_CODE_MAX EYA_RETURN_MAX

/**
 * @def EYA_ERROR_CODE_NONE
 * @brief Code indicating no error occurred.
 *
 * The `EYA_ERROR_CODE_NONE` macro represents the value 0,
 * indicating successful execution or absence of errors.
 *
 * Used in functions returning `eya_error_code_t`
 * to denote error-free execution.
 */
#define EYA_ERROR_CODE_NONE 0

/**
 * @typedef eya_error_code_t
 * @brief Defines the error code type for functions.
 *
 * The `eya_error_code_t` type is an alias for `eya_return_t` and is used
 * to represent error codes returned by functions. These codes enable
 * easy identification and handling of error conditions.
 *
 * Positive values of `eya_error_code_t` may indicate successful execution
 * or various success states, while negative values
 * are reserved for specific error conditions.
 */
typedef eya_return_t eya_error_code_t;

#endif // EYA_ERROR_CODE_H