/**
 * @file runtime_terminate.h
 * @brief Library emergency termination management.
 *
 * This module provides:
 * - Global termination handler `m_runtime_terminate`
 * - Function `eya_runtime_terminate()` to invoke current handler
 * - Function `eya_runtime_terminate_set_handler()` to override handler
 *
 * Behavior depends on CMake option `EYA_LIBRARY_OPTION_TERMINATE_INIT_STDLIB`:
 * - When `ON`: Default handler is `abort()`
 * - When `OFF`: Handler initializes to `nullptr` (requires explicit setup)
 *
 * @warning Calling `eya_runtime_terminate()`
 *          with unset handler (`nullptr`) results in UB
 */

#ifndef EYA_RUNTIME_TERMINATE_H
#define EYA_RUNTIME_TERMINATE_H

#include "runtime_terminate_fn.h"
#include "attribute.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Sets custom emergency termination handler.
 *
 * @details Allows overriding default program termination handler.
 *          Analogous to `std::set_terminate()` in C++.
 *
 * @param[in] fn Handler function pointer.
 *               Valid values:
 *               - `nullptr`: Reset handler (causes UB if `terminate` called)
 *               - Valid function pointer: Set new handler
 *
 * @return Previous handler pointer (may be `nullptr`)
 *
 * @note Termination behavior depends on configured handler:
 *       - `nullptr` → Undefined Behavior (UB)
 *       - Else → Invokes assigned function
 *
 * @see eya_runtime_terminate()
 *
 * Usage example:
 * @code
 * eya_runtime_terminate_fn* old_handler = eya_runtime_terminate_set(my_handler);
 * // ...
 * eya_runtime_terminate_set(old_handler); // Restore previous
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
eya_runtime_terminate_fn *
eya_runtime_terminate_set(eya_runtime_terminate_fn *fn);

/**
 * @brief Invokes current emergency termination handler.
 *
 * @details Immediately terminates program execution
 *          through currently configured handler.
 *          Behavior mirrors `std::terminate()` in C++.
 *
 * @note Behavior depends on installed handler:
 *       - No handler set (or reset to nullptr)
 *         → Undefined Behavior (UB)
 *       - Else → Invokes registered handler function
 *
 * @warning This function never returns!
 *          Handler MUST guarantee program termination.
 *
 * @see eya_runtime_terminate_set()
 *
 * Usage example:
 * @code
 * if (critical_error) {
 *     eya_runtime_terminate(); // Invokes current handler (abort() by default)
 * }
 * @endcode
 *
 * Handler override example:
 * @code
 * EYA_ATTRIBUTE(NORETURN)
 * void custom_terminate() {
 *     log_error("Fatal termination!");
 *     _Exit(127);
 * }
 *
 * int main() {
 *     eya_runtime_terminate_set(custom_terminate);
 *     // ...
 *     eya_runtime_terminate(); // Now calls custom_terminate()
 * }
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
EYA_ATTRIBUTE(NORETURN)
void
eya_runtime_terminate(void);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_RUNTIME_TERMINATE_H