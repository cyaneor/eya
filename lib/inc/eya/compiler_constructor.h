/**
 * @file compiler_constructor.h
 * @brief Macro definition for compiler-specific constructor functions.
 *
 * This file defines the `eya_compiler_constructor` macro for declaring
 * constructor functions that execute before `main()` entry point.
 *
 * The macro provides cross-compiler support for:
 * - GCC/Clang: Uses `__attribute__((constructor))`
 * - MSVC: Implements via `.CRT$XCU` section manipulation
 * - Others: Empty implementation with compiler warning
 *
 * @details
 * - GCC/Clang: Marks functions with constructor attribute for automatic pre-main execution
 * - MSVC: Uses PE section directives for constructor registration
 * - Unsupported compilers: Generates empty implementation with diagnostic warning
 *
 * @warning Using `eya_compiler_constructor` with unsupported compilers
 *          will disable constructor functionality and trigger warnings.
 *
 * @pre Include this header to enable `eya_compiler_constructor` functionality.
 */

#ifndef EYA_COMPILER_CONSTRUCTOR_H
#define EYA_COMPILER_CONSTRUCTOR_H

#include "compiler_type.h"

#if (EYA_COMPILER_GCC_LIKE)
/**
 * @def eya_compiler_constructor(f)
 * @brief Constructor attribute for GCC/Clang compilers
 * @details Defines static constructor function that executes
 *          automatically before main(). Uses GCC-style attribute.
 */
#    define eya_compiler_constructor(f) __attribute__((constructor)) static void f(void)

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def eya_compiler_constructor(f)
 * @brief Constructor implementation for MSVC compiler
 * @details Implements pre-main execution through PE section:
 *          1. Creates dedicated CRT section
 *          2. Allocates function pointer in section
 *          3. Forces linker inclusion
 */
#    if EYA_COMPILER_BIT_DEPTH == 64
#        define eya_compiler_constructor(f)                                                        \
            __pragma(section(".CRT$XCU", read)) static void __cdecl f(void);                       \
            __declspec(allocate(".CRT$XCU")) void(__cdecl * f##_)(void) = f;                       \
            __pragma(comment(linker, "/include:" #f "_"));                                         \
            static void __cdecl f(void)
#    elif EYA_COMPILER_BIT_DEPTH == 32
#        define eya_compiler_constructor(f)                                                        \
            __pragma(section(".CRT$XCU", read)) static void __cdecl f(void);                       \
            __declspec(allocate(".CRT$XCU")) void(__cdecl * f##_)(void) = f;                       \
            __pragma(comment(linker, "/include:_" #f "_"));                                        \
            static void __cdecl f(void)
#    endif

#else
/**
 * @def eya_compiler_constructor
 * @brief Empty constructor stub for unsupported compilers
 * @warning Constructor functionality disabled - functions
 *          declared with this macro won't auto-execute.
 * @details Generates compiler warning about missing support
 *          while maintaining source compatibility.
 */
#    define eya_compiler_constructor

#    pragma message("Warning: Constructor attribute not supported by this compiler")
#endif

#endif // EYA_COMPILER_CONSTRUCTOR_H