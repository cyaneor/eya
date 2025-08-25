# Option:
#
#     EYA_COMPILE_OPTION_DEBUG
#
# Description:
#
#     Enables debugging flags and disables optimizations that obscure source code mapping.
#     When enabled:
#     - Adds debug symbols (-g or -ggdb) for detailed debugging information
#     - Sets optimization level to -O0 or -Og to preserve variable states
#     - Enables assertions and runtime checks
#     - May include frame pointers for better stack traces
#
# Usage:
#
#     ON: Development mode - enables debugging, larger binaries, slower execution (default)
#     OFF: Production mode - no debug symbols, optimized code
#
# Technical Impact:
#     Binary size: Significant increase (50-300%) due to debug information
#     Performance: 2-10x slower execution
#     Debugability: Excellent for development and troubleshooting
#
# Recommendation:
#     Enable during development and testing. Disable for production releases.
#     Consider generating separate debug symbol packages for production debugging.
#
option(EYA_COMPILE_OPTION_DEBUG
        "Enable debug flags, assertions, and disable optimizations for development" ON)

# Option:
#
#     EYA_COMPILE_OPTION_OPTIMIZATION
#
# Description:
#
#     Controls compiler optimization levels for performance improvement.
#     When enabled, applies standard optimizations such as:
#     - Inlining of small functions
#     - Loop optimizations and reordering
#     - Dead code elimination
#     - Constant propagation and common subexpression elimination
#
# Usage:
#
#     ON: Enable performance optimizations (typically -O2 or -O3)
#     OFF: Disable optimizations for debugging purposes (default)
#
# Technical Impact:
#     Performance: 10-100% improvement depending on code characteristics
#     Compilation time: Increased due to optimization passes
#     Debugging: More difficult due to code transformation
#
# Recommendation:
#     Enable for production builds. Test thoroughly as optimizations may
#     occasionally expose hidden bugs or change floating-point behavior.
#
option(EYA_COMPILE_OPTION_OPTIMIZATION
        "Enable standard performance optimizations (e.g., -O2)" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_LTO
#
# Description:
#
#     Enables Link-Time Optimization, a whole-program optimization technique that:
#     - Analyzes the entire program during linking phase
#     - Enables cross-module inlining and interprocedural optimization
#     - Improves code layout for better cache locality
#     - Can specialize functions based on cross-module usage patterns
#
# Usage:
#
#     ON: Enable whole-program optimization
#     OFF: Use traditional per-module compilation model (default)
#
# Technical Impact:
#     Performance: 5-15% additional gain over standard optimizations
#     Link time: Significantly increased (2-5x normal link time)
#     Memory usage: High memory consumption during linking
#
# Recommendation:
#     Enable for production builds where maximum performance is critical.
#     Ensure sufficient memory is available during linking.
#
option(EYA_COMPILE_OPTION_LTO
        "Enable Link-Time Optimization (whole-program optimization)" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_MEMORY_OPT
#
# Description:
#
#     Enables memory subsystem optimizations targeting:
#     - Cache line optimization and prefetching
#     - Data structure alignment and layout improvements
#     - Memory access pattern optimizations
#     - Reduction of cache conflicts and false sharing
#
# Usage:
#
#     ON: Enable advanced memory access optimizations
#     OFF: Use standard memory access patterns (default)
#
# Technical Impact:
#     Memory-bound performance: 10-40% improvement for data-intensive workloads
#     Code size: Slight increase due to specialized routines
#     CPU usage: Minimal impact on CPU-bound code
#
# Recommendation:
#     Essential for database, scientific computing, and data processing applications.
#     Less critical for purely computational workloads.
#
option(EYA_COMPILE_OPTION_MEMORY_OPT
        "Enable optimizations targeting cache and memory access patterns" OFF)

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
#     ON: Enable branch prediction hints and optimizations
#     OFF: Use neutral branch prediction behavior (default)
#
# Technical Impact:
#     Performance: 1-5% improvement for branch-heavy code
#     Modern CPUs: Reduced benefit due to sophisticated hardware predictors
#     Maintenance: Requires profiling for effective use
#
# Recommendation:
#     Enable for performance-critical builds. Supplement with manual
#     annotations based on actual profiling data for best results.
#
option(EYA_COMPILE_OPTION_BRANCH_PREDICTION
        "Enable optimizations based on static branch prediction" OFF)

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
#     ON: Enable aggressive loop unrolling
#     OFF: Preserve original loop structure (default)
#
# Technical Impact:
#     Performance: 5-20% improvement for loop-dominated code
#     Code size: 2-10x increase for unrolled loops
#     Instruction cache: Potential negative impact from larger code size
#
# Recommendation:
#     Enable for numerical and processing workloads. Monitor instruction
#     cache performance for very large applications.
#
option(EYA_COMPILE_OPTION_UNROLL_LOOPS
        "Enable automatic loop unrolling" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_STACK_PROTECTOR
#
# Description:
#
#     Enables stack buffer overflow protection mechanisms:
#     - Stack canaries (protector cookies) before return addresses
#     - Runtime validation of canary values during function exit
#     - Protection against return-oriented programming (ROP) attacks
#     - Mitigation of stack-based buffer overflow vulnerabilities
#
# Usage:
#
#     ON: Enable comprehensive stack protection (recommended for security) (default)
#     OFF: Disable protection for minimal performance gain
#
# Technical Impact:
#     Security: Critical protection against common exploit techniques
#     Performance: 0.5-2% overhead depending on function call frequency
#     Memory: 4-8 bytes per stack frame for canary storage
#
# Recommendation:
#     Strongly recommend enabling for all security-sensitive deployments.
#     Disable only in exceptionally performance-critical, trusted environments.
#
option(EYA_COMPILE_OPTION_STACK_PROTECTOR
        "Enable stack smashing protection (security hardening)" ON)

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
#
# Usage:
#
#     ON: Optimize for native CPU microarchitecture
#     OFF: Use generic, portable optimizations (default)
#
# Technical Impact:
#     Performance: 5-25% improvement on target hardware
#     Portability: Binary may not run on different CPU architectures
#     Compilation: Requires detection of build machine capabilities
#
# Recommendation:
#     Enable when building for specific deployment hardware.
#     Disable when building distributable binaries for heterogeneous environments.
#
option(EYA_COMPILE_OPTION_NATIVE_TUNE
        "Optimize for the native CPU microarchitecture (reduces portability)" OFF)

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
#
# Usage:
#
#     ON: Enable automatic vectorization
#     OFF: Disable automatic SIMD code generation (default)
#
# Technical Impact:
#     Performance: 2-8x improvement for vectorizable numerical code
#     Requirements: Data alignment, stride patterns, dependency freedom
#     Compilation time: Increased due to vectorization analysis
#
# Recommendation:
#     Essential for scientific computing, image processing, and machine learning.
#     Supplement with manual SIMD intrinsics for performance-critical sections.
#
option(EYA_COMPILE_OPTION_TREE_VECTORIZE
        "Enable automatic loop vectorization with SIMD instructions" OFF)

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
#     ON: Assume no symbol interposition, enable cross-module optimization
#     OFF: Preserve interposition capability, use conservative optimization (default)
#
# Technical Impact:
#     Performance: 5-15% improvement for modular codebases
#     Compatibility: Disables LD_PRELOAD and runtime symbol overriding
#     Binary size: Reduced through more aggressive dead code elimination
#
# Recommendation:
#     Enable for maximum performance when dynamic symbol interposition is not required.
#     Disable if using LD_PRELOAD, runtime instrumentation, or hot-patching techniques.
#
option(EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION
        "Assume no symbol interposition, enabling aggressive cross-module optimizations" OFF)