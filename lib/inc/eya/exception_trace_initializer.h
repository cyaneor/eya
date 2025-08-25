/**
 * @file exception_trace_initializer.h
 * @brief Macros for initializing exception trace structures
 *
 * This header provides macros for convenient initialization of structures
 * that contain exception tracing information (timestamp, filename and function),
 * as defined by the eya_exception_trace_t structure.
 */

#ifndef EYA_EXCEPTION_TRACE_INITIALIZER_H
#define EYA_EXCEPTION_TRACE_INITIALIZER_H

#include "initializer.h"

/**
 * @def eya_exception_trace_initializer(timestamp, filename, function, ...)
 * @brief Initializes an exception trace structure with debug information
 * @param timestamp Exception occurrence timestamp (typically __TIMESTAMP__)
 * @param filename Source file where exception occurred (typically __FILE__)
 * @param function Function where exception occurred (typically __FUNCTION__)
 * @param ... Additional initialization arguments (if needed)
 * @return Initialized exception trace structure with specified debug information
 *
 * @note This macro wraps eya_initializer to set up a structure with standard
 *       exception trace fields (timestamp, filename and function).
 *
 * Example usage:
 * @code
 * eya_exception_trace_t trace = eya_exception_trace_initializer(
 *     __TIMESTAMP__,
 *     __FILE__,
 *     __FUNCTION__);
 * // Results in trace with current timestamp, file and function info
 * @endcode
 *
 * @warning The strings passed should be string literals or persistent strings,
 *          as the structure stores only pointers to these strings.
 *
 * @see eya_exception_trace_t
 */
#define eya_exception_trace_initializer(timestamp, filename, function, ...)                        \
    eya_initializer(timestamp, filename, function, __VA_ARGS__)

/**
 * @def eya_exception_trace_initializer_now()
 * @brief Initializes an exception trace structure with current debug information
 * @return Initialized exception trace structure with current timestamp,
 *         file and function information
 *
 * @note This is a convenience macro that automatically fills in the current
 *       timestamp, filename and function name using predefined macros.
 *
 * Example usage:
 * @code
 * eya_exception_trace_t trace = eya_exception_trace_initializer_now();
 * // Automatically fills in current context information
 * @endcode
 *
 * @warning The strings used are compiler-generated macros (__TIMESTAMP__, etc.)
 *          and point to static data. Do not use this if you need different
 *          location information than the actual call site.
 *
 * @see eya_exception_trace_initializer()
 * @see eya_exception_trace_t
 */
#define eya_exception_trace_initializer_now()                                                      \
    eya_exception_trace_initializer(__TIMESTAMP__, __FILE__, __FUNCTION__)

#endif // EYA_EXCEPTION_TRACE_INITIALIZER_H