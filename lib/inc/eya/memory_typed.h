/**
 * @file memory_typed.h
 * @brief Typed memory range operations and utilities
 *
 * This header defines the `eya_memory_typed_t` structure and associated operations
 * for working with typed memory ranges. The structure combines standard memory range
 * semantics with element size information, enabling type-safe operations on memory blocks.
 */

#ifndef EYA_MEMORY_TYPED_H
#define EYA_MEMORY_TYPED_H

#include "memory_typed_fields.h"
#include "memory_range.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @struct eya_memory_typed
 * @brief Represents a typed memory range with element size information.
 *
 * This structure extends the basic memory range (eya_memory_range_t) by adding
 * information about the size of individual elements stored in the memory block.
 * This enables type-aware operations on the memory range.
 *
 * @note The structure is valid only when:
 *       - The underlying range is valid (begin <= end, non-nullptr)
 *       - element_size > 0
 *       - (end - begin) is divisible by element_size
 */
typedef struct eya_memory_typed
{
    eya_memory_typed_fields(eya_memory_range_t);
} eya_memory_typed_t;

/**
 * @brief Unpack a typed memory range into its components
 * @param self Pointer to typed memory range structure
 * @param begin [out] Pointer to store begin address (can be nullptr)
 * @param end [out] Pointer to store end address (can be nullptr)
 * @param element_size [out] Pointer to store element size (can be nullptr)
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_unpack(const void *self, void **begin, void **end, eya_usize_t *element_size);

/**
 * @brief Get the element size of a typed memory range
 * @param self Pointer to typed memory range structure
 * @return Size of individual elements in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_typed_get_element_size(const void *self);

/**
 * @brief Check if a typed memory range is valid
 * @param self Pointer to typed memory range structure
 * @return true if valid (memory range is multiple of element size), false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_valid(const void *self);

/**
 * @brief Get the number of elements in a typed memory range
 * @param self Pointer to typed memory range structure
 * @return Number of elements in the range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_typed_get_size(const void *self);

/**
 * @brief Check if a typed memory range is empty
 * @param self Pointer to typed memory range structure
 * @return true if empty (contains 0 elements), false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_empty(const void *self);

/**
 * @brief Swap contents of two typed memory ranges
 * @param self First typed memory range
 * @param other Second typed memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE
 *         if element sizes don't match
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_swap(void *self, void *other);

/**
 * @brief Exchange contents of two typed memory ranges
 * @param self First typed memory range
 * @param other Second typed memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE
 *         if element sizes don't match
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_exchange(void *self, void *other);

/**
 * @brief Check if index is valid for a typed memory range
 * @param self Pointer to typed memory range structure
 * @param index Index to check
 * @return true if index is valid, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid_index(const void *self, eya_usize_t index);

/**
 * @brief Get byte offset for a given element index
 * @param self Pointer to typed memory range structure
 * @param index Element index
 * @return Byte offset from start of range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
eya_uoffset_t
eya_memory_typed_get_offset_by_index(const void *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index (front-to-back order)
 * @param self Pointer to typed memory range structure
 * @param index Element index
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_at_from_front(void *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index (back-to-front order)
 * @param self Pointer to typed memory range structure
 * @param index Reverse element index
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_at_from_back(void *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index with direction control
 * @param self Pointer to typed memory range structure
 * @param index Element index
 * @param reversed If true, uses back-to-front indexing
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         if index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_at(void *self, eya_usize_t index, bool reversed);

/**
 * @brief Get pointer to first element in range
 * @param self Pointer to typed memory range structure
 * @return Pointer to first element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_front(void *self);

/**
 * @brief Get pointer to last element in range
 * @param self Pointer to typed memory range structure
 * @return Pointer to last element
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_back(void *self);

/**
 * @brief Check if element size matches given value
 * @param self Pointer to typed memory range structure
 * @param element_size Size to compare against
 * @return true if sizes match, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal_element_size_to(const void *self, eya_usize_t element_size);

/**
 * @brief Check if two typed memory ranges have equal element sizes
 * @param self First typed memory range
 * @param other Second typed memory range
 * @return true if element sizes match, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal_element_size(const void *self, const void *other);

/**
 * @brief Check if two typed memory ranges are equal
 * @param self First typed memory range
 * @param other Second typed memory range
 * @return true if both ranges have same element size and memory contents, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal(const void *self, const void *other);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_TYPED_H