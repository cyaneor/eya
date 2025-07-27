/**
 * @file eya_aligned_range.h
 * @brief Specialized memory range operations for aligned allocations
 *
 * This header provides alignment-aware operations for memory ranges, extending
 * the basic memory range functionality with alignment guarantees.
 *
 * It defines:
 * - @ref eya_aligned_range_t type for representing aligned ranges
 * - Alignment-preserving memory management operations
 * - Safe range manipulation with alignment constraints
 *
 * Key features:
 * - Guaranteed proper alignment handling in all operations
 * - Type-safe interface for aligned memory ranges
 * - Integration with the system's aligned allocator
 * - Maintenance of alignment during resize and exchange operations
 *
 * Usage requirements:
 * - All ranges must be initialized with properly aligned memory
 * - Alignment parameters must remain consistent across operations
 * - Mixed operations with non-aligned ranges are not supported
 *
 * @note While the type is structurally identical to @ref eya_memory_range_t,
 *       it enforces alignment semantics through its operations.
 */

#ifndef EYA_ALIGNED_RANGE_H
#define EYA_ALIGNED_RANGE_H

#include "memory_range.h"

/**
 * @typedef eya_aligned_range_t
 * @brief A specialized memory range type for aligned memory allocations.
 *
 * This type extends eya_memory_range_t to represent memory ranges with explicit
 * alignment requirements. It provides alignment-aware operations including:
 * - Alignment-preserving deallocation (@ref eya_aligned_range_clear)
 * - Safe exchange of aligned ranges (@ref eya_aligned_range_exchange)
 * - Alignment-maintaining resizing (@ref eya_aligned_range_resize)
 *
 * Unlike regular memory ranges, all operations on aligned ranges guarantee:
 * 1. Proper use of alignment-aware allocator functions
 * 2. Preservation of alignment during resize operations
 * 3. Correct handling of alignment in memory management
 *
 * @note The alignment properties are enforced by the specialized operations
 *       rather than the type itself. The type serves as documentation of
 *       alignment requirements for API consumers.
 *
 * @see eya_memory_range_t
 * @see eya_aligned_range_clear
 * @see eya_aligned_range_exchange
 * @see eya_aligned_range_resize
 */
typedef eya_memory_range_t eya_aligned_range_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Clears and deallocates an aligned memory range.
 *
 * This function safely deallocates an aligned memory block using the runtime allocator's
 * aligned deallocation function. It properly handles the alignment requirements while
 * freeing the memory and clears the range descriptor.
 *
 * @note The range structure itself remains valid after this operation but will be empty.
 * @warning The pointer must have been allocated with the corresponding aligned allocation function.
 *
 * @param self Pointer to the aligned range structure to clear.
 *             Must be a valid, non-NULL pointer to an initialized aligned range.
 *
 * @see eya_memory_range_get_begin()
 * @see eya_memory_allocator_align_free()
 * @see eya_runtime_allocator()
 * @see eya_memory_range_clear()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_aligned_range_clear(eya_aligned_range_t *self);

/**
 * @brief Exchanges the contents of two aligned memory ranges.
 *
 * This function performs a safe exchange operation between two aligned ranges:
 * 1. First clears/deallocates the memory referenced by the target range (`self`)
 * 2. Then swaps the range descriptors with the source range (`other`)
 *
 * @note After execution:
 *       - `self` will contain `other`'s range (now owns its memory)
 *       - `other` will be left empty (no memory ownership)
 * @warning Both ranges must have compatible alignment characteristics.
 *          This operation transfers memory ownership between the ranges.
 *
 * @param self Pointer to the target range that will receive new memory.
 *             Will be cleared before the swap.
 * @param other Pointer to the source range that provides new memory.
 *              Will be left empty after the operation.
 *
 * @see eya_aligned_range_clear()
 * @see eya_memory_range_swap()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_aligned_range_exchange(eya_aligned_range_t *self, eya_aligned_range_t *other);

/**
 * @brief Resizes an aligned memory range while maintaining alignment.
 *
 * This function safely resizes an aligned memory block:
 * 1. Retrieves the current memory pointer and size
 * 2. Uses the runtime allocator to perform aligned reallocation
 * 3. Updates the range to reference the new memory block
 *
 * @note Preserves the alignment requirements during reallocation.
 *       If reallocation fails, the original range remains unchanged.
 * @warning Both size and alignment must be compatible with the original allocation.
 *          The alignment_size must be a power of two.
 *
 * @param self Pointer to the aligned range structure to resize.
 *             Must be a valid, non-NULL pointer to an initialized range.
 * @param size The new desired size in bytes for the memory range.
 * @param alignment_size The alignment requirement for the memory block.
 *                       Must match or be compatible with original allocation.
 *
 * @see eya_memory_range_get_begin()
 * @see eya_memory_range_get_size()
 * @see eya_memory_allocator_align_realloc()
 * @see eya_memory_range_set_by_size_v()
 * @see eya_runtime_allocator()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_aligned_range_resize(eya_aligned_range_t *self, eya_usize_t size, eya_usize_t alignment_size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_ALIGNED_RANGE_H
