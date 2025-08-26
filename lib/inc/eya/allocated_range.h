/**
 * @file allocated_range.h
 * @brief Memory range management for allocated memory regions
 *
 * This header provides operations for working with allocated memory ranges:
 * - Safe memory deallocation
 * - Range exchange operations
 * - Memory resizing capabilities
 *
 * The @ref eya_allocated_range_t type extends the basic memory range functionality
 * with ownership semantics, making it suitable for managing dynamically allocated
 * memory regions through an explicit interface.
 *
 * Key features:
 * - Integrates with the system memory allocator
 * - Provides ownership-aware operations
 * - Maintains memory safety through clear interface contracts
 * - Supports range resizing and exchange operations
 *
 * @note All functions in this header are thread-compatible but not thread-safe by default.
 *       External synchronization is required for concurrent access to the same range objects.
 *
 * @see eya_memory_range.h
 * @see eya_memory_allocator.h
 */

#ifndef EYA_ALLOCATED_RANGE_H
#define EYA_ALLOCATED_RANGE_H

#include "memory_range.h"

/**
 * @typedef eya_allocated_range_t
 * @brief A type alias for representing allocated memory ranges.
 *
 * This type is an alias for eya_memory_range_t and is used specifically
 * to represent memory ranges that have been allocated by the system.
 * It inherits all properties and functionality of eya_memory_range_t.
 *
 * @see eya_memory_range_t
 */
typedef eya_memory_range_t eya_allocated_range_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Get the size of the allocated memory range in bytes
 * @param[in] self Pointer to memory range structure
 * @return Size of memory range in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         If the memory range contains invalid pointers
 *
 * @see eya_memory_range_get_size()
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_allocated_range_get_size(const eya_allocated_range_t *self);

/**
 * @brief Clears and deallocates the memory of an allocated range.
 *
 * This function safely deallocates the memory block referenced by the range
 * using the runtime's default allocator. It retrieves the begin pointer
 * from the range structure and passes it to the allocator's free function.
 *
 * @note The range structure itself is not deallocated, only the memory it points to.
 *       The caller is responsible for managing the range structure's lifetime.
 *
 * @param[in,out] self Pointer to the allocated range structure to clear.
 *                     Must be a valid, non-nullptr pointer.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         If the memory range is invalid
 *
 * @see eya_memory_range_get_begin()
 * @see eya_memory_allocator_free()
 * @see eya_runtime_allocator()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_allocated_range_clear(eya_allocated_range_t *self);

/**
 * @brief Exchanges the contents of two allocated memory ranges.
 *
 * This function performs a safe exchange operation between two allocated ranges:
 * 1. First clears/deallocates the memory referenced by the target range (`self`)
 * 2. Then swaps the range descriptors with the source range (`other`)
 *
 * @note After execution:
 *       - `self` will contain `other`'s range (now owns its memory)
 *       - `other` will be left empty (no memory ownership)
 * @warning The caller must ensure both ranges are valid.
 *          This operation transfers memory ownership between the ranges.
 *
 * @param[in,out] self Pointer to the target range that will receive new memory.
 *                     Will be cleared before the swap.
 * @param[in,out] other Pointer to the source range that provides new memory.
 *                      Will be left empty after the operation.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         If either memory range is invalid
 *
 * @see eya_allocated_range_clear()
 * @see eya_memory_range_swap()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_allocated_range_exchange(eya_allocated_range_t *self, eya_allocated_range_t *other);

/**
 * @brief Resizes an allocated memory range to a new size.
 *
 * This function safely resizes the memory block referenced by the range:
 * 1. Retrieves the current memory pointer and size
 * 2. Uses the runtime allocator to reallocate memory
 * 3. Updates the range to reference the new memory block
 *
 * @note The function handles all necessary size calculations and memory management.
 *       If reallocation fails, the original range remains unchanged.
 * @warning The new size must be a valid, non-zero value that the allocator can handle.
 *
 * @param[in,out] self Pointer to the allocated range structure to resize.
 *                     Must be a valid, non-nullptr pointer to an initialized range.
 * @param[in] size The new desired size in bytes for the memory range.
 *                 Must be a valid size supported by the allocator.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If memory reallocation fails
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's allocation function is not initialized
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 *
 * @see eya_memory_range_reset_f()
 * @see eya_allocated_range_get_size()
 * @see eya_memory_allocator_realloc()
 * @see eya_memory_range_get_begin()
 * @see eya_runtime_allocator()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_allocated_range_resize(eya_allocated_range_t *self, eya_usize_t size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_ALLOCATED_RANGE_H