/**
 * @file memory_range_fields.h
 * @brief Definition of memory range field macros for contiguous memory regions.
 *
 * This header provides a macro for easily defining the standard fields needed
 * to represent a contiguous memory range in C/C++ structures.
 */

#ifndef EYA_MEMORY_RANGE_FIELDS_H
#define EYA_MEMORY_RANGE_FIELDS_H

/**
 * @def eya_memory_range_fields(T)
 * @brief Defines the fields for a memory range structure.
 *
 * This macro generates the standard fields for a memory range structure that
 * uses pointers to denote the beginning and end of a contiguous memory region.
 *
 * @tparam T The type of elements in the memory range.
 *
 * The generated structure contains:
 * - A pointer to the start of the memory region (inclusive)
 * - A pointer to the end of the memory region (exclusive)
 *
 * @note The end pointer points to one past the last valid element,
 *       following the standard C++ iterator convention.
 *
 * Example usage:
 * @code
 * struct IntRange {
 *     eya_memory_range_fields(int);
 * };
 * @endcode
 *
 * This would create a structure with int* begin and int* end members.
 */
#define eya_memory_range_fields(T)                                                                 \
    T *begin; /**< Pointer to the start of the memory region. */                                   \
    T *end    /**< Pointer to the end of the memory region (exclusive). */

#endif // EYA_MEMORY_RANGE_FIELDS_H
