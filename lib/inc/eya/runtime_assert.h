/**
 * @file runtime_assert.h
 * @brief Runtime assertion verification macros
 *
 * Provides assertion checking macros that generate exceptions with diagnostic
 * information when validation conditions fail.
 *
 * Key features:
 * - Conditional checks with exception throwing
 * - Fixed error code `EYA_RUNTIME_ERROR_INTERRUPT`
 * - Support for both positive and negative validation
 * - Variadic interface for developer convenience
 */

#ifndef EYA_RUNTIME_ASSERT_H
#define EYA_RUNTIME_ASSERT_H

#include "runtime_throw_with_desc.h"

/**
 * @def eya_runtime_assert_if
 * @brief Evaluates condition and throws exception with description if `true`
 *
 * @param expr Boolean expression to evaluate
 * @param desc Error description (string literal)
 * @note Always uses `EYA_RUNTIME_ERROR_INTERRUPT` error code
 *
 * Example:
 * @code
 * // Throw if pointer is NULL
 * eya_runtime_assert_if(ptr == NULL, "Null pointer dereference attempt");
 * @endcode
 *
 * @see eya_runtime_throw_with_desc()
 */
#define eya_runtime_assert_if(expr, desc)                                                          \
    if (expr)                                                                                      \
    eya_runtime_throw_with_desc(desc)

/**
 * @def eya_runtime_assert_ifn
 * @brief Evaluates condition and throws exception with description if `false`
 *
 * @param expr Boolean expression to evaluate
 * @param desc Error description (string literal)
 * @note Always uses `EYA_RUNTIME_ERROR_INTERRUPT` error code
 *
 * Example:
 * @code
 * // Throw if memory allocation fails
 * eya_runtime_assert_ifn(memory != NULL, "Heap allocation failure");
 * @endcode
 *
 * @see eya_runtime_assert_if()
 */
#define eya_runtime_assert_ifn(expr, desc) eya_runtime_assert_if(!(expr), desc)

/**
 * @def eya_runtime_assert
 * @brief Primary assertion macro (alias for eya_runtime_assert_ifn)
 *
 * Evaluates condition and throws exception with description if `false`.
 * Supports variadic argument syntax identical to `eya_runtime_assert_ifn`.
 *
 * @param ... Condition and error description parameters
 * @note Always uses `EYA_RUNTIME_ERROR_INTERRUPT` error code
 *
 * Example:
 * @code
 * // Validate array bounds
 * eya_runtime_assert(index < array_size, "Index exceeds container capacity");
 * @endcode
 *
 * @see eya_runtime_assert_ifn()
 */
#define eya_runtime_assert(...) eya_runtime_assert_ifn(__VA_ARGS__)

#endif // EYA_RUNTIME_ASSERT_H