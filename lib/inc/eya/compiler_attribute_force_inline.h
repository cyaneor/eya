/**
 * @file compiler_attribute_force_inline.h
 * @brief Header file defining function force inlining attribute.
 *
 * This file provides the `EYA_COMPILER_ATTRIBUTE_FORCE_INLINE` macro
 * for compiler-specific function force inlining. The macro is used
 * to optimize performance-critical code sections by minimizing
 * function call overhead through forced inlining.
 *
 * Supported compilers:
 * - GCC/Clang: `__attribute__((always_inline)) inline`
 * - MSVC: `__forceinline`
 *
 * @note On unsupported compilers, the macro expands to empty
 *       with a compiler warning.
 *
 * Macros:
 * - `EYA_COMPILER_ATTRIBUTE_FORCE_INLINE`:
 *    Forces function inlining at compiler level
 */

#ifndef EYA_COMPILER_ATTRIBUTE_FORCE_INLINE_H
#define EYA_COMPILER_ATTRIBUTE_FORCE_INLINE_H

#include "compiler_type.h"

#if (EYA_COMPILER_TYPE == EYA_COMPILER_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
/**
 * @def EYA_COMPILER_ATTRIBUTE_FORCE_INLINE
 * @brief Forces function inlining for GCC/Clang compilers
 * @details This macro ensures the compiler attempts to inline
 *          the function regardless of optimization level.
 *          Used in performance-critical code sections where
 *          minimizing call overhead is crucial.
 */
#    define EYA_COMPILER_ATTRIBUTE_FORCE_INLINE __attribute__((always_inline)) inline

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def EYA_COMPILER_ATTRIBUTE_FORCE_INLINE
 * @brief Forces function inlining for MSVC compiler
 * @details Directs the MSVC compiler to inline the function
 *          whenever possible. Particularly useful for
 *          performance-sensitive code paths requiring
 *          minimal call overhead.
 */
#    define EYA_COMPILER_ATTRIBUTE_FORCE_INLINE __forceinline
#else
/**
 * @def EYA_COMPILER_ATTRIBUTE_FORCE_INLINE
 * @brief Empty stub for unsupported compilers
 * @warning Using this macro with unsupported compilers
 *          will generate a warning and provide no
 *          inlining guarantees. Function behavior
 *          depends on compiler's default inlining
 *          heuristics.
 */
#    define EYA_COMPILER_ATTRIBUTE_FORCE_INLINE

#    pragma message("Warning: Compiler does not support force inlining attribute")
#endif

#endif // EYA_COMPILER_ATTRIBUTE_FORCE_INLINE_H