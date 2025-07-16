/**
 * @file exception.h
 * @brief Header file containing exception structure definition
 *
 * Defines the `eya_exception_t` structure
 * that represents an exception within the system.
 *
 * Contains error information and, in debug mode,
 * additional stack trace context.
 */

#ifndef EYA_EXCEPTION_H
#define EYA_EXCEPTION_H

#include "error.h"

#ifdef EYA_COMPILE_OPTION_DEBUG
#    include "exception_trace.h"
#endif // EYA_COMPILE_OPTION_DEBUG

/**
 * @brief Structure representing an exception
 *
 * Contains error context information and,
 * in debug builds, additional call stack trace details.
 */
typedef struct eya_exception
{
    eya_error_t err; /**< Error code and associated message */

#ifdef EYA_COMPILE_OPTION_DEBUG
    eya_exception_trace_t trace; /**< Exception tracing information */
#endif

} eya_exception_t;

#endif // EYA_EXCEPTION_H