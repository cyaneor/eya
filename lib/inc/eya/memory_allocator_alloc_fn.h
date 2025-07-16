/**
 * @file memory_allocator_alloc_fn.h
 * @brief Header file defining the memory allocation function type.
 *
 * This file contains the definition of a function type used for allocating
 * memory of a specific size. The function type specifies the signature
 * for memory allocation functions, including parameters and return value.
 *
 * @note Ensure that allocated memory is properly deallocated
 *       using the corresponding memory deallocation mechanism.
 */

#ifndef EYA_MEMORY_ALLOCATOR_ALLOC_FN_H
#define EYA_MEMORY_ALLOCATOR_ALLOC_FN_H

#include "size.h"

/**
 * @typedef eya_memory_allocator_alloc_fn
 * @brief Function type for memory allocation.
 * @details This function type is used to allocate memory of a specified size.
 *
 * @param size_of_bytes Size of memory to allocate in bytes.
 * @return Pointer to the allocated memory block, or NULL on allocation failure.
 *
 * @note The function must handle cases where
 *       the requested size is 0.
 */
typedef void *(eya_memory_allocator_alloc_fn)(eya_usize_t size_of_bytes);

#endif // EYA_MEMORY_ALLOCATOR_ALLOC_FN_H