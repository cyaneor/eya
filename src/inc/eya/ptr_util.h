/**
 * @file ptr_util.h
 * @brief Utilities for pointer operations and arithmetic.
 *
 * This header provides a collection of macros to facilitate pointer manipulation,
 * including type casting, pointer arithmetic (addition, subtraction, shifting),
 * difference calculations, alignment checks, and range validations.
 *
 * The macros support both safe operations (with NULL pointer checks) and unsafe
 * operations (without checks) for performance-critical scenarios.
 *
 * Included features:
 * - Pointer type casting and conversion to address types.
 * - Calculating differences between pointers as signed or unsigned addresses.
 * - Shifting pointers by offsets, adding and subtracting pointers or offsets.
 * - Checking pointer alignment and aligning pointers up or down to a specified boundary.
 * - Validating pointer ranges and checking for overlaps or containment of ranges.
 *
 * Dependencies:
 * - addr_util.h: Address manipulation utilities.
 * - interval_util.h: Interval/range checking utilities.
 * - nullptr.h: nullptr definition.
 * - static_cast.h: Static cast macro.
 *
 * @note All macros assume pointers are convertible
 *       to integral address types and vice versa.
 */

#ifndef EYA_PTR_UTIL_H
#define EYA_PTR_UTIL_H

#include "addr_util.h"
#include "interval_util.h"
#include "nullptr.h"

/**
 * @def eya_ptr_cast(T, ptr)
 * @brief Casts a pointer to a pointer of type T.
 *
 * @param T Target type (without pointer).
 * @param ptr Pointer to cast.
 * @return Pointer of type T*.
 */
#define eya_ptr_cast(T, ptr) eya_type_cast(T *, ptr)

/**
 * @def eya_ptr_to_uaddr(ptr)
 * @brief Converts a pointer to an unsigned address representation.
 *
 * @param ptr Pointer to convert.
 * @return Unsigned address representation of the pointer.
 */
#define eya_ptr_to_uaddr(ptr) eya_uaddr_from_ptr(ptr)

/**
 * @def eya_ptr_to_saddr(ptr)
 * @brief Converts a pointer to a signed address representation.
 *
 * @param ptr Pointer to convert.
 * @return Signed address representation of the pointer.
 */
#define eya_ptr_to_saddr(ptr) eya_saddr_from_ptr(ptr)

/**
 * @def eya_ptr_to_diff(ptr)
 * @brief Converts a pointer to a signed integer suitable for difference calculations.
 *
 * @param ptr Pointer to convert.
 * @return Signed integer representation of the pointer.
 */
#define eya_ptr_to_diff(ptr) eya_type_cast(eya_saddr_t, ptr)

/**
 * @def eya_ptr_diff(ptr1, ptr2)
 * @brief Calculates the difference between two pointers as signed integers.
 *
 * @param ptr1 First pointer.
 * @param ptr2 Second pointer.
 * @return Signed difference between ptr1 and ptr2.
 */
#define eya_ptr_diff(ptr1, ptr2) (eya_ptr_to_diff(ptr1) - eya_ptr_to_diff(ptr2))

/**
 * @def eya_ptr_uaddr_diff(ptr1, ptr2)
 * @brief Calculates the difference between two pointers as unsigned addresses.
 *
 * @param ptr1 First pointer.
 * @param ptr2 Second pointer.
 * @return Unsigned difference between ptr1 and ptr2.
 */
#define eya_ptr_uaddr_diff(ptr1, ptr2) eya_addr_diff(eya_ptr_to_uaddr(ptr1), eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_saddr_diff(ptr1, ptr2)
 * @brief Calculates the difference between two pointers as signed addresses.
 *
 * @param ptr1 First pointer.
 * @param ptr2 Second pointer.
 * @return Signed difference between ptr1 and ptr2.
 */
#define eya_ptr_saddr_diff(ptr1, ptr2) eya_addr_diff(eya_ptr_to_saddr(ptr1), eya_ptr_to_saddr(ptr2))

/**
 * @def eya_ptr_add_offset_unsafe(T, ptr, offset)
 * @brief Shifts a pointer by an offset without NULL pointer check.
 *
 * @param T Target pointer type.
 * @param ptr Pointer to shift.
 * @param offset Offset in bytes to add.
 * @return Shifted pointer of type T*.
 */
#define eya_ptr_add_offset_unsafe(T, ptr, offset)                                                  \
    eya_addr_to_ptr(T, (eya_ptr_to_uaddr(ptr) + offset))

/**
 * @def eya_ptr_add_unsafe(T, ptr1, ptr2)
 * @brief Adds the unsigned address of ptr2 to ptr1 without NULL checks.
 *
 * @param T Target pointer type.
 * @param ptr1 Base pointer.
 * @param ptr2 Pointer whose address is added as offset.
 * @return Resulting pointer of type T*.
 */
#define eya_ptr_add_unsafe(T, ptr1, ptr2) eya_ptr_add_offset_unsafe(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_add_offset(T, ptr, offset)
 * @brief Safely shifts a pointer by an offset with NULL pointer check.
 *
 * @param T Target pointer type.
 * @param ptr Pointer to shift.
 * @param offset Offset in bytes to add.
 * @return Shifted pointer of type T*, or nullptr if ptr is nullptr.
 */
#define eya_ptr_add_offset(T, ptr, offset)                                                         \
    (ptr == nullptr ? ptr : eya_ptr_add_offset_unsafe(T, ptr, offset))

/**
 * @def eya_ptr_add(T, ptr1, ptr2)
 * @brief Safely adds the unsigned address of ptr2 to ptr1 with NULL check.
 *
 * @param T Target pointer type.
 * @param ptr1 Base pointer.
 * @param ptr2 Pointer whose address is added as offset.
 * @return Resulting pointer of type T*, or nullptr if ptr1 is nullptr.
 */
#define eya_ptr_add(T, ptr1, ptr2) eya_ptr_add_offset(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_sub_offset_unsafe(T, ptr, offset)
 * @brief Subtracts an offset from a pointer without NULL pointer check.
 *
 * @param T Target pointer type.
 * @param ptr Pointer to subtract from.
 * @param offset Offset in bytes to subtract.
 * @return Resulting pointer of type T*.
 */
#define eya_ptr_sub_offset_unsafe(T, ptr, offset)                                                  \
    eya_addr_to_ptr(T, (eya_ptr_to_uaddr(ptr) - offset))

/**
 * @def eya_ptr_sub_unsafe(T, ptr1, ptr2)
 * @brief Subtracts the address of ptr2 from ptr1 without NULL checks.
 *
 * @param T Target pointer type.
 * @param ptr1 Pointer to subtract from.
 * @param ptr2 Pointer whose address is subtracted.
 * @return Resulting pointer of type T*.
 */
#define eya_ptr_sub_unsafe(T, ptr1, ptr2) eya_ptr_sub_offset_unsafe(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_sub_offset(T, ptr, offset)
 * @brief Safely subtracts an offset from a pointer with NULL pointer check.
 *
 * @param T Target pointer type.
 * @param ptr Pointer to subtract from.
 * @param offset Offset in bytes to subtract.
 * @return Resulting pointer of type T*, or nullptr if ptr is nullptr.
 */
#define eya_ptr_sub_offset(T, ptr, offset)                                                         \
    (ptr == nullptr ? ptr : eya_ptr_sub_offset_unsafe(T, ptr, offset))

/**
 * @def eya_ptr_sub(T, ptr1, ptr2)
 * @brief Safely subtracts the address of ptr2 from ptr1 with NULL check.
 *
 * @param T Target pointer type.
 * @param ptr1 Pointer to subtract from.
 * @param ptr2 Pointer whose address is subtracted.
 * @return Resulting pointer of type T*, or nullptr if ptr1 is nullptr.
 */
#define eya_ptr_sub(T, ptr1, ptr2) eya_ptr_sub_offset(T, ptr1, eya_ptr_to_uaddr(ptr2))

/**
 * @def eya_ptr_align_offset
 * @brief Computes the offset of a pointer within an alignment boundary
 *
 * This macro calculates the offset of a pointer
 * within the specified alignment boundary using bitwise operations.
 *
 * The operation is equivalent to:
 * `(uintptr_t)ptr % align` but more efficient when align is a power of two.
 *
 * @note Alignment value must be a power of two for correct results.
 *       The implementation uses `addr & (align - 1)` which is
 *       equivalent to modulo operation for power-of-two values.
 *
 * @param ptr Pointer to compute offset for (may be any pointer type)
 * @param align Alignment boundary (must be power of two)
 * @return Offset of the pointer within the alignment block (0 to align-1)
 *
 * @see eya_addr_align_offset
 */
#define eya_ptr_align_offset(ptr, align) eya_addr_align_offset(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_is_aligned
 * @brief Checks if a pointer meets the specified alignment requirement
 *
 * This macro verifies whether a pointer is aligned to the specified boundary
 * by converting it to an address and checking its alignment.
 *
 * @note Alignment value must be a power of two for correct results.
 *
 * @param ptr Pointer to verify
 * @param align Alignment boundary to check against (must be power of two)
 * @return Non-zero (true) if pointer is aligned, zero (false) otherwise
 *
 * @see eya_addr_is_aligned
 */
#define eya_ptr_is_aligned(ptr, align) eya_addr_is_aligned(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_align_up
 * @brief Aligns a pointer's address upward to the specified boundary
 *
 * This macro converts the given pointer to an integer address
 * and adjusts it to the nearest higher address that is a multiple
 * of the alignment value using the eya_addr_align_up macro.
 *
 * @warning Requires power-of-two alignment value for correct operation.
 *          Using non-power-of-two values will produce incorrect results.
 *
 * @param[in] ptr   Pointer to align (will be converted to an integer address).
 * @param[in] align Alignment boundary (must be a power of two).
 * @return Adjusted integer address aligned upward to the specified boundary.
 *
 * @note The pointer is converted to an address using eya_ptr_to_uaddr before alignment.
 *       This macro is efficient due to bitwise operations used internally.
 */
#define eya_ptr_align_up(ptr, align) eya_addr_align_up(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_align_down
 * @brief Aligns a pointer's address downward to the specified boundary
 *
 * This macro converts the given pointer to an integer address
 * and adjusts it to the nearest lower address that is a multiple
 * of the alignment value using the eya_addr_align_down macro.
 *
 * @warning Requires power-of-two alignment value for correct operation.
 *          Using non-power-of-two values will produce incorrect results.
 *
 * @param[in] ptr   Pointer to align (will be converted to an integer address).
 * @param[in] align Alignment boundary (must be a power of two).
 * @return Adjusted integer address aligned downward to the specified boundary.
 *
 * @note The pointer is converted to an address using eya_ptr_to_uaddr before alignment.
 *       This macro is efficient due to bitwise operations used internally.
 */
#define eya_ptr_align_down(ptr, align) eya_addr_align_down(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_align_up_by_size(T, ptr, begin, size)
 * @brief Aligns a pointer upwards to the next multiple of `size` bytes relative to `begin`.
 *
 * @param T         Target pointer type.
 * @param ptr       Pointer to align.
 * @param begin     Base address for alignment calculation.
 * @param size      Alignment size in bytes (must be a power of two).
 * @return          Aligned pointer of type `T*`.
 */
#define eya_ptr_align_up_by_size(T, ptr, begin, size)                                              \
    eya_ptr_add_offset_unsafe(T, begin, eya_addr_align_up(eya_ptr_diff(ptr, begin), size))

/**
 * @def eya_ptr_align_up_by_type(T, ptr, begin)
 * @brief Aligns a pointer upwards to the next multiple of type's size relative to begin.
 *
 * @param T Target type whose size is used for alignment calculation.
 * @param ptr Pointer to be aligned.
 * @param begin Base address for alignment calculation.
 * @return Aligned pointer of type T*.
 */
#define eya_ptr_align_up_by_type(T, ptr, begin) eya_ptr_align_up_by_size(T, ptr, begin, sizeof(T))

/**
 * @def eya_ptr_align_down_by_size(T, ptr, begin, size)
 * @brief Aligns a pointer downwards to the previous multiple of `size` bytes relative to `begin`.
 *
 * @param T         Target pointer type.
 * @param ptr       Pointer to align.
 * @param begin     Base address for alignment calculation.
 * @param size      Alignment size in bytes (must be a power of two).
 * @return          Aligned pointer of type `T*`.
 */
#define eya_ptr_align_down_by_size(T, ptr, begin, size)                                            \
    eya_ptr_sub_offset_unsafe(T, ptr, eya_addr_align_offset(eya_ptr_diff(ptr, begin), size))

/**
 * @def eya_ptr_align_down_by_type(T, ptr, begin)
 * @brief Aligns a pointer downwards to the previous multiple of type's size relative to begin.
 *
 * @param T Target type whose size is used for alignment calculation.
 * @param ptr Pointer to be aligned.
 * @param begin Base address for alignment calculation.
 * @return Aligned pointer of type T*.
 */
#define eya_ptr_align_down_by_type(T, ptr, begin)                                                  \
    eya_ptr_align_down_by_size(T, ptr, begin, sizeof(T))

/**
 * @def eya_ptr_range_contains(begin, end, ptr)
 * @brief Checks if a pointer lies within a closed range [begin, end].
 *
 * @param begin Range start pointer.
 * @param end Range end pointer.
 * @param ptr Pointer to check.
 * @return Non-zero if ptr is within [begin, end], zero otherwise.
 */
#define eya_ptr_range_contains(begin, end, ptr) eya_interval_closed_contains(begin, end, ptr)

/**
 * @def eya_ptr_ranges_is_aligned(r1_begin, r1_end, r2_begin, r2_end, align)
 * @brief Checks if all pointers defining two ranges are aligned to the specified boundary.
 *
 * @param r1_begin First range start pointer.
 * @param r1_end First range end pointer.
 * @param r2_begin Second range start pointer.
 * @param r2_end Second range end pointer.
 * @param align Alignment boundary.
 * @return Non-zero if all pointers are aligned, zero otherwise.
 */
#define eya_ptr_ranges_is_aligned(r1_begin, r1_end, r2_begin, r2_end, align)                       \
    (eya_ptr_pair_is_aligned(r1_begin, r1_end, align) &&                                           \
     eya_ptr_pair_is_aligned(r2_begin, r2_end, align))

/**
 * @def eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end)
 * @brief Checks if two ranges do not overlap.
 *
 * @param r1_begin Start pointer of first range.
 * @param r2_begin Start pointer of second range.
 * @param r2_end End pointer of second range.
 * @return Non-zero if no overlap, zero if ranges overlap.
 *
 * @note Assumes first range ends before r2_begin or starts after r2_end.
 */
#define eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end)                                      \
    ((r1_begin <= r2_begin) || (r2_end <= r1_begin))

/**
 * @def eya_ptr_ranges_is_overlap(r1_begin, r2_begin, r2_end)
 * @brief Checks if two ranges overlap.
 *
 * @param r1_begin Start pointer of first range.
 * @param r2_begin Start pointer of second range.
 * @param r2_end End pointer of second range.
 * @return Non-zero if ranges overlap, zero otherwise.
 */
#define eya_ptr_ranges_is_overlap(r1_begin, r2_begin, r2_end)                                      \
    (!eya_ptr_ranges_no_overlap(r1_begin, r2_begin, r2_end))

/**
 * @def eya_ptr_range_element_count(begin, end, type_size)
 * @brief Calculates the number of elements of given size in a pointer range.
 *
 * @param begin Range start pointer.
 * @param end Range end pointer.
 * @param type_size Size of one element in bytes.
 * @return Number of elements in the range.
 */
#define eya_ptr_range_element_count(begin, end, type_size)                                         \
    (eya_ptr_addr_diff(end, begin) / (type_size))

/**
 * @def eya_ptr_range_is_valid(begin, end)
 * @brief Checks if a pointer range is valid (non-null and properly ordered).
 *
 * @param begin Range start pointer.
 * @param end Range end pointer.
 * @return Non-zero if valid, zero otherwise.
 */
#define eya_ptr_range_is_valid(begin, end) (begin && eya_interval_closed_is_valid(begin, end))

#endif // EYA_PTR_UTIL_H
