/**
 * @file attribute_force_inline.h
 * @brief Header file providing an alias for the function force inlining attribute.
 *
 * This file defines the `EYA_ATTRIBUTE_FORCE_INLINE` macro,
 * which serves as a convenient alias for `EYA_COMPILER_ATTRIBUTE_FORCE_INLINE`.
 *
 * It is used to enforce function inlining in performance-critical code sections.
 *
 * Key Features:
 * - Provides a uniform shorthand name for the inlining attribute
 * - Fully compatible with the original `EYA_COMPILER_ATTRIBUTE_FORCE_INLINE` macro
 * - Supports all compilers compatible with the base macro
 *
 * Usage example:
 * @code
 * EYA_ATTRIBUTE_FORCE_INLINE void critical_function() {
 *     // Function body
 * }
 * @endcode
 *
 * @see EYA_COMPILER_ATTRIBUTE_FORCE_INLINE
 */
#ifndef EYA_ATTRIBUTE_FORCE_INLINE_H
#define EYA_ATTRIBUTE_FORCE_INLINE_H

#include "compiler.h"

/**
 * @def EYA_ATTRIBUTE_FORCE_INLINE
 * @brief Alias for the function force inlining macro
 * @details This macro is an alias for `EYA_COMPILER_ATTRIBUTE_FORCE_INLINE`,
 *          providing a shorter and more convenient name for the force inlining attribute.
 *          Its behavior and supported compilers are identical to the original macro.
 *
 * @see EYA_COMPILER_ATTRIBUTE_FORCE_INLINE
 */
#define EYA_ATTRIBUTE_FORCE_INLINE EYA_COMPILER_ATTRIBUTE_FORCE_INLINE

#endif // EYA_ATTRIBUTE_FORCE_INLINE_H