/**
 * @file memory_allocator.h
 * @brief Defines a memory allocator interface
 *        with functions for allocation, deallocation, and aligned memory management.
 *
 * This header file provides the structure and function declarations
 * for a customizable memory allocator.
 *
 * The `eya_memory_allocator_t` structure holds function pointers
 * for allocation and deallocation, enabling flexible memory management implementations.
 * The provided functions support standard memory allocation, deallocation, reallocation,
 * as well as aligned memory operations.
 *
 * Runtime checks ensure the validity of inputs and operations,
 * and optional zero-initialization is supported for allocated memory.
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
    eya_memory_allocator_alloc_fn   *alloc_fn;   /**< Pointer to the allocation function. */
    eya_memory_allocator_dealloc_fn *dealloc_fn; /**< Pointer to the deallocation function. */
} eya_memory_allocator_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Retrieves the allocation function pointer from a memory allocator.
 *
 * This function returns the function pointer to the allocation function stored in the given
 * memory allocator structure. It performs a runtime check to ensure the allocator is valid.
 *
 * @param self Pointer to the memory allocator structure.
 * @return The allocation function pointer, or NULL if the allocator is invalid.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_allocator_alloc_fn *
eya_memory_allocator_get_alloc_fn(const eya_memory_allocator_t *self);

/**
 * @brief Retrieves the deallocation function pointer from a memory allocator.
 *
 * This function returns the function pointer to the deallocation function stored in the given
 * memory allocator structure. It performs a runtime check to ensure the allocator is valid.
 *
 * @param self Pointer to the memory allocator structure.
 * @return The deallocation function pointer, or NULL if the allocator is invalid.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_allocator_dealloc_fn *
eya_memory_allocator_get_dealloc_fn(const eya_memory_allocator_t *self);

/**
 * @brief Allocates memory using the provided memory allocator.
 *
 * This function allocates a block of memory of the specified size
 * using the allocation function stored in the given memory allocator structure.
 * It performs runtime checks to ensure the allocator and allocation function are valid.
 *
 * If the `EYA_LIBRARY_OPTION_FILL_ZERO_AFTER_MEMORY_ALLOCATE` option is enabled,
 * the allocated memory is initialized to zero.
 *
 * @param self Pointer to the memory allocator structure.
 * @param size The size of the memory block to allocate, in bytes.
 * @return A pointer to the allocated memory, or NULL if allocation fails or inputs are invalid.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_allocator_alloc(const eya_memory_allocator_t *self, eya_usize_t size);

/**
 * @brief Frees memory using the provided memory allocator.
 *
 * This function deallocates a block of memory pointed to by `ptr`
 * using the deallocation function stored in the given memory allocator structure.
 * It performs runtime checks to ensure the pointer and deallocation function
 * are valid before proceeding with the deallocation.
 *
 * @param self Pointer to the memory allocator structure.
 * @param ptr Pointer to the memory block to deallocate.
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_allocator_free(const eya_memory_allocator_t *self, void *ptr);

/**
 * @brief Reallocates memory using the provided memory allocator.
 *
 * This function reallocates a block of memory pointed to by `old_ptr`
 * from `old_size` to `new_size` using the provided memory allocator.
 *
 * - If the new size equals the old size, the original pointer is returned.
 * - If the old pointer is NULL, it behaves like `eya_memory_allocator_alloc`.
 * - If the new size is zero, it frees the old memory and returns NULL.
 * - Otherwise, it allocates a new block, copies the data from the old block,
 *   and frees the old block.
 *
 * @param self Pointer to the memory allocator structure.
 * @param old_ptr Pointer to the previously allocated memory block.
 * @param old_size Size of the old memory block, in bytes.
 * @param new_size Desired size of the new memory block, in bytes.
 * @return A pointer to the reallocated memory,
 *         or NULL if the new size is zero or allocation fails.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_allocator_realloc(const eya_memory_allocator_t *self,
                             void                         *old_ptr,
                             eya_usize_t                   old_size,
                             eya_usize_t                   new_size);

/**
 * @brief Allocates memory with specified alignment
 *        using the provided memory allocator.
 *
 * This function allocates a block of memory of the specified size with the requested alignment.
 * It ensures the alignment size is a power of two and allocates extra space to store the original
 * unaligned pointer. The allocated memory is adjusted to meet the alignment requirement,
 * and the original unaligned pointer is stored just before the aligned memory block.
 *
 * @param self Pointer to the memory allocator structure.
 * @param size The size of the memory block to allocate, in bytes.
 * @param alignment_size The desired alignment of the memory block,
 *                       which must be a power of two.
 * @return A pointer to the aligned memory block,
 *         or NULL if allocation fails or alignment is invalid.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_allocator_align_alloc(const eya_memory_allocator_t *self,
                                 eya_usize_t                   size,
                                 eya_usize_t                   alignment_size);

/**
 * @brief Frees aligned memory using the provided memory allocator.
 *
 * This function deallocates a block of memory that was previously allocated with alignment
 * using `eya_memory_allocator_align_alloc`. It retrieves the original unaligned pointer stored
 * just before the aligned memory block and passes it to the allocator's deallocation function.
 * A runtime check ensures the input pointer is valid.
 *
 * @param self Pointer to the memory allocator structure.
 * @param ptr Pointer to the aligned memory block to deallocate.
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_allocator_align_free(const eya_memory_allocator_t *self, void *ptr);

/**
 * @brief Reallocates aligned memory using the provided memory allocator.
 *
 * This function reallocates a block of aligned memory pointed to by `old_ptr`
 * from `old_size` to `new_size` with the specified `alignment_size`
 * using the provided memory allocator.
 *
 * - If the new size equals the old size, the original pointer is returned.
 * - If the old pointer is NULL, it behaves like `eya_memory_allocator_align_alloc`.
 * - If the new size is zero, it frees the old  aligned memory and returns NULL.
 * - Otherwise, it allocates a new aligned block,
 *   copies the data from the old block, and frees the old block.
 *
 * @param self Pointer to the memory allocator structure.
 * @param old_ptr Pointer to the previously allocated aligned memory block.
 * @param old_size Size of the old memory block, in bytes.
 * @param new_size Desired size of the new memory block, in bytes.
 * @param alignment_size The desired alignment of the new memory block,
 *                       which must be a power of two.
 * @return A pointer to the reallocated aligned memory,
 *         or NULL if the new size is zero or allocation fails.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_allocator_align_realloc(const eya_memory_allocator_t *self,
                                   void                         *old_ptr,
                                   eya_usize_t                   old_size,
                                   eya_usize_t                   new_size,
                                   eya_usize_t                   alignment_size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_ALLOCATOR_H
