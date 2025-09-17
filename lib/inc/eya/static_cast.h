/**
 * @file static_cast.h
 * @brief Provides a portable static cast macro.
 *
 * This header file defines a macro for performing static casts
 * that works consistently in both C and C++ compilation environments.
 */

#ifndef EYA_STATIC_CAST_H
#define EYA_STATIC_CAST_H

#include "compiler_cxx.h"

/**
 * @def eya_static_cast
 * @brief Macro for performing a static cast operation in a portable manner.
 *
 * This macro performs a static cast from the given @p value to the type @p T.
 * - In C++ mode (EYA_COMPILER_CXX == EYA_OPTION_ON),
 *   it uses the standard @c static_cast<T>(value) operator.
 * - In C mode (EYA_COMPILER_CXX == EYA_OPTION_OFF),
 *   it uses the C-style cast (T(value)).
 *
 * @param T The target type to cast to.
 * @param v The value to cast.
 * @return The value cast to type @p T.
 */
#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
#    define eya_static_cast(T, v) static_cast<T>(v)
#elif (EYA_COMPILER_CXX == EYA_OPTION_OFF)
#    define eya_static_cast(T, v) ((T)v)
#endif // __cplusplus

#endif // EYA_STATIC_CAST_H