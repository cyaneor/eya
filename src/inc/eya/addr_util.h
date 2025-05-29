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
 * @def eya_uaddr_from_ptr
 * @brief Converts a pointer to an unsigned address.
 *
 * This macro uses `eya_reinterpret_cast` to convert a pointer
 * to an unsigned integer address type (`eya_uaddr_t`).
 *
 * @param ptr Pointer to convert.
 * @return Address of type `eya_uaddr_t` representing @p ptr.
 */
#define eya_uaddr_from_ptr(ptr) eya_reinterpret_cast(eya_uaddr_t, ptr)

/**
 * @def eya_saddr_from_ptr
 * @brief Converts a pointer to a signed address.
 *
 * This macro uses `eya_reinterpret_cast` to convert a pointer
 * to a signed integer address type (`eya_saddr_t`).
 *
 * @param ptr Pointer to convert.
 * @return Address of type `eya_saddr_t` representing @p ptr.
 */
#define eya_saddr_from_ptr(ptr) eya_reinterpret_cast(eya_saddr_t, ptr)

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
 * @def eya_addr_align_offset
 * @brief Computes the offset of an address within an alignment boundary
 *
 * This macro calculates the remainder when the address is divided by the
 * alignment value. The result represents how many bytes the address is offset
 * from the previous aligned boundary.
 *
 * @note Alignment value must be a power of two for correct results.
 *       The operation is equivalent to: addr % align
 *
 * @param addr Memory address to compute offset for
 * @param align Alignment boundary (must be power of two)
 * @return Offset of the address within the alignment block (0 to align-1)
 */
#define eya_addr_align_offset(addr, align) eya_bit_and(addr, eya_math_sub_one(align))

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
#define eya_addr_is_aligned(addr, align) (eya_addr_align_offset(addr, align) == 0)

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