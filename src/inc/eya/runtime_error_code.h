#ifndef EYA_RUNTIME_ERROR_CODE_H
#define EYA_RUNTIME_ERROR_CODE_H

#include "error_code.h"

/**
 * @enum eya_runtime_error_code
 * @brief Runtime error codes enumeration
 *
 * This enumeration contains error codes that may occur
 * during runtime operations.
 *
 * Each error code represents a specific problem
 * that can happen during execution.
 */
typedef enum eya_runtime_error_code
{
    /**
     * @var EYA_RUNTIME_ERROR_OK
     * @brief Operation completed successfully
     *
     * Indicates successful execution
     * with no errors encountered.
     */
    EYA_RUNTIME_ERROR_OK = EYA_ERROR_CODE_NONE,

    /**
     * @var EYA_RUNTIME_ERROR_NULL_POINTER
     * @brief Null pointer access error
     *
     * Indicates an attempt to access an object
     * through a null pointer. This may lead to
     * program crashes if not properly handled.
     */
    EYA_RUNTIME_ERROR_NULL_POINTER,

    /**
     * @var EYA_RUNTIME_ERROR_INTERRUPT
     * @brief Execution interruption error
     *
     * Indicates operation execution was
     * interrupted. This could be caused by
     * external factors or internal conditions
     * requiring immediate termination.
     */
    EYA_RUNTIME_ERROR_INTERRUPT,

    /**
     * @var EYA_RUNTIME_ERROR_OUT_OF_RANGE
     * @brief Out-of-bounds access error
     *
     * Indicates an attempt to access an element
     * outside valid boundaries. Common with
     * array operations.
     */
    EYA_RUNTIME_ERROR_OUT_OF_RANGE,

    /**
     * @var EYA_RUNTIME_ERROR_INVALID_ARGUMENT
     * @brief Invalid parameter error
     *
     * Indicates one or more function arguments
     * are invalid or don't meet expected
     * value requirements.
     */
    EYA_RUNTIME_ERROR_INVALID_ARGUMENT,

    /**
     * @var EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
     * @brief Invalid memory access error
     *
     * Indicates an attempt to access
     * an invalid or inaccessible memory range.
     */
    EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE,
} eya_runtime_error_code_t;

#endif // EYA_RUNTIME_ERROR_CODE_H