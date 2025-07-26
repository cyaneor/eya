/**
 * @file compiler_destructor.h
 * @brief Header file defining compiler-specific destructor attributes.
 *
 * This file contains the `eya_compiler_destructor` macro for declaring
 * destructor functions that execute after program exit from main().
 * Destructors enable cleanup operations like resource deallocation.
 *
 * @details Implementation varies by compiler:
 * - GCC/Clang: Uses `__attribute__((destructor))`
 * - MSVC: Implements via `.CRT$XTU` section manipulation
 * - Others: Empty implementation with compiler warning
 *
 * @warning Using destructors with unsupported compilers
 *          will disable functionality and trigger warnings.
 */

#ifndef EYA_COMPILER_DESTRUCTOR_H
#define EYA_COMPILER_DESTRUCTOR_H

#include "compiler_type.h"

#if (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_CLANG)
/**
 * @def eya_compiler_destructor(f)
 * @brief Destructor attribute for GCC/Clang compilers
 * @details Defines static destructor function that executes
 *          automatically after main() exit. Uses GCC-style attribute.
 */
#    define eya_compiler_destructor(f) __attribute__((destructor)) static void f(void)

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_TYPE_MSVC)
/**
 * @def eya_compiler_destructor(f)
 * @brief Destructor implementation for MSVC compiler
 * @details Implements post-main execution through PE section:
 *          1. Creates dedicated CRT termination section
 *          2. Allocates function pointer in section
 *          3. Forces linker inclusion
 */
#    if EYA_COMPILER_BIT_DEPTH == 64
#        define eya_compiler_destructor(f)                                                         \
            __pragma(section(".CRT$XTU", read)) static void __cdecl f(void);                       \
            __declspec(allocate(".CRT$XTU")) void(__cdecl * f##_)(void) = f;                       \
            __pragma(comment(linker, "/include:" #f "_"));                                         \
            static void __cdecl f(void)
#    elif EYA_COMPILER_BIT_DEPTH == 32
#        define eya_compiler_destructor(f)                                                         \
            __pragma(section(".CRT$XTU", read)) static void __cdecl f(void);                       \
            __declspec(allocate(".CRT$XTU")) void(__cdecl * f##_)(void) = f;                       \
            __pragma(comment(linker, "/include:_" #f "_"));                                        \
            static void __cdecl f(void)
#    endif

#else
/**
 * @def eya_compiler_destructor
 * @brief Empty destructor stub for unsupported compilers
 * @warning Destructor functionality disabled - functions
 *          declared with this macro won't auto-execute.
 * @details Generates compiler warning about missing support
 *          while maintaining source compatibility.
 */
#    define eya_compiler_destructor

#    pragma message("Warning: Destructor attribute not supported by this compiler")
#endif

#endif // EYA_COMPILER_DESTRUCTOR_H