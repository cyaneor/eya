# Option:
#
#     EYA_COMPILE_OPTION_SSE2
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_SSE2 controls SSE2 (Streaming SIMD Extensions 2)
#     instruction support at compile-time. SSE2 extends original SSE capabilities by adding
#     double-precision floating-point operations and new integer instructions, improving
#     performance in multimedia, scientific, and gaming applications.
#
#     Setting to ON enables compiler-generated SSE2 code for performance gains on compatible CPUs.
#
# Usage:
#
#     ON: Enables SSE2 support (recommended for all x86/x86_64 CPUs since 2003)
#     OFF: Disables SSE2 (for legacy CPU compatibility) with significant performance penalty
#
# Notes:
#
#     - SSE2 is natively supported on x86_64 architectures
#     - Disabling may severely degrade performance as modern libraries rely on SSE2
#     - Default enabled for x86_64 targets
#
option(EYA_COMPILE_OPTION_SSE2
        "Enable SSE2 instruction set support" ON)

# Option:
#
#     EYA_COMPILE_OPTION_AVX2
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_AVX2 controls AVX2 (Advanced Vector Extensions 2)
#     instruction support. Enhances vector processing and floating-point computations
#     for high-performance applications in data processing and scientific computing.
#
# Usage:
#
#     ON: Enables AVX2 instructions (significant performance boost on supported CPUs)
#     OFF: Disables AVX2 support
#
# Notes:
#
#     - Verify CPU compatibility before enabling
#     - May cause crashes on pre-Haswell (2013) Intel CPUs and pre-Excavator (2015) AMD CPUs
#
option(EYA_COMPILE_OPTION_AVX2
        "Enable AVX2 instruction set support" ON)

# Option:
#
#     EYA_COMPILE_OPTION_AVX512
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_AVX512 controls AVX-512 instruction support,
#     providing enhanced vector processing capabilities for HPC, ML, and big data applications.
#
# Usage:
#
#     ON: Enables AVX-512 instructions (requires Skylake-X/SP or newer Intel CPUs)
#     OFF: Disables AVX-512 support (default)
#
# Notes:
#
#     - Check CPU support (Intel Xeon Scalable, Core i9 10th+ Gen)
#     - May cause thermal throttling on some implementations
#
option(EYA_COMPILE_OPTION_AVX512
        "Enable AVX-512 instruction set support" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_UNROLL_LOOPS
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_UNROLL_LOOPS controls compiler loop unrolling
#     optimizations to reduce loop control overhead and improve instruction-level parallelism.
#
# Usage:
#
#     ON: Enables aggressive loop unrolling (default)
#     OFF: Disables automatic loop unrolling
#
# Notes:
#
#     - May increase code size by 10-30%
#     - Combine with -O3 for maximum effect
#     - Use #pragma unroll for manual control
#
option(EYA_COMPILE_OPTION_UNROLL_LOOPS
        "Enable compiler loop unrolling optimizations" ON)

# Option:
#
#     EYA_COMPILE_OPTION_NO_STACK_PROTECTOR
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_NO_STACK_PROTECTOR controls stack overflow
#     protection mechanisms (SSP) using canary values.
#
# Usage:
#
#     ON: Disables stack protection (reduces security)
#     OFF: Enables stack protection (recommended for production)
#
# Notes:
#
#     - Disabling improves performance by ~2% in microbenchmarks
#     - Required for some low-level systems programming
#     - Not recommended for network-facing services
#
option(EYA_COMPILE_OPTION_NO_STACK_PROTECTOR
        "Disable stack overflow protection" ON)

# Option:
#
#     EYA_COMPILE_OPTION_PIC
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_PIC controls Position Independent Code
#     generation for shared libraries and ASLR-compatible executables.
#
# Usage:
#
#     ON: Enables PIC (required for shared libraries)
#     OFF: Disables PIC (for static linking optimizations)
#
# Notes:
#
#     - Adds ~5% overhead for global data access
#     - Required for proper ASLR implementation
#     - Automatically enabled when BUILD_SHARED_LIBS=ON
#
option(EYA_COMPILE_OPTION_PIC
        "Generate position-independent code" ON)

# Option:
#
#     EYA_COMPILE_OPTION_THREAD_SAFETY
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_THREAD_SAFETY enables thread-safe compilation
#     by linking with platform-specific threading libraries.
#
# Usage:
#
#     ON: Enables pthread linking (Unix) or equivalent thread support
#     OFF: Disables explicit thread library linking
#
# Notes:
#
#     - Required for proper mutex and atomic operation support
#     - Adds minimal runtime overhead when enabled
#     - Recommended for all multi-threaded applications
#
option(EYA_COMPILE_OPTION_THREAD_SAFETY
        "Enable thread-safe compilation" ON)

# Option:
#
#     EYA_COMPILE_OPTION_NATIVE_TUNE
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_NATIVE_TUNE optimizes 
#     code specifically for the host CPU architecture.
#
# Usage:
#
#     ON: Enables -march=native and -mtune=native optimizations
#     OFF: Uses generic architecture settings
#
# Notes:
#
#     - Provides 5-15% performance improvement on host system
#     - May produce binaries incompatible with older CPUs
#     - Not recommended for distributed builds
#
option(EYA_COMPILE_OPTION_NATIVE_TUNE
        "Optimize for native CPU architecture" OFF)