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
    eya_addr_to_ptr(T, (eya_ptr_to_addr(ptr) - offset))

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
 * @def eya_ptr_align_mask
 * @brief Computes pointer alignment offset using bitmask operation
 *
 * This macro converts the pointer to an integer address via eya_ptr_to_uaddr()
 * and calculates the byte offset from the previous alignment boundary using
 * bitwise AND with (alignment - 1). Equivalent to addr % align for power-of-two
 * values, but more efficient.
 *
 * @note Alignment value must be a power of two for correct results
 * @param[in] ptr Pointer to check (will be converted to integer address)
 * @param[in] align Alignment boundary (power of two)
 * @return Offset in bytes from previous aligned address (0 = already aligned)
 */
#define eya_ptr_align_mask(ptr, align) eya_addr_align_mask(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_is_aligned_mask
 * @brief Checks pointer alignment using bitmask comparison
 *
 * This macro converts the pointer to an integer address and checks alignment
 * using bitwise operations. Optimized for power-of-two alignment values.
 *
 * @note Alignment value must be a power of two for correct results
 * @param ptr Pointer to check (will be converted to integer via eya_ptr_to_uaddr)
 * @param align Alignment boundary (power of two)
 * @return Non-zero (1) if aligned, 0 if not aligned
 */
#define eya_ptr_is_aligned_mask(ptr, align) eya_addr_is_aligned_mask(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_align_rem
 * @brief Calculates pointer alignment offset using modulus operation
 *
 * Converts pointer to integer address via eya_ptr_to_uaddr() and computes
 * offset from alignment boundary using modulus. Works with arbitrary alignment
 * values but less efficient than bitmask method.
 *
 * @note For power-of-two alignments, prefer eya_ptr_align_mask for better performance
 * @param[in] ptr Pointer to check (will be converted to integer address)
 * @param[in] align Alignment boundary (any positive integer)
 * @return Offset in bytes from previous aligned address (0 = already aligned)
 */
#define eya_ptr_align_rem(ptr, align) eya_addr_align_rem(eya_ptr_to_uaddr(ptr), align)

/**
 * @def eya_ptr_is_aligned_rem
 * @brief Checks pointer alignment using modulus operation
 *
 * Converts pointer to integer address and checks alignment by calculating
 * remainder of division. Returns zero for aligned pointers.
 *
 * @warning Uses division operation - less efficient than bitmask method.
 *          Suitable for arbitrary alignment values
 * @param ptr Pointer to check (will be converted to integer via eya_ptr_to_uaddr)
 * @param align Alignment boundary
 * @return 0 if aligned, non-zero remainder if not aligned
 */
#define eya_ptr_is_aligned_rem(ptr, align) eya_addr_is_aligned_rem(eya_ptr_to_uaddr(ptr), align)

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
 * @param T         Target pointer type (e.g., `uint8_t`, `struct MyType`).
 * @param ptr       Pointer to align (type must be compatible with `begin`).
 * @param begin     Base address for alignment calculation (memory block starting address).
 * @param size      Alignment size in bytes (must be a power of two for proper alignment).
 * @return          Aligned pointer of type `T*`.
 *
 * @note Example: If `begin = 0x1000`, `ptr = 0x1005`, `size = 4`, result is `0x1008`.
 */
#define eya_ptr_align_up_by_size(T, ptr, begin, size)                                              \
    eya_ptr_add_offset(T, ptr, (size - (eya_ptr_diff(ptr, begin) % size)) % size)

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
 * @param size      Alignment size in bytes.
 * @return          Aligned pointer of type `T*`.
 *
 * @note Example: If `begin = 0x1000`, `ptr = 0x1005`, `size = 4`, result is `0x1004`.
 */
#define eya_ptr_align_down_by_size(T, ptr, begin, size)                                            \
    eya_ptr_sub_offset(T, ptr, (eya_ptr_diff(ptr, begin) % size))

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
 * @def eya_ptr_range_is_within(begin, end, ptr)
 * @brief Checks if a pointer lies within a closed range [begin, end].
 *
 * @param begin Range start pointer.
 * @param end Range end pointer.
 * @param ptr Pointer to check.
 * @return Non-zero if ptr is within [begin, end], zero otherwise.
 */
#define eya_ptr_range_is_within(begin, end, ptr) eya_interval_is_within_closed(begin, end, ptr)

/**
 * @def eya_ptr_pair_is_aligned(ptr1, ptr2, align)
 * @brief Checks if both pointers are aligned to the specified boundary.
 *
 * @param ptr1 First pointer.
 * @param ptr2 Second pointer.
 * @param align Alignment boundary.
 * @return Non-zero if both pointers are aligned, zero otherwise.
 */
#define eya_ptr_pair_is_aligned(ptr1, ptr2, align)                                                 \
    (eya_ptr_is_aligned(ptr1, align) && eya_ptr_is_aligned(ptr2, align))

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
#define eya_ptr_range_is_valid(begin, end) (begin && eya_interval_is_valid_closed(begin, end))

/**
 * @def eya_ptr_range_contains(r1_begin, r1_end, r2_begin, r2_end)
 * @brief Checks if one pointer range fully contains another.
 *
 * @param r1_begin Outer range start pointer.
 * @param r1_end Outer range end pointer.
 * @param r2_begin Inner range start pointer.
 * @param r2_end Inner range end pointer.
 * @return Non-zero if outer range contains inner range, zero otherwise.
 */
#define eya_ptr_range_contains(r1_begin, r1_end, r2_begin, r2_end)                                 \
    eya_interval_contains_closed(r1_begin, r1_end, r2_begin, r2_end)

/**
 * @def eya_ptr_ranges_is_valid(r1_begin, r1_end, r2_begin, r2_end)
 * @brief Checks if two pointer ranges are both valid.
 *
 * @param r1_begin First range start pointer.
 * @param r1_end First range end pointer.
 * @param r2_begin Second range start pointer.
 * @param r2_end Second range end pointer.
 * @return Non-zero if both ranges are valid, zero otherwise.
 */
#define eya_ptr_ranges_is_valid(r1_begin, r1_end, r2_begin, r2_end)                                \
    (eya_ptr_range_is_valid(r1_begin, r1_end) && eya_ptr_range_is_valid(r2_begin, r2_end))

#endif // EYA_PTR_UTIL_H
