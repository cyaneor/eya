/**
 * @file memory_view.h
 * @brief Memory view abstraction for read-only memory regions.
 *
 * This header defines the eya_memory_view_t structure
 * and associated functions for working with read-only views of memory regions.
 * The memory view abstraction provides bounds checking, state validation,
 * and various utility operations for memory ranges defined by [begin, end) pointers.
 *
 * Key features include:
 * - Memory region state checking (uninitialized, empty, valid, invalid)
 * - Safe pointer access with boundary validation
 * - Memory range containment checks
 * - Searching and comparison operations
 * - Offset-based access with validation
 *
 * The memory view uses right-open interval semantics [begin, end), where:
 * - begin points to the first byte of the region
 * - end points one byte past the last byte
 * - An empty region has begin == end (but not nullptr)
 *
 * All operations validate the memory view state before proceeding.
 * Invalid operations will trigger runtime errors.
 *
 * @note This is a read-only interface. For mutable memory operations,
 *       see the corresponding mutable memory range implementation.
 */

#ifndef EYA_MEMORY_VIEW_H
#define EYA_MEMORY_VIEW_H

#include "memory_view_fields.h"
#include "memory_view_state.h"
#include "attribute.h"
#include "offset.h"
#include "bool.h"
#include "addr.h"

/**
 * @struct eya_memory_view
 * @brief A structure representing a view into a memory region.
 *
 * This struct defines a read-only view of a memory segment,
 * specified by pointers to the beginning and end of the memory region.
 */
typedef struct eya_memory_view
{
    eya_memory_view_fields(const void);
} eya_memory_view_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Unpacks the memory view into begin and end pointers.
 *
 * This function extracts the begin and end pointers from the given memory view.
 * It performs a runtime check on the provided memory view and assigns the
 * respective pointers if the input parameters are not null.
 *
 * @param self Pointer to the eya_memory_view_t structure.
 * @param begin Pointer to store the start of the memory region (can be null).
 * @param end Pointer to store the end of the memory region (can be null).
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_view_unpack(const eya_memory_view_t *self, const void **begin, const void **end);

/**
 * @brief Gets the begin pointer of the memory view.
 *
 * This function retrieves the start pointer of the memory region from the given
 * memory view by calling eya_memory_view_unpack internally.
 *
 * @param self Pointer to the eya_memory_view_t structure.
 * @return The pointer to the start of the memory region.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_get_begin(const eya_memory_view_t *self);

/**
 * @brief Gets the end pointer of the memory view.
 *
 * This function retrieves the end pointer of the memory region from the given
 * memory view by calling eya_memory_view_unpack internally.
 *
 * @param self Pointer to the eya_memory_view_t structure.
 * @return The pointer to the end of the memory region (exclusive).
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_get_end(const eya_memory_view_t *self);

/**
 * @brief Determines the state of a memory view based on its begin and end pointers.
 *
 * This function analyzes the memory view's pointers and returns
 * its current state according to the eya_memory_view_state_t enumeration.
 * It checks for various valid and invalid conditions of the memory range.
 *
 * @param[in] self Pointer to the memory view object to analyze.
 * @return The state of the memory view as eya_memory_view_state_t enum value.
 *
 * @retval EYA_MEMORY_VIEW_UNINITIALIZED        Both begin and end pointers are nullptr
 * @retval EYA_MEMORY_VIEW_EMPTY                begin equals end (but not nullptr)
 * @retval EYA_MEMORY_VIEW_HAS_DATA             Valid non-empty range (begin < end)
 * @retval EYA_MEMORY_VIEW_INVALID_NULL_BEGIN   begin is nullptr while end is not
 * @retval EYA_MEMORY_VIEW_INVALID_NULL_END     end is nullptr while begin is not
 * @retval EYA_MEMORY_VIEW_INVALID_DANGLING     begin is after end (invalid range)
 *
 * @note The function assumes that eya_memory_view_unpack() provides valid pointers
 *       even for uninitialized/empty views. The caller must ensure the memory view
 *       object itself is valid.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_view_state_t
eya_memory_view_get_state(const eya_memory_view_t *self);

/**
 * @brief Checks if the memory view is uninitialized
 * @param self The memory view to check
 * @return true if uninitialized (both pointers NULL), false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_uninit(const eya_memory_view_t *self);

/**
 * @brief Checks if the memory view is empty
 * @param self The memory view to check
 * @return true if empty (begin equals end but not NULL), false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_empty(const eya_memory_view_t *self);

/**
 * @brief Checks if the memory view contains data
 * @param self The memory view to check
 * @return true if contains valid data (begin < end), false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_has_data(const eya_memory_view_t *self);

/**
 * @brief Checks if the memory view is in an invalid state
 * @param self The memory view to check
 * @return true if invalid (uninitialized or any invalid state), false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_invalid(const eya_memory_view_t *self);

/**
 * @brief Checks if the memory view is in a valid state
 * @param self The memory view to check
 * @return true if valid (either empty or has data), false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_valid(const eya_memory_view_t *self);

/**
 * @brief Unpacks the memory view into begin and end pointers with validation.
 *
 * This function performs a validity check on the memory view before unpacking.
 * If the memory view is invalid, it will raise a runtime error.
 * Otherwise, it extracts the begin and end pointers from the given memory view.
 *
 * @param self Pointer to the eya_memory_view_t structure to unpack (must be valid).
 * @param begin Pointer to store the start of the memory region (can be null).
 * @param end Pointer to store the end of the memory region (can be null).
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_memory_view_unpack_v(const eya_memory_view_t *self, const void **begin, const void **end);

/**
 * @brief Calculates the unsigned difference between end
 *        and begin pointers of a memory view.
 *
 * This function unpacks the memory view into begin and end pointers (with validation)
 * and returns the unsigned difference between them. The difference represents
 * the size of the memory region in bytes.
 *
 * @param self Pointer to the eya_memory_view_t structure
 *             to calculate difference for (must be valid).
 * @return Unsigned difference between end and begin pointers
 *         (size of memory region in bytes).
 *
 * @note This function uses eya_memory_view_unpack_v internally,
 *       which will raise a runtime error if the memory view is invalid.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_uaddr_t
eya_memory_view_diff(const eya_memory_view_t *self);

/**
 * @brief Gets the size in bytes of the memory view's range
 * @param self The memory view to examine
 * @return The size in bytes of the valid memory range
 * @note This is a convenience wrapper around eya_memory_view_diff()
 *       with an explicit size-related return type
 */
EYA_ATTRIBUTE(SYMBOL)
eya_usize_t
eya_memory_view_get_size(const eya_memory_view_t *self);

/**
 * @brief Checks if the memory view's start address is aligned to the specified boundary.
 *
 * This function verifies that the alignment requirement is a valid power of two,
 * and then checks whether the beginning pointer of the memory view meets the
 * specified alignment requirement.
 *
 * @param self Pointer to the eya_memory_view_t structure to check (must be valid).
 * @param align Alignment boundary to check (must be a power of two).
 * @return true if the start address is aligned to the specified boundary, false otherwise.
 *
 * @note This function validates the alignment value before performing the check.
 * @see eya_ptr_is_aligned()
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_aligned(const eya_memory_view_t *self, eya_usize_t align);

/**
 * @brief Checks if a pointer is contained within the memory view's range.
 *
 * This function verifies whether the given pointer lies within the memory region
 * defined by the memory view (inclusive of start, exclusive of end).
 * The memory view is first unpacked and validated.
 *
 * @param self Pointer to the eya_memory_view_t structure to check against (must be valid).
 * @param ptr Pointer to check for containment in the memory view.
 * @return true if the pointer is within the memory view's range, false otherwise.
 *
 * @note Uses eya_memory_view_unpack_v internally,
 *       which will raise a runtime error if the memory view is invalid.
 * @note The check uses right-open interval [begin, end) semantics.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_contains_ptr(const eya_memory_view_t *self, const void *ptr);

/**
 * @brief Checks if a memory range is fully contained within the memory view's range.
 *
 * This function verifies whether the given memory range [begin, end) lies entirely within
 * the memory region defined by the memory view (inclusive of start, exclusive of end).
 * The memory view is first unpacked and validated.
 *
 * @param self Pointer to the eya_memory_view_t structure to check against (must be valid).
 * @param begin Pointer to the start of the range to check (inclusive).
 * @param end Pointer to the end of the range to check (exclusive).
 * @return true if the entire range [begin, end) is within the memory view's range,
 *         false otherwise.
 *
 * @note Uses eya_memory_view_unpack_v internally,
 *       which will raise a runtime error if the memory view is invalid.
 * @note Both the memory view and the checked range
 *       use right-open interval [begin, end) semantics.
 * @note If begin == end, the range is considered empty
 *       and will return true if within bounds.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_contains_range(const eya_memory_view_t *self, const void *begin, const void *end);

/**
 * @brief Checks if another memory view is fully contained within this memory view.
 *
 * This function verifies whether the entire range of the 'other' memory view
 * lies within the range of 'self' memory view. Both memory views are validated.
 *
 * @param self Pointer to the containing eya_memory_view_t structure (must be valid).
 * @param other Pointer to the eya_memory_view_t structure to check for containment (must be valid).
 * @return true if the other memory view is fully contained within this one, false otherwise.
 *
 * @note Uses eya_memory_view_unpack_v internally for both views,
 *       which will raise a runtime error if either memory view is invalid.
 * @note The check uses right-open interval [begin, end) semantics for both views.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_contains(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Checks if an offset is valid within the memory view.
 *
 * This function verifies whether the given byte offset is within the valid range
 * of the memory view. The offset is considered valid if it is strictly less than
 * the size of the memory region (offset ∈ [0, size - 1]).
 *
 * @param self Pointer to the eya_memory_view_t structure
 *             to validate against (must be valid).
 * @param offset Byte offset to check for validity.
 * @return true if the offset is within valid range (0 ≤ offset < size),
 *         false otherwise.
 *
 * @note This function relies on eya_memory_view_get_size() internally,
 *       which may have its own validation logic.
 *       The memory view must be valid.
 *
 * @note The offset is treated as a zero-based index into the memory region.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_valid_offset(const eya_memory_view_t *self, eya_uoffset_t offset);

/**
 * @brief Gets a pointer to an element at a specified offset from the beginning.
 *
 * This function calculates the address of an element at the given byte offset
 * from the start of the memory view. The offset is validated before calculation.
 *
 * @param self Pointer to the eya_memory_view_t structure (must be valid).
 * @param offset Byte offset from the beginning (0-based).
 * @return Pointer to the element at the specified offset.
 *
 * @note Uses eya_memory_view_is_valid_offset() for validation.
 * @see eya_memory_view_get_begin()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_at_begin(const eya_memory_view_t *self, eya_uoffset_t offset);

/**
 * @brief Gets a pointer to an element
 *        at a specified offset from the end.
 *
 * This function calculates the address of an element at the given byte offset
 * from the end of the memory view. Offset 0 refers to the last byte.
 *
 * @param self Pointer to the eya_memory_view_t structure (must be valid).
 * @param offset Byte offset from the end (0 = last byte, 1 = second last, etc.).
 * @return Pointer to the element at the specified offset from the end.
 *
 * @note Internally converts to begin-relative offset and calls eya_memory_view_at_begin().
 * @note Automatically validates converted offset (size - offset - 1).
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_at_end(const eya_memory_view_t *self, eya_uoffset_t offset);

/**
 * @brief Gets a pointer to an element
 *        using either begin-relative or end-relative offset.
 *
 * This function provides unified access
 * to memory elements using either:
 *
 * - Begin-relative indexing (when reversed = false)
 * - End-relative indexing (when reversed = true)
 *
 * @param self Pointer to the eya_memory_view_t structure (must be valid).
 * @param offset Byte offset from either beginning or end.
 * @param reversed false: offset from begin, true: offset from end.
 * @return Pointer to the element at specified offset.
 *
 * @see eya_memory_view_at_begin()
 * @see eya_memory_view_at_end()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_at(const eya_memory_view_t *self, eya_uoffset_t offset, bool reversed);

/**
 * @brief Gets a pointer to the first byte of the memory view.
 *
 * This function is equivalent to accessing the memory view at offset 0
 * from the beginning (eya_memory_view_at(self, 0, false)).
 *
 * @param self Pointer to the eya_memory_view_t structure (must be valid).
 * @return Pointer to the first byte in the memory region.
 *
 * @note Uses eya_memory_view_at() internally with reversed=false.
 * @see eya_memory_view_at()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_at_first(const void *self);

/**
 * @brief Gets a pointer to the last byte of the memory view.
 *
 * This function is equivalent to accessing the memory view at offset 0
 * from the end (eya_memory_view_at(self, 0, true)).
 *
 * @param self Pointer to the eya_memory_view_t structure (must be valid).
 * @return Pointer to the last byte in the memory region.
 *
 * @note Uses eya_memory_view_at() internally with reversed=true.
 * @see eya_memory_view_at()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_at_last(const void *self);

/**
 * @brief Checks if the memory view's begin pointer equals the given pointer.
 *
 * This function compares the start address
 * of the memory view with the provided pointer.
 *
 * @param self Pointer to the eya_memory_view_t structure to check (must be valid).
 * @param ptr Pointer to compare with the view's begin address.
 * @return true if the view's begin address matches ptr, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_equal_begin_to(const eya_memory_view_t *self, const void *ptr);

/**
 * @brief Checks if the memory view's end pointer equals the given pointer.
 *
 * This function compares the end address (exclusive boundary)
 * of the memory view with the provided pointer.
 *
 * @param self Pointer to the eya_memory_view_t structure to check (must be valid).
 * @param ptr Pointer to compare with the view's end address.
 * @return true if the view's end address matches ptr, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_equal_end_to(const eya_memory_view_t *self, const void *ptr);

/**
 * @brief Checks if two memory views share the same begin address.
 *
 * This function compares the start addresses
 * of two memory views.
 *
 * @param self First memory view to compare (must be valid).
 * @param other Second memory view to compare (must be valid).
 * @return true if both views start at the same address, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_equal_begin(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Checks if two memory views share the same end address.
 *
 * This function compares the end addresses (exclusive boundaries)
 * of two memory views.
 *
 * @param self First memory view to compare (must be valid).
 * @param other Second memory view to compare (must be valid).
 * @return true if both views end at the same address, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_equal_end(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Checks if two memory views represent identical memory regions.
 *
 * This function verifies whether two memory views cover exactly the same range,
 * meaning they have identical begin and end addresses.
 *
 * @param self First memory view to compare (must be valid).
 * @param other Second memory view to compare (must be valid).
 * @return true if both views cover identical memory ranges, false otherwise.
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_memory_view_is_equal(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Finds the first occurrence of a memory range within the memory view.
 *
 * Searches for the first occurrence of the range [begin, end) within the memory view's
 * range. The search is performed byte-by-byte from the start of the memory view.
 *
 * @param[in] self  Pointer to the eya_memory_view_t structure to search within (must be valid).
 * @param[in] begin Pointer to the start of the range to find (inclusive).
 * @param[in] end   Pointer to the end of the range to find (exclusive).
 * @return Pointer to the first occurrence of the range within the memory view,
 *         or the memory view's end pointer if not found.
 *         Returns the memory view's start pointer if the search range is empty.
 *
 * @note Uses eya_memory_view_unpack_v internally, which validates the memory view.
 * @note Uses eya_memory_raw_find() for the actual search operation.
 * @note Both the memory view and search range use right-open interval [begin, end) semantics.
 * @warning Behavior is undefined if:
 *          - The memory view is invalid
 *          - Search range pointers are not in the same memory segment
 *          - end < begin
 *
 * Example:
 * @code
 * eya_memory_view_t view = ...; // initialized memory view
 * const char pattern[] = "abc";
 * const void *found = eya_memory_view_find_range(
 *     &view, pattern, pattern + sizeof(pattern)-1);
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_find_range(const eya_memory_view_t *self, const void *begin, const void *end);

/**
 * @brief Finds the first occurrence of another memory view within this memory view.
 *
 * Searches for the first occurrence of the other memory view's range within this
 * memory view's range. The search is performed byte-by-byte from the start.
 *
 * @param[in] self  Pointer to the eya_memory_view_t structure to search within (must be valid).
 * @param[in] other Pointer to the eya_memory_view_t structure to find (must be valid).
 * @return Pointer to the first occurrence of the other view within this view,
 *         or this view's end pointer if not found.
 *         Returns this view's start pointer if the other view is empty.
 *
 * @note Uses eya_memory_view_unpack_v internally for both memory views.
 * @note Essentially a convenience wrapper around eya_memory_view_find_range().
 * @warning Behavior is undefined if either memory view is invalid.
 *
 * Example:
 * @code
 * eya_memory_view_t view1 = ...; // initialized memory view
 * eya_memory_view_t view2 = ...; // another memory view
 * const void *found = eya_memory_view_find(&view1, &view2);
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_find(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Finds the last occurrence of a memory range within the memory view.
 *
 * Searches backward for the last occurrence of the range [begin, end)
 * within the memory view's range. The search is performed byte-by-byte
 * from the end of the memory view.
 *
 * @param[in] self  Pointer to the eya_memory_view_t structure to search within (must be valid).
 * @param[in] begin Pointer to the start of the range to find (inclusive).
 * @param[in] end   Pointer to the end of the range to find (exclusive).
 * @return Pointer to the start of the last occurrence of the range within the memory view,
 *         or the memory view's end pointer if not found.
 *         Returns the memory view's start pointer if the search range is empty.
 *
 * @note Uses eya_memory_view_unpack_v internally, which validates the memory view.
 * @note Uses eya_memory_raw_rfind() for the actual reverse search operation.
 * @note Both the memory view and search range use right-open interval [begin, end) semantics.
 * @warning Behavior is undefined if:
 *          - The memory view is invalid
 *          - Search range pointers are not in the same memory segment
 *          - end < begin
 *          - Pointers are misaligned for the operation
 *
 * Example:
 * @code
 * eya_memory_view_t view = ...; // initialized memory view
 * const char pattern[] = "abc";
 * const void *found = eya_memory_view_rfind_range(
 *     &view, pattern, pattern + sizeof(pattern)-1);
 * // found points to the last occurrence of "abc" in view
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_rfind_range(const eya_memory_view_t *self, const void *begin, const void *end);

/**
 * @brief Finds the last occurrence of another memory view within this memory view.
 *
 * Searches backward for the last occurrence of the other memory view's range
 * within this memory view's range. The search is performed byte-by-byte from the end.
 *
 * @param[in] self  Pointer to the eya_memory_view_t structure to search within (must be valid).
 * @param[in] other Pointer to the eya_memory_view_t structure to find (must be valid).
 * @return Pointer to the start of the last occurrence of the other view within this view,
 *         or this view's end pointer if not found.
 *         Returns this view's start pointer if the other view is empty.
 *
 * @note Uses eya_memory_view_unpack_v internally for both memory views.
 * @note Essentially a convenience wrapper around eya_memory_view_rfind_range().
 * @warning Behavior is undefined if either memory view is invalid.
 * @see eya_memory_view_rfind_range()
 *
 * Example:
 * @code
 * eya_memory_view_t view1 = ...; // initialized memory view
 * eya_memory_view_t view2 = ...; // another memory view
 * const void *found = eya_memory_view_rfind(&view1, &view2);
 * // found points to the last occurrence of view2 in view1
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_rfind(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Compares a memory view with a range [begin, end).
 *
 * Performs forward comparison between the memory view's contents and the specified range.
 * The comparison stops at the first difference found or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the eya_memory_view_t structure (must be valid).
 * @param[in] begin Pointer to the start of the range to compare (inclusive).
 * @param[in] end   Pointer to the end of the range to compare (exclusive).
 * @return NULL if ranges are identical,
 *         otherwise pointer to the first differing byte in the memory view.
 *
 * @note Uses eya_memory_view_unpack_v internally for validation.
 * @note Comparison follows same semantics as eya_memory_raw_compare().
 * @warning Undefined behavior if:
 *          - Memory view is invalid
 *          - Range pointers are invalid (end < begin)
 *          - Pointers span different memory segments
 *
 * Example:
 * @code
 * eya_memory_view_t view = ...; // contains "HelloWorld"
 * const char test[] = "HelloMoon";
 * const void *diff = eya_memory_view_compare_range(
 *     &view, test, test + 9);
 * // diff points to 'W' in view
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_compare_range(const eya_memory_view_t *self, const void *begin, const void *end);

/**
 * @brief Compares two memory views contents.
 *
 * Performs forward comparison between two memory views' contents.
 * The comparison stops at the first difference found or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the first eya_memory_view_t structure (must be valid).
 * @param[in] other Pointer to the second eya_memory_view_t structure (must be valid).
 * @return NULL if views are identical,
 *         otherwise pointer to the first differing byte in 'self'.
 *
 * @note Convenience wrapper around eya_memory_view_compare_range().
 * @note Both views are validated via eya_memory_view_unpack_v.
 * @see eya_memory_view_compare_range()
 *
 * Example:
 * @code
 * eya_memory_view_t view1 = ...; // contains "HelloWorld"
 * eya_memory_view_t view2 = ...; // contains "HelloThere"
 * const void *diff = eya_memory_view_compare(&view1, &view2);
 * // diff points to 'W' in view1
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_compare(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Reverse compares a memory view with a range [begin, end).
 *
 * Performs backward comparison between the memory view's contents and the specified range,
 * starting from the end of both ranges. The comparison stops at the first difference found
 * or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the eya_memory_view_t structure (must be valid).
 * @param[in] begin Pointer to the start of the range to compare (inclusive).
 * @param[in] end   Pointer to the end of the range to compare (exclusive).
 * @return NULL if suffix regions are identical,
 *         otherwise pointer to the last differing byte in the memory view.
 *
 * @note Uses eya_memory_raw_rcompare() for the actual comparison.
 * @note Particularly useful for comparing checksums or footers.
 * @warning Same undefined behavior conditions as eya_memory_view_compare_range().
 *
 * Example:
 * @code
 * eya_memory_view_t view = ...; // contains "file_v1.bin"
 * const char test[] = "file_v2.bin";
 * const void *diff = eya_memory_view_rcompare_range(
 *     &view, test, test + 11);
 * // diff points to '1' in view
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_rcompare_range(const eya_memory_view_t *self, const void *begin, const void *end);

/**
 * @brief Reverse compares two memory views contents.
 *
 * Performs backward comparison between two memory views' contents,
 * starting from the end of both views.
 *
 * The comparison stops at the first
 * difference found or when the minimum size is reached.
 *
 * @param[in] self  Pointer to the first eya_memory_view_t structure (must be valid).
 * @param[in] other Pointer to the second eya_memory_view_t structure (must be valid).
 * @return NULL if suffix regions are identical,
 *         otherwise pointer to the last differing byte in 'self'.
 *
 * @note Convenience wrapper around eya_memory_view_rcompare_range().
 * @note Useful for version trailers or checksum verification.
 * @see eya_memory_view_rcompare_range()
 *
 * Example:
 * @code
 * eya_memory_view_t view1 = ...; // contains "data_2023.log"
 * eya_memory_view_t view2 = ...; // contains "data_2024.log"
 * const void *diff = eya_memory_view_rcompare(&view1, &view2);
 * // diff points to '3' in view1
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_view_rcompare(const eya_memory_view_t *self, const eya_memory_view_t *other);

/**
 * @brief Creates and validates a memory view from begin and end pointers.
 *
 * Constructs a read-only memory view structure and verifies it represents a valid
 * memory region before returning.
 *
 * @param[in] begin Pointer to the start of the memory region (inclusive).
 * @param[in] end Pointer to the end of the memory region (exclusive).
 * @return eya_memory_view_t Validated memory view object.
 *
 * @note Performs validation via eya_memory_view_is_valid().
 * @note The view must satisfy begin <= end to be considered valid.
 * @note This is the safe version of eya_memory_view_make().
 * @note The resulting view provides read-only access to the memory region.
 *
 * Example usage:
 * @code
 * const int array[10];
 * // This will throw if pointers are invalid
 * eya_memory_view_t view = eya_memory_view_make(array, array + 10);
 * @endcode
 *
 * @see eya_memory_view_make()
 * @see eya_memory_view_is_valid()
 * @see eya_memory_range_make_v()
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_view_t
eya_memory_view_make(const void *begin, const void *end);

/**
 * @brief Creates a copy of an existing memory view.
 *
 * Constructs a new memory view with the same bounds as the input view.
 * No validation is performed on the source view.
 *
 * @param[in] self Pointer to the source memory view to clone.
 * @return eya_memory_view_t New memory view with same bounds.
 *
 * @note This is a shallow copy - both views reference the same memory.
 * @note For a validated version, use eya_memory_view_clone_v().
 *
 * Example usage:
 * @code
 * eya_memory_view_t view = ...;
 * eya_memory_view_t copy = eya_memory_view_clone(&view);
 * @endcode
 *
 * @see eya_memory_view_clone_v()
 * @see eya_memory_view_make()
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_view_t
eya_memory_view_clone(const eya_memory_view_t *self);

/**
 * @brief Creates and validates a copy of an existing memory view.
 *
 * Constructs a new memory view with the same bounds as the input view
 * after validating the source view.
 *
 * @param[in] self Pointer to the source memory view to clone.
 * @return eya_memory_view_t New validated memory view with same bounds.
 *
 * @throws EYA_RUNTIME_ERROR_INVALID_MEMORY_RANGE If the source view is invalid.
 * @note This is a shallow copy - both views reference the same memory.
 * @note This is the safe version of eya_memory_view_clone().
 *
 * Example usage:
 * @code
 * eya_memory_view_t view = ...;
 * // This will throw if source view is invalid
 * eya_memory_view_t copy = eya_memory_view_clone_v(&view);
 * @endcode
 *
 * @see eya_memory_view_clone()
 * @see eya_memory_view_make()
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_view_t
eya_memory_view_clone_v(const eya_memory_view_t *self);

/**
 * @brief Creates a sub-view of an existing memory view.
 *
 * Constructs a new memory view representing a portion of the original view,
 * specified by offset and size. No validation is performed.
 *
 * @param[in] self Pointer to the source memory view.
 * @param[in] offset Byte offset from start of original view.
 * @param[in] size Size in bytes of the new sub-view.
 * @return eya_memory_view_t New sub-view of the original memory.
 *
 * @note The sub-view must be fully contained within the original view.
 * @note No bounds checking is performed - may create invalid views.
 * @note For a safe version, consider checking bounds first.
 *
 * Example usage:
 * @code
 * eya_memory_view_t view = ...;
 * // Create view of 4 bytes starting at offset 8
 * eya_memory_view_t subview = eya_memory_view_slice(&view, 8, 4);
 * @endcode
 *
 * @see eya_memory_view_at_begin()
 * @see eya_memory_view_make()
 */
EYA_ATTRIBUTE(SYMBOL)
eya_memory_view_t
eya_memory_view_slice(const eya_memory_view_t *self, eya_uoffset_t offset, eya_uoffset_t size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_VIEW_H
