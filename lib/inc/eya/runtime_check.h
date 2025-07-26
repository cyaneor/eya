/**
 * @file runtime_check.h
 * @brief Macros for runtime condition checks and exception throwing
 *
 * Header provides a set of macros for validating runtime conditions
 * with exception generation on failure.
 *
 * Key features:
 * - Conditional checks with exception throwing
 * - Support for both positive and negative assertions
 * - Variadic interface for flexible usage
 * - Integration with exception handling system
 */

#ifndef EYA_RUNTIME_CHECK_H
#define EYA_RUNTIME_CHECK_H

#include "runtime_throw_with_code.h"

/**
 * @def eya_runtime_check_if
 * @brief Checks condition and throws exception if true
 *
 * @param expr Condition to evaluate
 * @param code Error code to throw if condition is true
 *
 * Example:
 * @code
 * // Throw if pointer is NULL
 * eya_runtime_check_if(ptr == NULL, EYA_RUNTIME_ERROR_NULL_POINTER);
 * @endcode
 *
 * @see eya_runtime_throw_with_code
 */
#define eya_runtime_check_if(expr, code)                                                           \
    if (expr)                                                                                      \
    eya_runtime_throw_with_code(code)

/**
 * @def eya_runtime_check_ifn
 * @brief Checks condition and throws exception if false
 *
 * @param expr Condition to evaluate
 * @param code Error code to throw if condition is false
 *
 * Example:
 * @code
 * // Throw if memory allocation fails
 * eya_runtime_check_ifn(memory != NULL, EYA_RUNTIME_ERROR_ALLOC_FAILED);
 * @endcode
 *
 * @see eya_runtime_check_if
 */
#define eya_runtime_check_ifn(expr, code) eya_runtime_check_if(!(expr), code)

/**
 * @def eya_runtime_check
 * @brief Primary check macro (alias for eya_runtime_check_ifn)
 *
 * Checks condition and throws exception if false.
 * Supports variadic syntax for flexible usage.
 *
 * @param ... Condition and error code (same as eya_runtime_check_ifn)
 *
 * Example:
 * @code
 * // Validate array index range
 * eya_runtime_check(index < max_size, EYA_RUNTIME_ERROR_OUT_OF_RANGE);
 * @endcode
 *
 * @see eya_runtime_check_ifn
 */
#define eya_runtime_check(...) eya_runtime_check_ifn(__VA_ARGS__)

#endif // EYA_RUNTIME_CHECK_H