#ifndef SE_BIT_UTIL_H
#define SE_BIT_UTIL_H

#include "math_util.h"
#include "type_util.h"

/**
 * @def eya_bit_and(a, b)
 * @brief Performs bitwise AND between two arguments.
 *
 * This macro computes the result of applying
 * the bitwise AND operation to two integer expressions.
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
#define eya_bit_and(a, b) ((a) & (b))

/**
 * @def eya_bit_not(x)
 * @brief Performs bitwise NOT (inversion) of the argument.
 *
 * This macro inverts all bits of an integer expression.
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
#define eya_bit_not(x) (~(x))

/**
 * @def eya_bit_has_common(a, b)
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
 * bool has_common = eya_bit_has_common(flags, mask); // Returns true (0b1000 != 0)
 * @endcode
 */
#define eya_bit_has_common(a, b) (eya_bit_and(a, b) != 0)

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
#define eya_bit_sign_type(T) (eya_type_cast(T, 1) << eya_bit_sign_type_pos(T))

#endif // SE_BIT_UTIL_H