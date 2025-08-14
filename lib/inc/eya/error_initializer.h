/**
* @file error_initializer.h
* @brief Macros for initializing error structures with standard fields
*
* This header provides macros for initializing the `eya_error_t` structure
* which contains error code and description fields. The macros simplify
* creation of error objects with either specific error information or
* default empty state.
*/

#ifndef EYA_ERROR_INITIALIZER_H
#define EYA_ERROR_INITIALIZER_H

#include "initializer.h"
#include "error_code.h"
#include "nullptr.h"

/**
* @def eya_error_initializer(code, desc)
* @brief Initializes an error structure with specified code and description
* @param code Error code (of type eya_error_code_t)
* @param desc Pointer to error description string (const char*)
* @return Initialized error structure with provided code and description
*
* @note This macro wraps eya_initializer to set up a structure with standard
*       error fields (code and description). The description can be nullptr
*       if no description is needed.
*
* Example usage:
* @code
* eya_error_t error = eya_error_initializer(EYA_ERROR_CODE_INVALID_ARG, "Invalid argument");
* // Results in: error.code = EYA_ERROR_CODE_INVALID_ARG, error.desc = "Invalid argument"
* @endcode
*
* @see eya_error_t
*/
#define eya_error_initializer(code, desc) eya_initializer(code, desc)

/**
* @def eya_error_empty_initializer()
* @brief Initializes an empty error structure (no error state)
* @return Initialized error structure with EYA_ERROR_CODE_NONE and nullptr description
*
* @note This macro creates an error object in its default "no error" state,
*       equivalent to what eya_error_clear() would produce.
*
* Example usage:
* @code
* eya_error_t error = eya_error_empty_initializer();
* // Results in: error.code = EYA_ERROR_CODE_NONE, error.desc = nullptr
* @endcode
*
* @see eya_error_clear
* @see eya_error_is_ok
*/
#define eya_error_empty_initializer() eya_error_initializer(EYA_ERROR_CODE_NONE, nullptr)

#endif // EYA_ERROR_INITIALIZER_H