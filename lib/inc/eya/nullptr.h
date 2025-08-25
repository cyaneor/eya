/**
 * @file nullptr.h
 * @brief Header file defining `nullptr` emulation for C language.
 *
 * This file contains a macro defining `nullptr` as a pointer's minimal value
 * when compiling C code where the `nullptr` keyword isn't natively supported.
 *
 * In C++, `nullptr` is a built-in keyword representing a null pointer constant.
 * In C, this macro emulates the behavior using the platform-specific minimal
 * pointer value from ptr.h (EYA_PTR_T_MIN) equivalent to a null pointer.
 *
 * Including this header enables `nullptr` usage in C code when not compiling
 * as C++, providing cross-compiler consistency and unified code patterns.
 */

#ifndef EYA_NULLPTR_H
#define EYA_NULLPTR_H

#include "ptr.h"

#if (EYA_COMPILER_CXX == EYA_OPTION_OFF)
/**
 * @def nullptr
 * @brief `nullptr` emulation for non-C++ environments.
 *
 * Defines `nullptr` as the platform-specific minimal pointer value (EYA_PTR_T_MIN)
 * when compiling as C code.
 *
 * While C++ uses `nullptr` as a null pointer keyword, this macro provides
 * equivalent functionality for C by using the minimal pointer value that
 * represents a null pointer in the implementation, as defined in ptr.h.
 *
 * @note This macro:
 *       - Is only active when compiling as C code
 *       - Uses EYA_PTR_T_MIN from ptr.h instead of direct numeric_limit call
 *       - Provides better abstraction through ptr.h's platform definitions
 */
#    define nullptr EYA_PTR_T_MIN
#endif

#endif // EYA_NULLPTR_H