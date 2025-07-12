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
 * @brief Checks if the memory range is uninitialized.
 *
 * Determines whether the memory range has been properly initialized
 * by checking if both begin and end pointers are NULL.
 *
 * @param self The memory range to check (may be NULL).
 * @return true if uninitialized (both pointers NULL), false otherwise.
 * @note An uninitialized range is different from an empty range.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_uninit(const eya_memory_range_t *self);

/**
 * @brief Checks if the memory range is empty.
 *
 * Verifies whether the memory range contains no data by checking
 * if the begin and end pointers are equal (but not NULL).
 *
 * @param self The memory range to check (must be valid if not NULL).
 * @return true if empty (begin equals end but not NULL), false otherwise.
 * @note An empty range is valid but contains no accessible data.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_empty(const eya_memory_range_t *self);

/**
 * @brief Checks if the memory range contains valid data.
 *
 * Determines whether the memory range contains accessible data
 * by verifying that the begin pointer is before the end pointer.
 *
 * @param self The memory range to check (must be valid if not NULL).
 * @return true if contains valid data (begin < end), false otherwise.
 * @note Returns false for both uninitialized and empty ranges.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_has_data(const eya_memory_range_t *self);

/**
 * @brief Checks if the memory range is in an invalid state.
 *
 * Comprehensive check for any invalid state, including:
 * - Uninitialized (both pointers NULL)
 * - Begin pointer greater than end pointer
 * - Other implementation-defined invalid states
 *
 * @param self The memory range to check (may be NULL).
 * @return true if invalid (uninitialized or any invalid state), false otherwise.
 * @note More thorough than just checking initialization status.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_invalid(const eya_memory_range_t *self);

/**
 * @brief Checks if the memory range is in a valid state.
 *
 * Verifies the memory range is either:
 * - Properly initialized and empty (begin == end != NULL)
 * - Contains valid data (begin < end)
 *
 * @param self The memory range to check (may be NULL).
 * @return true if valid (either empty or has data), false otherwise.
 * @note Complementary to eya_memory_range_is_invalid().
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_valid(const eya_memory_range_t *self);

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
 * @brief Gets the size in bytes of the memory range
 *
 * @param[in] self Pointer to the memory range object to examine
 * @return Size in bytes of the valid memory range
 *
 * @note This function internally casts the memory range
 *       to a memory view and calls eya_memory_view_get_size() on it.
 *
 * @see eya_memory_view_get_size()
 */
eya_usize_t
eya_memory_range_get_size(const eya_memory_range_t *self);

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

/**
 * @brief Checks if the memory range's begin pointer equals the given pointer.
 *
 * This function compares the start address
 * of the memory range with the provided pointer.
 *
 * @param self Pointer to the eya_memory_range_t structure to check (must be valid).
 * @param ptr Pointer to compare with the range's begin address.
 * @return true if the range's begin address matches ptr, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_begin_to(const eya_memory_range_t *self, const void *ptr);

/**
 * @brief Checks if the memory range's end pointer equals the given pointer.
 *
 * This function compares the end address (exclusive boundary)
 * of the memory range with the provided pointer.
 *
 * @param self Pointer to the eya_memory_range_t structure to check (must be valid).
 * @param ptr Pointer to compare with the range's end address.
 * @return true if the range's end address matches ptr, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_end_to(const eya_memory_range_t *self, const void *ptr);

/**
 * @brief Checks if two memory ranges share the same begin address.
 *
 * This function compares the start addresses
 * of two memory ranges.
 *
 * @param self First memory range to compare (must be valid).
 * @param other Second memory range to compare (must be valid).
 * @return true if both ranges start at the same address, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_begin(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Checks if two memory ranges share the same end address.
 *
 * This function compares the end addresses
 * (exclusive boundaries) of two memory ranges.
 *
 * @param self First memory range to compare (must be valid).
 * @param other Second memory range to compare (must be valid).
 * @return true if both ranges end at the same address, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal_end(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Checks if two memory ranges represent identical memory regions.
 *
 * This function verifies whether two memory ranges cover exactly the same range,
 * meaning they have identical begin and end addresses.
 *
 * @param self First memory range to compare (must be valid).
 * @param other Second memory range to compare (must be valid).
 * @return true if both ranges cover identical memory ranges, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_range_is_equal(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Finds the first occurrence of a memory range within this memory range.
 *
 * Searches for the first occurrence of the range [begin, end) within the memory range's range.
 * The search is performed byte-by-byte from the start of the memory range.
 *
 * @param[in] self  Pointer to the eya_memory_range_t structure to search within (must be valid).
 * @param[in] begin Pointer to the start of the range to find (inclusive).
 * @param[in] end   Pointer to the end of the range to find (exclusive).
 * @return Pointer to the first occurrence of the range within the memory range,
 *         or the memory range's end pointer if not found.
 *         Returns the memory range's start pointer if the search range is empty.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_find_range(const eya_memory_range_t *self, const void *begin, const void *end);

/**
 * @brief Finds the first occurrence of another memory range within this memory range.
 *
 * Searches for the first occurrence of the other memory range's range within this
 * memory range's range. The search is performed byte-by-byte from the start.
 *
 * @param[in] self  Pointer to the eya_memory_range_t structure to search within (must be valid).
 * @param[in] other Pointer to the eya_memory_range_t structure to find (must be valid).
 * @return Pointer to the first occurrence of the other range within this range,
 *         or this range's end pointer if not found.
 *         Returns this range's start pointer if the other range is empty.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_find(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Finds the last occurrence of a memory range within this memory range.
 *
 * Searches backward for the last occurrence of the range [begin, end)
 * within the memory range's range. The search is performed byte-by-byte
 * from the end of the memory range.
 *
 * @param[in] self  Pointer to the eya_memory_range_t structure to search within (must be valid).
 * @param[in] begin Pointer to the start of the range to find (inclusive).
 * @param[in] end   Pointer to the end of the range to find (exclusive).
 * @return Pointer to the start of the last occurrence of the range within the memory range,
 *         or the memory range's end pointer if not found.
 *         Returns the memory range's start pointer if the search range is empty.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rfind_range(const eya_memory_range_t *self, const void *begin, const void *end);

/**
 * @brief Finds the last occurrence of another memory range within this memory range.
 *
 * Searches backward for the last occurrence of the other memory range's range
 * within this memory range's range. The search is performed byte-by-byte from the end.
 *
 * @param[in] self  Pointer to the eya_memory_range_t structure to search within (must be valid).
 * @param[in] other Pointer to the eya_memory_range_t structure to find (must be valid).
 * @return Pointer to the start of the last occurrence of the other range within this range,
 *         or this range's end pointer if not found.
 *         Returns this range's start pointer if the other range is empty.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rfind(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Compares a memory range with a range [begin, end).
 *
 * Performs forward comparison between the memory range's contents and the specified range.
 * The comparison stops at the first difference found or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the eya_memory_range_t structure (must be valid).
 * @param[in] begin Pointer to the start of the range to compare (inclusive).
 * @param[in] end   Pointer to the end of the range to compare (exclusive).
 * @return NULL if ranges are identical,
 *         otherwise pointer to the first differing byte in the memory range.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_compare_range(const eya_memory_range_t *self, const void *begin, const void *end);

/**
 * @brief Compares two memory ranges contents.
 *
 * Performs forward comparison between two memory ranges' contents.
 * The comparison stops at the first difference found
 * or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the first eya_memory_range_t structure (must be valid).
 * @param[in] other Pointer to the second eya_memory_range_t structure (must be valid).
 * @return NULL if ranges are identical,
 *         otherwise pointer to the first differing byte in 'self'.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_compare(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Reverse compares a memory range with a range [begin, end).
 *
 * Performs backward comparison between the memory range's contents and the specified range,
 * starting from the end of both ranges. The comparison stops at the first difference found
 * or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the eya_memory_range_t structure (must be valid).
 * @param[in] begin Pointer to the start of the range to compare (inclusive).
 * @param[in] end   Pointer to the end of the range to compare (exclusive).
 * @return NULL if suffix regions are identical,
 *         otherwise pointer to the last differing byte in the memory range.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rcompare_range(const eya_memory_range_t *self, const void *begin, const void *end);

/**
 * @brief Reverse compares two memory ranges contents.
 *
 * Performs backward comparison between two memory ranges' contents,
 * starting from the end of both ranges.
 *
 * The comparison stops at the first difference found
 * or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the first eya_memory_range_t structure (must be valid).
 * @param[in] other Pointer to the second eya_memory_range_t structure (must be valid).
 * @return NULL if suffix regions are identical,
 *         otherwise pointer to the last differing byte in 'self'.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_range_rcompare(const eya_memory_range_t *self, const eya_memory_range_t *other);

/**
 * @brief Creates and validates a new memory range structure.
 *
 * Constructs a memory range from the given begin and end pointers,
 * performing runtime validation to ensure the resulting range is valid.
 *
 * @param[in] begin Pointer to the start of the memory range (inclusive).
 * @param[in] end   Pointer to the end of the memory range (exclusive).
 * @return Initialized eya_memory_range_t structure.
 *
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE if the resulting range would be invalid
 *         (begin > end or either pointer is NULL when the other isn't).
 *
 * @note Uses eya_memory_range_is_valid() for validation.
 * @note The range follows right-open interval semantics [begin, end).
 * @warning Aborts program execution if validation fails (in debug builds).
 * @warning Behavior is undefined if:
 *          - Pointers belong to different memory segments
 *          - Pointers are misaligned for the intended use
 *
 * Example usage:
 * @code
 * char buffer[1024];
 * eya_memory_range_t range = eya_memory_range_make(buffer, buffer + sizeof(buffer));
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_range_t
eya_memory_range_make(void *begin, void *end);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_RANGE_H
