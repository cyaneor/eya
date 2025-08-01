#ifndef EYA_ARRAY_H
#define EYA_ARRAY_H

#include "allocated_array.h"
#include "array_fields.h"

/**
 * @struct eya_array
 * @brief Array of dynamically allocated arrays.
 *
 * This structure represents an array where each element
 * is itself a dynamically allocated array of type `eya_allocated_array_t`.
 *
 * It utilizes the `eya_array_fields` macro
 * to define the standard array fields:
 *
 * `data` (a pointer to the array of `eya_allocated_array_t` elements) and
 * `size` (the number of elements in the array).
 *
 * The structure is essentially a dynamic array of dynamic arrays,
 * allowing for flexible management of collections of `eya_allocated_array_t` structures.
 *
 * Example usage:
 * @code{.c}
 * eya_array_t my_array;
 * my_array.data = malloc(10 * sizeof(eya_allocated_array_t));
 * my_array.size = 10;
 * @endcode
 *
 * @see eya_array_fields for the definition of the `data` and `size` fields.
 * @see eya_allocated_array_t for the type of the array elements.
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
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_capacity(const void *self);

/**
 * @brief Resizes the array storage
 * @param self Pointer to the array object
 * @param size New element count
 * @note Increases capacity if needed, preserves existing elements
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_resize(void *self, eya_usize_t size);

/**
 * @brief Unpacks array metadata into provided pointers
 * @param self Pointer to the array object
 * @param[out] begin Pointer to store the start of data (can be nullptr)
 * @param[out] end Pointer to store the end of data (can be nullptr)
 * @param[out] element_size Pointer to store element size in bytes (can be nullptr)
 * @param[out] size Pointer to store element count (can be nullptr)
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_unpack(const void  *self,
                 void       **begin,
                 void       **end,
                 eya_usize_t *element_size,
                 eya_usize_t *size);

/**
 * @brief Gets the current number of elements in the array
 * @param self Pointer to the array object
 * @return Current element count
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_size(const void *self);

/**
 * @brief Checks if an index is valid for the array.
 *
 * This function verifies whether the given index is within the valid bounds
 * of the array (index is less than the array size).
 *
 * @param[in] self Pointer to the array.
 * @param[in] index Index to be validated.
 *
 * @return true if the index is valid (index < array size),
 * @return false if the index is out of bounds.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_valid_index(const void *self, eya_usize_t index);

/**
 * @brief Checks if the array is empty
 * @param self Pointer to the array object
 * @return true if array contains no elements, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_array_is_empty(const void *self);

/**
 * @brief Clears the array (sets size to 0 without deallocating memory)
 * @param self Pointer to the array object
 * @note Performs reference validity check
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_clear(void *self);

/**
 * @brief Gets pointer to the first element
 * @param self Pointer to the array object
 * @return Pointer to beginning of data storage
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_get_begin(const void *self);

/**
 * @brief Calculates total data size in bytes
 * @param self Pointer to the array object
 * @return Total size of all elements in bytes
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_total_size(const void *self);

/**
 * @brief Calculates available space for new elements
 * @param self Pointer to the array object
 * @return Available capacity in bytes
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_array_get_available_size(const void *self);

/**
 * @brief Gets pointer to the end of used storage
 * @param self Pointer to the array object
 * @return Pointer to the first byte after last element
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_array_get_end(const void *self);

/**
 * @brief Shrinks storage if utilization is below threshold
 * @param self Pointer to the array object
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_shrink(void *self);

/**
 * @brief Ensures capacity for additional elements
 * @param self Pointer to the array object
 * @param size Number of additional elements to accommodate
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_array_reserve(void *self, eya_usize_t size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_ARRAY_H
