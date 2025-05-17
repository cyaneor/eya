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
 * @brief Checks if a memory address is aligned
 *        to a specified boundary using modulus operation
 *
 * This macro determines alignment by calculating
 * the remainder of the address divided by the alignment value.
 * It returns `true` (non-zero) when the address is aligned,
 * and `false` (zero) otherwise.
 *
 * @warning Less efficient than bitmask-based alignment checks.
 *          Suitable for non-power-of-two alignment values,
 *          but ensure `align` is a positive integer to avoid undefined behavior.
 *
 *          Prefer bitmask methods (e.g., `& (align - 1)`)
 *          for power-of-two alignment where possible.
 *
 * @param[in] addr  Memory address to check (integer or pointer type).
 * @param[in] align Alignment boundary (must be a positive integer).
 * @return Non-zero (true) if `addr` is aligned to `align`, zero (false) otherwise.
 *
 * @note Unlike bitmask alignment checks, this method works for arbitrary alignment values,
 *       but division/modulus operations are generally slower than bitwise operations.
 */
#define eya_addr_is_aligned_mod(addr, align) (((addr) % (align)) == 0)

#endif // EYA_ADDR_UTIL_H