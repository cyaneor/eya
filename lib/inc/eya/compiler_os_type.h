/**
 * @file compiler_os_type.h
 * @brief Operating system detection macros for compiler environment
 *
 * This header defines constants and detection logic for identifying the host
 * operating system during compilation. The detection is based on predefined
 * compiler macros that are automatically defined by different toolchains
 * (MSVC, GCC, Clang, etc.).
 *
 * The detection logic follows this hierarchy:
 * 1. Windows platforms (_WIN32 or _WIN64 defined)
 * 2. Linux platforms (__linux__ defined)
 * 3. macOS platforms (__APPLE__ defined and TARGET_OS_MAC verified)
 * 4. Fallback to unknown OS if no matches found
 *
 * @note _WIN32 is defined for both 32-bit and 64-bit Windows environments
 * @note For Apple platforms, additional verification through TargetConditionals.h
 *       ensures we're specifically targeting macOS (not iOS or other Apple OS)
 *
 * Usage example:
 * @code
 * #if EYA_COMPILER_OS_TYPE == EYA_COMPILER_OS_TYPE_WINDOWS
 *     // Windows-specific code
 * #elif EYA_COMPILER_OS_TYPE == EYA_COMPILER_OS_TYPE_LINUX
 *     // Linux-specific code
 * #endif
 * @endcode
 */

#ifndef EYA_COMPILER_OS_TYPE_H
#define EYA_COMPILER_OS_TYPE_H

/** @brief Unknown or undetectable operating system */
#define EYA_COMPILER_OS_TYPE_UNKNOWN 0

/** @brief Microsoft Windows operating system (detected via _WIN32 or similar) */
#define EYA_COMPILER_OS_TYPE_WINDOWS 1

/** @brief Linux operating system (detected via __linux__) */
#define EYA_COMPILER_OS_TYPE_LINUX 2

/** @brief Apple macOS operating system (detected via __APPLE__ and TARGET_OS_MAC) */
#define EYA_COMPILER_OS_TYPE_MAC 3

#ifndef EYA_COMPILER_OS_TYPE
#    if defined(_WIN32) || defined(_WIN64)
#        define EYA_COMPILER_OS_TYPE EYA_COMPILER_OS_TYPE_WINDOWS

#    elif defined(__linux__)
#        define EYA_COMPILER_OS_TYPE EYA_COMPILER_OS_TYPE_LINUX

#    elif defined(__APPLE__)
#        include <TargetConditionals.h>
#        if TARGET_OS_OSX
#            define EYA_COMPILER_OS_TYPE EYA_COMPILER_OS_TYPE_MAC
#        else
#            define EYA_COMPILER_OS_TYPE EYA_COMPILER_OS_TYPE_UNKNOWN
#        endif

#    else
#        define EYA_COMPILER_OS_TYPE EYA_COMPILER_OS_TYPE_UNKNOWN
#    endif
#endif // EYA_COMPILER_OS_TYPE

#endif // EYA_COMPILER_OS_TYPE_H