/**
 * @file compiler_attribute_unused.h
 * @brief Definition of macro for marking unused variables and functions.
 *
 * This file provides the `EYA_COMPILER_ATTRIBUTE_UNUSED` macro to suppress
 * compiler warnings about unused variables or functions.
 *
 * The macro supports different implementations based on compiler type:
 * - GCC/Clang: `__attribute__((unused))`
 * - MSVC: Warning suppression workaround
 *
 * For unrecognized compilers, an empty attribute is used
 * with a compilation warning about potential lack of support.
 *
 * @note Particularly useful for conditional compilation scenarios
 *       where elements might be unused in specific configurations.
 */

#ifndef EYA_COMPILER_ATTRIBUTE_UNUSED_H
#define EYA_COMPILER_ATTRIBUTE_UNUSED_H

#include "compiler_type.h"

#if (EYA_COMPILER_GCC_LIKE)
/**
 * @def EYA_COMPILER_ATTRIBUTE_UNUSED
 * @brief Marks variables/functions as potentially unused for GCC/Clang
 * @details This attribute informs GCC/Clang compilers that the element
 *          may be intentionally unused, suppressing related warnings.
 *          Essential for conditionally compiled code with elements
 *          unused in certain configurations.
 */
#    define EYA_COMPILER_ATTRIBUTE_UNUSED __attribute__((unused))

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def EYA_COMPILER_ATTRIBUTE_UNUSED
 * @brief Warning suppression workaround for MSVC
 * @details Uses void casting technique to suppress
 *          C4189 ("unused variable") warnings in MSVC.
 *          Particularly useful for platform-specific code
 *          with variables unused in Windows builds.
 */
#    define EYA_COMPILER_ATTRIBUTE_UNUSED (void)

#else
/**
 * @def EYA_COMPILER_ATTRIBUTE_UNUSED
 * @brief Empty stub for unsupported compilers
 * @warning Using this macro with unsupported compilers
 *          provides no warning suppression guarantees.
 * @details Expands to empty implementation with compiler
 *          diagnostic about missing attribute support.
 */
#    define EYA_COMPILER_ATTRIBUTE_UNUSED
#    pragma message("Warning: Unused attribute not supported by this compiler")
#endif

#endif // EYA_COMPILER_ATTRIBUTE_UNUSED_H