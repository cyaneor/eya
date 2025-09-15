/**
 * @file compiler_attribute_noreturn.h
 * @brief Definition of macro for marking non-returning functions.
 *
 * This file provides the `EYA_COMPILER_ATTRIBUTE_NORETURN` macro
 * to indicate to the compiler that a function does not return
 * (e.g., program termination functions or infinite loops).
 *
 * Compiler-specific implementations:
 * - GCC/Clang: `__attribute__((noreturn))`
 * - MSVC: `__declspec(noreturn)`
 *
 * For unsupported compilers, an empty attribute is used
 * with a compilation warning about potential lack of support.
 *
 * @note Using this attribute enables compiler optimizations
 *       and more accurate warning generation.
 */

#ifndef EYA_COMPILER_ATTRIBUTE_NORETURN_H
#define EYA_COMPILER_ATTRIBUTE_NORETURN_H

#include "compiler_type.h"

#if (EYA_COMPILER_TYPE == EYA_COMPILER_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
/**
 * @def EYA_COMPILER_ATTRIBUTE_NORETURN
 * @brief Marks non-returning functions for GCC/Clang
 *
 * @details This attribute informs the compiler that the function
 *          does not return normally (e.g., calls abort(), exit(),
 *          or enters infinite loop). Enables additional optimizations
 *          and prevents unreachable code warnings.
 *
 * @warning Code following calls to functions with this attribute
 *          will be considered unreachable.
 */
#    define EYA_COMPILER_ATTRIBUTE_NORETURN __attribute__((noreturn))

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def EYA_COMPILER_ATTRIBUTE_NORETURN
 * @brief Marks non-returning functions for MSVC
 *
 * @details This specifier tells MSVC that the function doesn't
 *          return normally. Helps optimize code and suppress
 *          unreachable code warnings.
 *
 * @note Unlike GCC/Clang, in MSVC this specifier must be applied
 *       to the function declaration.
 */
#    define EYA_COMPILER_ATTRIBUTE_NORETURN __declspec(noreturn)

#else
/**
 * @def EYA_COMPILER_ATTRIBUTE_NORETURN
 * @brief Stub for compilers without noreturn support
 *
 * @warning Using this macro with unsupported compilers
 *          provides no optimization benefits and may
 *          fail to trigger unreachable code warnings.
 *
 * @details Expands to empty on unsupported compilers
 *          with a diagnostic message about missing
 *          attribute support.
 */
#    define EYA_COMPILER_ATTRIBUTE_NORETURN
#    pragma message("Warning: Compiler does not support noreturn attribute")
#endif

#endif // EYA_COMPILER_ATTRIBUTE_NORETURN_H