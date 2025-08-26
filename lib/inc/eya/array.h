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
 * @brief Unpacks array metadata into provided pointers
 * @param[in] self Pointer to the array object
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
eya_array_unpack(const eya_array_t *self,
                 void             **begin,
                 void             **end,
                 eya_usize_t       *element_size,
                 eya_usize_t       *size);

/**
 * @brief Gets current storage capacity in elements
 * @param[in] self Pointer to the array object
 * @return Maximum elements that can be stored without reallocation
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_capacity(const eya_array_t *self);

/**
 * @brief Gets the current number of elements
 * @param[in] self Pointer to the array object
 * @return Current element count
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_size(const eya_array_t *self);

/**
 * @brief Checks if the array has reached its capacity
 * @param[in] self Pointer to the array object
 * @return true if array is full (size == capacity), false otherwise
 *
 * @details This function compares the current size of the array with its capacity
 *          to determine if no more elements can be added without reallocation.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_full(const eya_array_t *self);

/**
 * @brief Checks if an index is valid
 * @param[in] self Pointer to the array
 * @param[in] index Index to validate
 * @return true if index is valid, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_valid_index(const eya_array_t *self, eya_usize_t index);

/**
 * @brief Gets element pointer from front
 * @param[in] self Pointer to the array
 * @param[in] index Front-based index
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_at_from_front(const eya_array_t *self, eya_usize_t index);

/**
 * @brief Gets element pointer from back
 * @param[in] self Pointer to the array
 * @param[in] index Back-based index
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_at_from_back(const eya_array_t *self, eya_usize_t index);

/**
 * @brief Gets element pointer with direction control
 * @param[in] self Pointer to the array
 * @param[in] index Element index
 * @param[in] reversed If true, indexes from back
 * @return Pointer to element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If index is invalid
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_at(const eya_array_t *self, eya_usize_t index, bool reversed);

/**
 * @brief Gets pointer to the first element in the array
 * @param[in] self Pointer to the array object
 * @return Pointer to the first element
 *
 * @details This is a convenience wrapper around eya_array_at() that always
 *          returns the first element (index 0 from front).
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If array is empty
 *
 * @see eya_array_at
 * @see eya_array_back
 * @see eya_array_get_begin
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_front(const eya_array_t *self);

/**
 * @brief Gets pointer to the last element in the array
 * @param[in] self Pointer to the array object
 * @return Pointer to the last element
 *
 * @details This is a convenience wrapper around eya_array_at() that always
 *          returns the last element (index 0 from back).
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_OUT_OF_RANGE
 *         If array is empty
 *
 * @see eya_array_at
 * @see eya_array_front
 * @see eya_array_get_end
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_back(const eya_array_t *self);

/**
 * @brief Checks if array is empty
 * @param[in] self Pointer to the array
 * @return true if empty, false otherwise
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_empty(const eya_array_t *self);

/**
 * @brief Clears the array (size=0)
 * @param[in,out] self Pointer to the array
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_clear(eya_array_t *self);

/**
 * @brief Gets pointer to first element
 * @param[in] self Pointer to the array
 * @return Pointer to first element
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_get_begin(const eya_array_t *self);

/**
 * @brief Calculates total used size in bytes
 * @param[in] self Pointer to the array
 * @return Total size in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_total_size(const eya_array_t *self);

/**
 * @brief Gets remaining capacity in bytes
 * @param[in] self Pointer to the array
 * @return Available capacity in bytes
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_available_size(const eya_array_t *self);

/**
 * @brief Gets pointer to end of used storage
 * @param[in] self Pointer to the array
 * @return Pointer to end of data
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_get_end(const eya_array_t *self);

/**
 * @brief Shrinks storage to fit current size
 * @param[in,out] self Pointer to the array
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If reallocation fails
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's allocation function is not initialized
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_shrink(eya_array_t *self);

/**
 * @brief Ensures capacity for additional elements
 * @param[in,out] self Pointer to the array
 * @param[in] size Number of additional elements needed
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 * @throws EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE
 *         If requested size exceeds maximum
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If allocation fails
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's allocation function is not initialized
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_reserve(eya_array_t *self, eya_usize_t size);

/**
 * @brief Resizes a dynamic array
 *
 * @param[in,out] self Pointer to the array
 * @param[in] size New size of the array
 *
 * @details Behavior depends on EYA_ARRAY_OPTIMIZE_RESIZE:
 * - If EYA_ARRAY_OPTIMIZE_RESIZE == 1 (default), reallocation only occurs
 *   when the new size exceeds the array's current capacity.
 * - If EYA_ARRAY_OPTIMIZE_RESIZE == 0, reallocation occurs on every call.
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 * @throws EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE
 *         If size exceeds maximum capacity
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If memory allocation fails
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's allocation function is not initialized
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_resize(eya_array_t *self, eya_usize_t size);

/**
 * @brief Creates and initializes a new dynamic array with specified parameters.
 *
 * @param[in] element_size Size of each element in bytes.
 * @param[in] size Initial number of elements in the array.
 *
 * @return Initialized `eya_array_t` structure with requested capacity.
 *
 * @throws EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE
 *         If requested size exceeds system limits
 * @throws EYA_RUNTIME_ERROR_MEMORY_NOT_ALLOCATED
 *         If memory allocation fails
 * @throws EYA_RUNTIME_ERROR_ALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's allocation function is not initialized
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 */
EYA_ATTRIBUTE(SYMBOL)
eya_array_t
eya_array_make(eya_usize_t element_size, eya_usize_t size);

/**
 * @brief Frees the array's memory and resets its size to zero
 * @param[in,out] self Pointer to the array to be freed
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is nullptr
 * @throws EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE
 *         If element size is zero
 * @throws EYA_RUNTIME_ERROR_DEALLOCATOR_FUNCTION_NOT_INITIALIZED
 *         If allocator's deallocation function is not initialized during free
 *
 * @see eya_array_clear()
 * @see eya_array_resize()
 * @see eya_allocated_array_resize()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_free(eya_array_t *self);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_ARRAY_H