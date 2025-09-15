/**
 * @file compiler_attribute_target.h
 * @brief Compiler attribute macros for target architecture/platform specification.
 *
 * This header defines the `EYA_COMPILER_ATTRIBUTE_TARGET(x)` macro for
 * compiler-specific target architecture/platform attributes. The implementation
 * varies based on compiler type:
 *
 * - GCC/Clang: Uses `__attribute__((target(x)))`
 * - MSVC: No attribute defined
 * - Other compilers: Emits compiler warning
 */

#ifndef EYA_COMPILER_ATTRIBUTE_TARGET_H
#define EYA_COMPILER_ATTRIBUTE_TARGET_H

#include "compiler_type.h"

/**
 * @def EYA_COMPILER_ATTRIBUTE_TARGET(x)
 * @brief Target architecture attribute for GCC/Clang compilers
 *
 * @details Specifies target architecture/feature for code generation.
 *          Enables architecture-specific optimizations through
 *          `__attribute__((target(x)))` where `x` represents:
 *          - CPU architectures ("x86_64", "armv7")
 *          - Instruction sets ("avx2", "sse4.2")
 *
 * Example:
 * @code
 * EYA_COMPILER_ATTRIBUTE_TARGET("x86_64") void optimized_function() { ... }
 * @endcode
 *
 * @param x Target specification string
 * @note Supported only in GCC/Clang toolchains
 */
#if (EYA_COMPILER_TYPE == EYA_COMPILER_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
#    define EYA_COMPILER_ATTRIBUTE_TARGET(x) __attribute__((target(x)))

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def EYA_COMPILER_ATTRIBUTE_TARGET(x)
 * @brief Empty target attribute for MSVC compiler
 *
 * @details MSVC lacks equivalent target attribute syntax.
 *          Parameter `x` is ignored to maintain cross-compiler compatibility.
 *
 * @param x Unused architecture specification
 * @note Target-specific optimizations in MSVC require different mechanisms
 */
#    define EYA_COMPILER_ATTRIBUTE_TARGET(x)

#else
/**
 * @def EYA_COMPILER_ATTRIBUTE_TARGET(x)
 * @brief Target attribute placeholder for unsupported compilers
 *
 * @details Expands to empty implementation with compiler warning.
 *          Preserves API compatibility without functional implementation.
 *
 * @param x Unused target specification
 * @warning Target-specific optimizations unavailable
 */
#    define EYA_COMPILER_ATTRIBUTE_TARGET(x)
#    pragma message("Warning: Target attribute not supported by this compiler")
#endif

#endif // EYA_COMPILER_ATTRIBUTE_TARGET_H