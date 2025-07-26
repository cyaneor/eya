/**
 * @file static_assert.h
 * @brief Macro definition for compile-time condition checking.
 *
 * This file provides the `eya_static_assert` macro for performing
 * static assertions during compilation. The macro generates compilation errors
 * when the specified boolean expression evaluates to false, enabling early
 * detection of potential issues during development.
 *
 * @note Essential for code requiring strict validation of type sizes,
 *       compatibility assumptions, or other compile-time verifiable conditions.
 */

#ifndef EYA_STATIC_ASSERT_H
#define EYA_STATIC_ASSERT_H

#ifdef __cplusplus
/**
 * @def eya_static_assert(expr, msg)
 * @brief Performs compile-time static assertion check (C++ implementation)
 *
 * Verifies boolean expression `expr` during compilation using C++11 static_assert.
 * Generates compilation error with specified message `msg` if assertion fails.
 *
 * @param expr Boolean expression that must evaluate to true for successful compilation
 * @param msg Error message string literal displayed when assertion fails
 *
 * @note Enforces code assumptions at compile-time to prevent potential runtime errors
 *
 * Usage example:
 * @code
 * #define MY_TYPE_SIZE 4
 * eya_static_assert(sizeof(int) == MY_TYPE_SIZE, "int size must match MY_TYPE_SIZE");
 * @endcode
 */
#    define eya_static_assert(expr, msg) static_assert(expr, msg)
#else
/**
 * @def eya_static_assert(expr, msg)
 * @brief Compile-time assertion check (C11 implementation)
 *
 * Verifies boolean expression `expr` during compilation using C11 _Static_assert.
 * Triggers compilation error with message `msg` if assertion fails.
 *
 * @param expr Boolean expression that must be true
 * @param msg Diagnostic message displayed when assertion fails
 *
 * @note Critical for validating platform-specific assumptions in C code
 *
 * Usage example:
 * @code
 * eya_static_assert(sizeof(int) == 4, "int type size must be 4 bytes");
 * @endcode
 */
#    define eya_static_assert(expr, msg) _Static_assert(expr, msg)
#endif // __cplusplus

#endif // EYA_STATIC_ASSERT_H