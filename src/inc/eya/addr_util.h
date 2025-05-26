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
#define eya_addr_align_mask(addr, align) ((addr) & ((align) - 1))

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
 * @def eya_addr_align_rem
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
#define eya_addr_align_rem(addr, align) ((addr) % (align))

/**
 * @def eya_addr_is_aligned_rem
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
#define eya_addr_is_aligned_rem(addr, align) (eya_addr_align_rem(addr, align) == 0)

/**
 * @def eya_addr_align_up
 * @brief Aligns a memory address upward to the specified boundary
 *
 * This macro adjusts the given address to the nearest higher address
 * that is a multiple of the alignment value using bitmask operations.
 *
 * @warning Requires power-of-two alignment value for correct operation.
 *          Using non-power-of-two values will produce incorrect results.
 *
 * @param[in] addr  Memory address to align (integer or pointer type).
 * @param[in] align Alignment boundary (must be a power of two).
 * @return Adjusted address aligned upward to the specified boundary.
 *
 * @note More efficient than modulus-based alignment due to bitwise operations.
 *       Formula: (addr + align - 1) & ~(align - 1)
 */
#define eya_addr_align_up(addr, align) (((addr) + (align) - 1) & ~((align) - 1))

/**
 * @def eya_addr_align_down
 * @brief Aligns a memory address downward to the specified boundary
 *
 * This macro adjusts the given address to the nearest lower address
 * that is a multiple of the alignment value using bitmask operations.
 *
 * @warning Requires power-of-two alignment value for correct operation.
 *          Using non-power-of-two values will produce incorrect results.
 *
 * @param[in] addr  Memory address to align (integer or pointer type).
 * @param[in] align Alignment boundary (must be a power of two).
 * @return Adjusted address aligned downward to the specified boundary.
 *
 * @note More efficient than modulus-based alignment due to bitwise operations.
 *       Formula: addr & ~(align - 1)
 */
#define eya_addr_align_down(addr, align) ((addr) & ~((align) - 1))

#endif // EYA_ADDR_UTIL_H