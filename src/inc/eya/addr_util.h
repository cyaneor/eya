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
 * @def eya_addr_align_mask
 * @brief Computes alignment offset using bitmask operation
 *
 * This macro calculates the byte offset of a memory address from the previous
 * alignment boundary by applying a bitmask. It performs a bitwise AND between
 * the address and (alignment - 1), which is equivalent to calculating:
 * offset = addr % align, but more efficient for power-of-two alignment values.
 *
 * @note Alignment value must be a power of two for correct results.
 *       To align the address to the next boundary, subtract the result from
 *       the alignment value when offset is non-zero.
 *
 * @param addr Memory address to check (integer or pointer type)
 * @param align Alignment boundary (must be power of two)
 * @return Offset in bytes from previous aligned address (0 indicates already aligned)
 */
#define eya_addr_align_mask(addr, align) eya_bit_and(addr, eya_math_sub_one(align))

/**
 * @def eya_addr_is_aligned_mask
 * @brief Checks if an address is aligned using bitmask comparison
 *
 * This macro checks if the specified address has its least significant bits
 * (corresponding to the alignment mask) set to zero. It is optimized for
 * powers of two alignment values.
 *
 * @note Alignment value must be a power of two for correct results
 * @param addr Memory address to check
 * @param align Alignment boundary (power of two)
 * @return true - address is aligned, false - not aligned
 */
#define eya_addr_is_aligned_mask(addr, align) (eya_addr_align_mask(addr, align) == 0)

/**
 * @def eya_addr_align_mod
 * @brief Calculates the address offset from the nearest alignment boundary
 *
 * This macro computes the remainder when the specified address is divided by
 * the alignment value. The result represents how many bytes the address needs
 * to be adjusted to reach the previous alignment boundary.
 *
 * @note Alignment value must be a power of two for correct results.
 *       For alignment to next boundary, subtract the result from alignment value.
 *
 * @param addr Memory address to check
 * @param align Alignment boundary (must be power of two)
 * @return Offset in bytes from previous aligned address (0 indicates already aligned)
 */
#define eya_addr_align_mod(addr, align) eya_math_mod(addr, align)

/**
 * @def eya_addr_is_aligned_mod
 * @brief Checks if a memory address is aligned to the specified boundary
 *
 * This macro determines whether the given address is aligned to the specified alignment
 * boundary by checking if the remainder of the address divided by the alignment is zero.
 *
 * @note The alignment value must be a power of two to ensure correct behavior.
 *       Uses ::eya_addr_align_mod internally to compute the alignment remainder.
 *
 * @param addr Memory address to check for alignment
 * @param align Alignment boundary (must be power of two)
 * @return `true` (non-zero) if address is aligned to the specified boundary
 *         `false` (zero) if address requires adjustment to meet alignment
 *
 * @see eya_addr_align_mod
 */
#define eya_addr_is_aligned_mod(addr, align) (eya_addr_align_mod(addr, align) == 0)

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