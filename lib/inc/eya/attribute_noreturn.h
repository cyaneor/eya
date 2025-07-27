/**
 * @file attribute_noreturn.h
 * @brief Adapter header file for the macro marking functions as non-returning.
 *
 * This file provides the simplified interface `EYA_ATTRIBUTE_NORETURN`
 * as an alias for the `EYA_COMPILER_ATTRIBUTE_NORETURN` macro,
 * which marks functions as non-returning.
 *
 * @see EYA_COMPILER_ATTRIBUTE_NORETURN
 */

#ifndef EYA_ATTRIBUTE_NORETURN_H
#define EYA_ATTRIBUTE_NORETURN_H

#include "compiler.h"

/**
 * @def EYA_ATTRIBUTE_NORETURN
 * @brief Alias for EYA_COMPILER_ATTRIBUTE_NORETURN,
 *        marking functions as non-returning.
 *
 * @details This macro serves as a simplified interface for `EYA_COMPILER_ATTRIBUTE_NORETURN`.
 *          It inherits all features and behavior of the base macro,
 *          including support for different compilers:
 *              - GCC/Clang: `__attribute__((noreturn))`
 *              - MSVC: `__declspec(noreturn)`
 *              - Other compilers: Empty implementation with compiler warning
 *
 * @note Use this macro to mark functions that never return control,
 *       enabling additional compiler optimizations.
 *
 * @warning Code following calls to functions with this attribute
 *          will be considered unreachable by the compiler.
 *
 * Usage example:
 * @code
 * EYA_ATTRIBUTE_NORETURN void fatal_error(const char* message) {
 *     printf("Fatal error: %s\n", message);
 *     exit(1);
 * }
 * @endcode
 */
#define EYA_ATTRIBUTE_NORETURN EYA_COMPILER_ATTRIBUTE_NORETURN

#endif // EYA_ATTRIBUTE_NORETURN_H