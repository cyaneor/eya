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
 * @typedef eya_memory_typed_t
 * @brief Represents a typed memory range with element size information.
 *
 * This structure extends the basic memory range (eya_memory_range_t) by adding
 * information about the size of individual elements stored in the memory block.
 * This enables type-aware operations on the memory range.
 *
 * @note The structure is valid only when:
 *       - The underlying range is valid (begin <= end, non-NULL)
 *       - element_size > 0
 *       - (end - begin) is divisible by element_size
 */
typedef struct eya_memory_typed
{
    eya_memory_typed_fields(eya_memory_range_t);
} eya_memory_typed_t;

/**
 * @brief Gets a mutable memory range from a typed memory object.
 *
 * This function performs a type cast to convert a typed memory pointer
 * into a generic memory range structure pointer. The returned range
 * provides access to the raw memory region with begin/end pointers.
 *
 * @param self Pointer to the typed memory object to convert.
 * @return Pointer to the generic memory range structure (mutable version).
 *
 * @see eya_memory_range_t
 * @see eya_ptr_cast
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_range_t *
eya_memory_typed_get_range(eya_memory_typed_t *self);

/**
 * @brief Gets a const memory range from a typed memory object.
 *
 * This function performs a type cast to convert a const typed memory pointer
 * into a const generic memory range structure pointer. The returned range
 * provides read-only access to the raw memory region with begin/end pointers.
 *
 * @param self Pointer to the const typed memory object to convert.
 * @return Pointer to the generic memory range structure (const version).
 *
 * @see eya_memory_range_t
 * @see eya_ptr_cast
 */
EYA_ATTRIBUTE(SYMBOL)
const eya_memory_range_t *
eya_memory_typed_get_crange(const eya_memory_typed_t *self);

/**
 * @brief Unpack a typed memory range into its components
 * @param self Pointer to typed memory range structure
 * @param begin [out] Pointer to store begin address (can be NULL)
 * @param end [out] Pointer to store end address (can be NULL)
 * @param element_size [out] Pointer to store element size (can be NULL)
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_unpack(const eya_memory_typed_t *self,
                        void                    **begin,
                        void                    **end,
                        eya_usize_t              *element_size);

/**
 * @brief Get the element size of a typed memory range
 * @param self Pointer to typed memory range structure
 * @return Size of individual elements in bytes
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_typed_get_element_size(const eya_memory_typed_t *self);

/**
 * @brief Check if a typed memory range is valid
 * @param self Pointer to typed memory range structure
 * @return true if valid (memory range is multiple of element size), false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_valid(const eya_memory_typed_t *self);

/**
 * @brief Get the number of elements in a typed memory range
 * @param self Pointer to typed memory range structure
 * @return Number of elements in the range
 * @note Asserts if the range size isn't a multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_typed_get_size(const eya_memory_typed_t *self);

/**
 * @brief Check if a typed memory range is empty
 * @param self Pointer to typed memory range structure
 * @return true if empty (contains 0 elements), false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_empty(const eya_memory_typed_t *self);

/**
 * @brief Swap contents of two typed memory ranges
 * @param self First typed memory range
 * @param other Second typed memory range
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_swap(eya_memory_typed_t *self, eya_memory_typed_t *other);

/**
 * @brief Exchange contents of two typed memory ranges
 * @param self First typed memory range
 * @param other Second typed memory range
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_exchange(eya_memory_typed_t *self, eya_memory_typed_t *other);

/**
 * @brief Check if index is valid for a typed memory range
 * @param self Pointer to typed memory range structure
 * @param index Index to check
 * @return true if index is valid, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid_index(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get byte offset for a given element index
 * @param self Pointer to typed memory range structure
 * @param index Element index
 * @return Byte offset from start of range
 */
EYA_ATTRIBUTE(SYMBOL)
eya_uoffset_t
eya_memory_typed_get_offset_by_index(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index (front-to-back order)
 * @param self Pointer to typed memory range structure
 * @param index Element index
 * @return Pointer to element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_at_from_front(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index (back-to-front order)
 * @param self Pointer to typed memory range structure
 * @param index Reverse element index
 * @return Pointer to element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_at_from_back(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index with direction control
 * @param self Pointer to typed memory range structure
 * @param index Element index
 * @param reversed If true, uses back-to-front indexing
 * @return Pointer to element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_at(const eya_memory_typed_t *self, eya_usize_t index, bool reversed);

/**
 * @brief Get pointer to first element in range
 * @param self Pointer to typed memory range structure
 * @return Pointer to first element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_front(const eya_memory_typed_t *self);

/**
 * @brief Get pointer to last element in range
 * @param self Pointer to typed memory range structure
 * @return Pointer to last element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_back(const eya_memory_typed_t *self);

/**
 * @brief Check if element size matches given value
 * @param self Pointer to typed memory range structure
 * @param element_size Size to compare against
 * @return true if sizes match, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal_element_size_to(const eya_memory_typed_t *self, eya_usize_t element_size);

/**
 * @brief Check if two typed memory ranges have equal element sizes
 * @param self First typed memory range
 * @param other Second typed memory range
 * @return true if element sizes match, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal_element_size(const eya_memory_typed_t *self,
                                       const eya_memory_typed_t *other);

/**
 * @brief Check if two typed memory ranges are equal
 * @param self First typed memory range
 * @param other Second typed memory range
 * @return true if both ranges have same element size and memory contents, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal(const eya_memory_typed_t *self, const eya_memory_typed_t *other);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_TYPED_H
