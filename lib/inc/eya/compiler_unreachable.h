/**
 * @file compiler_unreachable.h
 * @brief Macro definition for compiler-specific unreachable code hints.
 *
 * This header defines the `eya_compiler_unreachable` macro to indicate
 * unreachable code paths to different compilers, enabling optimization improvements.
 *
 * The macro provides cross-compiler support for:
 * - GCC/Clang: Uses `__builtin_unreachable()`
 * - MSVC: Implements via `__assume(0)` directive
 * - Others: Empty implementation with compiler warning
 *
 * @details
 * - GCC/Clang: Informs compiler about unreachable code through built-in
 * - MSVC: Uses assumption directive for code path optimization
 * - Unsupported compilers: Generates empty implementation with diagnostic
 *
 * @warning Using with unsupported compilers disables optimization hints
 *          and may generate compiler warnings.
 *
 * @pre Include this header to enable unreachable code hint functionality.
 */

#ifndef EYA_COMPILER_UNREACHABLE_H
#define EYA_COMPILER_UNREACHABLE_H

#include "compiler_type.h"

#if (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_CLANG)
/**
 * @def eya_compiler_unreachable
 * @brief Unreachable code hint for GCC/Clang compilers
 * @details Uses built-in function to mark unreachable code paths,
 *          enabling dead code elimination and optimization.
 */
#    define eya_compiler_unreachable() __builtin_unreachable()

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_MSVC)
/**
 * @def eya_compiler_unreachable
 * @brief Unreachable code directive for MSVC
 * @details Employs assumption intrinsic to optimize code flow
 *          by indicating unreachable execution paths.
 */
#    define eya_compiler_unreachable() __assume(0)

#else
/**
 * @def eya_compiler_unreachable
 * @brief Empty stub for unsupported compilers
 * @warning Unreachable hint functionality disabled -
 *          no optimization benefits provided.
 * @details Generates compiler warning about missing support
 *          while maintaining source compatibility.
 */
#    define eya_compiler_unreachable()

#    pragma message("Warning: Compiler does not support unreachable hint functionality")
#endif

#endif // EYA_COMPILER_UNREACHABLE_H