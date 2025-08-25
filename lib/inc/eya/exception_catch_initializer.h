/**
 * @file exception_catch_initializer.h
 * @brief Macros for initializing exception catch blocks
 *        with proper exception handling
 *
 * This header provides specialized macros for initializing exception handling structures
 * in catch blocks. The macros ensure proper exception initialization while maintaining
 * consistency with the library's error handling patterns.
 *
 * The file contains two main macros:
 * 1. @ref eya_exception_catch_initializer
 *    - For initializing exceptions with specific error  information
 * 2. @ref eya_exception_catch_empty_initializer
 *    - For initializing exceptions with empty error fields
 *
 * These macros wrap the standard exception initializers
 * to provide a consistent interface for catch block initialization.
 */

#ifndef EYA_EXCEPTION_CATCH_INITIALIZER_H
#define EYA_EXCEPTION_CATCH_INITIALIZER_H

#include "exception_initializer.h"

/**
 * @def eya_exception_catch_initializer(...)
 * @brief Initializes an exception structure in a catch block with specific error information
 * @param ... Error initialization arguments (code and description)
 * @return Fully initialized exception structure ready for catch handling
 *
 * This macro provides a standardized way to initialize exceptions in catch blocks while
 * preserving all the functionality of the standard @ref eya_exception_initializer.
 *
 * @note The behavior respects the current compilation mode (debug/release):
 *       - Debug mode includes trace information
 *       - Release mode contains only essential error data
 *
 * Example usage:
 * @code
 * catch {
 *     eya_exception_t ex = eya_exception_catch_initializer(EYA_ERROR_CODE_RUNTIME, "Operation
 * failed");
 *     // Handle the exception...
 * }
 * @endcode
 *
 * @see eya_exception_initializer
 * @see eya_exception_catch_empty_initializer
 */
#define eya_exception_catch_initializer(...) eya_initializer(eya_exception_initializer(__VA_ARGS__))

/**
 * @def eya_exception_catch_empty_initializer()
 * @brief Initializes an empty exception structure in a catch block
 * @return Exception structure with empty error fields ready for catch handling
 *
 * Creates an exception structure with empty/zero error information specifically
 * designed for catch block initialization.
 *
 * @note Maintains consistent behavior across all compilation modes
 *       (never includes trace information)
 *
 * Example usage:
 * @code
 * catch {
 *     eya_exception_t ex = eya_exception_catch_empty_initializer();
 *     // Handle empty exception case...
 * }
 * @endcode
 *
 * @see eya_exception_empty_initializer
 * @see eya_exception_catch_initializer
 */
#define eya_exception_catch_empty_initializer() eya_initializer(eya_exception_empty_initializer())

#endif // EYA_EXCEPTION_CATCH_INITIALIZER_H