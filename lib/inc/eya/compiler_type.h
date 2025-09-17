/**
 * @file compiler_type.h
 * @brief Definition of macros for compiler type identification.
 *
 * This header file contains macros for detecting the compiler used for code compilation.
 * Using conditional compilation, it identifies compilers (GCC, MSVC, Clang)
 * and provides the ability to adapt code for specific compilers.
 *
 * The defined macros assign unique identifiers to supported compilers:
 * - `EYA_COMPILER_GCC` for GNU Compiler Collection (GCC)
 * - `EYA_COMPILER_MSVC` for Microsoft Visual C++ (MSVC)
 * - `EYA_COMPILER_CLANG` for Clang compiler
 * - `EYA_COMPILER_UNKNOWN` for unrecognized compilers
 *
 * The `EYA_COMPILER_TYPE` macro is automatically set according to the detected compiler,
 * ensuring cross-platform compatibility and integration with build tools.
 *
 * @note Required in environments that need specific solutions
 *       or configurations for particular compilers.
 */

#ifndef EYA_COMPILER_TYPE_H
#define EYA_COMPILER_TYPE_H

/**
 * @def EYA_COMPILER_UNKNOWN
 * @brief Identifier for unknown compiler
 */
#ifndef EYA_COMPILER_UNKNOWN
#    define EYA_COMPILER_UNKNOWN 0
#endif // EYA_COMPILER_UNKNOWN

/**
 * @def EYA_COMPILER_GCC
 * @brief Identifier for GCC compiler
 */
#ifndef EYA_COMPILER_GCC
#    define EYA_COMPILER_GCC 1
#endif // EYA_COMPILER_GCC

/**
 * @def EYA_COMPILER_MSVC
 * @brief Identifier for Microsoft Visual C++ compiler
 */
#ifndef EYA_COMPILER_MSVC
#    define EYA_COMPILER_MSVC 2
#endif // EYA_COMPILER_MSVC

/**
 * @def EYA_COMPILER_CLANG
 * @brief Identifier for Clang compiler
 */
#ifndef EYA_COMPILER_CLANG
#    define EYA_COMPILER_CLANG 3
#endif // EYA_COMPILER_CLANG

/**
 * @def EYA_COMPILER_TYPE
 * @brief Macro defining the current compiler type
 *
 * Automatically detects and sets the compiler type based
 * on predefined compiler macros.
 *
 * The detection follows this order:
 * 1. Clang compiler (__clang__)
 * 2. Microsoft Visual C++ (_MSC_VER)
 * 3. GNU Compiler Collection (__GNUC__)
 * 4. Unknown compiler (if none of the above are detected)
 *
 * The macro is only defined if not already previously defined,
 * allowing for manual override.
 *
 * @see EYA_COMPILER_CLANG
 * @see EYA_COMPILER_MSVC
 * @see EYA_COMPILER_GCC
 * @see EYA_COMPILER_UNKNOWN
 */

#if defined(__clang__)
/**
 * @def EYA_COMPILER_TYPE
 * @brief Sets compiler type to Clang
 *
 * Defined when the Clang compiler is detected via the __clang__ predefined macro.
 * Clang defines this macro to indicate its identity.
 */
#    ifndef EYA_COMPILER_TYPE
#        define EYA_COMPILER_TYPE EYA_COMPILER_CLANG
#    endif // EYA_COMPILER_TYPE

#elif defined(_MSC_VER)
/**
 * @def EYA_COMPILER_TYPE
 * @brief Sets compiler type to Microsoft Visual C++
 *
 * Defined when MSVC compiler is detected via the _MSC_VER predefined macro.
 * _MSC_VER indicates the version of Microsoft Visual C++ compiler.
 */
#    ifndef EYA_COMPILER_TYPE
#        define EYA_COMPILER_TYPE EYA_COMPILER_MSVC
#    endif // EYA_COMPILER_TYPE

#elif defined(__GNUC__)
/**
 * @def EYA_COMPILER_TYPE
 * @brief Sets compiler type to GNU Compiler Collection
 *
 * Defined when GCC compiler is detected via the __GNUC__ predefined macro.
 * __GNUC__ indicates the major version number of GCC.
 */
#    ifndef EYA_COMPILER_TYPE
#        define EYA_COMPILER_TYPE EYA_COMPILER_GCC
#    endif // EYA_COMPILER_TYPE

#else
/**
 * @def EYA_COMPILER_TYPE
 * @brief Sets compiler type to unknown
 *
 * Defined when none of the known compiler detection macros are present.
 * This serves as a fallback for unrecognized or unsupported compilers.
 */
#    ifndef EYA_COMPILER_TYPE
#        define EYA_COMPILER_TYPE EYA_COMPILER_UNKNOWN
#    endif // EYA_COMPILER_TYPE
#endif

/**
 * @def EYA_COMPILER_GCC_LIKE
 * @brief Identifier for GCC-like compilers
 *
 * Defined when the compiler is GCC or Clang, allowing the use of code paths
 * compatible with GCC-like compiler behavior.
 *
 * @note Useful for common optimizations or features shared by GCC and Clang.
 * @return true if compiler is GCC-like, otherwise false
 */
#ifndef EYA_COMPILER_GCC_LIKE
#    define EYA_COMPILER_GCC_LIKE                                                                  \
        (EYA_COMPILER_TYPE == EYA_COMPILER_GCC) || (EYA_COMPILER_TYPE == EYA_COMPILER_CLANG)
#endif // EYA_COMPILER_GCC_LIKE

#endif // EYA_COMPILER_TYPE_H