/**
 * @file compile_option_fallback.h
 * @brief Compiler optimization configuration system
 *
 * This header provides default compilation options and optimization settings
 * when they are not explicitly defined. It serves as a central configuration
 * point for compiler behavior.
 *
 * Configuration sections:
 * 1. Optimization levels - Control compiler optimization aggressiveness
 * 2. Instruction sets - Enable specific CPU instruction extensions
 * 3. Debug features - Debug symbols and stack protection
 * 4. Performance tweaks - Loop unrolling, branch prediction, etc.
 * 5. Code generation - Position independence, symbol visibility
 *
 * All options provide safe defaults but can be overridden before inclusion.
 * Each option includes compiler-specific flag details and performance considerations.
 *
 * @see compile_option.h for the core definitions and basic options
 */

#ifndef EYA_COMPILE_OPTION_FALLBACK_H
#define EYA_COMPILE_OPTION_FALLBACK_H

#include "compile_option.h"

// --------------------------------------------------------------------------------------------- //
//                                        COMPILATION OPTIONS                                     //
// --------------------------------------------------------------------------------------------- //

/**
 * @def EYA_COMPILE_OPTION_OPTIMIZATION
 * @brief Enables/disables compiler optimizations
 * @details When enabled, activates high-level optimizations
 *          that may increase code size but improve performance.
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -O3 (aggressive optimization)
 *   - MSVC: /O2 (maximum optimization)
 * - <b>OFF</b>:
 *   - GCC/Clang: -O0 (no optimization)
 *   - MSVC: /Od (disable optimization)
 */
#ifndef EYA_COMPILE_OPTION_OPTIMIZATION
#    define EYA_COMPILE_OPTION_OPTIMIZATION EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_DEBUG
 * @brief Enables/disables debug information generation
 * @details Controls whether debug symbols are included in the output binary.
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -g (generate debug info)
 *   - MSVC: /Zi (detailed debug info)
 */
#ifndef EYA_COMPILE_OPTION_DEBUG
#    define EYA_COMPILE_OPTION_DEBUG EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_SSE2
 * @brief Enables/disables SSE2 instruction set
 * @details Allows compiler to generate SSE2 instructions
 *          (available on most x86 CPUs since 2003).
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -msse2
 *   - MSVC: /arch:SSE2
 */
#ifndef EYA_COMPILE_OPTION_SSE2
#    define EYA_COMPILE_OPTION_SSE2 EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_AVX2
 * @brief Enables/disables AVX2 instruction set
 * @details Allows compiler to generate AVX2 instructions
 *          (requires Haswell or newer CPU).
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -mavx2
 *   - MSVC: /arch:AVX2
 */
#ifndef EYA_COMPILE_OPTION_AVX2
#    define EYA_COMPILE_OPTION_AVX2 EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_AVX512
 * @brief Enables/disables AVX-512 instruction set
 * @details Allows compiler to generate AVX-512 instructions
 *          (requires Skylake-X or newer CPU).
 *
 * @warning May cause throttling on some CPUs
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -mavx512f -mavx512bw -mavx512vl
 *   - MSVC: /arch:AVX512
 */
#ifndef EYA_COMPILE_OPTION_AVX512
#    define EYA_COMPILE_OPTION_AVX512 EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_LTO
 * @brief Enables/disables Link Time Optimization
 * @details Performs whole-program optimization during linking.
 *
 * @warning May significantly increase compilation time
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC: -flto=auto
 *   - Clang: -flto=auto -fuse-ld=lld (if available)
 *   - MSVC: /GL (whole program optimization) /LTCG (link-time code generation)
 */
#ifndef EYA_COMPILE_OPTION_LTO
#    define EYA_COMPILE_OPTION_LTO EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_UNROLL_LOOPS
 * @brief Enables/disables loop unrolling
 * @details Controls whether compiler should unroll loops for better performance.
 *
 * @note May increase code size significantly
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -funroll-loops
 */
#ifndef EYA_COMPILE_OPTION_UNROLL_LOOPS
#    define EYA_COMPILE_OPTION_UNROLL_LOOPS EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_STACK_PROTECTOR
 * @brief Enables/disables stack protection
 * @details Adds protection against stack buffer overflows.
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -fstack-protector
 *   - MSVC: /GS
 * - <b>OFF</b>:
 *   - GCC/Clang: -fno-stack-protector
 *   - MSVC: /GS-
 */
#ifndef EYA_COMPILE_OPTION_STACK_PROTECTOR
#    define EYA_COMPILE_OPTION_STACK_PROTECTOR EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_PIC
 * @brief Enables/disables Position Independent Code
 * @details Required for shared libraries.
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -fPIC
 */
#ifndef EYA_COMPILE_OPTION_PIC
#    define EYA_COMPILE_OPTION_PIC EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_THREAD_SAFETY
 * @brief Enables/disables thread safety features
 *
 * @details Adds support for multithreading.
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -pthread
 */
#ifndef EYA_COMPILE_OPTION_THREAD_SAFETY
#    define EYA_COMPILE_OPTION_THREAD_SAFETY EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_FAST_MATH
 * @brief Enables/disables fast math optimizations
 *
 * @warning May affect floating-point precision
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -ffast-math -fno-math-errno -funsafe-math-optimizations
 *   - MSVC: /fp:fast
 */
#ifndef EYA_COMPILE_OPTION_FAST_MATH
#    define EYA_COMPILE_OPTION_FAST_MATH EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_NATIVE_TUNE
 * @brief Enables/disables CPU-specific tuning
 * @details Optimizes for the current CPU architecture.
 *
 * @warning Reduces portability
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -march=native -mtune=native
 */
#ifndef EYA_COMPILE_OPTION_NATIVE_TUNE
#    define EYA_COMPILE_OPTION_NATIVE_TUNE EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_BRANCH_PREDICTION
 * @brief Enables/disables branch prediction optimizations
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -fprofile-arcs -fpredictive-commoning
 *   - MSVC: /Qspectre (Spectre mitigations)
 */
#ifndef EYA_COMPILE_OPTION_BRANCH_PREDICTION
#    define EYA_COMPILE_OPTION_BRANCH_PREDICTION EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_MEMORY_OPT
 * @brief Enables/disables memory access optimizations
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC: -fprefetch-loop-arrays
 *   - MSVC: /Oi (enable intrinsic functions)
 */
#ifndef EYA_COMPILE_OPTION_MEMORY_OPT
#    define EYA_COMPILE_OPTION_MEMORY_OPT EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_VISIBILITY_HIDDEN
 * @brief Enables/disables hidden symbol visibility
 * @details Improves performance of shared libraries by reducing symbol table size.
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -fvisibility=hidden
 */
#ifndef EYA_COMPILE_OPTION_VISIBILITY_HIDDEN
#    define EYA_COMPILE_OPTION_VISIBILITY_HIDDEN EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_TREE_VECTORIZE
 * @brief Enables/disables tree vectorization
 * @details Controls automatic vectorization of loops.
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -ftree-vectorize
 * - <b>OFF</b>:
 *   - GCC/Clang: -fno-tree-vectorize
 */
#ifndef EYA_COMPILE_OPTION_TREE_VECTORIZE
#    define EYA_COMPILE_OPTION_TREE_VECTORIZE EYA_COMPILE_OPTION_OFF
#endif

/**
 * @def EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION
 * @brief Enables/disables semantic interposition prevention
 * @details Allows more aggressive optimizations when symbols cannot be interposed.
 *
 * @note Default: EYA_COMPILE_OPTION_OFF
 *
 * Options:
 * - <b>ON</b>:
 *   - GCC/Clang: -fno-semantic-interposition
 */
#ifndef EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION
#    define EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION EYA_COMPILE_OPTION_OFF
#endif

#endif // EYA_COMPILE_OPTION_FALLBACK_H