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
 * @param[in] self Pointer to typed memory range structure
 * @param[out] begin Pointer to store begin address (can be nullptr)
 * @param[out] end Pointer to store end address (can be nullptr)
 * @param[out] element_size Pointer to store element size (can be nullptr)
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_unpack_full(const eya_memory_typed_t *self,
                             void                    **begin,
                             void                    **end,
                             eya_usize_t              *element_size);

/**
 * @brief Unpack a typed memory range into its components
 * @param[in] self Pointer to typed memory range structure
 * @param[out] range Pointer to store memory range with begin and end addresses (can be nullptr)
 * @param[out] element_size Pointer to store element size (can be nullptr)
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_unpack(const eya_memory_typed_t *self,
                        eya_memory_range_t       *range,
                        eya_usize_t              *element_size);

/**
 * @brief Get the element size of a typed memory range
 * @param[in] self Pointer to typed memory range structure
 * @return Size of individual elements in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_typed_get_element_size(const eya_memory_typed_t *self);

/**
 * @brief Check if a typed memory range is valid
 * @param[in] self Pointer to typed memory range structure
 * @return true if valid (memory range is multiple of element size), false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_valid(const eya_memory_typed_t *self);

/**
 * @brief Get the number of elements in a typed memory range
 * @param[in] self Pointer to typed memory range structure
 * @return Number of elements in the range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_typed_get_size(const eya_memory_typed_t *self);

/**
 * @brief Check if a typed memory range is empty
 * @param[in] self Pointer to typed memory range structure
 * @return true if empty (contains 0 elements), false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_empty(const eya_memory_typed_t *self);

/**
 * @brief Swap contents of two typed memory ranges
 * @param[in,out] self First typed memory range
 * @param[in,out] other Second typed memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE
 *         if element sizes don't match
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_swap(eya_memory_typed_t *self, eya_memory_typed_t *other);

/**
 * @brief Exchange two typed memory (clear self and swap)
 * @param[in,out] self First typed memory range
 * @param[in,out] other Second typed memory range
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 * @throws EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE
 *         if element sizes don't match
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_typed_exchange(eya_memory_typed_t *self, eya_memory_typed_t *other);

/**
 * @brief Check if index is valid for a typed memory range
 * @param[in] self Pointer to typed memory range structure
 * @param[in] index Index to check
 * @return true if index is valid, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid_index(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get byte offset for a given element index
 * @param[in] self Pointer to typed memory range structure
 * @param[in] index Element index
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
eya_memory_typed_get_offset_by_index(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index (front-to-back order)
 * @param[in] self Pointer to typed memory range structure
 * @param[in] index Element index
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
eya_memory_typed_at_from_front(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index (back-to-front order)
 * @param[in] self Pointer to typed memory range structure
 * @param[in] index Reverse element index
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
eya_memory_typed_at_from_back(const eya_memory_typed_t *self, eya_usize_t index);

/**
 * @brief Get pointer to element at index with direction control
 * @param[in] self Pointer to typed memory range structure
 * @param[in] index Element index
 * @param[in] reversed If true, uses back-to-front indexing
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
eya_memory_typed_at(const eya_memory_typed_t *self, eya_usize_t index, bool reversed);

/**
 * @brief Get pointer to first element in range
 * @param[in] self Pointer to typed memory range structure
 * @return Pointer to first element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_front(eya_memory_typed_t *self);

/**
 * @brief Get pointer to last element in range
 * @param[in] self Pointer to typed memory range structure
 * @return Pointer to last element
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 * @throws EYA_RUNTIME_ERROR_SIZE_NOT_MULTIPLE_OF_ELEMENT_SIZE
 *         if range size isn't multiple of element size
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_typed_back(eya_memory_typed_t *self);

/**
 * @brief Check if element size matches given value
 * @param[in] self Pointer to typed memory range structure
 * @param[in] element_size Size to compare against
 * @return true if sizes match, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal_element_size_to(const eya_memory_typed_t *self, eya_usize_t element_size);

/**
 * @brief Check if two typed memory ranges have equal element sizes
 * @param[in] self First typed memory range
 * @param[in] other Second typed memory range
 * @return true if element sizes match, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal_element_size(const eya_memory_typed_t *self,
                                       const eya_memory_typed_t *other);

/**
 * @brief Check if two typed memory ranges are equal
 * @param[in] self First typed memory range
 * @param[in] other Second typed memory range
 * @return true if both ranges have same element size and memory contents, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         if self or other is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_typed_is_equal(const eya_memory_typed_t *self, const eya_memory_typed_t *other);

/**
 * @brief Creates a typed memory block with specified parameters.
 *
 * @param[in] begin Pointer to the start of the memory block.
 * @param[in] end Pointer to the end of the memory block (exclusive).
 * @param[in] element_size Size of a single element in bytes.
 *
 * @return Initialized `eya_memory_typed_t` structure representing the typed memory range.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_typed_t
eya_memory_typed_make(void *begin, void *end, eya_usize_t element_size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_TYPED_H