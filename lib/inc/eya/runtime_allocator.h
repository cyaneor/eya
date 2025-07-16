/**
 * @file runtime_allocator.h
 * @brief Header file providing functions
 *        for working with the runtime memory allocator.
 *
 * This file contains function definitions for working
 * with the global runtime memory allocator.
 *
 * The allocator is used for memory allocation, deallocation, and reallocation.
 * These functions take memory alignment into account and provide support
 * for various errors and exceptions.
 *
 * The allocator is thread-aware, providing thread-local memory for each thread.
 * Functions are defined for working with both regular and aligned memory blocks.
 *
 * @note Includes support for options and features such as zero-initialization of memory
 *       and initialization using standard library functions.
 */

#ifndef EYA_RUNTIME_ALLOCATOR_H
#define EYA_RUNTIME_ALLOCATOR_H

#include "memory_allocator.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Returns a pointer to the thread-local
 *        runtime memory allocator.
 *
 * This function returns a pointer to the global variable `m_runtime_allocator`,
 * which is a thread-local instance of the `eya_memory_allocator` structure.
 * This allocator is initialized using standard library functions
 * if `EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_INIT_STDLIB` is defined.
 *
 * @return Pointer to the thread-local runtime memory allocator.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_allocator_t *
eya_runtime_allocator();

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_RUNTIME_ALLOCATOR_H