/**
 * @file runtime_error_code.h
 * @brief Runtime error codes definitions
 *
 * This header file defines the enumeration of runtime error codes used throughout the application.
 * These codes represent various error conditions that may occur during program execution.
 */

#ifndef EYA_RUNTIME_ERROR_CODE_H
#define EYA_RUNTIME_ERROR_CODE_H

#include "error_code.h"

/**
 * @brief Runtime error codes enumeration
 *
 * This enumeration contains error codes that may occur
 * during runtime operations.
 *
 * Each error code represents a specific problem
 * that can happen during execution.
 */
enum
{
    /**
     * @var EYA_RUNTIME_ERROR_OK
     * @brief Operation completed successfully.
     *
     * Indicates successful execution with no errors encountered.
     */
    EYA_RUNTIME_ERROR_OK = EYA_ERROR_CODE_NONE,

    /**
     * @var EYA_RUNTIME_ERROR_NULL_POINTER
     * @brief Null pointer access error.
     *
     * Indicates an attempt to access an object through a null pointer. This may
     * lead to program crashes if not properly handled.
     */
    EYA_RUNTIME_ERROR_NULL_POINTER,

    /**
     * @var EYA_RUNTIME_ERROR_OVERFLOW
     * @brief Arithmetic overflow error.
     *
     * Indicates an arithmetic operation resulted in a value that exceeds the
     * allowable range for the data type, causing an overflow condition.
     */
    EYA_RUNTIME_ERROR_OVERFLOW,

    /**
     * @var EYA_RUNTIME_ERROR_INTERRUPT
     * @brief Execution interruption error.
     *
     * Indicates operation execution was interrupted. This could be caused by
     * external factors or internal conditions requiring immediate termination.
     */
    EYA_RUNTIME_ERROR_INTERRUPT,

    /**
     * @var EYA_RUNTIME_ERROR_OUT_OF_RANGE
     * @brief Out-of-bounds access error.
     *
     * Indicates an attempt to access
     * an element outside valid boundaries.
     */
    EYA_RUNTIME_ERROR_OUT_OF_RANGE,

    /**
     * @var EYA_RUNTIME_ERROR_INVALID_ARGUMENT
     * @brief Invalid parameter error.
     *
     * Indicates one or more function arguments are invalid
     * or don't meet expected value requirements.
     */
    EYA_RUNTIME_ERROR_INVALID_ARGUMENT,

    /**
     * @var EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
     * @brief Invalid memory access error.
     *
     * Indicates an attempt to access an invalid
     * or inaccessible memory range.
     */
    EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE,

    /**
     * @var EYA_RUNTIME_ERROR_NOT_POWER_OF_TWO
     * @brief Non-power-of-two value error.
     *
     * Indicates an operation expected a value
     * that is a power of two but received a non-compliant value.
     */
    EYA_RUNTIME_ERROR_NOT_POWER_OF_TWO,

    /**
     * @var EYA_RUNTIME_ERROR_ZERO_MEMORY_ALLOCATE
     * @brief Zero memory size error.
     *
     * Indicates an attempt to allocate or operate
     * on a memory block with a size of zero, which is invalid.
     */
    EYA_RUNTIME_ERROR_ZERO_MEMORY_ALLOCATE,

    /**
     * @var EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
     * @brief Zero element size error.
     *
     * Indicates an attempt to perform an operation with an element
     * size of zero, which is invalid for memory operations or array processing.
     */
    EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE,

    /**
     * @var EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
     * @brief Size alignment error.
     *
     * Indicates that the provided size is not a multiple
     * of the element size, which is required for the operation.
     */
    EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE,

    /**
     * @var EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE
     * @brief Different element size error.
     *
     * Indicates an attempt to perform an operation between memory ranges
     * or typed memory structures that have different element sizes.
     */
    EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE,

    /**
     * @var EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
     * @brief Memory allocation failure error.
     *
     * Indicates that a memory allocation request failed. This occurs when
     * the system or custom allocator is unable to allocate the requested
     * amount of memory, typically due to insufficient available memory
     * or allocation policy restrictions.
     */
    EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED,

    /**
     * @var EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE
     * @brief Maximum size exceeded error.
     *
     * Indicates that an attempt was made to resize an array
     * or memory range beyond its maximum allowed capacity.
     *
     * This error occurs when the requested
     * number of elements exceeds the predefined maximum size limit.
     */
    EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE,

    /**
     * @var EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
     * @brief Allocator function not initialized error.
     *
     * Indicates that the memory allocator function
     * has not been initialized before use.
     */
    EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED,

    /**
     * @var EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
     * @brief Deallocator function not initialized error.
     *
     * Indicates that the memory deallocator function
     * has not been initialized before use.
     */
    EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
};

/**
 * @typedef eya_runtime_error_code_t
 * @brief Type alias for runtime error codes.
 *
 * This typedef defines `eya_runtime_error_code_t` as an alias for `eya_error_code_t`.
 * It is used to represent runtime error codes throughout the application,
 * providing a consistent type for error handling related to runtime operations.
 */
typedef eya_error_code_t eya_runtime_error_code_t;

#endif // EYA_RUNTIME_ERROR_CODE_H