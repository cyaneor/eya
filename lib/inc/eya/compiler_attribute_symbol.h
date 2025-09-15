/**
 * @file compiler_attribute_symbol.h
 * @brief Symbol visibility attribute macros for shared library exports/imports.
 *
 * This file provides macros to control symbol visibility in shared libraries,
 * enabling management of symbol exports, imports, and hiding across different
 * compilers and platforms.
 *
 * Macros:
 * - `EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT`:
 *    Marks symbols for export from shared libraries
 * - `EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT`:
 *    Marks symbols for import from external shared libraries
 * - `EYA_COMPILER_ATTRIBUTE_SYMBOL_HIDDEN`:
 *    Hides symbols from external linkage
 *
 * Supported compilers:
 * - **GCC/Clang**: Uses `__attribute__((visibility("default")))` for export/import
 *                 and `__attribute__((visibility("hidden")))` for hiding
 * - **MSVC**: Uses `__declspec(dllexport)` for export and
 *            `__declspec(dllimport)` for import. No direct hidden equivalent.
 *
 * @note For unsupported compilers, these macros expand to empty values
 *       with a compiler warning about missing attribute support.
 */

#ifndef EYA_COMPILER_ATTRIBUTE_SYMBOL_H
#define EYA_COMPILER_ATTRIBUTE_SYMBOL_H

#include "compiler_type.h"

#if (EYA_COMPILER_TYPE == EYA_COMPILER_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT
 * @brief Exports symbols in shared libraries for GCC/Clang
 * @details Marks symbols as publicly visible for inter-library linking.
 *          Required for symbols exposed in shared library interfaces.
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT __attribute__((visibility("default")))

/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT
 * @brief Imports symbols from shared libraries for GCC/Clang
 * @details Declares symbols as being defined in external shared libraries.
 *          Used when consuming prebuilt shared libraries.
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT __attribute__((visibility("default")))

/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_HIDDEN
 * @brief Hides symbols from external linkage for GCC/Clang
 * @details Restricts symbol visibility to the current shared library,
 *          preventing export even if publicly declared.
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_HIDDEN __attribute__((visibility("hidden")))

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT
 * @brief Exports symbols in DLLs for MSVC
 * @details Marks symbols for export when building shared libraries.
 *          Required for public symbols in DLL interfaces.
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT __declspec(dllexport)

/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT
 * @brief Imports symbols from DLLs for MSVC
 * @details Declares symbols as imported from external DLLs.
 *          Used when linking against prebuilt DLLs.
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT __declspec(dllimport)

/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_HIDDEN
 * @brief Placeholder for MSVC hidden equivalent
 * @details MSVC lacks direct hidden visibility support.
 *          Symbols not explicitly exported remain private by default.
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_HIDDEN

#else
/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT
 * @brief Empty export placeholder for unsupported compilers
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT

/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT
 * @brief Empty import placeholder for unsupported compilers
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT

/**
 * @def EYA_COMPILER_ATTRIBUTE_SYMBOL_HIDDEN
 * @brief Empty hidden placeholder for unsupported compilers
 */
#    define EYA_COMPILER_ATTRIBUTE_SYMBOL_HIDDEN

#    pragma message("Warning: Symbol visibility attributes not supported for this compiler")
#endif

#endif // EYA_COMPILER_ATTRIBUTE_SYMBOL_H