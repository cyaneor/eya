/**
 * @file attribute_unused.h
 * @brief Header file for the unused code attribute alias.
 *
 * Provides the convenient shorthand macro `EYA_ATTRIBUTE_UNUSED`
 * to mark unused variables, functions and parameters for
 * compiler warning suppression.
 *
 * Key Features:
 * - Simplified syntax compared to base macro
 * - Cross-compiler support (GCC, Clang, MSVC)
 * - Unused element warning suppression
 * - Conditional compilation support
 *
 * @note Requires compiler.h inclusion
 * @warning May not function properly with unsupported compilers
 *
 * Usage example:
 * @code
 * // Variables
 * EYA_ATTRIBUTE_UNUSED int debug_counter;
 *
 * // Functions
 * EYA_ATTRIBUTE_UNUSED void deprecated_function() {}
 *
 * // Function parameters
 * void callback(int param1, EYA_ATTRIBUTE_UNUSED int param2) {}
 * @endcode
 *
 * @see EYA_COMPILER_ATTRIBUTE_UNUSED
 */

#ifndef EYA_ATTRIBUTE_UNUSED_H
#define EYA_ATTRIBUTE_UNUSED_H

#include "compiler.h"

/**
 * @def EYA_ATTRIBUTE_UNUSED
 * @brief Convenient alias for marking unused code elements
 * @details This macro serves as a shorthand for EYA_COMPILER_ATTRIBUTE_UNUSED,
 *          designed to suppress compiler warnings about unused variables,
 *          functions or parameters.
 *
 *          Compiler-specific behavior:
 *          - GCC/Clang: Expands to `__attribute__((unused))`
 *          - MSVC: Uses `(void)` cast suppression
 *          - Other compilers: May expand to empty macro
 *
 * @note Particularly useful for conditionally compiled code where elements
 *       might be unused in specific configurations.
 *
 * Example:
 * @code
 * EYA_ATTRIBUTE_UNUSED int unused_var;  // Will not trigger warnings
 * EYA_ATTRIBUTE_UNUSED void unused_function() {}  // Same for functions
 * @endcode
 *
 * @see EYA_COMPILER_ATTRIBUTE_UNUSED
 */
#define EYA_ATTRIBUTE_UNUSED EYA_COMPILER_ATTRIBUTE_UNUSED

#endif // EYA_ATTRIBUTE_UNUSED_H