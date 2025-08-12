#ifndef EYA_ARRAY_H
#define EYA_ARRAY_H

#include "allocated_array.h"
#include "array_fields.h"
#include "config.h"

/**
 * @def EYA_ARRAY_OPTIMIZE_RESIZE
 * @brief Configuration option for array resize optimization behavior
 *
 * This macro controls whether array resizing operations should be optimized
 * to only occur when necessary. The optimization prevents unnecessary memory
 * reallocations when the new size would fit within the current capacity.
 *
 * @note Default value is EYA_CONFIG_ON if not previously defined.
 * @see eya_array_resize() where this option is implemented
 *
 * @value EYA_CONFIG_ON  Enable resize optimization (only resize when capacity exceeded)
 * @value EYA_CONFIG_OFF Disable optimization (resize on every call)
 *
 * @warning Disabling optimization (EYA_CONFIG_OFF) may impact performance
 *          due to frequent reallocations, but ensures minimal memory usage.
 */
#ifndef EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE
#    define EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE EYA_CONFIG_ON
#endif // EYA_LIBRARY_OPTION_ARRAY_OPTIMIZE_RESIZE

/**
 * @def EYA_ARRAY_DEFAULT_SHRINK_RATIO
 * @brief Default ratio used to determine when to shrink the array capacity
 *
 * This macro defines the default shrink ratio used by eya_array_shrink().
 * When the array size becomes less than or equal to the current capacity divided by this ratio,
 * the array will be shrunk to fit its current size.
 */
#ifndef EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO
#    define EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO 2
#endif // EYA_LIBRARY_OPTION_ARRAY_DEFAULT_SHRINK_RATIO

/**
 * @def EYA_ARRAY_DEFAULT_GROWTH_RATIO
 * @brief Default growth multiplier for array expansion (fixed-point, per mille)
 *
 * Defines the growth factor as a fixed-point value where 1000 = 1.0x (no growth).
 * A value of 1500 means the array will grow by 1.5x (1500/1000) of its current capacity.
 * Used in integer arithmetic to avoid floating-point operations in embedded systems.
 * Can be redefined before including the header file.
 */
#ifndef EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO
#    define EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO 1500
#endif // EYA_LIBRARY_OPTION_ARRAY_DEFAULT_GROWTH_RATIO

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
 * @param[in] self Pointer to the array object
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
 * @throws EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE
 *         If size exceeds maximum capacity
 * @throws EYA_RUNTIME_ERROR_ALLOCATION_FAILED
 *         If memory allocation fails
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_resize(void *self, eya_usize_t size);

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
eya_array_unpack(const void  *self,
                 void       **begin,
                 void       **end,
                 eya_usize_t *element_size,
                 eya_usize_t *size);

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
eya_array_get_size(const void *self);

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
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_full(const void *self);

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
eya_array_is_valid_index(const void *self, eya_usize_t index);

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
eya_array_at_from_front(const void *self, eya_usize_t index);

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
eya_array_at_from_back(const void *self, eya_usize_t index);

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
eya_array_at(const void *self, eya_usize_t index, bool reversed);

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
eya_array_front(const void *self);

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
eya_array_back(const void *self);

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
eya_array_is_empty(const void *self);

/**
 * @brief Clears the array (size=0)
 * @param[in,out] self Pointer to the array
 *
 * @throws EYA_RUNTIME_ERROR_NULL_POINTER
 *         If self is NULL
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_clear(void *self);

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
eya_array_get_begin(const void *self);

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
eya_array_get_total_size(const void *self);

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
eya_array_get_available_size(const void *self);

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
eya_array_get_end(const void *self);

/**
 * @brief Shrinks storage to fit current size
 * @param[in,out] self Pointer to the array
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
 * @param[in,out] self Pointer to the array
 * @param[in] size Number of additional elements needed
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