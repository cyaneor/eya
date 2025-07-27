/**
 * @file runtime_throw_with_code.h
 * @brief Simplified interface for throwing exceptions by error code
 *
 * Header provides specialized @ref eya_runtime_throw_with_code macro
 * for cases requiring exception throwing with only an error code,
 * without additional parameters.
 *
 * Key characteristics:
 * - Thin wrapper over @ref eya_runtime_throw
 * - Optimizes common exception throwing patterns
 * - Retains all base exception mechanism features
 * - Automatically adds error context in DEBUG builds
 */

#ifndef EYA_RUNTIME_THROW_WITH_CODE_H
#define EYA_RUNTIME_THROW_WITH_CODE_H

#include "runtime_throw.h"

/**
 * @def eya_runtime_throw_with_code
 * @brief Simplified macro for throwing exceptions with error code
 *
 * Provides shorthand syntax for calling `eya_runtime_throw` with minimal
 * parameters when only error code needs to be specified.
 *
 * @param code Error code of type eya_error_code_t (e.g., `EYA_ERROR_INVALID_ARGUMENT`)
 * @note Essentially an alias for `eya_runtime_throw(code)`
 *
 * Example:
 * @code
 * // Throw exception for invalid argument
 * if (arg == nullptr) {
 *     eya_runtime_throw_with_code(EYA_ERROR_NULL_ARGUMENT);
 * }
 * @endcode
 *
 * @see eya_runtime_throw
 * @see eya_runtime_exception_catch_stack_throw_error
 */
#define eya_runtime_throw_with_code(code) eya_runtime_throw(code)

#endif // EYA_RUNTIME_THROW_WITH_CODE_H