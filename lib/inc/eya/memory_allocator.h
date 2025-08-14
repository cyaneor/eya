/**
 * @file memory_allocator.h
 * @brief Memory allocator interface with customizable allocation functions.
 *
 * This header defines a flexible memory allocator interface that allows
 * custom implementations of memory management through function pointers.
 *
 * It provides functions for allocation, deallocation, and reallocation of memory,
 * with runtime safety checks and optional memory initialization.
 */

#ifndef EYA_MEMORY_ALLOCATOR_H
#define EYA_MEMORY_ALLOCATOR_H

#include "memory_allocator_alloc_fn.h"
#include "memory_allocator_dealloc_fn.h"
#include "attribute.h"
#include "size.h"

/**
 * @struct eya_memory_allocator
 * @brief A structure representing a memory allocator
 *        with function pointers for allocation and deallocation.
 *
 * This structure holds function pointers to custom memory allocation
 * and deallocation functions, allowing flexible memory management implementations.
 */
typedef struct eya_memory_allocator
{
    eya_memory_allocator_alloc_fn   *alloc_fn;   /**< Pointer to the allocation function */
    eya_memory_allocator_dealloc_fn *dealloc_fn; /**< Pointer to the deallocation function */
} eya_memory_allocator_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Retrieves the allocation function pointer
 * @param[in] self Pointer to the memory allocator structure
 * @return The allocation function pointer
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_allocator_alloc_fn *
eya_memory_allocator_get_alloc_fn(const eya_memory_allocator_t *self);

/**
 * @brief Retrieves the deallocation function pointer
 * @param[in] self Pointer to the memory allocator structure
 * @return The deallocation function pointer
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_allocator_dealloc_fn *
eya_memory_allocator_get_dealloc_fn(const eya_memory_allocator_t *self);

/**
 * @brief Allocates memory using the allocator
 * @param[in] self Pointer to the memory allocator structure
 * @param[in] size Size of memory to allocate in bytes
 * @return Pointer to allocated memory
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_MEMORY_ALLOCATE
 *         If size is zero
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If alloc_fn is NULL
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If allocation fails
 *
 * @note When EYA_LIBRARY_OPTION_FILL_ZERO_AFTER_MEMORY_ALLOCATE is enabled,
 *       allocated memory will be zero-initialized
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_allocator_alloc(const eya_memory_allocator_t *self, eya_usize_t size);

/**
 * @brief Frees memory using the allocator
 * @param[in] self Pointer to the memory allocator structure
 * @param[in] ptr Pointer to memory to free
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If dealloc_fn is NULL
 *
 * @note Does nothing if ptr is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_allocator_free(const eya_memory_allocator_t *self, void *ptr);

/**
 * @brief Reallocates memory using the allocator
 * @param[in] self Pointer to the memory allocator structure
 * @param[in] old_ptr Pointer to previously allocated memory
 * @param[in] old_size Size of previously allocated memory
 * @param[in] new_size New desired size
 * @return Pointer to reallocated memory
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_MEMORY_ALLOCATE
 *         If new_size is zero during allocation
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If alloc_fn is NULL
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If dealloc_fn is NULL during free
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If reallocation fails
 *
 * @note Behavior details:
 *       - Returns old_ptr if old_size == new_size
 *       - Allocates new memory if old_ptr is NULL
 *       - Frees memory and returns NULL if new_size is zero
 *       - Otherwise allocates new block, copies data, and frees old block
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_allocator_realloc(const eya_memory_allocator_t *self,
                             void                         *old_ptr,
                             eya_usize_t                   old_size,
                             eya_usize_t                   new_size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_ALLOCATOR_H