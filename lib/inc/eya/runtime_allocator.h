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
 * @brief Returns a pointer to the thread-local runtime memory allocator instance.
 *
 * This function provides access to the thread-local
 * instance of `eya_memory_allocator_t` named `m_runtime_allocator`.
 *
 * The allocator's behavior depends on the configuration:
 * - When `EYA_LIBRARY_OPTION_RUNTIME_ALLOCATOR_USE_STDLIB` is enabled,
 *   the allocator is initialized with standard library functions
 *   (`malloc` for allocation and `free` for deallocation).
 * - When disabled, the allocator is zero-initialized
 *   and must be configured before use.
 *
 * The thread-local storage ensures each thread has its own independent instance
 * of the allocator, preventing synchronization issues in multi-threaded environments.
 *
 * @return Pointer to the thread-local `eya_memory_allocator_t` instance.
 *         The pointer is always valid, though the allocator may need
 *         initialization depending on configuration.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_allocator_t *
eya_runtime_allocator();

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_RUNTIME_ALLOCATOR_H