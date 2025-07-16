/**
 * @file addr_util.h
 * @brief Utilities for address manipulation and pointer conversions.
 *
 * This header contains macros for conversions between pointers and addresses,
 * address difference calculations, and address alignment checks.
 */

#ifndef EYA_ADDR_UTIL_H
#define EYA_ADDR_UTIL_H

#include "addr.h"
#include "bit_util.h"
#include "reinterpret_cast.h"

/**
 * @def eya_addr_to_ptr
 * @brief Converts an address to a pointer of specified type.
 *
 * This macro uses `eya_reinterpret_cast`
 * to convert an integer address to
 * a pointer of type @p T*.
 *
 * @param T Target pointer type.
 * @param addr Integer address to convert.
 * @return Pointer of type @p T* pointing to @p addr.
 */
#define eya_addr_to_ptr(T, addr) eya_reinterpret_cast(T *, addr)

/**
 * @def eya_addr_to_void(addr)
 * @brief Converts an address to a void pointer.
 * @details This is a convenience wrapper around eya_addr_to_ptr()
 *          specifically for void pointers.
 * @param addr Integer address to convert.
 * @return void* pointer pointing to @p addr.
 */
#define eya_addr_to_void(addr) eya_addr_to_ptr(void, addr)

/**
 * @def eya_addr_diff
 * @brief Calculates the difference between two addresses.
 *
 * This macro returns the result of
 * subtracting address @p addr2 from @p addr1.
 *
 * @param addr1 First address.
 * @param addr2 Second address.
 * @return Address difference (addr1 - addr2).
 */
#define eya_addr_diff(addr1, addr2) eya_math_sub(addr1, addr2)

/**
 * @def eya_addr_align_by_offset
 * @brief Computes the offset of an address within a power-of-two alignment boundary
 *
 * This macro efficiently calculates the offset of an address from the previous
 * aligned boundary by performing a bitwise AND operation with (align-1).
 * This method is equivalent to addr % align but only works correctly when
 * align is a power of two.
 *
 * @note For correct results:
 *       - Alignment must be a power of two
 *       - Behavior is undefined if align is zero
 *       - Works with both pointer and integer addresses
 *
 * @param addr Memory address (pointer or integer) to compute offset for
 * @param align Alignment boundary (must be power of two and > 0)
 * @return Offset in bytes from the previous aligned address [0, align-1]
 */
#define eya_addr_align_by_offset(addr, align) eya_bit_and(addr, eya_math_sub_one(align))

/**
 * @def eya_addr_is_aligned
 * @brief Checks if an address meets the specified alignment requirement
 *
 * This macro verifies whether the given address is aligned to the specified
 * boundary by checking if the address offset within the alignment block is zero.
 *
 * @note Alignment value must be a power of two for correct results.
 *
 * @param addr Memory address to verify
 * @param align Alignment boundary to check against (must be power of two)
 * @return Non-zero (true) if address is aligned, zero (false) otherwise
 */
#define eya_addr_is_aligned(addr, align) (eya_addr_align_by_offset(addr, align) == 0)

/**
 * @def eya_addr_align_up
 * @brief Aligns a memory address up to the next specified boundary
 *
 * This macro adjusts the given address to the nearest higher (or equal) memory address
 * that matches the specified alignment boundary. Useful for ensuring memory allocations
 * or pointers meet specific alignment requirements.
 *
 * @note Alignment value must be a power of two for correct results.
 *       The operation works by rounding up to the next multiple of `align`.
 *
 * @param addr Memory address to align
 * @param align Alignment boundary (must be power of two)
 * @return Aligned memory address (always >= original address)
 *
 * @see eya_addr_align_mod
 * @see eya_addr_align_down
 */
#define eya_addr_align_up(addr, align)                                                             \
    eya_bit_and(eya_math_add(addr, eya_math_sub_one(align)), eya_bit_not(eya_math_sub_one(align)))

/**
 * @def eya_addr_align_down
 * @brief Aligns a memory address down to the previous specified boundary
 *
 * This macro adjusts the given address to the nearest lower (or equal) memory address
 * that matches the specified alignment boundary. Useful for finding the start of aligned
 * memory regions from an arbitrary address.
 *
 * @note Alignment value must be a power of two for correct results.
 *       The operation works by masking off lower bits of the address.
 *
 * @param addr Memory address to align
 * @param align Alignment boundary (must be power of two)
 * @return Aligned memory address (always <= original address)
 *
 * @see eya_addr_align_mod
 * @see eya_addr_align_up
 */
#define eya_addr_align_down(addr, align) eya_bit_and(addr, eya_bit_not(eya_math_sub_one(align)))

#endif // EYA_ADDR_UTIL_H