/**
 * @file compiler_std_version.h
 * @brief Macro definitions for C language standard versions.
 *
 * This header provides macros representing different C language standard versions
 * (C99, C11, C17, C23) for compatibility control and feature detection
 * based on compiler-supported standards.
 *
 * Macros:
 * - `EYA_COMPILER_STD_VERSION_C99`: C99 standard (ISO/IEC 9899:1999)
 * - `EYA_COMPILER_STD_VERSION_C11`: C11 standard (ISO/IEC 9899:2011)
 * - `EYA_COMPILER_STD_VERSION_C17`: C17/C18 standard (ISO/IEC 9899:2018)
 * - `EYA_COMPILER_STD_VERSION_C23`: C23 standard (ISO/IEC 9899:2023)
 * - `EYA_COMPILER_STD_VERSION_C`: Maps to compiler's __STDC_VERSION__ macro
 *
 * @note C23 version value varies by compiler:
 *       - Clang uses 202311L
 *       - Other compilers default to 202000L
 */

#ifndef EYA_COMPILER_STD_VERSION_H
#define EYA_COMPILER_STD_VERSION_H

#include "compiler_type.h"

/**
 * @def EYA_COMPILER_STD_VERSION_C99
 * @brief Represents ISO/IEC 9899:1999 standard (C99)
 */
#define EYA_COMPILER_STD_VERSION_C99 199901L

/**
 * @def EYA_COMPILER_STD_VERSION_C11
 * @brief Represents ISO/IEC 9899:2011 standard (C11)
 */
#define EYA_COMPILER_STD_VERSION_C11 201112L

/**
 * @def EYA_COMPILER_STD_VERSION_C17
 * @brief Represents ISO/IEC 9899:2018 standard (C17/C18)
 */
#define EYA_COMPILER_STD_VERSION_C17 201710L

/**
 * @def EYA_COMPILER_STD_VERSION_C23
 * @brief Represents ISO/IEC 9899:2023 standard (C23)
 * @details Version value varies by compiler implementation:
 *          - Clang: 202311L
 *          - Other compilers: 202000L (provisional value)
 */
#if (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
#    define EYA_COMPILER_STD_VERSION_C23 202311L
#else
#    define EYA_COMPILER_STD_VERSION_C23 202000L
#endif

/**
 * @def EYA_COMPILER_STD_VERSION_C
 * @brief Maps to compiler's __STDC_VERSION__ macro
 * @details Reflects the actual C standard version supported by the compiler
 */
#define EYA_COMPILER_STD_VERSION_C __STDC_VERSION__

#endif // EYA_COMPILER_STD_VERSION_H