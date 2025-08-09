#ifndef EYA_ARRAY_H
#define EYA_ARRAY_H

#include "allocated_array.h"
#include "array_fields.h"

/**
 * @struct eya_array
 * @brief Dynamic array structure with size tracking
 *
 * Combines allocated array storage with current size information.
 * Provides safe element access and automatic growth.
 *
 * @invariant size <= capacity (where capacity = allocated elements)
 * @see eya_array_fields for field definitions
 */
typedef struct eya_array
{
    eya_array_fields(eya_allocated_array_t);
} eya_array_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Gets current storage capacity in elements
 * @param self Pointer to the array object
 * @return Maximum elements that can be stored without reallocation
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_capacity(const void *self);

/**
 * @brief Resizes a dynamic array
 *
 * @param self Pointer to the array
 * @param size New size of the array
 *
 * @details Behavior depends on EYA_ARRAY_OPTIMIZE_RESIZE:
 * - If EYA_ARRAY_OPTIMIZE_RESIZE == 1 (default), reallocation only occurs
 *   when the new size exceeds the array's current capacity.
 * - If EYA_ARRAY_OPTIMIZE_RESIZE == 0, reallocation occurs on every call.
 *
 * In all cases, the array's size field will be updated to the specified value.
 *
 * @see eya_allocated_array_resize
 * @see eya_array_capacity
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_resize(void *self, eya_usize_t size);

/**
 * @brief Unpacks array metadata into provided pointers
 * @param self Pointer to the array object
 * @param[out] begin Pointer to store the start of data
 * @param[out] end Pointer to store the end of data
 * @param[out] element_size Pointer to store element size
 * @param[out] size Pointer to store element count
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_unpack(const void  *self,
                 void       **begin,
                 void       **end,
                 eya_usize_t *element_size,
                 eya_usize_t *size);

/**
 * @brief Gets the current number of elements
 * @param self Pointer to the array object
 * @return Current element count
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_size(const void *self);

/**
 * @brief Checks if an index is valid
 * @param self Pointer to the array
 * @param index Index to validate
 * @return true if index is valid, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_valid_index(const void *self, eya_usize_t index);

/**
 * @brief Gets element pointer from front
 * @param self Pointer to the array
 * @param index Front-based index
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_at_from_front(void *self, eya_usize_t index);

/**
 * @brief Gets element pointer from back
 * @param self Pointer to the array
 * @param index Back-based index
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_at_from_back(void *self, eya_usize_t index);

/**
 * @brief Gets element pointer with direction control
 * @param self Pointer to the array
 * @param index Element index
 * @param reversed If true, indexes from back
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_at(void *self, eya_usize_t index, bool reversed);

/**
 * @brief Checks if array is empty
 * @param self Pointer to the array
 * @return true if empty, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_empty(const void *self);

/**
 * @brief Clears the array (size=0)
 * @param self Pointer to the array
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_clear(void *self);

/**
 * @brief Gets pointer to first element
 * @param self Pointer to the array
 * @return Pointer to first element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_get_begin(const void *self);

/**
 * @brief Calculates total used size in bytes
 * @param self Pointer to the array
 * @return Total size in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_total_size(const void *self);

/**
 * @brief Gets remaining capacity in bytes
 * @param self Pointer to the array
 * @return Available capacity in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_available_size(const void *self);

/**
 * @brief Gets pointer to end of used storage
 * @param self Pointer to the array
 * @return Pointer to end of data
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_get_end(const void *self);

/**
 * @brief Shrinks storage to fit current size
 * @param self Pointer to the array
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ALLOCATION_FAILED
 *         If reallocation fails
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_shrink(void *self);

/**
 * @brief Ensures capacity for additional elements
 * @param self Pointer to the array
 * @param size Number of additional elements needed
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE
 *         If requested size exceeds maximum
 * @throws EYA_RUNTIME_ERROR_ALLOCATION_FAILED
 *         If allocation fails
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_reserve(void *self, eya_usize_t size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_ARRAY_H