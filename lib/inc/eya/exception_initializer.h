/**
 * @file exception_initializer.h
 * @brief Exception initialization with dual-mode debug/release support
 *
 * Provides comprehensive macros for initializing exception structures,
 * featuring distinct behaviors between development and production environments.
 *
 * Key Features:
 * - Dual-mode initialization:
 *   * Debug mode: Full error context with stack traces (file, function, timestamp)
 *   * Release mode: Minimal error information for optimized performance
 *
 * - Two initialization variants:
 *   1. @ref eya_exception_initializer - For explicit error cases (with error code/message)
 *   2. @ref eya_exception_empty_initializer - For default/empty error state initialization
 *
 * @note All macros maintain ABI compatibility between modes while varying
 *       the available diagnostic information.
 */

#ifndef EYA_EXCEPTION_INITIALIZER_H
#define EYA_EXCEPTION_INITIALIZER_H

#include "error_initializer.h"
#include "compile_option_fallback.h"
#include "exception_trace_initializer.h"

/**
 * @def eya_exception_initializer(...)
 * @brief Initializes an exception structure with error information and optional trace data
 * @param ... Error initialization arguments (code and description)
 * @return Initialized exception structure with error information
 *
 * @note The behavior of this macro depends on the compilation mode:
 *       - In debug mode (EYA_COMPILE_OPTION_DEBUG=ON): includes both error information
 *         and current trace data (timestamp, file, function)
 *       - In release mode (EYA_COMPILE_OPTION_DEBUG=OFF): includes only error information
 *
 * @warning In debug mode, this macro captures the current location information
 *          (file, function) at the point of initialization.
 *
 * Example usage in debug mode:
 * @code
 * // Debug build
 * eya_exception_t ex = eya_exception_initializer(EYA_ERROR_CODE_RUNTIME, "Runtime error");
 * // Initializes both error fields and trace information
 * @endcode
 *
 * Example usage in release mode:
 * @code
 * // Release build
 * eya_exception_t ex = eya_exception_initializer(EYA_ERROR_CODE_RUNTIME, "Runtime error");
 * // Initializes only error fields
 * @endcode
 *
 * @see eya_error_initializer
 * @see eya_exception_trace_initializer_now
 */
#if (EYA_COMPILE_OPTION_DEBUG == EYA_COMPILE_OPTION_ON)
#    define eya_exception_initializer(...)                                                         \
        eya_initializer(eya_error_initializer(__VA_ARGS__), eya_exception_trace_initializer_now())
#else
#    define eya_exception_initializer(...) eya_initializer(eya_error_initializer(__VA_ARGS__))
#endif

/**
 * @def eya_exception_empty_initializer()
 * @brief Initializes an exception structure with empty error information and optional trace data
 * @return Initialized exception structure with empty error fields
 *
 * @note The behavior of this macro depends on the compilation mode:
 *       - In debug mode (EYA_COMPILE_OPTION_DEBUG=ON): includes both empty error information
 *         and current trace data (timestamp, file, function)
 *       - In release mode (EYA_COMPILE_OPTION_DEBUG=OFF): includes only empty error information
 *
 * @warning In debug mode, this macro captures the current location information
 *          (file, function) at the point of initialization.
 *
 * Example usage in debug mode:
 * @code
 * // Debug build
 * eya_exception_t ex = eya_exception_empty_initializer();
 * // Initializes empty error fields and trace information
 * @endcode
 *
 * Example usage in release mode:
 * @code
 * // Release build
 * eya_exception_t ex = eya_exception_empty_initializer();
 * // Initializes only empty error fields
 * @endcode
 *
 * @see eya_error_empty_initializer
 * @see eya_exception_trace_initializer_now
 * @see eya_exception_initializer
 */
#if (EYA_COMPILE_OPTION_DEBUG == EYA_COMPILE_OPTION_ON)
#    define eya_exception_empty_initializer()                                                      \
        eya_initializer(eya_error_empty_initializer(), eya_exception_trace_initializer_now())
#else
#    define eya_exception_empty_initializer() eya_initializer(eya_error_empty_initializer())
#endif

#endif // EYA_EXCEPTION_INITIALIZER_H