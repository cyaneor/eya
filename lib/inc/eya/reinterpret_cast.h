/**
 * @file reinterpret_cast.h
 * @brief Provides a portable reinterpret cast macro.
 *
 * This header file defines a macro for performing reinterpret casts
 * that works consistently in both C and C++ compilation environments.
 */

#ifndef EYA_REINTERPRET_CAST_H
#define EYA_REINTERPRET_CAST_H

#include "static_cast.h"

/**
 * @def eya_reinterpret_cast
 * @brief Macro for performing a reinterpret cast operation in a portable manner.
 *
 * This macro reinterprets the bits of the given @p v as the type @p T,
 * enabling type punning without changing the underlying bit representation.
 *
 * - In C++ mode (EYA_COMPILER_CXX == EYA_OPTION_ON),
 *   it uses the standard @c reinterpret_cast<T>(v) operator.
 * - In C mode (EYA_COMPILER_CXX == EYA_OPTION_OFF),
 *   it uses @c eya_static_cast(T, v),
 *   which applies a C-style cast (T(v)).
 *
 * @param T The target type to reinterpret the value as.
 * @param v The value whose bits should be reinterpreted.
 * @return The value reinterpreted as type @p T.
 *
 * @warning In C mode, the fallback to static cast may not provide the same strict guarantees
 *          as reinterpret_cast in C++, but it serves as a practical approximation for type punning.
 */
#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
#    define eya_reinterpret_cast(T, v) reinterpret_cast<T>(v)
#else
#    define eya_reinterpret_cast(T, v) eya_static_cast(T, v)
#endif

#endif // EYA_REINTERPRET_CAST_H