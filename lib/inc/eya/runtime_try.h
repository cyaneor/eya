/**
 * @file eya_runtime_try.h
 * @brief Exception handling macros for EYA runtime (try-catch implementation)
 *
 * Provides a set of macros that implement try-catch exception handling mechanism
 * in C using setjmp/longjmp-like functionality through exception frames.
 *
 * The implementation consists of:
 * - `eya_runtime_try`: Creates a protected block and exception frame
 * - `eya_runtime_catch`: Marks the beginning of exception handling code
 */

#ifndef EYA_RUNTIME_TRY_H
#define EYA_RUNTIME_TRY_H

#include "runtime_exception_catch_stack.h"

/**
 * @def eya_runtime_try
 * @brief Macro for organizing an exception handling block (try-block)
 *
 * Creates a code block with exception handling that performs:
 * 1. Creation of an exception frame with automatic storage
 * 2. Setting an entry point for exception handling
 * 3. Checking the execution context (initial entry or jump on exception)
 *
 * @param e Name of the exception frame variable (automatically created)
 *
 * @note Used as a foundation for implementing try/catch blocks
 * @warning Requires a corresponding exception handling block
 * @warning Only supports local exception frames (automatic storage)
 *
 * Usage example:
 * @code
 * eya_runtime_try(frame) {
 *     // Code that might throw an exception
 * }
 * @endcode
 *
 * @see eya_runtime_catch()
 * @see eya_runtime_exception_catch_stack_capture()
 * @see eya_exception_catch_t
 */
#define eya_runtime_try(e)                                                                         \
    eya_exception_catch_t e = {};                                                                  \
    if (eya_runtime_exception_catch_stack_capture(&e) == 0)

/**
 * @def eya_runtime_catch
 * @brief Macro for organizing an exception handling catch-block
 *
 * Forms the second part of the exception handling construct (catch-block)
 * that follows a try-block created with eya_runtime_try().
 *
 * This macro simply expands to the 'else' keyword, creating a syntactic
 * construct that resembles traditional try-catch blocks while leveraging
 * C's native conditional flow control.
 *
 * @note Must be used in conjunction with eya_runtime_try()
 * @note The actual exception handling logic is implemented through
 *       the exception frame created by eya_runtime_try()
 *
 * Usage example:
 * @code
 * eya_runtime_try(frame) {
 *     // Try block code
 * } eya_runtime_catch {
 *     // Catch block code
 * }
 * @endcode
 *
 * @see eya_runtime_try()
 * @see eya_exception_catch_t
 * @see eya_runtime_exception_catch_stack_capture()
 */
#define eya_runtime_catch else

#endif // EYA_RUNTIME_TRY_H