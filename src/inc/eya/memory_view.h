#ifndef EYA_MEMORY_VIEW_H
#define EYA_MEMORY_VIEW_H

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
    const void *begin; /**< Pointer to the start of the memory region. */
    const void *end;   /**< Pointer to the end of the memory region (exclusive). */
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
eya_memory_view_is_uninitialized(const eya_memory_view_t *self);

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
eya_memory_view_udiff(const eya_memory_view_t *self);

/**
 * @brief Gets the size in bytes of the memory view's range
 * @param self The memory view to examine
 * @return The size in bytes of the valid memory range
 * @note This is a convenience wrapper around eya_memory_view_udiff()
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
eya_memory_view_contains_other(const eya_memory_view_t *self, const eya_memory_view_t *other);

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
eya_memory_view_is_begin_equal(const eya_memory_view_t *self, const void *ptr);

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
eya_memory_view_is_end_equal(const eya_memory_view_t *self, const void *ptr);

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
eya_memory_view_is_begin_equal_to(const eya_memory_view_t *self, const eya_memory_view_t *other);

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
eya_memory_view_is_end_equal_to(const eya_memory_view_t *self, const eya_memory_view_t *other);

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

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_VIEW_H
