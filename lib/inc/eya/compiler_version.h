/**
 * @file compiler_version.h
 * @brief Macro definitions for compiler version detection.
 *
 * This header provides macros to detect compiler versions based on type
 * (Clang, GCC, MSVC). The macros extract major, minor and patch version numbers,
 * enabling version-based conditional compilation.
 *
 * Macros:
 * - `EYA_COMPILER_VERSION_MAJOR`: Compiler major version
 * - `EYA_COMPILER_VERSION_MINOR`: Compiler minor version
 * - `EYA_COMPILER_VERSION_PATCH`: Compiler patch version
 *
 * @note Unrecognized compilers default all versions to 0.
 */

#ifndef EYA_COMPILER_VERSION_H
#define EYA_COMPILER_VERSION_H

#include "compiler_type.h"

#if (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
/** @brief Major version number for Clang compiler */
#    define EYA_COMPILER_VERSION_MAJOR __clang_major__
/** @brief Minor version number for Clang compiler */
#    define EYA_COMPILER_VERSION_MINOR __clang_minor__
/** @brief Patch version number for Clang compiler */
#    define EYA_COMPILER_VERSION_PATCH __clang_patchlevel__

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_GCC)
/** @brief Major version number for GCC compiler */
#    define EYA_COMPILER_VERSION_MAJOR __GNUC__
/** @brief Minor version number for GCC compiler */
#    define EYA_COMPILER_VERSION_MINOR __GNUC_MINOR__
/** @brief Patch version number for GCC compiler */
#    define EYA_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/** @brief Major version number for MSVC (derived from _MSC_FULL_VER) */
#    define EYA_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
/** @brief Minor version number for MSVC (derived from _MSC_FULL_VER) */
#    define EYA_COMPILER_VERSION_MINOR ((_MSC_FULL_VER / 100000) % 100)
/** @brief Patch version number for MSVC (derived from _MSC_FULL_VER) */
#    define EYA_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)

#else
/** @brief Default major version (0) for unrecognized compilers */
#    define EYA_COMPILER_VERSION_MAJOR 0
/** @brief Default minor version (0) for unrecognized compilers */
#    define EYA_COMPILER_VERSION_MINOR 0
/** @brief Default patch version (0) for unrecognized compilers */
#    define EYA_COMPILER_VERSION_PATCH 0
#endif

#endif // EYA_COMPILER_VERSION_H