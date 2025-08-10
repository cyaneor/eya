/**
 * @file nullptr.h
 * @brief Header file defining `nullptr` emulation for C language.
 *
 * This file contains a macro defining `nullptr` as a pointer's minimal value
 * when compiling C code where the `nullptr` keyword isn't natively supported.
 *
 * In C++, `nullptr` is a built-in keyword representing a null pointer constant.
 * In C, this macro emulates the behavior using the minimal pointer value
 * equivalent to a null pointer.
 *
 * Including this header enables `nullptr` usage in C code when not compiling
 * as C++, providing cross-compiler consistency and unified code patterns.
 */

#ifndef EYA_NULLPTR_H
#define EYA_NULLPTR_H

#include "numeric_limit.h"

#ifndef __cplusplus
/**
 * @def nullptr
 * @brief `nullptr` emulation for non-C++ environments.
 *
 * Defines `nullptr` as the minimal pointer value when compiling as C code.
 *
 * While C++ uses `nullptr` as a null pointer keyword, this macro provides
 * equivalent functionality for C by using the minimal pointer value that
 * represents a null pointer in the implementation.
 *
 * @note This macro is only active when compiling as C code, determined by
 *       the `#ifndef __cplusplus` preprocessor directive.
 */
#    define nullptr eya_numeric_limit_umin(void *)
#endif // __cplusplus

#endif // EYA_NULLPTR_H