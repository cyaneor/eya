/**
 * @file allocated_array.h
 * @brief Typed array management with dynamic allocation and type safety
 *
 * This header defines a typed array structure
 * that combines dynamic memory management with type safety features.
 * The implementation builds upon the untyped allocated range functionality
 * while adding explicit element size tracking and typed access operations.
 *
 * The structure provides:
 * - Dynamic memory range management (inherited from eya_allocated_range_t)
 * - Type-safe element access through explicit element size
 * - Bounds checking capabilities
 * - Memory operation safety guarantees
 *
 * @note All operations maintain the invariant that the memory range
 *       is properly sized and aligned for the specified element type.
 */

#ifndef EYA_ALLOCATED_ARRAY_H
#define EYA_ALLOCATED_ARRAY_H

#include "allocated_range.h"
#include "memory_typed_fields.h"

/**
 * @struct eya_allocated_array
 * @brief Typed array structure for managing dynamically
 *        allocated arrays with element size tracking
 *
 * This structure combines the functionality of an allocated memory range
 * with typed element access, providing a type-safe interface for working
 * with dynamically allocated arrays.
 *
 * It inherits memory management capabilities from `eya_allocated_range_t`
 * while adding explicit element size tracking.
 *
 * The structure contains:
 * - A typed memory range (begin/end pointers)
 * - Element size information for proper array indexing
 *
 * @note This is a typed version of `eya_allocated_range_t` that maintains
 *       additional type safety through the `element_size` field
 *       and typed range pointers.
 *
 * Example usage:
 * @code{.c}
 * eya_allocated_array_t int_array;
 * // Initialize array with 10 integers
 * int_array.range.begin = malloc(10 * sizeof(int));
 * int_array.range.end = int_array.range.begin + 10;
 * int_array.element_size = sizeof(int);
 * @endcode
 *
 * @invariant The structure maintains these properties:
 *      - range.begin <= range.end
 *      - element_size > 0
 *      - (range.end - range.begin) must be divisible by element_size
 *      - All elements between begin and end must be properly aligned for their type
 *
 * @see eya_allocated_range_t for the untyped base functionality
 * @see eya_memory_typed_fields for the field definition macro
 */
typedef struct eya_allocated_array
{
    eya_memory_typed_fields(eya_allocated_range_t);
} eya_allocated_array_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Get the number of elements in the allocated array
 *
 * Returns the current size (number of elements) of the allocated array.
 * If the array's memory range is uninitialized, returns zero.
 *
 * @param[in] self Pointer to the allocated array
 * @return Number of elements in the array, or 0 if uninitialized
 *
 * @note This function safely handles uninitialized arrays by checking
 *       if the memory range is valid before attempting to calculate size
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         If the memory range contains invalid pointers
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_allocated_array_get_size(const eya_allocated_array_t *self);

/**
 * @brief Exchange contents of two allocated arrays
 *
 * Swaps the memory ranges of two arrays.
 * Both arrays must have the same element size.
 *
 * @param[in,out] self Pointer to the first array
 * @param[in,out] other Pointer to the second array
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE
 *         If arrays have different element sizes
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         If either array contains an invalid range
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_allocated_array_exchange(eya_allocated_array_t *self, eya_allocated_array_t *other);

/**
 * @brief Calculate maximum possible elements in array
 *
 * Computes the theoretical maximum number of elements the array
 * can hold based on its element size and system address space limitations.
 *
 * @param[in] self Pointer to the array
 * @return Maximum number of elements array can hold
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_allocated_array_get_max_size(const eya_allocated_array_t *self);

/**
 * @brief Check if requested size exceeds maximum
 *
 * Verifies whether the requested number of elements
 * would exceed the array's maximum capacity.
 *
 * @param[in] self Pointer to the array
 * @param[in] size Requested number of elements
 * @return true if requested size exceeds maximum, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_allocated_array_is_max_size_exceeds(const eya_allocated_array_t *self, eya_usize_t size);

/**
 * @brief Resize allocated array
 *
 * Changes the size of the array's allocated memory.
 * The new size must not exceed the maximum possible size for the array's element type.
 *
 * @param[in,out] self Pointer to the array
 * @param[in] size New number of elements
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 * @throws EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE
 *         If requested size exceeds maximum capacity
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If memory allocation fails
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's allocation function is not initialized
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_allocated_array_resize(eya_allocated_array_t *self, eya_usize_t size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_ALLOCATED_ARRAY_H