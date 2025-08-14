/**
 * @file attribute_thread_local.h
 * @brief Thread-local storage attribute definition and configuration.
 *
 * This header defines the `EYA_ATTRIBUTE_THREAD_LOCAL` macro for specifying
 * thread-local variable storage. The implementation varies based on build configuration:
 *
 * - When `EYA_LIBRARY_OPTION_THREAD_LOCAL` is enabled, the macro expands to
 *   a compiler-specific thread-local storage attribute
 *
 * - Otherwise, the macro remains empty, indicating no special thread-local
 *   storage qualifier is applied
 */

#ifndef EYA_ATTRIBUTE_THREAD_LOCAL_H
#define EYA_ATTRIBUTE_THREAD_LOCAL_H

#include "compiler.h"
#include "library_option.h"

/**
 * @def EYA_LIBRARY_OPTION_THREAD_LOCAL
 * @brief Configuration macro for thread-local storage support
 *
 * @details Determines whether thread-local storage is enabled in the library.
 *          Defaults to `EYA_LIBRARY_OPTION_OFF` if not explicitly defined.
 *
 * Possible values:
 * - `EYA_LIBRARY_OPTION_ON` - Enable thread-local storage support
 * - `EYA_LIBRARY_OPTION_OFF` - Disable thread-local storage support
 *
 * @note This macro should be defined before including this header if the default
 *       behavior needs to be overridden. The value must be either `EYA_LIBRARY_OPTION_ON`
 *       or `EYA_LIBRARY_OPTION_OFF`.
 *
 * @see EYA_ATTRIBUTE_THREAD_LOCAL
 */
#ifndef EYA_LIBRARY_OPTION_THREAD_LOCAL
#    define EYA_LIBRARY_OPTION_THREAD_LOCAL EYA_LIBRARY_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_THREAD_LOCAL

#if (EYA_LIBRARY_OPTION_THREAD_LOCAL == EYA_LIBRARY_OPTION_ON)
/**
 * @def EYA_ATTRIBUTE_THREAD_LOCAL
 * @brief Compiler-specific thread-local storage attribute
 *
 * @details Expands to `EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL` when thread-local
 *          storage is enabled. Marks variables with thread storage duration:
 *          - GCC/Clang: `__thread` or `_Thread_local`
 *          - MSVC: `__declspec(thread)`
 *          - C11: `thread_local` (where supported)
 *
 * @note Requires compiler support for thread-local storage and proper TLS
 *       implementation in the target environment
 */
#    define EYA_ATTRIBUTE_THREAD_LOCAL EYA_COMPILER_ATTRIBUTE_THREAD_LOCAL
#elif (EYA_LIBRARY_OPTION_THREAD_LOCAL == EYA_LIBRARY_OPTION_OFF)
/**
 * @def EYA_ATTRIBUTE_THREAD_LOCAL
 * @brief Empty placeholder for thread-local storage attribute
 *
 * @details Expands to nothing when thread-local storage is disabled.
 *          Variables declared with this macro will have static storage duration.
 *
 * @warning Using this configuration assumes thread safety is managed
 *          through other mechanisms if required
 */
#    define EYA_ATTRIBUTE_THREAD_LOCAL
#endif

#endif // EYA_ATTRIBUTE_THREAD_LOCAL_H