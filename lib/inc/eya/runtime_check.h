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
 * @brief Checks condition and throws exception if false (inverse check)
 *
 * This macro is an alias for eya_runtime_check_ifn and provides a more intuitive name
 * for the common case of checking positive conditions. It evaluates the expression
 * and throws an exception with the specified error code if the expression evaluates to false.
 *
 * @param expr Condition expression to evaluate (exception thrown if false)
 * @param code Error code to throw when condition fails
 *
 * Example usage:
 * @code
 * // Throw if file opening fails
 * eya_runtime_check(file.is_open(), EYA_RUNTIME_ERROR_FILE_OPEN);
 *
 * // Throw if index is out of bounds
 * eya_runtime_check(index < array_size, EYA_RUNTIME_ERROR_INDEX_OUT_OF_RANGE);
 * @endcode
 *
 * @note This is equivalent to eya_runtime_check_ifn(expr, code)
 * @see eya_runtime_check_ifn The underlying implementation
 * @see eya_runtime_check_if The inverse operation (throws if true)
 */
#define eya_runtime_check(expr, code) eya_runtime_check_ifn(expr, code)

#endif // EYA_RUNTIME_CHECK_H