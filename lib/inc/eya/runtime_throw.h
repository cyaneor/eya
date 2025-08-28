/**
 * @file runtime_throw.h
 * @brief Simplified interface for runtime exception generation
 *
 * This header provides the `eya_runtime_throw` macro for convenient
 * exception throwing with support for arbitrary error parameters.
 *
 * Key features:
 * - Variadic syntax for error structure initialization
 * - Automatic debug information in DEBUG builds
 * - Integration with exception handling via `runtime_exception_catch_stack`
 *
 * @warning Requires at least one exception handler to be present,
 *          otherwise triggers program termination.
 *
 * @see eya_runtime_throw
 * @see runtime_error_code.h
 * @see runtime_exception_catch_stack.h
 */

#ifndef EYA_RUNTIME_THROW_H
#define EYA_RUNTIME_THROW_H

#include "exception_initializer.h"
#include "runtime_exception_catch_stack.h"

/**
 * @def eya_runtime_throw
 * @brief Macro for generating and throwing runtime exceptions
 *
 * Simplifies exception mechanism usage by allowing error parameters
 * to be specified as a `eya_error_t` structure initializer list.
 * Automatically adds debug information (timestamp, file, function) in DEBUG builds.
 *
 * @param ... Arguments for `eya_error_t` initialization (error code and description)
 *
 * @warning Causes program crash if no active exception handlers exist
 *
 * Example usage:
 * @code
 * // Simple exception with error code
 * eya_runtime_throw(EYA_ERROR_INVALID_ARGUMENT);
 *
 * // Exception with additional parameters
 * eya_runtime_throw(EYA_ERROR_FILE_IO, "Failed to open file");
 * @endcode
 *
 * @see eya_runtime_exception_catch_stack_throw
 */
#define eya_runtime_throw(...)                                                                     \
    do                                                                                             \
    {                                                                                              \
        const eya_exception_t e = eya_exception_initializer(__VA_ARGS__);                          \
        eya_runtime_exception_catch_stack_throw(&e);                                               \
    } while (0)

/**
 * @def eya_runtime_rethrow
 * @brief Macro for re-throwing current exception
 *
 * Delegates to `eya_runtime_exception_catch_stack_rethrow()`.
 * Used to re-throw currently handled exception.
 *
 * @note Preserves original exception context
 * @note Thread-safe through thread-local storage
 *
 * @see eya_runtime_exception_catch_stack_rethrow()
 * @see eya_runtime_exception_catch_stack_get_current()
 *
 * Usage example:
 * @code
 * try {
 *     // code that might throw
 * } catch {
 *     // exception handling
 *     eya_runtime_rethrow(); // re-throw same exception
 * }
 * @endcode
 */
#define eya_runtime_rethrow() eya_runtime_exception_catch_stack_rethrow()

#endif // EYA_RUNTIME_THROW_H