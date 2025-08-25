/**
 * @file runtime_exception_catch_stack.h
 * @brief Runtime exception handling mechanism implementation.
 *
 * This module provides:
 * - Bounded-depth exception frame stack
 * - Exception context management functions
 * - Non-local jump mechanism for error propagation
 * - Debug information support in DEBUG builds
 *
 * @note Maximum stack depth is defined by `EYA_RUNTIME_EXCEPTION_CATCH_STACK_MAX`
 * @warning Requires careful use to maintain stack integrity
 */

#ifndef EYA_RUNTIME_EXCEPTION_CATCH_STACK_H
#define EYA_RUNTIME_EXCEPTION_CATCH_STACK_H

#include "exception_catch.h"
#include "runtime_terminate.h"

/**
 * @def eya_runtime_exception_catch_stack_capture
 * @brief Macro for capturing execution context and setting exception handlers
 *
 * Combines stack push and setjmp into atomic operation:
 * 1. Pushes exception frame to handler stack
 * 2. Captures execution context via setjmp
 * 3. Returns entry point for exception handling
 *
 * @param x Exception frame pointer (`eya_exception_catch_t*`)
 * @return 0 - during initial context saving
 * @return >0 - when returning from `eya_runtime_exception_catch_stack_throw()`
 *
 * @note Used as foundation for try/catch block implementation
 * @warning MUST only be used in if/switch conditions
 *
 * Usage example:
 * @code
 * if (eya_runtime_exception_catch_stack_capture(frame)) {
 *   // Exception handling code
 * }
 * @endcode
 *
 * @see eya_runtime_exception_catch_stack_push()
 * @see eya_runtime_exception_catch_stack_throw()
 */
#define eya_runtime_exception_catch_stack_capture(x)                                               \
    setjmp(eya_runtime_exception_catch_stack_push(x)->env)

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Retrieves current active exception frame from handler stack
 *
 * Returns pointer to thread's current active exception frame.
 * The frame represents exception handling context in current code location.
 *
 * @return eya_exception_catch_t* Current exception frame pointer
 */
eya_exception_catch_t *
eya_runtime_exception_catch_stack_get_current(void);

/**
 * @brief Checks if exception handling mechanism is in initial state
 *
 * Verifies whether current exception pointer (`m_runtime_exception`)
 * points to start of exception frame array (`m_runtime_exceptions`).
 * Indicates empty stack with no active handlers.
 *
 * @return true - if exception pointer is at initial position (no active handlers)
 * @return false - if at least one active handler exists
 */
bool
eya_runtime_exception_catch_stack_is_begin(void);

/**
 * @brief Checks if maximum exception handling nesting level is reached
 *
 * Determines if current exception pointer (`m_runtime_exception`)
 * has reached end of frame array. Indicates stack is full to maximum capacity
 * (`EYA_RUNTIME_EXCEPTION_CATCH_STACK_MAX`).
 *
 * @return true - if maximum nesting level reached
 * @return false - if more handlers can be added
 */
bool
eya_runtime_exception_catch_stack_is_end(void);

/**
 * @brief Advances stack pointer to next frame and returns it
 *
 * Operations performed:
 * 1. Checks advancement possibility (stack end not reached)
 * 2. Increments current exception pointer if possible
 * 3. Returns new current frame
 *
 * @return Pointer to next exception frame if successful
 * @return nullptr if stack limit reached
 *
 * @note Used for registering new exception handlers
 * @warning Verify stack availability with `eya_runtime_exception_catch_stack_is_end()`
 *          before calling
 */
eya_exception_catch_t *
eya_runtime_exception_catch_stack_next(void);

/**
 * @brief Moves stack pointer to previous frame and returns it
 *
 * Operations performed:
 * 1. Checks if pointer is not at initial position
 * 2. Decrements current exception pointer if possible
 * 3. Returns new current frame
 *
 * @return Pointer to previous frame if successful
 * @return nullptr if pointer at initial position
 *
 * @note Used when exiting exception handling context
 * @warning Verify pointer position with `eya_runtime_exception_catch_stack_is_begin()`
 *          before calling
 */
eya_exception_catch_t *
eya_runtime_exception_catch_stack_prev(void);

/**
 * @brief Pushes exception frame onto handler stack
 *
 * Operations performed:
 * 1. Checks stack space availability
 * 2. Stores provided frame in current position
 * 3. Advances stack pointer
 *
 * @param e Exception frame pointer to push
 * @return Pointer to pushed frame on success
 * @return nullptr if stack full (reached `EYA_RUNTIME_EXCEPTION_CATCH_STACK_MAX`)
 *
 * @note Used when entering try block to register handler
 * @warning Ensure each push is balanced with corresponding pop
 */
eya_exception_catch_t *
eya_runtime_exception_catch_stack_push(eya_exception_catch_t *e);

/**
 * @brief Throws exception and transfers control to nearest handler
 *
 * Performs non-local jump to last registered handler:
 * 1. Retrieves previous frame from stack
 * 2. Copies exception data to frame
 * 3. Executes longjmp to handler
 * 4. Terminates program if no handlers available
 *
 * @param exception Pointer to exception object to propagate
 * @note Force-inlined for critical path optimization
 * @warning Must only be called in error handling context
 * @warning Undefined behavior if called with empty handler stack
 */
EYA_ATTRIBUTE(FORCE_INLINE)
EYA_ATTRIBUTE(NORETURN)
void
eya_runtime_exception_catch_stack_throw(const eya_exception_t *exception)
{
    eya_exception_catch_t *prev = eya_runtime_exception_catch_stack_prev();
    if (prev)
    {
        prev->exception = *exception;
        longjmp(prev->env, eya_error_get_code((eya_error_t *)prev));
    }
    eya_runtime_terminate();
}

/**
 * @brief Re-throws current exception up handler stack
 *
 * Operations performed:
 * 1. Retrieves current exception frame
 * 2. Re-throws contained exception via `eya_runtime_exception_catch_stack_throw()`
 *
 * @note Force-inlined for optimization
 * @note Used in catch blocks to propagate exceptions
 * @warning Must only be called in exception handling context
 *
 * Usage example:
 * @code
 * if (eya_runtime_exception_catch_stack_capture(frame)) {
 *   // Exception handling
 *   eya_runtime_exception_catch_stack_rethrow(); // Propagate up
 * }
 * @endcode
 *
 * @see eya_runtime_exception_catch_stack_throw()
 * @see eya_runtime_exception_catch_stack_get_current()
 */
EYA_ATTRIBUTE(FORCE_INLINE)
EYA_ATTRIBUTE(NORETURN)
void
eya_runtime_exception_catch_stack_rethrow(void)
{
    const eya_exception_catch_t *cur = eya_runtime_exception_catch_stack_get_current();
    eya_runtime_exception_catch_stack_throw(&cur->exception);
}

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_RUNTIME_EXCEPTION_CATCH_STACK_H