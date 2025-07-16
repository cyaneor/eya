/**
 * @file compiler.h
 * @brief Comprehensive header for compiler environment configuration and attributes.
 *
 * This file aggregates multiple compiler-related headers to provide a unified interface
 * for managing compiler characteristics including version detection, bit depth,
 * standard version support, compiler-specific attributes, and operating system detection.
 *
 * Includes:
 * - `compiler_version.h`: Compiler version detection
 * - `compiler_extern.h`: External storage specifier definition
 * - `compiler_extern_c.h`: C linkage management for C++ compatibility
 * - `compiler_attribute.h`: Compiler attribute macros
 * - `compiler_bit_depth.h`: System architecture bitness detection (32/64-bit)
 * - `compiler_destructor.h`: Destructor attribute declarations
 * - `compiler_constructor.h`: Constructor attribute declarations
 * - `compiler_os_type.h`: Operating system type detection (Windows/Linux/macOS)
 * - `compiler_std_version.h`: C language standard version detection
 * - `compiler_unreachable.h`: Unreachable code path markers
 *
 * @note Using this header simplifies cross-platform development by ensuring consistent
 *       compiler environment configuration across different toolchains and operating systems.
 * @note All component headers are aggregated here to minimize include statements
 *       while maintaining full compiler configuration capabilities.
 * @note The operating system detection in `compiler_os_type.h` supports Windows, Linux,
 *       and macOS platforms with proper verification for Apple environments.
 */

#ifndef EYA_COMPILER_H
#define EYA_COMPILER_H

#include "compiler_attribute.h"
#include "compiler_bit_depth.h"
#include "compiler_constructor.h"
#include "compiler_destructor.h"
#include "compiler_extern.h"
#include "compiler_extern_c.h"
#include "compiler_os_type.h"
#include "compiler_std_version.h"
#include "compiler_unreachable.h"
#include "compiler_version.h"

/**
 * @def EYA_COMPILER(N)
 * @brief Expands to compiler-specific macro
 *
 * This macro takes a single argument `N` and concatenates it with
 * `EYA_COMPILER_` prefix to form complete compiler-specific macro name.
 *
 * @param N Suffix specifying target compiler macro
 */
#define EYA_COMPILER(N) EYA_COMPILER_##N

#endif // EYA_COMPILER_H