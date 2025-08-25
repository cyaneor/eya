/**
 * @file exception_trace.h
 * @brief Header file defining exception tracing structure
 *
 * Contains definition of `eya_exception_trace_t` structure used
 * to store exception tracing information in debug mode.
 * Designed to record exception origin location and timing data.
 */

#ifndef EYA_EXCEPTION_TRACE_H
#define EYA_EXCEPTION_TRACE_H

/**
 * @struct eya_exception_trace
 * @brief Structure containing exception tracing information
 *
 * Used in debug mode to store context data about
 * the location where exception was thrown.
 */
typedef struct eya_exception_trace
{
    /**
     * @var timestamp
     * @brief Exception occurrence timestamp
     *
     * Pointer to string containing `__TIMESTAMP__`
     * value at exception throw time
     */
    const char *timestamp;

    /**
     * @var filename
     * @brief Source file where exception occurred
     *
     * Pointer to string containing `__FILE__`
     * value at exception throw time
     */
    const char *filename;

    /**
     * @var function
     * @brief Function where exception occurred
     *
     * Pointer to string containing `__FUNCTION__`
     * value at exception throw time
     */
    const char *function;
} eya_exception_trace_t;

#endif // EYA_EXCEPTION_TRACE_H