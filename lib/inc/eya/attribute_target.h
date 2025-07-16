/**
 * @file attribute_target.h
 * @brief Header file containing the `EYA_ATTRIBUTE_TARGET(x)` macro wrapper
 *        for architecture-specific compiler attributes.
 *
 * This file provides the `EYA_ATTRIBUTE_TARGET(x)` macro as a wrapper
 * for `EYA_COMPILER_ATTRIBUTE_TARGET(x)`, used to specify target architecture
 * or platform based on compiler type.
 *
 * The macro behavior varies by compiler:
 * - GCC/Clang: Expands to `__attribute__((target(x)))`
 * - MSVC: No attribute defined
 * - Other compilers: Emits compiler warning
 *
 * Usage example:
 * @code
 * EYA_ATTRIBUTE_TARGET("x86_64");
 * @endcode
 *
 * @see EYA_COMPILER_ATTRIBUTE_TARGET
 * @note The `EYA_ATTRIBUTE_TARGET` macro behavior depends on
 *       the implementation of `EYA_COMPILER_ATTRIBUTE_TARGET`.
 */

#ifndef EYA_ATTRIBUTE_TARGET_H
#define EYA_ATTRIBUTE_TARGET_H

#include "compiler.h"

/**
 * @def EYA_ATTRIBUTE_TARGET(x)
 * @brief Wrapper macro for `EYA_COMPILER_ATTRIBUTE_TARGET(x)`
 *        specifying target architecture attributes.
 *
 * @details This macro forwards to compiler-specific implementations:
 * - GCC/Clang: Generates `__attribute__((target(x)))`
 * - MSVC: No operation (macro expands to empty)
 * - Other compilers: Triggers "attribute not supported" warning
 *
 * Use to optimize code generation for specific CPU architectures
 * or enable platform-specific instruction sets.
 *
 * @param x Target architecture/feature string
 *          (e.g., "x86_64", "avx2", "neon")
 *
 * Example:
 * @code
 * EYA_ATTRIBUTE_TARGET("sse4.2") void vector_operation() {
 *     // SIMD-optimized code
 * }
 * @endcode
 *
 * @see EYA_COMPILER_ATTRIBUTE_TARGET
 * @note Implementation details depend on the underlying
 *       compiler attribute macro behavior.
 */
#define EYA_ATTRIBUTE_TARGET(x) EYA_COMPILER_ATTRIBUTE_TARGET(x)

#endif // EYA_ATTRIBUTE_TARGET_H