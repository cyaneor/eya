/**
 * @file attribute_symbol.h
 * @brief Header file defining macros
 *        for symbol visibility control during library builds.
 *
 * This file provides the `EYA_ATTRIBUTE_SYMBOL` macro
 * to manage symbol visibility based on the library build type (static or dynamic).
 *
 * The macro automatically adapts to compilation settings,
 * ensuring proper symbol export/import handling.
 */

#ifndef EYA_ATTRIBUTE_SYMBOL_H
#define EYA_ATTRIBUTE_SYMBOL_H

#include "compiler.h"
#include "library_option_fallback.h"

#if (EYA_LIBRARY_OPTION_STATIC_BUILD == EYA_LIBRARY_OPTION_ON)
/**
 * @def EYA_ATTRIBUTE_SYMBOL
 * @brief Marks symbols as public for static library builds.
 *
 * When building as a static library or when not using shared library conventions,
 * symbols are marked as public without shared library attributes.
 * This follows standard static linking behavior where symbols remain accessible
 * but lack shared library-specific attributes.
 */
#    define EYA_ATTRIBUTE_SYMBOL
#elif (EYA_LIBRARY_OPTION_SHARED_BUILD == EYA_LIBRARY_OPTION_ON)
/**
 * @def EYA_ATTRIBUTE_SYMBOL
 * @brief Marks symbols for export in shared library builds.
 *
 * When building as a shared library, this macro marks symbols as public
 * for export. It expands to `EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT`,
 * making symbols visible to external applications and libraries.
 */
#    define EYA_ATTRIBUTE_SYMBOL EYA_COMPILER_ATTRIBUTE_SYMBOL_EXPORT
#else
/**
 * @def EYA_ATTRIBUTE_SYMBOL
 * @brief Marks symbols for import when using a shared library.
 *
 * When consuming a prebuilt shared library, this macro marks symbols for import.
 * It expands to `EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT`, enabling proper linkage
 * for applications and libraries using this shared library.
 */
#    define EYA_ATTRIBUTE_SYMBOL EYA_COMPILER_ATTRIBUTE_SYMBOL_IMPORT
#endif

#endif // EYA_ATTRIBUTE_SYMBOL_H