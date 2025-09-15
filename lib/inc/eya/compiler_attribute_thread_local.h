/**
 * @file compiler_attribute_thread_local.h
 * @brief Thread-local storage attribute definition for different compilers.
 *
 * This file provides the `EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL` macro
 * for specifying thread-local storage attributes. The attribute enables
 * per-thread variable instances, essential for thread-safe data handling
 * in multithreaded applications.
 *
 * Supported compilers:
 * - GCC/Clang: Uses `__thread`
 * - MSVC: Uses `__declspec(thread)`
 *
 * @note For unsupported compilers, the macro expands to empty
 *       with a compiler warning.
 *
 * Macro:
 * - `EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL`:
 *    Specifies thread-local storage duration
 *
 * @warning Using this macro with unsupported compilers
 *          will not provide thread-local storage guarantees.
 */

#ifndef EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL_H
#define EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL_H

#include "compiler_type.h"

#if (EYA_COMPILER_TYPE == EYA_COMPILER_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
/**
 * @def EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL
 * @brief Thread-local storage attribute for GCC/Clang
 * @details Specifies thread-local storage duration using `__thread`,
 *          creating unique variable instances per thread.
 */
#    define EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL __thread

#elif (EYA_COMPILER_TYPE == EYA_COMPILER_MSVC)
/**
 * @def EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL
 * @brief Thread-local storage attribute for MSVC
 * @details Specifies thread-local storage duration using
 *          `__declspec(thread)`, creating per-thread instances.
 */
#    define EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL __declspec(thread)

#else
/**
 * @def EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL
 * @brief Empty implementation for unsupported compilers
 * @warning Thread-local storage unavailable - variables will have
 *          static storage duration instead.
 * @details Expands to empty macro with compiler warning about
 *          missing thread-local support.
 */
#    define EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL
#    pragma message("Warning: Compiler does not support thread-local storage attribute")
#endif

#endif // EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL_H