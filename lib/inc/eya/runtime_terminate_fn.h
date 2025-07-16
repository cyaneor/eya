/**
 * @file runtime_terminate_fn.h
 * @brief Header file defining the emergency termination function type.
 *
 * This file declares the `eya_runtime_terminate_fn` type — a function
 * invoked during critical errors within the library.
 *
 * @see eya_runtime_terminate()
 * @see eya_runtime_terminate_set()
 */

#ifndef EYA_RUNTIME_TERMINATE_FN_H
#define EYA_RUNTIME_TERMINATE_FN_H

/**
 * @typedef eya_runtime_terminate_fn
 * @brief Function type for handling fatal program termination.
 *
 * Functions of this type MUST:
 * 1. **Never return** (marked with the `NORETURN` attribute).
 * 2. **Terminate the program** (e.g., via `abort()`, `_Exit()`, or equivalents).
 *
 * @note - Used with `eya_runtime_terminate_set()`
 *         to override default critical error handling behavior.
 *       - May be initialized to `abort()` by default
 *         (see CMake option `EYA_LIBRARY_OPTION_TERMINATE_INIT_STDLIB`).
 *
 * Usage example:
 * @code
 * void custom_terminate() {
 *     log_error("Critical failure!");
 *     _Exit(EXIT_FAILURE);
 * }
 *
 * eya_runtime_terminate_set(custom_terminate); // Set custom handler
 * @endcode
 *
 * @see eya_runtime_terminate()
 * @see eya_runtime_terminate_set()
 */
typedef void(eya_runtime_terminate_fn)(void);

#endif // EYA_RUNTIME_TERMINATE_FN_H