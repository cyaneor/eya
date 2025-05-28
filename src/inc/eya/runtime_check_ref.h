/**
 * @file runtime_check_ref.h
 * @brief Specialized runtime null pointer validation utilities
 *
 * Extends the runtime check system with a dedicated macro for null pointer validation.
 * Provides a concise interface for pointer validity checks with automatic error code handling.
 *
 * Key features:
 * - Dedicated null pointer validation macro
 * - Automatic appending of EYA_RUNTIME_ERROR_NULL_POINTER code
 * - Variadic argument support for flexible syntax
 * - Seamless integration with base runtime check system
 */

#ifndef EYA_RUNTIME_CHECK_REF_H
#define EYA_RUNTIME_CHECK_REF_H

#include "runtime_check.h"
#include "runtime_error_code.h"

/**
 * @def eya_runtime_check_ref
 * @brief Validates pointer validity and throws null pointer exception on failure
 *
 * Specialized macro for null pointer checks. Automatically appends
 * EYA_RUNTIME_ERROR_NULL_POINTER error code. Evaluates pointer in boolean
 * context (false = NULL).
 *
 * @param ... Pointer expression to check. Accepts variable arguments
 *            for compatibility with different check styles
 *
 * Example:
 * @code
 * // Throw if pointer is NULL
 * eya_runtime_check_ref(resource_ptr);
 * @endcode
 *
 * @note Wraps eya_runtime_check with predefined null pointer error
 */
#define eya_runtime_check_ref(...) eya_runtime_check(__VA_ARGS__, EYA_RUNTIME_ERROR_NULL_POINTER)

#endif // EYA_RUNTIME_CHECK_REF_H