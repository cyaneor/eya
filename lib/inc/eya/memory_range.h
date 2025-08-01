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
 * @brief Represents a memory range with start and end pointers.
 *
 * This structure defines a contiguous block of memory by storing its starting
 * and ending addresses. The end pointer typically points to the first byte
 * after the allocated memory block (similar to STL end iterators).
 *
 * @note The memory range is considered valid only if:
 *       - Both begin and end are non-NULL
 *       - begin <= end
 *       - The pointers point to the same memory segment/allocation
 */
typedef struct eya_memory_range
{
    eya_memory_range_fields(void); /**< Expands to void* begin and void* end pointers */
} eya_memory_range_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Unpack a memory range into begin and end pointers
 * @param self Pointer to memory range structure
 * @param begin [out] Pointer to store begin address (can be nullptr)
 * @param end [out] Pointer to store end address (can be nullptr)
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_unpack(const void *self, void **begin, void **end);

/**
 * @brief Get the begin pointer of a memory range
 * @param self Pointer to memory range structure
 * @return Begin pointer
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_get_begin(const void *self);

/**
 * @brief Get the end pointer of a memory range
 * @param self Pointer to memory range structure
 * @return End pointer
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_get_end(const void *self);

/**
 * @brief Get the state of a memory range
 * @param self Pointer to memory range structure
 * @return State of the memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_range_state_t
eya_memory_range_get_state(const void *self);

/**
 * @brief Check if memory range is uninitialized
 * @param self Pointer to memory range structure
 * @return true if uninitialized, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_uninit(const void *self);

/**
 * @brief Check if memory range is empty
 * @param self Pointer to memory range structure
 * @return true if empty, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_empty(const void *self);

/**
 * @brief Check if memory range contains data
 * @param self Pointer to memory range structure
 * @return true if contains data, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_has_data(const void *self);

/**
 * @brief Check if memory range is invalid
 * @param self Pointer to memory range structure
 * @return true if invalid, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_invalid(const void *self);

/**
 * @brief Check if memory range is valid
 * @param self Pointer to memory range structure
 * @return true if valid, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid(const void *self);

/**
 * @brief Unpack a memory range into begin and end pointers with validation
 * @param self Pointer to memory range structure
 * @param begin [out] Pointer to store begin address
 * @param end [out] Pointer to store end address
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_unpack_v(const void *self, void **begin, void **end);

/**
 * @brief Calculate the difference between begin and end pointers
 * @param self Pointer to memory range structure
 * @return Difference between end and begin pointers
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
eya_uaddr_t
eya_memory_range_diff(const void *self);

/**
 * @brief Get the size of the memory range in bytes
 * @param self Pointer to memory range structure
 * @return Size of memory range in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_range_get_size(const void *self);

/**
 * @brief Check if memory range is aligned
 * @param self Pointer to memory range structure
 * @param align Alignment to check (must be power of two)
 * @return true if aligned, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 * @throws EYA_RUNTIME_ERROR_NOT_POWER_OF_TWO
 *         if align is not power of two
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_aligned(const void *self, eya_usize_t align);

/**
 * @brief Check if memory range size is multiple of element size
 * @param self Pointer to memory range structure
 * @param element_size Size of element
 * @return true if size is multiple, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         if element_size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_multiple_of_size(const void *self, eya_usize_t element_size);

/**
 * @brief Check if memory range contains a pointer
 * @param self Pointer to memory range structure
 * @param ptr Pointer to check
 * @return true if pointer is within range, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_contains_ptr(const void *self, const void *ptr);

/**
 * @brief Check if memory range contains another range
 * @param self Pointer to memory range structure
 * @param begin Start of range to check
 * @param end End of range to check (exclusive)
 * @return true if range is contained, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_contains_range(const void *self, const void *begin, const void *end);

/**
 * @brief Check if memory range contains another memory range
 * @param self Pointer to memory range structure
 * @param other Pointer to another memory range
 * @return true if range is contained, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if either range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_contains(const void *self, const void *other);

/**
 * @brief Check if offset is valid for this memory range
 * @param self Pointer to memory range structure
 * @param offset Offset to check
 * @return true if offset is valid, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid_offset(const void *self, eya_uoffset_t offset);

/**
 * @brief Get pointer at offset from begin
 * @param self Pointer to memory range structure
 * @param offset Offset from begin
 * @return Pointer at offset
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if offset is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_from_front(void *self, eya_uoffset_t offset);

/**
 * @brief Get pointer at offset from end
 * @param self Pointer to memory range structure
 * @param offset Offset from end
 * @return Pointer at offset
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if offset is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_from_back(void *self, eya_uoffset_t offset);

/**
 * @brief Get pointer at offset (direction specified)
 * @param self Pointer to memory range structure
 * @param offset Offset from begin or end
 * @param reversed If true, offset from end; if false, offset from begin
 * @return Pointer at offset
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if offset is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at(void *self, eya_uoffset_t offset, bool reversed);

/**
 * @brief Get pointer to first element in range
 * @param self Pointer to memory range structure
 * @return Pointer to first element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_front(void *self);

/**
 * @brief Get pointer to last element in range
 * @param self Pointer to memory range structure
 * @return Pointer to last element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_back(void *self);

/**
 * @brief Check if range begin equals pointer
 * @param self Pointer to memory range structure
 * @param ptr Pointer to compare
 * @return true if equal, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_begin_to(const void *self, const void *ptr);

/**
 * @brief Check if range end equals pointer
 * @param self Pointer to memory range structure
 * @param ptr Pointer to compare
 * @return true if equal, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_end_to(const void *self, const void *ptr);

/**
 * @brief Check if two ranges have equal begin pointers
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 * @return true if begins are equal, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_begin(const void *self, const void *other);

/**
 * @brief Check if two ranges have equal end pointers
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 * @return true if ends are equal, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_end(const void *self, const void *other);

/**
 * @brief Check if two ranges are equal
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 * @return true if ranges are equal, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal(const void *self, const void *other);

/**
 * @brief Clear memory range (set to uninitialized state)
 * @param self Pointer to memory range structure
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_clear(void *self);

/**
 * @brief Assign one memory range to another with validation
 * @param self Pointer to destination memory range
 * @param other Pointer to source memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if other range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_assign(void *self, const void *other);

/**
 * @brief Set memory range begin and end pointers with validation
 * @param self Pointer to memory range structure
 * @param begin New begin pointer
 * @param end New end pointer
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if resulting range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_set_range(void *self, void *begin, void *end);

/**
 * @brief Set memory range from begin pointer and size
 * @param self Pointer to memory range structure
 * @param begin New begin pointer
 * @param size Size of range in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_ARGUMENT
 *         if begin is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if resulting range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_set_by_size(void *self, void *begin, eya_usize_t size);

/**
 * @brief Set memory range from begin pointer and size (null-safe)
 * @param self Pointer to memory range structure
 * @param begin New begin pointer (can be null)
 * @param size Size of range in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if resulting range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_set_by_size_v(void *self, void *begin, eya_usize_t size);

/**
 * @brief Swap two memory ranges
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_swap(void *self, void *other);

/**
 * @brief Exchange two memory ranges (clear self and swap)
 * @param self Pointer to first memory range
 * @param other Pointer to second memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_exchange(void *self, void *other);

/**
 * @brief Create a new memory range from begin and end pointers
 * @param begin Start of memory range
 * @param end End of memory range (exclusive)
 * @return New memory range
 *
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if resulting range is invalid
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
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if offset or size are invalid
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_range_t
eya_memory_range_slice(const void *self, eya_uoffset_t offset, eya_usize_t size);

/**
 * @brief Sets all bytes in a memory range to a specified value.
 * @param self Pointer to the memory range structure
 *             defining the destination memory range.
 * @param value The byte value to set in the memory range.
 * @return Returns a pointer to the end of the memory range.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_set(void *self, eya_uchar_t value);

/**
 * @brief Sets a single byte at a specified offset in a memory range
 * @param self Pointer to the memory range structure
 * @param offset Offset from the start of the memory range
 * @param reversed If true, offset is calculated from the end of the range
 * @param value The byte value to set at the specified offset
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if offset is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_set_value(void *self, eya_uoffset_t offset, bool reversed, eya_uchar_t value);

/**
 * @brief Copy data from external range to this memory range
 * @param self Pointer to destination memory range
 * @param begin Start of source data range
 * @param end End of source data range (exclusive)
 * @return Pointer to end of copied data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_copy_range(void *self, const void *begin, const void *end);

/**
 * @brief Fills a memory range with a repeating pattern from a pointer range.
 * @param self Destination memory range to fill with pattern
 * @param begin Start of pattern source range (inclusive)
 * @param end End of pattern source range (exclusive)
 * @return Pointer to the end of filled data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 *
 * @note The pattern will be repeated as needed to fill the entire destination range
 * @note Uses eya_memory_raw_set_pattern internally after range unpacking
 * @warning If source range is empty (begin == end), no operation is performed
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_set_pattern_range(void *self, const void *begin, const void *end);

/**
 * @brief Fills a memory range with a repeating pattern from another memory range.
 * @param self Destination memory range to fill with pattern
 * @param other Source memory range containing the pattern to repeat
 * @return Pointer to the end of filled data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 *
 * @note The entire source range is treated as the pattern to repeat
 * @note Internally calls eya_memory_range_set_pattern_range after unpacking ranges
 *
 * @warning If source range is empty, no operation is performed
 * @see eya_memory_range_set_pattern_range For version with explicit pointers
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_set_pattern(void *self, const eya_memory_range_t *other);

/**
 * @brief Copy data from another memory range to this memory range
 * @param self Pointer to destination memory range
 * @param other Pointer to source memory range
 * @return Pointer to end of copied data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_copy(void *self, const void *other);

/**
 * @brief Copies data from a pointer range to a memory range in reverse order.
 * @param self Destination memory range (will receive reversed copy)
 * @param begin Start of source memory range (inclusive)
 * @param end End of source memory range (exclusive)
 * @return Pointer to the beginning of the destination range.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_copy_rev_range(void *self, const void *begin, const void *end);

/**
 * @brief Copies data between two memory ranges in reverse order.
 * @param self Destination memory range (will receive reversed copy)
 * @param other Source memory range to copy from
 * @return Pointer to the beginning of the destination range.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_copy_rev(void *self, const void *other);

/**
 * @brief Copy data from external range to this memory range in reverse order
 * @param self Pointer to destination memory range
 * @param begin Start of source data range
 * @param end End of source data range (exclusive)
 * @return Pointer to end of copied data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_rcopy_range(void *self, const void *begin, const void *end);

/**
 * @brief Copy data from another memory range to this memory range in reverse order
 * @param self Pointer to destination memory range
 * @param other Pointer to source memory range
 * @return Pointer to end of copied data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_rcopy(void *self, const void *other);

/**
 * @brief Move data from external range to this memory range
 * @param self Pointer to destination memory range
 * @param begin Start of source data range
 * @param end End of source data range (exclusive)
 * @return Pointer to end of moved data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 *
 * @note Source and destination ranges may overlap
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_move_range(void *self, const void *begin, const void *end);

/**
 * @brief Move data from another memory range to this memory range
 * @param self Pointer to destination memory range
 * @param other Pointer to source memory range
 * @return Pointer to end of moved data in destination range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 *
 * @note Source and destination ranges may overlap
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_move(void *self, const void *other);

/**
 * @brief Find first occurrence of a subrange within memory range
 * @param[in] self Pointer to memory range to search in
 * @param[in] begin Start of subrange to find
 * @param[in] end End of subrange to find (exclusive)
 * @return Pointer to first occurrence or nullptr if not found
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_find_range(const void *self, const void *begin, const void *end);

/**
 * @brief Find first occurrence of another memory range within this range
 * @param[in] self Pointer to memory range to search in
 * @param[in] other Pointer to memory range to find
 * @return Pointer to first occurrence or nullptr if not found
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_find(const void *self, const void *other);

/**
 * @brief Find last occurrence of a subrange within memory range
 * @param[in] self Pointer to memory range to search in
 * @param[in] begin Start of subrange to find
 * @param[in] end End of subrange to find (exclusive)
 * @return Pointer to last occurrence or nullptr if not found
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rfind_range(const void *self, const void *begin, const void *end);

/**
 * @brief Find last occurrence of another memory range within this range
 * @param[in] self Pointer to memory range to search in
 * @param[in] other Pointer to memory range to find
 * @return Pointer to last occurrence or nullptr if not found
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rfind(const void *self, const void *other);

/**
 * @brief Compare memory range with a subrange
 * @param[in] self Pointer to first memory range
 * @param[in] begin Start of subrange to compare
 * @param[in] end End of subrange to compare (exclusive)
 * @return Pointer to first difference or nullptr if ranges are equal
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_compare_range(const void *self, const void *begin, const void *end);

/**
 * @brief Compare two memory ranges
 * @param[in] self Pointer to first memory range
 * @param[in] other Pointer to second memory range
 * @return Pointer to first difference or nullptr if ranges are equal
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_compare(const void *self, const void *other);

/**
 * @brief Compare memory range with a subrange in reverse order
 * @param[in] self Pointer to first memory range
 * @param[in] begin Start of subrange to compare
 * @param[in] end End of subrange to compare (exclusive)
 * @return Pointer to last difference or nullptr if ranges are equal
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rcompare_range(const void *self, const void *begin, const void *end);

/**
 * @brief Compare two memory ranges in reverse order
 * @param[in] self Pointer to first memory range
 * @param[in] other Pointer to second memory range
 * @return Pointer to last difference or nullptr if ranges are equal
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE
 *         if range is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rcompare(const void *self, const void *other);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_RANGE_H