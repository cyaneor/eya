# Option:
#
#     EYA_COMPILE_OPTION_DEBUG
#
# Description:
#
#     Controls comprehensive debugging support including symbols, assertions,
#     and debugging-friendly code generation. When enabled:
#     - Adds -g or -ggdb for detailed debug symbols (DWARF format)
#     - Sets -O0 or -Og to disable optimizations that obscure source mapping
#     - Enables assertions (NDEBUG not defined) for runtime validation
#     - May include frame pointers for better stack traces
#     - Preserves variable names and eliminates code reordering
#
# Usage:
#
#     ON: Full debugging support - larger binaries, slower execution, development use
#     OFF: Production mode - stripped symbols, optimized code (default)
#
# Technical Impact:
#     Binary size increase: 50-300% due to debug symbols
#     Performance penalty: 2-10x slower execution
#     Memory usage: Increased debug information in memory
#
# Recommendation:
#     Always enable during development. For production deployments, consider
#     generating separate debug symbol packages for post-mortem analysis.
#
option(EYA_COMPILE_OPTION_DEBUG
        "Enable comprehensive debugging support including symbols and assertions" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_OPTIMIZATION
#
# Description:
#
#     Controls the baseline optimization level for performance-critical code.
#     When enabled, typically sets -O2 or -O3 optimization levels:
#     - -O2: Standard optimizations (inlining, loop optimizations, code reordering)
#     - -O3: Aggressive optimizations (vectorization, function cloning, more inlining)
#     - Includes dead code elimination, constant propagation, and common subexpression elimination
#
# Usage:
#
#     ON: Enable performance optimizations (default for production)
#     OFF: Disable optimizations (primarily for debugging)
#
# Technical Impact:
#     Performance improvement: 10-100% depending on code characteristics
#     Compilation time: Increased due to optimization passes
#     Debugging difficulty: Medium to high with optimizations enabled
#
# Recommendation:
#     Enable for all production builds. Test thoroughly as aggressive optimizations
#     may occasionally introduce subtle bugs or change floating-point behavior.
#
option(EYA_COMPILE_OPTION_OPTIMIZATION
        "Enable standard compiler optimizations for performance" ON)

# Option:
#
#     EYA_COMPILE_OPTION_LTO
#
# Description:
#
#     Enables Link-Time Optimization, a whole-program optimization technique that:
#     - Analyzes the entire program during linking, not just individual compilation units
#     - Enables cross-module inlining and interprocedural optimization
#     - Improves cache locality through better code layout
#     - Can specialize functions based on cross-module usage patterns
#
# Usage:
#
#     ON: Enable whole-program optimization (default)
#     OFF: Disable LTO, use traditional compilation model
#
# Technical Impact:
#     Performance improvement: 5-15% additional gain over -O3
#     Link time: Significantly increased (2-5x normal link time)
#     Memory usage: High memory consumption during linking
#     Compatibility: Requires toolchain support (GCC/Clang recent versions)
#
# Recommendation:
#     Enable for production builds where maximum performance is critical.
#     Ensure sufficient memory is available during linking (8GB+ for large projects).
#
option(EYA_COMPILE_OPTION_LTO
        "Enable Link-Time Optimization for whole-program analysis" ON)

# Option:
#
#     EYA_COMPILE_OPTION_MEMORY_OPT
#
# Description:
#
#     Enables memory subsystem optimizations targeting:
#     - Cache line optimization (prefetching, alignment)
#     - Data structure layout optimizations
#     - Memory access pattern improvements
#     - Reduction of cache conflicts and false sharing
#     - Optimized memcpy/memset implementations
#
# Usage:
#
#     ON: Enable advanced memory optimizations (default)
#     OFF: Use standard memory access patterns
#
# Technical Impact:
#     Memory-bound performance: 10-40% improvement for data-intensive workloads
#     CPU-bound performance: Minimal impact
#     Code size: Slight increase due to specialized routines
#
# Recommendation:
#     Essential for database, scientific computing, and data processing applications.
#     Less critical for CPU-bound mathematical computations.
#
option(EYA_COMPILE_OPTION_MEMORY_OPT
        "Enable advanced memory subsystem optimizations" ON)

# Option:
#
#     EYA_COMPILE_OPTION_BRANCH_PREDICTION
#
# Description:
#
#     Controls compiler-assisted branch prediction optimization through:
#     - __builtin_expect() directives for hinting likely/unlikely branches
#     - Static branch prediction based on profiling or heuristics
#     - Code layout optimizations to improve instruction cache behavior
#     - Reduction of branch misprediction penalties
#
# Usage:
#
#     ON: Enable branch prediction hints and optimizations (default)
#     OFF: Use neutral branch prediction behavior
#
# Technical Impact:
#     Performance improvement: 1-5% for branch-heavy code
#     Modern CPU impact: Reduced benefit due to sophisticated hardware predictors
#     Maintenance: Requires careful profiling for effective use
#
# Recommendation:
#     Enable by default. For critical performance sections, supplement with
#     manual __builtin_expect() annotations based on actual profiling data.
#
option(EYA_COMPILE_OPTION_BRANCH_PREDICTION
        "Enable compiler-assisted branch prediction optimization" ON)

# Option:
#
#     EYA_COMPILE_OPTION_UNROLL_LOOPS
#
# Description:
#
#     Controls automatic loop unrolling strategies:
#     - Full unrolling of small, fixed-count loops
#     - Partial unrolling of larger loops with runtime trip counts
#     - Heuristic-based unrolling factor selection
#     - Integration with vectorization and software pipelining
#
# Usage:
#
#     ON: Enable aggressive loop unrolling (default)
#     OFF: Disable automatic unrolling, preserve original loop structure
#
# Technical Impact:
#     Performance improvement: 5-20% for loop-dominated code
#     Code size increase: 2-10x for unrolled loops
#     Instruction cache: Potential negative impact from larger code size
#
# Recommendation:
#     Enable for numerical and processing workloads. Monitor instruction cache
#     performance for very large applications. Consider manual unrolling for
#     critical loops where compiler heuristics may be suboptimal.
#
option(EYA_COMPILE_OPTION_UNROLL_LOOPS
        "Enable automatic loop unrolling optimization" ON)

# Option:
#
#     EYA_COMPILE_OPTION_STACK_PROTECTOR
#
# Description:
#
#     Enables stack buffer overflow protection mechanisms:
#     - Stack canaries (protector cookies) inserted before return addresses
#     - Runtime validation of canary values during function exit
#     - Protection against return-oriented programming (ROP) attacks
#     - Mitigation of stack-based buffer overflow vulnerabilities
#
# Usage:
#
#     ON: Enable comprehensive stack protection (recommended for security)
#     OFF: Disable protection for minimal performance gain (default)
#
# Technical Impact:
#     Security: Critical protection against common exploit techniques
#     Performance overhead: 0.5-2% depending on function call frequency
#     Memory overhead: 4-8 bytes per stack frame for canary storage
#
# Recommendation:
#     Strongly recommend enabling for all security-sensitive deployments.
#     The performance cost is minimal compared to the security benefits.
#     Disable only in exceptionally performance-critical, trusted environments.
#
option(EYA_COMPILE_OPTION_STACK_PROTECTOR
        "Enable stack buffer overflow protection" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_NATIVE_TUNE
#
# Description:
#
#     Enables CPU-specific microarchitecture tuning:
#     - Instruction scheduling for specific CPU pipelines
#     - Cache hierarchy optimization (sizes, associativity)
#     - Branch prediction tuning for specific CPU implementations
#     - Optimal instruction selection for target microarchitecture
#     - Use of extended instruction sets available on the build machine
#
# Usage:
#
#     ON: Optimize for native CPU microarchitecture (default)
#     OFF: Use generic, portable optimizations
#
# Technical Impact:
#     Performance improvement: 5-25% on target hardware
#     Portability: Binary may not run on older or different CPU architectures
#     Compilation: Requires detection of build machine capabilities
#
# Recommendation:
#     Enable when building for specific deployment hardware (HPC, embedded).
#     Disable when building distributable binaries for heterogeneous environments.
#     Use in combination with CI/CD pipelines that build on representative hardware.
#
option(EYA_COMPILE_OPTION_NATIVE_TUNE
        "Enable CPU-specific microarchitecture tuning" ON)

# Option:
#
#     EYA_COMPILE_OPTION_TREE_VECTORIZE
#
# Description:
#
#     Enables advanced tree vectorization using SIMD instructions:
#     - Automatic detection of vectorizable loops
#     - Generation of SSE, AVX, or NEON instructions
#     - Data alignment analysis and optimization
#     - Loop restructuring for vectorization opportunities
#     - Integration with outer loop optimizations
#
# Usage:
#
#     ON: Enable automatic vectorization (default)
#     OFF: Disable automatic SIMD code generation
#
# Technical Impact:
#     Performance improvement: 2-8x for vectorizable numerical code
#     Requirements: Data alignment, stride patterns, dependency freedom
#     Compilation time: Increased due to vectorization analysis
#
# Recommendation:
#     Essential for scientific computing, image processing, and machine learning.
#     Supplement with manual SIMD intrinsics for performance-critical sections
#     where compiler auto-vectorization may be suboptimal.
#
option(EYA_COMPILE_OPTION_TREE_VECTORIZE
        "Enable automatic loop vectorization using SIMD instructions" ON)

# Option:
#
#     EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION
#
# Description:
#
#     Assumes no symbol interposition, enabling aggressive optimizations:
#     - Function inlining across translation unit boundaries
#     - Whole-program devirtualization and constant propagation
#     - Aggressive dead code elimination of unused global functions
#     - Optimized virtual call resolution through speculative devirtualization
#
# Usage:
#
#     ON: Assume no symbol interposition, enable cross-module optimization (default)
#     OFF: Preserve interposition capability, use conservative optimization
#
# Technical Impact:
#     Performance improvement: 5-15% for modular codebases
#     Compatibility: Disables LD_PRELOAD and runtime symbol overriding
#     Binary size: Reduced through more aggressive dead code elimination
#
# Recommendation:
#     Enable for maximum performance when dynamic symbol interposition is not required.
#     Disable if using LD_PRELOAD, runtime instrumentation, or hot-patching techniques.
#
option(EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION
        "Disable semantic interposition for cross-module optimization" ON)

# Option:
#
#     EYA_COMPILE_OPTION_SSE2
#
# Description:
#
#     Enables SSE2 (Streaming SIMD Extensions 2) instruction set:
#     - 128-bit vector operations on packed and scalar double-precision floating-point
#     - 128-bit integer SIMD operations
#     - Enhanced memory management and cacheability instructions
#     - Foundation for later SSE versions and advanced vectorization
#
# Usage:
#
#     ON: Enable SSE2 instruction generation (default)
#     OFF: Disable SSE2, use x87 floating-point and traditional integer operations
#
# Technical Impact:
#     Floating-point performance: 2-4x improvement for vectorizable code
#     Portability: Requires Pentium 4/AMD Opteron or newer (circa 2000+)
#     Precision: Improved floating-point consistency compared to x87
#
# Recommendation:
#     Essential for x86-64 targets (SSE2 is mandatory in x86-64 architecture).
#     Disable only for compatibility with very old 32-bit x86 systems.
#
option(EYA_COMPILE_OPTION_SSE2
        "Enable SSE2 instruction set for enhanced vector operations" ON)

# Option:
#
#     EYA_COMPILE_OPTION_AVX2
#
# Description:
#
#     Enables AVX2 (Advanced Vector Extensions 2) instruction set:
#     - 256-bit vector operations on integer and floating-point data
#     - Fused Multiply-Add (FMA) operations for improved precision and performance
#     - Enhanced gather operations for scattered memory access
#     - Bit manipulation and vector shift instructions
#
# Usage:
#
#     ON: Enable AVX2 instruction generation (default)
#     OFF: Disable AVX2, use SSE-based vectorization
#
# Technical Impact:
#     Vector performance: 2x improvement over SSE for compatible workloads
#     Hardware requirements: Haswell microarchitecture or newer (2013+)
#     Power consumption: May cause increased thermal design power (TDP)
#
# Recommendation:
#     Enable for servers and workstations with known AVX2 support.
#     Consider runtime dispatch for heterogeneous deployment environments.
#
option(EYA_COMPILE_OPTION_AVX2
        "Enable AVX2 instruction set for 256-bit vector operations" ON)

# Option:
#
#     EYA_COMPILE_OPTION_AVX512
#
# Description:
#
#     Enables AVX-512 (Advanced Vector Extensions 512) instruction set:
#     - 512-bit vector operations for maximum throughput
#     - Enhanced opmask registers for predicated execution
#     - Advanced scatter-gather and compression operations
#     - Extended vector length and new data types
#
# Usage:
#
#     ON: Enable AVX-512 instruction generation
#     OFF: Disable AVX-512, use AVX2/SSE vectorization (default)
#
# Technical Impact:
#     Vector performance: 2x improvement over AVX2 for optimized code
#     Hardware requirements: Skylake-X, Ice Lake, or newer server CPUs
#     Frequency impact: May cause clock frequency throttling on some CPUs
#     Power consumption: Significant increase in power usage
#
# Recommendation:
#     Enable only for HPC and specialized workloads on known AVX-512 capable hardware.
#     Use runtime CPU detection and feature-specific dispatch for mixed environments.
#     Thoroughly test thermal and power implications in target deployment.
#
option(EYA_COMPILE_OPTION_AVX512
        "Enable AVX-512 instruction set for 512-bit vector operations" OFF)