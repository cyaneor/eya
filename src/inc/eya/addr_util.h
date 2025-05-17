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
#define eya_addr_diff(addr1, addr2) (addr1 - addr2)

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
#define eya_addr_is_aligned_mask(addr, align) ((addr & ((align) - 1)) == 0)

/**
 * @def eya_addr_is_aligned_mod
 * @brief Checks address alignment using modulus operation
 *
 * This macro checks alignment by calculating the remainder of division
 * by the alignment value. Returns zero for aligned addresses.
 *
 * @warning Less efficient than bitmask method. Suitable for non-power-of-two
 *          alignment values but requires additional checks
 * @param addr Memory address to check
 * @param align Alignment boundary
 * @return 0 if aligned, non-zero remainder if not aligned
 */
#define eya_addr_is_aligned_mod(addr, align) ((addr) % (align))

#endif // EYA_ADDR_UTIL_H