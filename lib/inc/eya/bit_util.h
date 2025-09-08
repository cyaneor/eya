/**
 * @file bit_util.h
 * @brief Bit manipulation utilities
 *
 * This header provides macros for performing various bit operations including:
 * - Basic bitwise operations (AND, NOT)
 * - Bit intersection checks
 * - Sign bit manipulation
 * - Bit scanning (forward/reverse for 32/64-bit values)
 * - Bit rotation
 *
 * The implementation uses compiler intrinsics when available for optimal performance.
 */

#ifndef EYA_BIT_UTIL_H
#define EYA_BIT_UTIL_H

#include "compiler.h"
#include "math_util.h"
#include "type_util.h"

/**
 * @def eya_bit_shl(a, n)
 * @brief Performs a left shift operation on the given value.
 *
 * This macro shifts the bits of the first operand left
 * by the number of positions specified by the second operand.
 *
 * @param a The value to shift. Must be of integer type (int, char, uint32_t, etc.).
 * @param n The number of positions to shift left.
 * @return The result of the left shift operation (a << n).
 *
 * @note Delegates to eya_math_bit_shl for implementation.
 *
 * Example:
 * @code
 * uint8_t value = 0b00000001;
 * uint8_t result = eya_bit_shl(value, 2); // Result: 0b00000100
 * @endcode
 */
#define eya_bit_shl(a, n) eya_math_bit_shl(a, n)

/**
 * @def eya_bit_make(n)
 * @brief Creates a value with a single bit set at the specified position.
 *
 * This macro generates a value with only the bit at position n set to 1,
 * by shifting 1 left by n positions.
 *
 * @param n The bit position (0-based index).
 * @return A value with only the nth bit set to 1.
 *
 * @note Delegates to eya_bit_shl for implementation.
 *
 * Example:
 * @code
 * uint8_t bit = eya_bit_make(3); // Result: 0b00001000
 * @endcode
 */
#define eya_bit_make(n) eya_bit_shl(1, n)

/**
 * @def eya_bit_or(a, b)
 * @brief Performs a bitwise OR operation on two operands.
 *
 * This macro performs a bitwise OR between the two input operands,
 * combining their bits such that the result has a 1 in each position
 * where at least one of the operands has a 1.
 *
 * @param a First operand. Must be of integer type (int, char, uint32_t, etc.).
 * @param b Second operand. Must be of integer type (int, char, uint32_t, etc.).
 * @return The result of the bitwise OR operation (a | b).
 *
 * @note Delegates to eya_math_bit_or for implementation.
 *
 * Example:
 * @code
 * uint8_t result = eya_bit_or(0b1100, 0b1010); // Result: 0b1110 (14)
 * @endcode
 */
#define eya_bit_or(a, b) eya_math_bit_or(a, b)

/**
 * @def eya_bit_join(a, b)
 * @brief Alias for eya_bit_or, performs a bitwise OR operation on two operands.
 *
 * This macro is an alias for eya_bit_or, providing the same functionality
 * of performing a bitwise OR between two operands.
 *
 * @param a First operand. Must be of integer type (int, char, uint32_t, etc.).
 * @param b Second operand. Must be of integer type (int, char, uint32_t, etc.).
 * @return The result of the bitwise OR operation (a | b).
 *
 * @note Delegates to eya_bit_or for implementation.
 *
 * Example:
 * @code
 * uint8_t result = eya_bit_join(0b1100, 0b1010); // Result: 0b1110 (14)
 * @endcode
 */
#define eya_bit_join(a, b) eya_bit_or(a, b)

/**
 * @def eya_bit_and(a, b)
 * @brief Performs bitwise AND between two arguments.
 *
 * @param a First operand. Must be of integer type (int, char, uint32_t, etc.).
 * @param b Second operand. Must be of integer type (int, char, uint32_t, etc.).
 * @return The result of the bitwise operation (a & b).
 *         The type corresponds to the operands' type
 *         after usual arithmetic conversions.
 *
 * @note The macro may cause multiple evaluations of arguments.
 *       Do not use expressions with side effects (e.g., ++a),
 *       as they will be executed twice.
 *
 * Example:
 * @code
 * uint8_t flags = 0b1010;
 * uint8_t mask = 0b1100;
 * uint8_t result = eya_bit_and(flags, mask); // Result: 0b1000
 * @endcode
 */
#define eya_bit_and(a, b) eya_math_bit_and(a, b)

/**
 * @def eya_bit_not(x)
 * @brief Performs bitwise NOT (inversion) of the argument.
 *
 * @param x The operand. Must be of integer type (int, char, uint32_t, etc.).
 * @return The result of the bitwise operation (~x).
 *         The result type matches the operand type.
 *
 * @note The macro may cause multiple evaluation of the argument.
 *       Avoid using expressions with side effects (e.g., ++x),
 *       as they will be executed multiple times.
 *
 * Example:
 * @code
 * uint8_t flags = 0b00001111;
 * uint8_t inverted = eya_bit_not(flags); // Result: 0b11110000
 * @endcode
 */
#define eya_bit_not(x) eya_math_bit_not(x)

/**
 * @def eya_bit_intersect(a, b)
 * @brief Checks if two integers have at least one common bit set to 1.
 *
 * This macro determines whether there is any bit position where both arguments
 * have a 1 by evaluating the result of their bitwise AND operation.
 *
 * @param a First operand. Must be of integer type (int, char, uint32_t, etc.).
 * @param b Second operand. Must be of integer type (int, char, uint32_t, etc.).
 * @return Logical value (1/0) indicating presence of common bits:
 *         - 1 (true) if (a & b) != 0
 *         - 0 (false) otherwise
 * @note Inherits argument evaluation behavior from `eya_bit_and`.
 *       Avoid expressions with side effects (e.g., ++a)
 *       as they will be evaluated twice.
 *
 * Example:
 * @code
 * uint8_t flags = 0b1010;
 * uint8_t mask = 0b1100;
 * bool intersect = eya_bit_intersect(flags, mask); // Returns true (0b1000 != 0)
 * @endcode
 */
#define eya_bit_intersect(a, b) (eya_bit_and(a, b) != 0)

/**
 * @def eya_bit_is_disjoint(a, b)
 * @brief Checks if two integers have no common bits set to 1.
 *
 * This macro verifies that there are no bit positions where both arguments
 * have a 1 by evaluating the result of their bitwise AND operation.
 *
 * @param a First operand. Must be of integer type (int, char, uint32_t, etc.).
 * @param b Second operand. Must be of integer type (int, char, uint32_t, etc.).
 * @return Logical value (1/0) indicating disjointness:
 *         - 1 (true) if (a & b) == 0
 *         - 0 (false) otherwise
 * @note Inherits argument evaluation behavior from `eya_bit_and`.
 *       Avoid expressions with side effects (e.g., ++a)
 *       as they will be evaluated twice.
 *
 * Example:
 * @code
 * uint8_t a = 0b0010;
 * uint8_t b = 0b1100;
 * bool is_disjoint = eya_bit_is_disjoint(a, b); // Returns true (0b0000 == 0)
 * @endcode
 */
#define eya_bit_is_disjoint(a, b) (eya_bit_and(a, b) == 0)

/**
 * @def eya_bit_sign_type_pos(T)
 * @brief Determines the sign bit position for type T
 * @param T Signed integer type (e.g., int)
 * @return Position of the sign bit (0-based index)
 *
 * @note Implemented as macro.
 *       Requires eya_type_bits(T) definition
 *
 * Example:
 * @code
 * int pos = eya_bit_sign_type_pos(int); // 31 for 32-bit int
 * @endcode
 */
#define eya_bit_sign_type_pos(T) eya_math_sub_one(eya_type_bits(T))

/**
 * @def eya_bit_sign_type(T)
 * @brief Generates a value with the sign bit set for type T
 * @param T Signed integer type (e.g., int)
 * @return Value of type T with the most significant bit set
 *
 * @note Implemented as a macro. Requires:
 *       - eya_type_cast(T, val) for literal casting
 *       - eya_bit_sign_type_pos(T) to get sign bit position
 *
 * Example:
 * @code
 * int val = eya_bit_sign_type(int); // 0x80000000 (interpreted as -2147483648)
 * @endcode
 */
#define eya_bit_sign_type(T) eya_bit_shl(eya_type_cast(T, 1), eya_bit_sign_type_pos(T))

#if (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_GCC || EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_CLANG)
/**
 * @def eya_bit_scan_forward64(index, mask)
 * @brief Finds the index of the first set bit
 *        (least significant bit) in a 64-bit mask (GCC/Clang).
 *
 * Uses the compiler intrinsic `__builtin_ctzll`
 * for fast search of the first set bit index in a 64-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..63) will be stored.
 * @param[in] mask 64-bit mask to scan for set bits.
 *
 * @warning Behavior is undefined if `mask` is 0.
 *
 * Example:
 * @code
 * uint64_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_forward64(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_forward64(index, mask) (*(index) = __builtin_ctzll(mask))

/**
 * @def eya_bit_scan_reverse64(index, mask)
 * @brief Finds the index of the last set bit
 *        (most significant bit) in a 64-bit mask (GCC/Clang).
 *
 * Uses the compiler intrinsic `__builtin_clzll`
 * for fast search of the last set bit index in a 64-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..63) will be stored.
 * @param[in] mask 64-bit mask to scan for set bits.
 *
 * @warning Behavior is undefined if `mask` is 0.
 *
 * Example:
 * @code
 * uint64_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_reverse64(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_reverse64(index, mask) (*(index) = 63 - __builtin_clzll(mask))

/**
 * @def eya_bit_scan_forward32(index, mask)
 * @brief Finds the index of the first set bit
 *        (least significant bit) in a 32-bit mask (GCC/Clang).
 *
 * Uses the compiler intrinsic `__builtin_ctz`
 * for fast search of the first set bit index in a 32-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..31) will be stored.
 * @param[in] mask 32-bit mask to scan for set bits.
 *
 * @warning Behavior is undefined if `mask` is 0.
 *
 * Example:
 * @code
 * uint32_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_forward32(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_forward32(index, mask) (*(index) = __builtin_ctz(mask))

/**
 * @def eya_bit_scan_reverse32(index, mask)
 * @brief Finds the index of the last set bit
 *        (most significant bit) in a 32-bit mask (GCC/Clang).
 *
 * Uses the compiler intrinsic `__builtin_clz` for fast search
 * of the last set bit index in a 32-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..31) will be stored.
 * @param[in] mask 32-bit mask to scan for set bits.
 *
 * @warning Behavior is undefined if `mask` is 0.
 *
 * Example:
 * @code
 * uint32_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_reverse32(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_reverse32(index, mask) (*(index) = 31 - __builtin_clz(mask))
#elif (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_MSVC)

/**
 * @def eya_bit_scan_forward64(index, mask)
 * @brief Finds the index of the first set bit
 *        (least significant bit) in a 64-bit mask (MSVC).
 *
 * Uses the MSVC intrinsic `_BitScanForward64` for fast search
 * of the first set bit index in a 64-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..63) will be stored.
 * @param[in] mask 64-bit mask to scan for set bits.
 *
 * @return Non-zero if a set bit was found, zero if `mask` is 0.
 *
 * @note If `mask` is 0, the function returns 0,
 *       but this does not indicate that bit 0 is set.
 *
 * Example:
 * @code
 * uint64_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_forward64(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_forward64(index, mask) _BitScanForward64(index, mask)

/**
 * @def eya_bit_scan_reverse64(index, mask)
 * @brief Finds the index of the last set bit
 *        (most significant bit) in a 64-bit mask (MSVC).
 *
 * Uses the MSVC intrinsic `_BitScanReverse64` for fast search
 * of the last set bit index in a 64-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..63) will be stored.
 * @param[in] mask 64-bit mask to scan for set bits.
 *
 * @return Non-zero if a set bit was found, zero if `mask` is 0.
 *
 * @note If `mask` is 0, the function returns 0,
 *       but this does not indicate that bit 0 is set.
 *
 * Example:
 * @code
 * uint64_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_reverse64(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_reverse64(index, mask) _BitScanReverse64(index, mask)

/**
 * @def eya_bit_scan_forward32(index, mask)
 * @brief Finds the index of the first set bit
 *        (least significant bit) in a 32-bit mask (MSVC).
 *
 * Uses the MSVC intrinsic `_BitScanForward` for fast search
 * of the first set bit index in a 32-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..31) will be stored.
 * @param[in] mask 32-bit mask to scan for set bits.
 *
 * @return Non-zero if a set bit was found, zero if `mask` is 0.
 *
 * @note If `mask` is 0, the function returns 0,
 *       but this does not indicate that bit 0 is set.
 *
 * Example:
 * @code
 * uint32_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_forward32(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_forward32(index, mask) _BitScanForward(index, mask)

/**
 * @def eya_bit_scan_reverse32(index, mask)
 * @brief Finds the index of the last set bit
 *        (most significant bit) in a 32-bit mask (MSVC).
 *
 * Uses the MSVC intrinsic `_BitScanReverse` for fast search
 * of the last set bit index in a 32-bit number.
 *
 * @param[out] index Pointer to the variable where the found index (0..31) will be stored.
 * @param[in] mask 32-bit mask to scan for set bits.
 *
 * @return Non-zero if a set bit was found, zero if `mask` is 0.
 *
 * @note If `mask` is 0, the function returns 0,
 *       but this does not indicate that bit 0 is set.
 *
 * Example:
 * @code
 * uint32_t mask = 0b1000;
 * unsigned long index;
 * eya_bit_scan_reverse32(&index, mask); // index = 3
 * @endcode
 */
#    define eya_bit_scan_reverse32(index, mask) _BitScanReverse(index, mask)
#else
#    pragma message("Warning: Compiler does not support bit scan functions")
#endif

/**
 * @def eya_bit_rotl(x, n, bits)
 * @brief Performs a left bit rotation on the given value.
 *
 * This macro rotates the bits of the input value left by the specified number of positions.
 * Bits that are shifted out from the left are reintroduced on the right.
 *
 * @param x The value to rotate. Must be of integer type (int, char, uint32_t, etc.).
 * @param n The number of positions to rotate left.
 * @param bits The total bit width of the value (e.g., 32 for uint32_t).
 * @return The result of the left rotation operation.
 *
 * Example:
 * @code
 * uint32_t value = 0b10000000000000000000000000000001;
 * uint32_t result = eya_bit_rotl(value, 2, 32); // Result: 0b00000000000000000000000000000110
 * @endcode
 */
#define eya_bit_rotl(x, n, bits) (((x) << (n)) | ((x) >> ((bits) - (n))))

/**
 * @def eya_bit_rotr(x, n, bits)
 * @brief Performs a right bit rotation on the given value.
 *
 * This macro rotates the bits of the input value right by the specified number of positions.
 * Bits that are shifted out from the right are reintroduced on the left.
 *
 * @param x The value to rotate. Must be of integer type (int, char, uint32_t, etc.).
 * @param n The number of positions to rotate right.
 * @param bits The total bit width of the value (e.g., 32 for uint32_t).
 * @return The result of the right rotation operation.
 *
 * Example:
 * @code
 * uint32_t value = 0b10000000000000000000000000000001;
 * uint32_t result = eya_bit_rotr(value, 2, 32); // Result: 0b01100000000000000000000000000000
 * @endcode
 */
#define eya_bit_rotr(x, n, bits) (((x) >> (n)) | ((x) << ((bits) - (n))))

#endif // EYA_BIT_UTIL_H