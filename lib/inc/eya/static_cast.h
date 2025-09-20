/**
 * @file static_cast.h
 * @brief Header file defining a portable static cast macro for C and C++.
 *
 * This file provides a macro for performing static casts that works consistently
 * in both C and C++ compilation environments, enabling unified code patterns
 * across different language standards.
 *
 * In C++, `static_cast<T>(expr)` provides type-safe casting with compile-time
 * checks. In C, this macro falls back to traditional C-style casting `((T)(expr))`
 * when not compiling as C++.
 *
 * Including this header enables consistent static casting syntax in mixed
 * C/C++ codebases or portable libraries that need to compile in both languages.
 */

#ifndef EYA_STATIC_CAST_H
#define EYA_STATIC_CAST_H

#include "compiler.h"

#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
/**
 * @def eya_static_cast(T, expr)
 * @brief Type-safe static cast for C++ environments.
 *
 * Uses C++ `static_cast<T>(expr)` when compiling as C++ code, providing
 * compile-time type checking and safer casting semantics compared to
 * traditional C-style casts.
 *
 * @param T The target type to cast to
 * @param expr The expression to be cast
 * @return The expression cast to type T with static_cast semantics
 */
#    define eya_static_cast(T, expr) static_cast<T>(expr)
#elif (EYA_COMPILER_CXX == EYA_OPTION_OFF)
/**
 * @def eya_static_cast(T, expr)
 * @brief Static cast emulation for non-C++ environments.
 *
 * Uses traditional C-style casting `((T)(expr))` when compiling as C code,
 * providing equivalent functionality without C++'s type safety features.
 *
 * @param T The target type to cast to
 * @param expr The expression to be cast
 * @return The expression cast to type T with C-style cast semantics
 */
#    define eya_static_cast(T, expr) ((T)(expr))
#endif // EYA_COMPILER_CXX

#endif // EYA_STATIC_CAST_H