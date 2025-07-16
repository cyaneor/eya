/**
 * @file runtime_assert.h
 * @brief Runtime assertion verification macros
 *
 * Provides assertion checking macros that generate exceptions with diagnostic
 * information when validation conditions fail.
 *
 * Key features:
 * - Conditional checks with exception throwing
 * - Fixed error code `SE_RUNTIME_ERROR_INTERRUPT`
 * - Support for both positive and negative validation
 * - Variadic interface for developer convenience
 */

#ifndef SE_RUNTIME_ASSERT_H
#define SE_RUNTIME_ASSERT_H

#include "runtime_throw_with_desc.h"

/**
 * @def se_runtime_assert_if
 * @brief Evaluates condition and throws exception with description if `true`
 *
 * @param expr Boolean expression to evaluate
 * @param desc Error description (string literal)
 * @note Always uses `SE_RUNTIME_ERROR_INTERRUPT` error code
 *
 * Example:
 * @code
 * // Throw if pointer is NULL
 * se_runtime_assert_if(ptr == NULL, "Null pointer dereference attempt");
 * @endcode
 *
 * @see se_runtime_throw_with_desc()
 */
#define se_runtime_assert_if(expr, desc)                                                           \
    if (expr)                                                                                      \
    se_runtime_throw_with_desc(desc)

/**
 * @def se_runtime_assert_ifn
 * @brief Evaluates condition and throws exception with description if `false`
 *
 * @param expr Boolean expression to evaluate
 * @param desc Error description (string literal)
 * @note Always uses `SE_RUNTIME_ERROR_INTERRUPT` error code
 *
 * Example:
 * @code
 * // Throw if memory allocation fails
 * se_runtime_assert_ifn(memory != NULL, "Heap allocation failure");
 * @endcode
 *
 * @see se_runtime_assert_if()
 */
#define se_runtime_assert_ifn(expr, desc) se_runtime_assert_if(!(expr), desc)

/**
 * @def se_runtime_assert
 * @brief Primary assertion macro (alias for se_runtime_assert_ifn)
 *
 * Evaluates condition and throws exception with description if `false`.
 * Supports variadic argument syntax identical to `se_runtime_assert_ifn`.
 *
 * @param ... Condition and error description parameters
 * @note Always uses `SE_RUNTIME_ERROR_INTERRUPT` error code
 *
 * Example:
 * @code
 * // Validate array bounds
 * se_runtime_assert(index < array_size, "Index exceeds container capacity");
 * @endcode
 *
 * @see se_runtime_assert_ifn()
 */
#define se_runtime_assert(...) se_runtime_assert_ifn(__VA_ARGS__)

#endif // SE_RUNTIME_ASSERT_H