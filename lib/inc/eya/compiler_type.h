/**
 * @file compiler_type.h
 * @brief Defines macros for compiler type identification.
 *
 * This header contains macros to detect the compiler used for code compilation.
 * Using conditional compilation, it identifies compilers (e.g., GCC, MSVC, Clang)
 * and enables compiler-specific adaptations in the codebase.
 *
 * Defined macros assign unique identifiers to supported compilers:
 * - `EYA_COMPILER_TYPE_GCC` for GNU Compiler Collection (GCC)
 * - `EYA_COMPILER_TYPE_MSVC` for Microsoft Visual C++ (MSVC)
 * - `EYA_COMPILER_TYPE_CLANG` for Clang compiler
 * - `EYA_COMPILER_TYPE_UNKNOWN` for unrecognized compilers
 *
 * The `EYA_COMPILER_TYPE` macro is automatically set to match the detected compiler,
 * enabling cross-platform compatibility and build tool interoperability.
 *
 * @note Essential for environments requiring compiler-specific
 *       workarounds or configurations.
 */

#ifndef EYA_COMPILER_TYPE_H
#define EYA_COMPILER_TYPE_H

/**
 * @def EYA_COMPILER_TYPE_UNKNOWN
 * @brief Identifier for unrecognized compiler type
 *
 * Used when build system fails to detect a known compiler.
 * @note Required for conditional compilation based on compiler type.
 */
#define EYA_COMPILER_TYPE_UNKNOWN 0

/**
 * @def EYA_COMPILER_TYPE_GCC
 * @brief Identifier for GNU Compiler Collection
 *
 * Used for GCC-specific code paths in conditional compilation.
 * @note Critical for cross-platform code with compiler-dependent behavior.
 */
#define EYA_COMPILER_TYPE_GCC 1

/**
 * @def EYA_COMPILER_TYPE_MSVC
 * @brief Identifier for Microsoft Visual C++
 *
 * Used for MSVC-specific code paths in conditional compilation.
 * @note Essential for Windows platform development adaptations.
 */
#define EYA_COMPILER_TYPE_MSVC 2

/**
 * @def EYA_COMPILER_TYPE_CLANG
 * @brief Identifier for LLVM Clang compiler
 *
 * Used for Clang-specific code paths in conditional compilation.
 * @note Important for modern toolchain compatibility.
 */
#define EYA_COMPILER_TYPE_CLANG 3

/**
 * @def EYA_COMPILER_TYPE
 * @brief Active compiler type identifier
 *
 * Detects compiler using vendor-specific predefined macros:
 * - Clang: __clang__
 * - MSVC: _MSC_VER
 * - GCC: __GNUC__
 *
 * @details Possible values:
 * - `EYA_COMPILER_TYPE_CLANG`
 * - `EYA_COMPILER_TYPE_MSVC`
 * - `EYA_COMPILER_TYPE_GCC`
 * - `EYA_COMPILER_TYPE_UNKNOWN`
 *
 * @note Fundamental for cross-platform development requiring
 *       compiler-specific implementations.
 */
#if defined(__clang__)
#    define EYA_COMPILER_TYPE EYA_COMPILER_TYPE_CLANG
#elif defined(_MSC_VER)
#    define EYA_COMPILER_TYPE EYA_COMPILER_TYPE_MSVC
#elif defined(__GNUC__)
#    define EYA_COMPILER_TYPE EYA_COMPILER_TYPE_GCC
#else
#    define EYA_COMPILER_TYPE EYA_COMPILER_TYPE_UNKNOWN
#endif

#endif // EYA_COMPILER_TYPE_H