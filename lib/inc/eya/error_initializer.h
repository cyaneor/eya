/**
 * @file error_initializer.h
 * @brief Macros for initializing error structures with standard fields
 *
 * This header provides macros for initializing structures that include
 * standard error fields (error code and description), as defined by the
 * eya_error_t structure. It is designed for convenient error object initialization.
 */

#ifndef EYA_ERROR_INITIALIZER_H
#define EYA_ERROR_INITIALIZER_H

#include "initializer.h"
#include "error_code.h"

/**
 * @def eya_error_initializer(code, ...)
 * @brief Initializes an error structure with specified code and optional description
 * @param code Error code (of type eya_error_code_t)
 * @param ... Additional initialization arguments including optional description (const char*)
 * @return Initialized error structure with specified code and optional description
 *
 * @note This macro wraps eya_initializer to set up a structure with standard
 *       error fields (code and optional description, as defined by eya_error_t).
 *       The description should be passed as the first argument after code if needed.
 *
 * Example usage:
 * @code
 * eya_error_t error1 = eya_error_initializer(EYA_ERROR_CODE_INVALID_ARG, "Invalid argument");
 * // Results in: error.code = EYA_ERROR_CODE_INVALID_ARG, error.desc = "Invalid argument"
 *
 * eya_error_t error2 = eya_error_initializer(EYA_ERROR_CODE_INVALID_ARG);
 * // Results in: error.code = EYA_ERROR_CODE_INVALID_ARG, error.desc = <not modified>
 * @endcode
 *
 * @see eya_error_t
 */
#define eya_error_initializer(code, ...) eya_initializer(code, __VA_ARGS__)

/**
 * @def eya_error_empty_initializer(...)
 * @brief Initializes an error structure with no error state
 * @param ... Additional initialization arguments including optional description (const char*)
 * @return Initialized error structure with EYA_ERROR_CODE_NONE and optional description
 *
 * @note This macro creates an error structure in "no error" state by setting
 *       code to EYA_ERROR_CODE_NONE. If description is needed, it should be passed
 *       as the first argument.
 *
 * Example usage:
 * @code
 * eya_error_t error1 = eya_error_empty_initializer();
 * // Results in: error.code = EYA_ERROR_CODE_NONE, error.desc = <not modified>
 *
 * eya_error_t error2 = eya_error_empty_initializer(nullptr);
 * // Results in: error.code = EYA_ERROR_CODE_NONE, error.desc = nullptr
 * @endcode
 *
 * @see eya_error_t
 * @see EYA_ERROR_CODE_NONE
 */
#define eya_error_empty_initializer(...) eya_error_initializer(EYA_ERROR_CODE_NONE, __VA_ARGS__)

#endif // EYA_ERROR_INITIALIZER_H