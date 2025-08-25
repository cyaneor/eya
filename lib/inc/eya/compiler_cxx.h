/**
 * @file compiler_cxx.h
 * @brief Header file for C++ compiler detection and version information
 *
 * This file provides macros to detect whether the code is being compiled
 * as C++ or not, and to determine the C++ standard version being used.
 *
 * It uses the standard `__cplusplus` macro
 * to determine the compilation mode and version.
 */

#ifndef EYA_COMPILER_CXX_H
#define EYA_COMPILER_CXX_H

#include "option.h"

#ifdef __cplusplus
/**
 * @def EYA_COMPILER_CXX
 * @brief Macro indicating C++ compilation mode
 *
 * Defined as @ref EYA_OPTION_ON (1) when compiling as C++.
 * Indicates that C++ features and syntax are available.
 */
#    define EYA_COMPILER_CXX EYA_OPTION_ON

/**
 * @def EYA_COMPILER_CXX_VERSION
 * @brief Macro containing the C++ standard version value
 *
 * Contains the value of standard `__cplusplus` macro representing
 * the C++ standard version in use.
 *
 * Typical values:
 * - 199711L for C++98/C++03
 * - 201103L for C++11
 * - 201402L for C++14
 * - 201703L for C++17
 * - 202002L for C++20
 * - 202302L for C++23
 */
#    define EYA_COMPILER_CXX_VERSION __cplusplus
#else
/**
 * @def EYA_COMPILER_CXX
 * @brief Macro indicating C compilation mode
 *
 * Defined as @ref EYA_OPTION_OFF (0) when compiling as C.
 * Indicates that only standard C features and syntax are available,
 * and C++ features cannot be used.
 *
 * @note When this macro is set to EYA_OPTION_OFF,
 * the EYA_COMPILER_CXX_VERSION macro is not defined at all.
 */
#    define EYA_COMPILER_CXX EYA_OPTION_OFF
#endif // __cplusplus

#endif // EYA_COMPILER_CXX_H