/**
 * @file reinterpret_cast.h
 * @brief Provides a portable reinterpret cast macro for C and C++.
 *
 * This header file defines a macro for performing reinterpret casts that
 * works consistently in both C and C++ compilation environments, providing
 * low-level pointer conversion with appropriate language semantics.
 *
 * In C++, `reinterpret_cast<T>(expr)` provides implementation-defined pointer
 * conversion with well-defined semantics. In C, this macro falls back to
 * static casting for equivalent functionality when not compiling as C++.
 */

#ifndef EYA_REINTERPRET_CAST_H
#define EYA_REINTERPRET_CAST_H

#include "static_cast.h"

#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
/**
 * @def eya_reinterpret_cast(T, expr)
 * @brief Type-safe reinterpret cast for C++ environments.
 *
 * Uses C++ `reinterpret_cast<T>(expr)` when compiling as C++ code, providing
 * implementation-defined pointer conversion between unrelated types with
 * well-defined semantics according to the C++ standard.
 *
 * @param T The target type to cast to (typically a pointer or reference type)
 * @param expr The expression to be reinterpreted
 * @return The expression reinterpreted as type T with implementation-defined conversion
 *
 * @note In C++, this preserves const/volatile qualifiers and provides stronger
 *       guarantees than C-style casts for pointer conversions.
 */
#    define eya_reinterpret_cast(T, expr) reinterpret_cast<T>(expr)
#else
/**
 * @def eya_reinterpret_cast(T, expr)
 * @brief Reinterpret cast emulation for non-C++ environments.
 *
 * Uses static casting `eya_static_cast(T, expr)` when compiling as C code,
 * providing equivalent pointer conversion functionality without C++'s
 * type safety features and semantic guarantees.
 *
 * @param T The target type to cast to
 * @param expr The expression to be reinterpreted
 * @return The expression cast to type T with C-style cast semantics
 *
 * @note In C mode, this behaves identically to static casting since C lacks
 *       proper reinterpret cast semantics. Use with caution for pointer
 *       conversions between unrelated types.
 */
#    define eya_reinterpret_cast(T, expr) eya_static_cast(T, expr)
#endif // EYA_COMPILER_CXX

#endif // EYA_REINTERPRET_CAST_H