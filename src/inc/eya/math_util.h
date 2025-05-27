#ifndef EYA_MATH_UTIL_H
#define EYA_MATH_UTIL_H

/**
 * @def eya_math_add
 * @brief Adds two numbers.
 * @param a First operand.
 * @param b Second operand.
 * @return The sum of a and b.
 * @note This is a function-like macro; arguments may be evaluated multiple times.
 */
#define eya_math_add(a, b) ((a) + (b))

/**
 * @def eya_math_sub
 * @brief Subtracts two numbers.
 * @param a First operand.
 * @param b Second operand.
 * @return The result of a minus b.
 * @note This is a function-like macro; arguments may be evaluated multiple times.
 */
#define eya_math_sub(a, b) ((a) - (b))

/**
 * @def eya_math_mul
 * @brief Multiplies two numbers.
 * @param a First operand.
 * @param b Second operand.
 * @return The product of a and b.
 * @note This is a function-like macro; arguments may be evaluated multiple times.
 */
#define eya_math_mul(a, b) ((a) * (b))

/**
 * @def eya_math_div
 * @brief Divides two numbers.
 * @param a Dividend.
 * @param b Divisor (must not be zero).
 * @return The quotient of a divided by b.
 * @note This is a function-like macro. For integers, performs integer division.
 * @warning Division by zero is undefined behavior.
 */
#define eya_math_div(a, b) ((a) / (b))

/**
 * @def eya_math_mod
 * @brief Computes the remainder of integer division.
 * @param a Integer dividend.
 * @param b Integer divisor (must not be zero).
 * @return The remainder of a divided by b.
 * @note This is a function-like macro; arguments must be integers.
 */
#define eya_math_mod(a, b) ((a) % (b))

/**
 * @def eya_math_abs
 * @brief Computes the absolute value.
 * @param x Input value.
 * @return x if x ≥ 0, -x otherwise.
 * @note This is a function-like macro; argument may be evaluated multiple times.
 */
#define eya_math_abs(x) ((x) < 0 ? -(x) : (x))

/**
 * @def eya_math_max
 * @brief Finds the greater of two values.
 * @param a First value.
 * @param b Second value.
 * @return The larger of a and b.
 * @note This is a function-like macro; arguments may be evaluated multiple times.
 */
#define eya_math_max(a, b) ((a) > (b) ? (a) : (b))

/**
 * @def eya_math_min
 * @brief Finds the lesser of two values.
 * @param a First value.
 * @param b Second value.
 * @return The smaller of a and b.
 * @note This is a function-like macro; arguments may be evaluated multiple times.
 */
#define eya_math_min(a, b) ((a) < (b) ? (a) : (b))

/**
 * @def eya_math_sign
 * @brief Determines the sign of a number.
 * @param a Input value.
 * @return -1 if a is negative, 0 if zero, 1 if positive.
 * @note This is a function-like macro; argument may be evaluated multiple times.
 */
#define eya_math_sign(a) (((a) < 0) ? -1 : ((a) > 0) ? 1 : 0)

/**
 * @def eya_math_is_even
 * @brief Checks if a number is even.
 * @param n Integer to check.
 * @return 1 (true) if n is even, 0 (false) otherwise.
 * @note This is a function-like macro; argument must be an integer.
 */
#define eya_math_is_even(n) (eya_math_mod(n, 2) == 0)

/**
 * @def eya_math_is_odd
 * @brief Checks if a number is odd.
 * @param n Integer to check.
 * @return 1 (true) if n is odd, 0 (false) otherwise.
 * @note This is a function-like macro; argument must be an integer.
 */
#define eya_math_is_odd(n) (eya_math_mod(n, 2) != 0)

#define eya_math_sub_one(a) ((a) - 1)

#endif // EYA_MATH_UTIL_H