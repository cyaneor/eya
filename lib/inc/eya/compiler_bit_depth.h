/**
 * @file compiler_bit_depth.h
 * @brief Macro definitions for compiler bit depth detection.
 *
 * This file provides the `EYA_COMPILER_BIT_DEPTH` macro
 * that determines compiler bitness (32 or 64 bits)
 * based on target platform and architecture.
 *
 * The macro enables conditional compilation for
 * architecture-dependent features across platforms.
 *
 * Supported platforms and architectures:
 * - Windows (32-bit and 64-bit)
 * - Apple (x86 and x86-64)
 * - Linux (x86, x86-64, AMD64)
 *
 * @note Unsupported platforms trigger a compiler warning
 *       about unknown bit depth.
 */

#ifndef EYA_COMPILER_BIT_DEPTH_H
#define EYA_COMPILER_BIT_DEPTH_H

#ifndef EYA_COMPILER_BIT_DEPTH
#    if defined(_WIN64)
/**
 * @def EYA_COMPILER_BIT_DEPTH
 * @brief Defines 64-bit compilation mode for 64-bit Windows
 */
#        define EYA_COMPILER_BIT_DEPTH 64
#    elif defined(_WIN32)
/**
 * @def EYA_COMPILER_BIT_DEPTH
 * @brief Defines 32-bit compilation mode for 32-bit Windows
 */
#        define EYA_COMPILER_BIT_DEPTH 32
#    elif defined(__APPLE__)
#        include <TargetConditionals.h>
#        if TARGET_CPU_X86_64
/**
 * @def EYA_COMPILER_BIT_DEPTH
 * @brief Defines 64-bit mode for Apple x86-64 architectures
 */
#            define EYA_COMPILER_BIT_DEPTH 64
#        elif TARGET_CPU_X86
/**
 * @def EYA_COMPILER_BIT_DEPTH
 * @brief Defines 32-bit mode for Apple x86 architectures
 */
#            define EYA_COMPILER_BIT_DEPTH 32
#        endif
#    elif defined(__linux__)
#        if defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64)
/**
 * @def EYA_COMPILER_BIT_DEPTH
 * @brief Defines 64-bit mode for Linux x86-64/AMD64 systems
 */
#            define EYA_COMPILER_BIT_DEPTH 64
#        elif defined(__i386__) || defined(__i386)
/**
 * @def EYA_COMPILER_BIT_DEPTH
 * @brief Defines 32-bit mode for Linux x86 architectures
 */
#            define EYA_COMPILER_BIT_DEPTH 32
#        endif
#    else
#        pragma message("Warning: Unknown compiler bit depth")
#    endif
#endif // EYA_COMPILER_BIT_DEPTH

#endif // EYA_COMPILER_BIT_DEPTH_H