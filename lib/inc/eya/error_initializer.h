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
#include "nullptr.h"

/**
 * @def eya_error_initializer(code, desc, ...)
 * @brief Initializes an error structure with specified code and description
 * @param code Error code (of type eya_error_code_t)
 * @param desc Pointer to error description string (const char*)
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized error structure with specified code and description
 *
 * @note This macro wraps eya_initializer to set up a structure with standard
 *       error fields (code and description, as defined by eya_error_t).
 *
 * Example usage:
 * @code
 * eya_error_t error = eya_error_initializer(EYA_ERROR_CODE_INVALID_ARG, "Invalid argument");
 * // Results in: error.code = EYA_ERROR_CODE_INVALID_ARG, error.desc = "Invalid argument"
 * @endcode
 *
 * @see eya_error_t
 */
#define eya_error_initializer(code, desc, ...) eya_initializer(code, desc, __VA_ARGS__)

/**
 * @def eya_error_empty_initializer(...)
 * @brief Initializes an error structure with no error state
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized error structure with EYA_ERROR_CODE_NONE and nullptr description
 *
 * @note This macro creates an error structure in "no error" state by setting
 *       code to EYA_ERROR_CODE_NONE and description to nullptr.
 *
 * Example usage:
 * @code
 * eya_error_t error = eya_error_empty_initializer();
 * // Results in: error.code = EYA_ERROR_CODE_NONE, error.desc = nullptr
 * @endcode
 *
 * @see eya_error_t
 * @see EYA_ERROR_CODE_NONE
 */
#define eya_error_empty_initializer(...)                                                           \
    eya_error_initializer(EYA_ERROR_CODE_NONE, nullptr, __VA_ARGS__)

#endif // EYA_ERROR_INITIALIZER_H