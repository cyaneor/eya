/**
 * @file compiler_attribute.h
 * @brief Common compiler attribute definitions for cross-platform development.
 *
 * This header aggregates various compiler attribute definitions, providing
 * a unified interface for compiler-specific attributes including:
 * - Function inlining control
 * - Symbol visibility management
 * - Unused element warning suppression
 * - Thread-local storage
 * - Architecture-specific optimizations
 * - Non-returning function markers
 *
 * Included headers:
 * - `compiler_attribute_force_inline.h`:
 *    Force inlining attributes for performance-critical code
 * - `compiler_attribute_noreturn.h`:
 *    Non-returning function attributes
 * - `compiler_attribute_symbol.h`:
 *    Symbol export/import management for shared libraries
 * - `compiler_attribute_target.h`:
 *    Architecture-specific optimization attributes
 * - `compiler_attribute_thread_local.h`:
 *    Thread-local storage attributes
 * - `compiler_attribute_unused.h`:
 *    Unused element warning suppression
 *
 * @note This header simplifies compiler attribute management,
 *       enhancing code portability and consistency across
 *       different compilers and platforms.
 * @note All attributes are centralized for ease of use
 *       and project-wide consistency.
 */

#ifndef EYA_COMPILER_ATTRIBUTE_H
#define EYA_COMPILER_ATTRIBUTE_H

#include "compiler_attribute_force_inline.h"
#include "compiler_attribute_noreturn.h"
#include "compiler_attribute_symbol.h"
#include "compiler_attribute_target.h"
#include "compiler_attribute_thread_local.h"
#include "compiler_attribute_unused.h"

#endif // EYA_COMPILER_ATTRIBUTE_H