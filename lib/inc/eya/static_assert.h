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

#include "compiler.h"

/**
 * @def eya_static_assert(expr, msg)
 * @brief Compile-time assertion macro that works in both C and C++.
 *
 * This macro provides a portable way to perform compile-time assertions across different
 * languages and compilers. It uses the appropriate static assertion mechanism based on:
 * - C++'s `static_assert` when compiling as C++
 * - C11's `_Static_assert` for C compilers (except MSVC)
 * - MSVC's `static_assert` (which works in both C and C++ modes)
 *
 * @param expr The boolean expression to evaluate at compile time.
 * @param msg The error message to display if the assertion fails (must be a string literal).
 *
 * @note The message parameter is mandatory in C++ but optional in C (C11 and later).
 *
 * Example Usage:
 * @code
 * eya_static_assert(sizeof(int) == 4, "int must be 4 bytes");
 * @endcode
 *
 * Compiler Support:
 * - C++: Uses standard static_assert
 * - MSVC: Uses static_assert in both C and C++ modes
 * - Other C compilers: Uses _Static_assert (C11 feature)
 */
#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
#    define eya_static_assert(expr, msg) static_assert(expr, msg)
#elif (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_MSVC)
#    define eya_static_assert(expr, msg) static_assert(expr, msg)
#else
#    define eya_static_assert(expr, msg) _Static_assert(expr, msg)
#endif

#endif // EYA_STATIC_ASSERT_H