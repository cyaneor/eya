/**
 * @file bit_util.h
 * @brief Bit manipulation utilities and operations
 *
 * This header provides a comprehensive set of macros
 * for bit-level operations including shifting, masking,
 * checking, and manipulating bits in integer values.
 *
 * The macros are designed to be compiler-agnostic where possible
 * and provide optimized implementations for different compilers.
 */

#ifndef EYA_BIT_UTIL_H
#define EYA_BIT_UTIL_H

#include "math_util.h"
#include "type_util.h"

/**
 * @def eya_bit_shl(a, n)
 * @brief Performs a left shift operation
 * @param a The value to shift (integer type)
 * @param n Number of positions to shift left
 * @return Result of left shift operation (a << n)
 */
#define eya_bit_shl(a, n) eya_math_bit_shl(a, n)

/**
 * @def eya_bit_shr(a, n)
 * @brief Performs a right shift operation
 * @param a The value to shift (integer type)
 * @param n Number of positions to shift right
 * @return Result of right shift operation (a >> n)
 */
#define eya_bit_shr(a, n) eya_math_bit_shr(a, n)

/**
 * @def eya_bit_make(n)
 * @brief Creates value with single bit set at specified position
 * @param n Bit position (0-based index)
 * @return Value with only nth bit set to 1
 */
#define eya_bit_make(n) eya_bit_shl(1, n)

/**
 * @def eya_bit_or(a, b)
 * @brief Performs bitwise OR operation
 * @param a First operand (integer type)
 * @param b Second operand (integer type)
 * @return Result of bitwise OR (a | b)
 */
#define eya_bit_or(a, b) eya_math_bit_or(a, b)

/**
 * @def eya_bit_join(a, b)
 * @brief Joins bits from two values (alias for bitwise OR)
 * @param a First value
 * @param b Second value
 * @return Combined bits (a | b)
 */
#define eya_bit_join(a, b) eya_bit_or(a, b)

/**
 * @def eya_bit_join_n(x, n)
 * @brief Sets specific bit in value
 * @param x Original value
 * @param n Bit position to set
 * @return Value with nth bit set
 */
#define eya_bit_join_n(x, n) eya_bit_join(x, eya_bit_make(n))

/**
 * @def eya_bit_xor(a, b)
 * @brief Performs bitwise XOR operation
 * @param a First operand (integer type)
 * @param b Second operand (integer type)
 * @return Result of bitwise XOR (a ^ b)
 */
#define eya_bit_xor(a, b) eya_math_bit_xor(a, b)

/**
 * @def eya_bit_toggle(a, b)
 * @brief Toggles bits specified by bitmask
 * @param a Original value
 * @param b Bitmask specifying bits to toggle
 * @return Value with specified bits inverted
 */
#define eya_bit_toggle(a, b) eya_bit_xor(a, b)

/**
 * @def eya_bit_toggle_n(x, n)
 * @brief Toggles specific bit in value
 * @param x Original value
 * @param n Bit position to toggle
 * @return Value with nth bit toggled
 */
#define eya_bit_toggle_n(x, n) eya_bit_toggle(x, eya_bit_make(n))

/**
 * @def eya_bit_and(a, b)
 * @brief Performs bitwise AND operation
 * @param a First operand (integer type)
 * @param b Second operand (integer type)
 * @return Result of bitwise AND (a & b)
 */
#define eya_bit_and(a, b) eya_math_bit_and(a, b)

/**
 * @def eya_bit_not(x)
 * @brief Performs bitwise NOT operation
 * @param x Operand (integer type)
 * @return Result of bitwise NOT (~x)
 */
#define eya_bit_not(x) eya_math_bit_not(x)

/**
 * @def eya_bit_clear(a, b)
 * @brief Clears bits specified by bitmask
 * @param a Original value
 * @param b Bitmask specifying bits to clear
 * @return Value with specified bits cleared
 */
#define eya_bit_clear(a, b) eya_bit_and(a, eya_bit_not(b))

/**
 * @def eya_bit_clear_n(x, n)
 * @brief Clears specific bit in value
 * @param x Original value
 * @param n Bit position to clear
 * @return Value with nth bit cleared
 */
#define eya_bit_clear_n(x, n) eya_bit_clear(x, eya_bit_make(n))

/**
 * @def eya_bit_check(a, b)
 * @brief Checks if any bits are set in both operands
 * @param a First value
 * @param b Second value
 * @return Non-zero if (a & b) != 0, zero otherwise
 */
#define eya_bit_check(a, b) (eya_bit_and(a, b) != 0)

/**
 * @def eya_bit_check_n(x, n)
 * @brief Checks if specific bit is set
 * @param x Value to check
 * @param n Bit position to check
 * @return Non-zero if nth bit is set, zero otherwise
 */
#define eya_bit_check_n(x, n) eya_bit_check(x, eya_bit_make(n))

/**
 * @def eya_bit_intersect(a, b)
 * @brief Checks if values have common bits set
 * @param a First value
 * @param b Second value
 * @return Non-zero if (a & b) != 0, zero otherwise
 */
#define eya_bit_intersect(a, b) eya_bit_check(a, b)

/**
 * @def eya_bit_is_odd(x)
 * @brief Checks if value is odd
 * @param x Integer value to check
 * @return Non-zero if value is odd, zero if even
 */
#define eya_bit_is_odd(x) eya_bit_intersect(x, 1)

/**
 * @def eya_bit_is_disjoint(a, b)
 * @brief Checks if values have no common bits set
 * @param a First value
 * @param b Second value
 * @return Non-zero if (a & b) == 0, zero otherwise
 */
#define eya_bit_is_disjoint(a, b) (eya_bit_and(a, b) == 0)

/**
 * @def eya_bit_is_even(x)
 * @brief Checks if value is even
 * @param x Integer value to check
 * @return Non-zero if value is even, zero if odd
 */
#define eya_bit_is_even(x) eya_bit_is_disjoint(x, 1)

/**
 * @def eya_bit_sign_type_pos(T)
 * @brief Gets sign bit position for type
 * @param T Signed integer type
 * @return Position of sign bit (0-based index)
 */
#define eya_bit_sign_type_pos(T) eya_math_sub_one(eya_type_bits(T))

/**
 * @def eya_bit_sign_type(T)
 * @brief Creates value with sign bit set for type
 * @param T Signed integer type
 * @return Value with most significant bit set
 */
#define eya_bit_sign_type(T) eya_bit_shl(eya_type_one_v(T), eya_bit_sign_type_pos(T))

#if EYA_COMPILER_GCC_LIKE
/**
 * @def eya_bit_scan_forward64(index, mask)
 * @brief Finds first set bit in 64-bit mask (GCC/Clang)
 * @param index Output variable for bit index (0-63)
 * @param mask 64-bit mask to scan
 */
#    define eya_bit_scan_forward64(index, mask) (*(index) = __builtin_ctzll(mask))

/**
 * @def eya_bit_scan_reverse64(index, mask)
 * @brief Finds last set bit in 64-bit mask (GCC/Clang)
 * @param index Output variable for bit index (0-63)
 * @param mask 64-bit mask to scan
 */
#    define eya_bit_scan_reverse64(index, mask) (*(index) = 63 - __builtin_clzll(mask))

/**
 * @def eya_bit_scan_forward32(index, mask)
 * @brief Finds first set bit in 32-bit mask (GCC/Clang)
 * @param index Output variable for bit index (0-31)
 * @param mask 32-bit mask to scan
 */
#    define eya_bit_scan_forward32(index, mask) (*(index) = __builtin_ctz(mask))

/**
 * @def eya_bit_scan_reverse32(index, mask)
 * @brief Finds last set bit in 32-bit mask (GCC/Clang)
 * @param index Output variable for bit index (0-31)
 * @param mask 32-bit mask to scan
 */
#    define eya_bit_scan_reverse32(index, mask) (*(index) = 31 - __builtin_clz(mask))
#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def eya_bit_scan_forward64(index, mask)
 * @brief Finds first set bit in 64-bit mask (MSVC)
 * @param index Output variable for bit index (0-63)
 * @param mask 64-bit mask to scan
 * @return Non-zero if bit found, zero if mask is 0
 */
#    define eya_bit_scan_forward64(index, mask) _BitScanForward64(index, mask)

/**
 * @def eya_bit_scan_reverse64(index, mask)
 * @brief Finds last set bit in 64-bit mask (MSVC)
 * @param index Output variable for bit index (0-63)
 * @param mask 64-bit mask to scan
 * @return Non-zero if bit found, zero if mask is 0
 */
#    define eya_bit_scan_reverse64(index, mask) _BitScanReverse64(index, mask)

/**
 * @def eya_bit_scan_forward32(index, mask)
 * @brief Finds first set bit in 32-bit mask (MSVC)
 * @param index Output variable for bit index (0-31)
 * @param mask 32-bit mask to scan
 * @return Non-zero if bit found, zero if mask is 0
 */
#    define eya_bit_scan_forward32(index, mask) _BitScanForward(index, mask)

/**
 * @def eya_bit_scan_reverse32(index, mask)
 * @brief Finds last set bit in 32-bit mask (MSVC)
 * @param index Output variable for bit index (0-31)
 * @param mask 32-bit mask to scan
 * @return Non-zero if bit found, zero if mask is 0
 */
#    define eya_bit_scan_reverse32(index, mask) _BitScanReverse(index, mask)
#else
#    pragma message("Warning: Compiler does not support bit scan functions")
#endif

/**
 * @def eya_bit_rotl(x, n, bits)
 * @brief Performs left bit rotation
 * @param x Value to rotate (integer type)
 * @param n Number of positions to rotate left
 * @param bits Total bit width of value
 * @return Result of left rotation
 */
#define eya_bit_rotl(x, n, bits) (((x) << (n)) | ((x) >> ((bits) - (n))))

/**
 * @def eya_bit_rotr(x, n, bits)
 * @brief Performs right bit rotation
 * @param x Value to rotate (integer type)
 * @param n Number of positions to rotate right
 * @param bits Total bit width of value
 * @return Result of right rotation
 */
#define eya_bit_rotr(x, n, bits) (((x) >> (n)) | ((x) << ((bits) - (n))))

#endif // EYA_BIT_UTIL_H