/**
 * @file math_util.h
 * @brief Mathematical utility macros for basic operations
 *
 * @details Provides function-like macros for common mathematical operations.
 *          Features include arithmetic operations, value clamping, type checks,
 *          angle conversions, and bit manipulation. All macros are properly
 *          parenthesized to ensure correct operator precedence.
 *
 * @warning Macros may evaluate arguments multiple times. Avoid using expressions
 *          with side effects (e.g., variable++ or function calls) as arguments.
 * @note Macros maintain internal dependencies - use consistent naming conventions.
 */

#ifndef EYA_MATH_UTIL_H
#define EYA_MATH_UTIL_H

// =============================================================================
// Mathematical Constants
// =============================================================================

/**
 * @def EYA_MATH_PI
 * @brief The mathematical constant π (pi)
 *
 * Used in angle conversions and geometric calculations.
 *
 * Example:
 * @code
 * double circumference = EYA_MATH_PI * diameter;
 * @endcode
 */
#define EYA_MATH_PI 3.14159265358979323846

/**
 * @def EYA_MATH_E
 * @brief Euler's number (base of natural logarithm)
 *
 * Used in exponential growth/decay calculations.
 *
 * Example:
 * @code
 * double decay = exp(-EYA_MATH_E * time);
 * @endcode
 */
#define EYA_MATH_E 2.71828182845904523536

/**
 * @def EYA_MATH_DEGREES_PER_TURN
 * @brief Degrees in a half circle (180°)
 *
 * Core constant for angle conversion macros.
 *
 * Example:
 * @code
 * double straight_angle = EYA_MATH_DEGREES_PER_TURN;
 * @endcode
 */
#define EYA_MATH_DEGREES_PER_TURN 180.0

// =============================================================================
// Core Arithmetic Operations
// =============================================================================

/**
 * @brief Addition
 * @param a First addend
 * @param b Second addend
 * @return Sum of a and b
 *
 * Example:
 * @code
 * int total = eya_math_add(5, 3);  // 8
 * @endcode
 */
#define eya_math_add(a, b) ((a) + (b))

/**
 * @brief Subtraction
 * @param a Minuend
 * @param b Subtrahend
 * @return Difference a - b
 *
 * Example:
 * @code
 * int diff = eya_math_sub(10, 4);  // 6
 * @endcode
 */
#define eya_math_sub(a, b) ((a) - (b))

/**
 * @brief Multiplication
 * @param a Multiplicand
 * @param b Multiplier
 * @return Product of a and b
 *
 * Example:
 * @code
 * double area = eya_math_mul(4.5, 2.0);  // 9.0
 * @endcode
 */
#define eya_math_mul(a, b) ((a) * (b))

/**
 * @brief Division
 * @param a Dividend
 * @param b Divisor (≠0)
 * @return Quotient of a divided by b
 *
 * Example:
 * @code
 * double ratio = eya_math_div(15.0, 4.0);  // 3.75
 * @endcode
 *
 * @warning Division by zero causes undefined behavior
 */
#define eya_math_div(a, b) ((a) / (b))

/**
 * @brief Modulo operation
 * @param a Dividend (integer)
 * @param b Divisor (integer, ≠0)
 * @return Remainder of a divided by b
 *
 * Example:
 * @code
 * int rem = eya_math_mod(17, 5);  // 2
 * @endcode
 *
 * @warning Undefined behavior for b=0
 */
#define eya_math_mod(a, b) ((a) % (b))

// =============================================================================
// Sign Checks
// =============================================================================

/**
 * @brief Positive number check
 * @param x Input value (integer or floating-point)
 * @return 1 if x > 0, 0 otherwise
 *
 * Example:
 * @code
 * if (eya_math_is_positive(balance)) { positive }
 * @endcode
 */
#define eya_math_is_positive(x) ((x) > 0)

/**
 * @brief Negative number check
 * @param x Input value (integer or floating-point)
 * @return 1 if x < 0, 0 otherwise
 *
 * Example:
 * @code
 * if (eya_math_is_negative(delta)) { negative }
 * @endcode
 */
#define eya_math_is_negative(x) ((x) < 0)

// =============================================================================
// Bitwise Operations
// =============================================================================

/**
 * @brief Bitwise AND
 * @param a First operand
 * @param b Second operand
 * @return Bitwise AND of a and b
 *
 * Example:
 * @code
 * uint8_t result = eya_math_bit_and(0b1100, 0b1010);  // 0b1000 (8)
 * @endcode
 */
#define eya_math_bit_and(a, b) ((a) & (b))

/**
 * @brief Bitwise OR
 * @param a First operand
 * @param b Second operand
 * @return Bitwise OR of a and b
 *
 * Example:
 * @code
 * uint8_t result = eya_math_bit_or(0b1100, 0b1010);   // 0b1110 (14)
 * @endcode
 */
#define eya_math_bit_or(a, b) ((a) | (b))

/**
 * @brief Bitwise XOR
 * @param a First operand
 * @param b Second operand
 * @return Bitwise XOR of a and b
 *
 * Example:
 * @code
 * uint8_t result = eya_math_bit_xor(0b1100, 0b1010);  // 0b0110 (6)
 * @endcode
 */
#define eya_math_bit_xor(a, b) ((a) ^ (b))

/**
 * @brief Bitwise NOT (One's complement)
 * @param a Operand
 * @return Bitwise inverse of a
 *
 * Example:
 * @code
 * uint8_t result = eya_math_bit_not(0b1010);  // 0b11110101 (245 for 8-bit)
 * @endcode
 */
#define eya_math_bit_not(a) (~(a))

/**
 * @brief Left bit shift
 * @param a Value to shift
 * @param n Number of bits to shift (≥0)
 * @return a shifted left by n bits
 *
 * Example:
 * @code
 * uint8_t result = eya_math_bit_shl(0b00001111, 2);  // 0b00111100 (60)
 * @endcode
 */
#define eya_math_bit_shl(a, n) ((a) << (n))

/**
 * @brief Right bit shift
 * @param a Value to shift
 * @param n Number of bits to shift (≥0)
 * @return a shifted right by n bits
 *
 * Example:
 * @code
 * uint8_t result = eya_math_bit_shr(0b11110000, 2);  // 0b00111100 (60)
 * @endcode
 */
#define eya_math_bit_shr(a, n) ((a) >> (n))

// =============================================================================
// Value Operations
// =============================================================================

/**
 * @brief Absolute value
 * @param x Input value
 * @return Non-negative magnitude
 *
 * Example:
 * @code
 * int magnitude = eya_math_abs(-8);  // 8
 * @endcode
 */
#define eya_math_abs(x) (eya_math_is_negative(x) ? -(x) : (x))

/**
 * @brief Maximum value
 * @param a First value
 * @param b Second value
 * @return Larger of a and b
 *
 * Example:
 * @code
 * int max_val = eya_math_max(-5, 10);  // 10
 * @endcode
 */
#define eya_math_max(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief Minimum value
 * @param a First value
 * @param b Second value
 * @return Smaller of a and b
 *
 * Example:
 * @code
 * double min_val = eya_math_min(7.8, 9.2);  // 7.8
 * @endcode
 */
#define eya_math_min(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief Clamps value between bounds
 * @param x Input value
 * @param lo Lower bound inclusive
 * @param hi Upper bound inclusive
 * @return Value constrained to [lo, hi] range
 *
 * Example:
 * @code
 * int clamped = eya_math_clamp(25, 10, 20);  // 20
 * @endcode
 */
#define eya_math_clamp(x, lo, hi) (eya_math_min(eya_math_max(x, lo), hi))

/**
 * @brief Value sign indicator
 * @param a Input value
 * @return -1 (negative), 0 (zero), or 1 (positive)
 *
 * Example:
 * @code
 * int sign = eya_math_sign(-0.5);  // -1
 * @endcode
 */
#define eya_math_sign(a) (((a) < 0) ? -1 : ((a) > 0) ? 1 : 0)

// =============================================================================
// Angle Conversion Utilities
// =============================================================================

/**
 * @brief Converts degrees to radians
 * @param deg Angle in degrees
 * @return Equivalent angle in radians
 *
 * Example:
 * @code
 * double radians = eya_math_deg_to_rad(90.0);  // π/2
 * @endcode
 */
#define eya_math_deg_to_rad(deg) (eya_math_mul(deg, EYA_MATH_PI) / EYA_MATH_DEGREES_PER_TURN)

/**
 * @brief Converts radians to degrees
 * @param rad Angle in radians
 * @return Equivalent angle in degrees
 *
 * Example:
 * @code
 * double degrees = eya_math_rad_to_deg(EYA_MATH_PI);  // 180.0
 * @endcode
 */
#define eya_math_rad_to_deg(rad) (eya_math_mul(rad, EYA_MATH_DEGREES_PER_TURN) / EYA_MATH_PI)

// =============================================================================
// Integer Properties
// =============================================================================

/**
 * @brief Even number check
 * @param n Integer to check
 * @return 1 if even, 0 otherwise
 *
 * Example:
 * @code
 * if (eya_math_is_even(x)) { even handling }
 * @endcode
 */
#define eya_math_is_even(n) (eya_math_mod(n, 2) == 0)

/**
 * @brief Odd number check
 * @param n Integer to check
 * @return 1 if odd, 0 otherwise
 *
 * Example:
 * @code
 * if (eya_math_is_odd(id)) { odd case }
 * @endcode
 */
#define eya_math_is_odd(n) (eya_math_mod(n, 2) != 0)

// =============================================================================
// Specialized Utilities
// =============================================================================

/**
 * @brief Decrement by one
 * @param a Value to decrement
 * @return a - 1
 *
 * Example:
 * @code
 * int prev_index = eya_math_sub_one(current);
 * @endcode
 */
#define eya_math_sub_one(a) eya_math_sub(a, 1)

/**
 * @brief Performs bitwise AND with the previous number
 * @param x Input value
 * @return Result of `x & (x-1)`
 * @note Internal helper for power-of-two checks
 */
#define eya_math_bitwise_and_with_prev(x) ((x) & eya_math_sub_one(x))

/**
 * @brief Checks if a number has exactly one bit set
 * @param x Input value
 * @return
 *   - Non-zero if x has exactly one bit set
 *   - Zero otherwise
 * @note Internal helper for power-of-two checks
 */
#define eya_math_has_single_bit(x) (!eya_math_bitwise_and_with_prev(x))

/**
 * @brief Power-of-two check
 * @param x Positive integer to check
 * @return 1 if power of two, 0 otherwise
 *
 * Example:
 * @code
 * if (eya_math_is_power_of_two(buffer_size)) { valid size }
 * @endcode
 */
#define eya_math_is_power_of_two(x) (eya_math_is_positive(x) && eya_math_has_single_bit(x))

/**
 * @brief Checks if division has no remainder
 * @param value Dividend (integer)
 * @param divisor Divisor (integer, ≠0)
 * @return
 *   - 1 if value is exactly divisible by divisor (no remainder)
 *   - 0 otherwise
 *
 * Example:
 * @code
 * if (eya_math_has_no_remainder(15, 3)) { // true }
 * if (eya_math_has_no_remainder(15, 4)) { // false }
 * @endcode
 *
 * @note This is a convenience wrapper around eya_math_mod()
 * @warning Undefined behavior for divisor=0
 */
#define eya_math_has_no_remainder(value, divisor) (eya_math_mod(value, divisor) == 0)

#endif // EYA_MATH_UTIL_H