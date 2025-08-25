/**
 * @file compiler_extern_c.h
 * @brief Macros for C/C++ linkage compatibility.
 *
 * This header provides macros for declaring C linkage blocks in C++ projects.
 * Enables inclusion of C code in C++ projects without name mangling and allows
 * defining functions callable from both C and C++.
 *
 * Macros:
 * - `EYA_COMPILER_EXTERN_C_BEGIN`: Starts C linkage block in C++ mode
 * - `EYA_COMPILER_EXTERN_C_END`: Ends C linkage block in C++ mode
 *
 * @note These macros expand to empty when compiling in pure C mode,
 *       as C linkage is the default behavior.
 */

#ifndef EYA_COMPILER_EXTERN_C_H
#define EYA_COMPILER_EXTERN_C_H

#include "compiler_cxx.h"

#if (EYA_COMPILER_CXX == EYA_OPTION_ON)
#    include "compiler_extern.h"

/**
 * @def EYA_COMPILER_EXTERN_C_BEGIN
 * @brief Starts C linkage declaration block
 *
 * Begins a code block with C language linkage when compiling in C++ mode.
 * Essential for including C headers in C++ projects and defining functions
 * callable from C code. Prevents C++ name mangling and ensures binary compatibility.
 */
#    define EYA_COMPILER_EXTERN_C_BEGIN                                                            \
        EYA_COMPILER_EXTERN "C"                                                                    \
        {

/**
 * @def EYA_COMPILER_EXTERN_C_END
 * @brief Ends C linkage declaration block
 *
 * Closes a C linkage block started with EYA_COMPILER_EXTERN_C_BEGIN.
 * Must be paired with EYA_COMPILER_EXTERN_C_BEGIN to maintain proper
 * linkage semantics.
 */
#    define EYA_COMPILER_EXTERN_C_END }
#else
/**
 * @def EYA_COMPILER_EXTERN_C_BEGIN
 * @brief Empty expansion in C compilation mode
 *
 * Expands to nothing when compiling with C compiler as C linkage
 * is the default behavior. Maintains source compatibility with C/C++.
 */
#    define EYA_COMPILER_EXTERN_C_BEGIN

/**
 * @def EYA_COMPILER_EXTERN_C_END
 * @brief Empty expansion in C compilation mode
 *
 * Expands to nothing in C mode to match EYA_COMPILER_EXTERN_C_BEGIN.
 * Preserves code symmetry between C and C++ implementations.
 */
#    define EYA_COMPILER_EXTERN_C_END
#endif

#endif // EYA_COMPILER_EXTERN_C_H