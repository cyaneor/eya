/**
 * @file memory_allocator_dealloc_fn.h
 * @brief Header file defining the memory deallocation function type.
 *
 * This file contains the definition of a function type used for deallocating
 * memory previously allocated by a corresponding allocator.
 *
 * The function type specifies the signature for memory deallocation functions,
 * including their parameters and behavior.
 *
 * @note Ensure that deallocated memory was originally allocated using
 *       the matching allocation mechanism to avoid undefined behavior.
 */

#ifndef EYA_MEMORY_ALLOCATOR_DEALLOC_FN_H
#define EYA_MEMORY_ALLOCATOR_DEALLOC_FN_H

/**
 * @typedef eya_memory_allocator_dealloc_fn
 * @brief Function type for memory deallocation.
 * @details This function type is used to release previously allocated memory.
 *
 * @param ptr Pointer to the memory block to be deallocated.
 * @note The function must not attempt to deallocate memory that has already
 *       been freed and must safely handle NULL pointer inputs.
 */
typedef void(eya_memory_allocator_dealloc_fn)(void *ptr);

#endif // EYA_MEMORY_ALLOCATOR_DEALLOC_FN_H