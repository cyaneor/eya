/**
 * @file memory_allocator_initializer.h
 * @brief Header file containing macros for initializing memory allocator structures.
 *
 * This file provides convenience macros for creating memory allocator initializers
 * with consistent syntax. The macros handle function pointer casting and provide
 * a standardized way to initialize memory allocator interfaces.
 *
 * The main macros are:
 * - `eya_memory_allocator_initializer` - Creates an allocator initializer with specified functions
 * - `eya_memory_allocator_empty_initializer` - Creates a null-initialized allocator structure
 *
 * @note These macros are designed to work with the eya_memory_allocator interface.
 *       The function pointers must match the expected signatures of:
 *       - Allocator function: void* (*)(size_t)
 *       - Deallocator function: void (*)(void*)
 */

#ifndef EYA_MEMORY_ALLOCATOR_INITIALIZER_H
#define EYA_MEMORY_ALLOCATOR_INITIALIZER_H

#include "initializer.h"
#include "ptr_util.h"

/**
 * @def eya_memory_allocator_initializer(alloc_fn, dealloc_fn)
 * @brief Creates a memory allocator initializer with specified allocation/deallocation functions.
 *
 * This macro constructs an initializer for a memory allocator structure by properly
 * casting the provided function pointers to the expected types. It ensures type safety
 * through the eya_ptr_cast utility while providing clean initialization syntax.
 *
 * @param alloc_fn Pointer to the allocation function (must be compatible with void* (*)(size_t))
 * @param dealloc_fn Pointer to the deallocation function (must be compatible with void (*)(void*))
 *
 * @return An initializer structure suitable for initializing a eya_memory_allocator.
 *
 * @note Both parameters will be cast to the appropriate function pointer types.
 *       Passing incompatible functions may lead to undefined behavior.
 *
 * Example usage:
 * @code
 * void* my_alloc(size_t size) { return malloc(size); }
 * void my_free(void* ptr) { free(ptr); }
 *
 * struct eya_memory_allocator allocator =
 *     eya_memory_allocator_initializer(my_alloc, my_free);
 * @endcode
 */
#define eya_memory_allocator_initializer(alloc_fn, dealloc_fn)                                     \
    eya_initializer(eya_ptr_cast(eya_memory_allocator_alloc_fn, alloc_fn),                         \
                    eya_ptr_cast(eya_memory_allocator_dealloc_fn, dealloc_fn))

/**
 * @def eya_memory_allocator_empty_initializer()
 * @brief Creates a null-initialized memory allocator structure.
 *
 * This macro provides a convenient way to create a memory allocator initializer
 * with both function pointers set to null. This is useful for creating empty
 * or default-initialized allocator structures.
 *
 * @return An initializer structure with null function pointers.
 *
 * Example usage:
 * @code
 * struct eya_memory_allocator empty_allocator =
 *     eya_memory_allocator_empty_initializer();
 * @endcode
 */
#define eya_memory_allocator_empty_initializer() eya_memory_allocator_initializer(nullptr, nullptr)

#endif // EYA_MEMORY_ALLOCATOR_INITIALIZER_H