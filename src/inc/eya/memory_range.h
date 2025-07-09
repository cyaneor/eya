/**
 * @file memory_range.h
 * @brief Header defining a mutable memory range structure and associated operations.
 *
 * This header provides the `eya_memory_range_t` structure and a set of functions
 * for working with mutable memory ranges. A memory range represents a contiguous
 * block of memory that can be modified, with bounds checking and safe access patterns.
 *
 * Key features:
 * - Mutable memory range representation ([begin, end) convention)
 * - Safe pointer access with bounds checking
 * - Convenience functions for common access patterns
 * - Validation support for range integrity
 *
 * The memory range follows the standard C++ convention where:
 * - begin points to the first element
 * - end points one past the last element
 * - Empty ranges have begin == end
 *
 * @note All functions perform implicit validation when accessing the memory range.
 * @note For immutable memory views, see eya_memory_view_t.
 */

#ifndef EYA_MEMORY_RANGE_H
#define EYA_MEMORY_RANGE_H

#include "memory_view_fields.h"
#include "attribute.h"
#include "offset.h"
#include "bool.h"

/**
 * @struct eya_memory_range
 * @brief A structure representing a mutable memory range.
 *
 * This struct defines a mutable view of a memory segment,
 * specified by pointers to the beginning and end of the memory region.
 * Unlike eya_memory_view_t, this structure allows modification of the memory contents.
 *
 * The memory range is defined as [begin, end) - inclusive of begin but exclusive of end.
 *
 * @see eya_memory_view_fields(T)
 * @see eya_memory_view_t
 */
typedef struct eya_memory_range
{
    eya_memory_view_fields(void);
} eya_memory_range_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Unpacks a memory range into individual begin and end pointers.
 *
 * This function safely extracts the begin and end pointers from an eya_memory_range_t object.
 * Either output parameter can be NULL if that value isn't needed.
 *
 * @param[in] self Pointer to the memory range object to unpack.
 *                 Must not be NULL (checked by eya_runtime_check_ref).
 * @param[out] begin Optional output parameter for the start of the memory range.
 *                   If non-NULL, will receive the begin pointer value.
 * @param[out] end Optional output parameter for the end of the memory range.
 *                 If non-NULL, will receive the end pointer value.
 *
 * @note The function performs a runtime reference check on the input parameter.
 * @note The memory range follows the [begin, end) convention (inclusive start, exclusive end).
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * void *begin_ptr, *end_ptr;
 * eya_memory_range_unpack(&range, &begin_ptr, &end_ptr);
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_unpack(const eya_memory_range_t *self, void **begin, void **end);

/**
 * @brief Gets the beginning pointer of a memory range.
 *
 * @param[in] self Pointer to the memory range object.
 *                 Must not be NULL (checked internally by eya_memory_range_unpack).
 * @return void* Pointer to the start of the memory range.
 *
 * @note This is a convenience wrapper around eya_memory_range_unpack() that only retrieves
 *       the begin pointer.
 * @note The memory range follows the [begin, end) convention (inclusive start, exclusive end).
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * void *data_start = eya_memory_range_get_begin(&range);
 * @endcode
 *
 * @see eya_memory_range_unpack()
 * @see eya_memory_range_get_end()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_get_begin(const eya_memory_range_t *self);

/**
 * @brief Gets the end pointer of a memory range (exclusive boundary).
 *
 * Retrieves the pointer that points one past the last element in the memory range,
 * conforming to the standard [begin, end) range convention.
 *
 * @param[in] self Pointer to the memory range object.
 *                 Must not be NULL (checked internally by eya_memory_range_unpack).
 * @return void* Pointer to the exclusive end of the memory range.
 *
 * @note This is a convenience wrapper around eya_memory_range_unpack() that only retrieves
 *       the end pointer.
 * @note The end pointer is exclusive - it points one element past the last valid element.
 * @note For an empty range, begin == end.
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * void *data_end = eya_memory_range_get_end(&range);
 * size_t data_size = (char*)data_end - (char*)eya_memory_range_get_begin(&range);
 * @endcode
 *
 * @see eya_memory_range_unpack()
 * @see eya_memory_range_get_begin()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_get_end(const eya_memory_range_t *self);

/**
 * @brief Validates and unpacks a memory range into begin/end pointers.
 *
 * This function performs validation on the memory range before unpacking it.
 * It first casts the range to a memory view and checks its validity before
 * proceeding with the standard unpack operation.
 *
 * @param[in] self Pointer to the memory range object to unpack and validate.
 * @param[out] begin Optional output parameter for the start of the memory range.
 *                   If non-NULL, will receive the begin pointer value.
 * @param[out] end Optional output parameter for the end of the memory range.
 *                 If non-NULL, will receive the end pointer value.
 *
 * @note This is the validated version of eya_memory_range_unpack().
 * @note The memory range follows the [begin, end) convention (inclusive start, exclusive end).
 * @note Performs both reference check (via eya_memory_range_unpack) and validity check.
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * void *begin, *end;
 * eya_memory_range_unpack_v(&range, &begin, &end); // Validates range first
 * @endcode
 *
 * @see eya_memory_range_unpack()
 * @see eya_memory_view_is_valid()
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_range_unpack_v(const eya_memory_range_t *self, void **begin, void **end);

/**
 * @brief Gets a pointer to an element at a specified offset from the beginning of the memory range.
 *
 * This function calculates a pointer to an element located at the given offset from the start
 * of the memory range, with bounds checking performed by the underlying memory view.
 *
 * @param[in] self Pointer to the memory range object. Must be a valid memory range.
 * @param[in] offset Byte offset from the beginning of the range.
 * @return void* Pointer to the element at the specified offset, or NULL if out of bounds.
 *
 * @note The offset is in bytes from the start of the range.
 * @note This function performs implicit validation through eya_memory_view_at_begin().
 * @note For type-safe access, consider using a typed wrapper function.
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * void *element = eya_memory_range_at_begin(&range, sizeof(MyType) * 2); // Gets third element
 * if (element) {
 *     // Safe to use the pointer
 * }
 * @endcode
 *
 * @see eya_memory_view_at_begin()
 * @see eya_memory_range_at_end()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_begin(const eya_memory_range_t *self, eya_uoffset_t offset);

/**
 * @brief Gets a pointer to an element at a specified offset from the end of the memory range.
 *
 * This function calculates a pointer to an element located at the given offset before
 * the exclusive end of the memory range, with bounds checking performed by the underlying memory
 * view.
 *
 * @param[in] self Pointer to the memory range object. Must be a valid memory range.
 * @param[in] offset Byte offset from the end of the range (positive value moves backward from end).
 * @return void* Pointer to the element at the specified offset from end, or NULL if out of bounds.
 *
 * @note The offset is in bytes from the end of the range (positive values move backward).
 * @note This is useful for getting elements relative to the end of the range.
 * @note Performs implicit validation through eya_memory_view_at_end().
 * @note For type-safe access, consider using a typed wrapper function.
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * // Get pointer to last element (offset 0 from end)
 * void *last = eya_memory_range_at_end(&range, 0);
 * // Get pointer to second-to-last element (offset sizeof(MyType) from end)
 * void *second_last = eya_memory_range_at_end(&range, sizeof(MyType));
 * @endcode
 *
 * @see eya_memory_view_at_end()
 * @see eya_memory_range_at_begin()
 * @see eya_memory_range_back()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_end(const eya_memory_range_t *self, eya_uoffset_t offset);

/**
 * @brief Gets a pointer to an element at a specified offset, optionally from the end.
 *
 * This function provides unified access to elements either from the beginning or end
 * of the memory range, with bounds checking performed by the underlying memory view.
 *
 * @param[in] self Pointer to the memory range object. Must be a valid memory range.
 * @param[in] offset Byte offset from either start or end of the range.
 * @param[in] reversed If true, offset is from end of range; if false, from beginning.
 * @return void* Pointer to the element at specified offset, or NULL if out of bounds.
 *
 * @note When reversed=true:
 *       - Offset is from the exclusive end (positive values move backward)
 *       - Equivalent to eya_memory_range_at_end(self, offset)
 * @note When reversed=false:
 *       - Offset is from the inclusive beginning
 *       - Equivalent to eya_memory_range_at_begin(self, offset)
 * @note The offset is always in bytes.
 * @note Performs implicit validation through eya_memory_view_at().
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 *
 * // Get third element from start
 * void *elem1 = eya_memory_range_at(&range, 2 * sizeof(MyType), false);
 *
 * // Get second element from end
 * void *elem2 = eya_memory_range_at(&range, 1 * sizeof(MyType), true);
 * @endcode
 *
 * @see eya_memory_view_at()
 * @see eya_memory_range_at_begin()
 * @see eya_memory_range_at_end()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at(const eya_memory_range_t *self, eya_uoffset_t offset, bool reversed);

/**
 * @brief Gets a pointer to the first element in the memory range.
 *
 * This is a convenience function that returns the beginning of the range,
 * equivalent to accessing with zero offset from start.
 *
 * @param[in] self Pointer to the memory range object. Must be a valid memory range.
 * @return void* Pointer to the first element, or NULL if range is empty.
 *
 * @note For empty ranges, returns NULL.
 * @note Performs implicit validation through eya_memory_view_at_first().
 * @note Equivalent to eya_memory_range_at_begin(self, 0) but more readable.
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * void *first_element = eya_memory_range_at_first(&range);
 * if (first_element) {
 *     // Safe to use the pointer
 * }
 * @endcode
 *
 * @see eya_memory_view_at_first()
 * @see eya_memory_range_at_begin()
 * @see eya_memory_range_at_last()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_first(const void *self);

/**
 * @brief Gets a pointer to the last element in the memory range.
 *
 * This is a convenience function that returns the last valid element,
 * equivalent to accessing with zero offset from end.
 *
 * @param[in] self Pointer to the memory range object. Must be a valid memory range.
 * @return void* Pointer to the last element, or NULL if range is empty.
 *
 * @note For empty ranges, returns NULL.
 * @note Performs implicit validation through eya_memory_view_at_last().
 * @note Equivalent to eya_memory_range_at_end(self, 0) but more readable.
 *
 * Example usage:
 * @code
 * eya_memory_range_t range = ...;
 * void *last_element = eya_memory_range_at_last(&range);
 * if (last_element) {
 *     // Safe to use the pointer
 * }
 * @endcode
 *
 * @see eya_memory_view_at_last()
 * @see eya_memory_range_at_end()
 * @see eya_memory_range_at_first()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_range_at_last(const void *self);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_RANGE_H
