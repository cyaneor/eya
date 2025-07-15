/**
 * @file memory_range.h
 * @brief Generic memory range operations and utilities
 *
 * This header defines a generic memory range structure
 * and associated operations for working with contiguous memory regions.
 *
 * The implementation provides functions for querying,
 * validating, and manipulating memory ranges.
 */

#ifndef EYA_MEMORY_RANGE_H
#define EYA_MEMORY_RANGE_H

#include "memory_range_fields.h"
#include "memory_range_state.h"
#include "attribute.h"
#include "offset.h"
#include "addr.h"
#include "size.h"
#include "bool.h"

/**
 * @struct eya_memory_range
 * @brief A generic memory range structure for contiguous byte regions.
 *
 * This structure provides a generic way to represent a contiguous memory range
 * using start and end pointers. The void pointer type allows it to work with
 * any memory region regardless of the underlying data type.
 */
typedef struct eya_memory_range
{
    eya_memory_range_fields(void); /**< Expands to void* begin and void* end pointers */
} eya_memory_range_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Unpack a memory range into begin and end pointers
 * @param self Pointer to memory range structure
 * @param begin [out] Pointer to store begin address (can be NULL)
 * @param end [out] Pointer to store end address (can be NULL)
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_unpack(const eya_memory_range_t *self, void **begin, void **end);

/**
 * @brief Get the begin pointer of a memory range
 * @param self Pointer to memory range structure
 * @return Begin pointer
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_get_begin(const eya_memory_range_t *self);

/**
 * @brief Get the end pointer of a memory range
 * @param self Pointer to memory range structure
 * @return End pointer
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_get_end(const eya_memory_range_t *self);

/**
 * @brief Get the state of a memory range
 * @param self Pointer to memory range structure
 * @return State of the memory range
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_range_state_t
eya_memory_range_get_state(const eya_memory_range_t *self);

/**
 * @brief Check if memory range is uninitialized
 * @param self Pointer to memory range structure
 * @return true if uninitialized, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_uninit(const eya_memory_range_t *self);

/**
 * @brief Check if memory range is empty
 * @param self Pointer to memory range structure
 * @return true if empty, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_empty(const eya_memory_range_t *self);

/**
 * @brief Check if memory range contains data
 * @param self Pointer to memory range structure
 * @return true if contains data, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_has_data(const eya_memory_range_t *self);

/**
 * @brief Check if memory range is invalid
 * @param self Pointer to memory range structure
 * @return true if invalid, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_invalid(const eya_memory_range_t *self);

/**
 * @brief Check if memory range is valid
 * @param self Pointer to memory range structure
 * @return true if valid, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid(const eya_memory_range_t *self);

/**
 * @brief Unpack a memory range into begin and end pointers with validation
 * @param self Pointer to memory range structure
 * @param begin [out] Pointer to store begin address
 * @param end [out] Pointer to store end address
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_unpack_v(const eya_memory_range_t *self, void **begin, void **end);

/**
 * @brief Calculate the difference between begin and end pointers
 * @param self Pointer to memory range structure
 * @return Difference between end and begin pointers
 */
EYA_ATTRIBUTE(SYMBOL)
eya_uaddr_t
eya_memory_range_diff(const eya_memory_range_t *self);

/**
 * @brief Get the size of the memory range in bytes
 * @param self Pointer to memory range structure
 * @return Size of memory range in bytes
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_range_get_size(const eya_memory_range_t *self);

/**
 * @brief Check if memory range is aligned
 * @param self Pointer to memory range structure
 * @param align Alignment to check (must be power of two)
 * @return true if aligned, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_aligned(const eya_memory_range_t *self, eya_usize_t align);

/**
 * @brief Check if memory range size is multiple of element size
 * @param self Pointer to memory range structure
 * @param element_size Size of element
 * @return true if size is multiple, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_multiple_of_size(const eya_memory_range_t *self, eya_usize_t element_size);

/**
 * @brief Check if memory range contains a pointer
 * @param self Pointer to memory range structure
 * @param ptr Pointer to check
 * @return true if pointer is within range, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_contains_ptr(const eya_memory_range_t *self, const void *ptr);

/**
 * @brief Check if memory range contains another range
 * @param self Pointer to memory range structure
 * @param begin Start of range to check
 * @param end End of range to check (exclusive)
 * @return true if range is contained, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_contains_range(const eya_memory_range_t *self, const void *begin, const void *end);

/**
 * @brief Check if memory range contains another memory range
 * @param self Pointer to memory range structure
 * @param other Pointer to another memory range
 * @return true if range is contained, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_contains(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Check if offset is valid for this memory range
 * @param self Pointer to memory range structure
 * @param offset Offset to check
 * @return true if offset is valid, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid_offset(const eya_memory_range_t *self, eya_uoffset_t offset);

/**
 * @brief Get pointer at offset from begin
 * @param self Pointer to memory range structure
 * @param offset Offset from begin
 * @return Pointer at offset
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_f(const eya_memory_range_t *self, eya_uoffset_t offset);

/**
 * @brief Get pointer at offset from end
 * @param self Pointer to memory range structure
 * @param offset Offset from end
 * @return Pointer at offset
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_b(const eya_memory_range_t *self, eya_uoffset_t offset);

/**
 * @brief Get pointer at offset (direction specified)
 * @param self Pointer to memory range structure
 * @param offset Offset from begin or end
 * @param reversed If true, offset from end; if false, offset from begin
 * @return Pointer at offset
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at(const eya_memory_range_t *self, eya_uoffset_t offset, bool reversed);

/**
 * @brief Get pointer to first element in range
 * @param self Pointer to memory range structure
 * @return Pointer to first element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_front(const eya_memory_range_t *self);

/**
 * @brief Get pointer to last element in range
 * @param self Pointer to memory range structure
 * @return Pointer to last element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_back(const eya_memory_range_t *self);

/**
 * @brief Check if range begin equals pointer
 * @param self Pointer to memory range structure
 * @param ptr Pointer to compare
 * @return true if equal, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_begin_to(const eya_memory_range_t *self, const void *ptr);

/**
 * @brief Check if range end equals pointer
 * @param self Pointer to memory range structure
 * @param ptr Pointer to compare
 * @return true if equal, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_end_to(const eya_memory_range_t *self, const void *ptr);

/**
 * @brief Check if two ranges have equal begin pointers
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 * @return true if begins are equal, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_begin(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Check if two ranges have equal end pointers
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 * @return true if ends are equal, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_end(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Check if two ranges are equal
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 * @return true if ranges are equal, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Clear memory range (set to uninitialized state)
 * @param self Pointer to memory range structure
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_clear(eya_memory_range_t *self);

/**
 * @brief Assign one memory range to another with validation
 * @param self Pointer to destination memory range
 * @param other Pointer to source memory range
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_assign(eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Set memory range begin and end pointers with validation
 * @param self Pointer to memory range structure
 * @param begin New begin pointer
 * @param end New end pointer
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_set(eya_memory_range_t *self, void *begin, void *end);

/**
 * @brief Set memory range from begin pointer and size
 * @param self Pointer to memory range structure
 * @param begin New begin pointer
 * @param size Size of range in bytes
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_set_s(eya_memory_range_t *self, void *begin, eya_usize_t size);

/**
 * @brief Set memory range from begin pointer and size (null-safe)
 * @param self Pointer to memory range structure
 * @param begin New begin pointer (can be null)
 * @param size Size of range in bytes
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_set_f(eya_memory_range_t *self, void *begin, eya_usize_t size);

/**
 * @brief Swap two memory ranges
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_swap(eya_memory_range_t *self, eya_memory_range_t *other);

/**
 * @brief Exchange two memory ranges (clear self and swap)
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_exchange(eya_memory_range_t *self, eya_memory_range_t *other);

/**
 * @brief Create a new memory range from begin and end pointers
 * @param begin Start of memory range
 * @param end End of memory range (exclusive)
 * @return New memory range
 * @note Will trigger runtime error if resulting range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_range_t
eya_memory_range_make(void *begin, void *end);

/**
 * @brief Create a slice of a memory range
 * @param self Pointer to memory range structure
 * @param offset Offset from begin
 * @param size Size of slice
 * @return New memory range slice
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_range_t
eya_memory_range_slice(const eya_memory_range_t *self, eya_uoffset_t offset, eya_usize_t size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_RANGE_H
