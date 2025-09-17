/**
 * @file reinterpret_cast.h
 * @brief Macro definition for type-safe casting
 *
 * This file contains the `eya_reinterpret_cast` macro that enables
 * type casting with different implementations depending on
 * whether the code is compiled as C++ or C.
 */

#ifndef EYA_REINTERPRET_CAST_H
#define EYA_REINTERPRET_CAST_H

#include "compiler.h"

#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
/**
 * @brief Type casting in C++
 *
 * Uses reinterpret_cast for type conversion
 *
 * @param T Target type
 * @param V Value to cast
 * @return Casted value of type T
 */
#    define eya_reinterpret_cast(T, V) reinterpret_cast<T>(V)
#else
/**
 * @brief Type casting in C
 *
 * Uses standard C-style cast
 *
 * @param T Target type
 * @param V Value to cast
 * @return Casted value of type T
 */
#    define eya_reinterpret_cast(T, V) ((T)V)
#endif // __cplusplus

#endif // EYA_REINTERPRET_CAST_H