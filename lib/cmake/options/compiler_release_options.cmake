# Verify current build type is "Release"
if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    # Exit script if not Release configuration
    return()
endif()

# Option:
#
#     EYA_COMPILE_OPTION_OPTIMIZATION
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_OPTIMIZATION controls compiler optimization
#     flags for performance-critical builds.
#
#     When enabled (default ON), activates aggressive compiler optimizations
#     including:
#     - Function inlining
#     - Loop vectorization
#     - Instruction scheduling
#     - Dead code elimination
#
# Usage:
#
#     ON: Enables -O2/-O3 optimization levels (recommended for production)
#     OFF: Disables optimizations (useful for debugging unoptimized code)
#
# Notes:
#
#     - Typically improves runtime performance by 20-40%
#     - May increase compilation time by 15-25%
#     - Can obscure debug information (line numbers, variable tracking)
#     - Test thoroughly after enabling - some optimizations may expose latent bugs
#
option(EYA_COMPILE_OPTION_OPTIMIZATION
        "Enable compiler optimization flags (-O2/-O3 level)" ON)

# Option:
#
#     EYA_COMPILE_OPTION_LTO
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_LTO controls Link Time Optimization (LTO),
#     enabling whole-program analysis during linking phase.
#
#     When enabled (default ON), allows cross-module optimizations that:
#     - Eliminate unused code paths
#     - Optimize cross-function calls
#     - Improve cache utilization
#
# Usage:
#
#     ON: Enables LTO (requires CMake 3.9+ and compiler support)
#     OFF: Disables interprocedural optimizations
#
# Notes:
#
#     - Reduces final binary size by 5-15%
#     - Improves runtime performance by 5-10%
#     - Increases build time by 30-50%
#     - Requires compatible toolchain (GCC 4.9+, Clang 3.9+, MSVC 2019+)
#     - May expose hidden symbol dependencies
#
option(EYA_COMPILE_OPTION_LTO
        "Enable link-time whole-program optimization" ON)

# Option:
#
#     EYA_COMPILE_OPTION_VISIBILITY_HIDDEN
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_VISIBILITY_HIDDEN controls symbol visibility
#     to reduce dynamic library export table size.
#
# Usage:
#
#     ON: Hides all non-exported symbols (recommended for shared libraries)
#     OFF: Uses default symbol visibility
#
# Notes:
#
#     - Can reduce shared library size by 10-20%
#     - Improves loading performance
#     - Requires explicit export declarations for public APIs
#
option(EYA_COMPILE_OPTION_VISIBILITY_HIDDEN
        "Enable hidden symbol visibility" ON)

# Option:
#
#     EYA_COMPILE_OPTION_MEMORY_OPT
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_MEMORY_OPT enables 
#     memory access pattern optimizations.
#
# Usage:
#
#     ON: Enables prefetch and memory access optimizations
#     OFF: Uses standard memory access patterns
#
# Notes:
#
#     - Can improve performance for memory-bound workloads
#     - May increase code size slightly
#     - Most effective on modern out-of-order CPUs
#
option(EYA_COMPILE_OPTION_MEMORY_OPT
        "Enable memory access optimizations" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_PARALLEL
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_PARALLEL enables 
#     automatic loop parallelization optimizations.
#
# Usage:
#
#     ON: Enables compiler auto-parallelization
#     OFF: Disables automatic parallel transforms
#
# Notes:
#
#     - Uses 4 threads by default for parallel loops
#     - Requires thread-safe runtime
#     - Effectiveness varies by code structure
#
option(EYA_COMPILE_OPTION_PARALLEL
        "Enable automatic loop parallelization" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_FUNCTION_SECTIONS
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_FUNCTION_SECTIONS enables
#     per-function/data section generation for better dead code elimination.
#
# Usage:
#
#     ON: Places each function in separate section
#     OFF: Uses standard section layout
#
# Notes:
#
#     - Can reduce final binary size by 5-15%
#     - Improves linker optimization opportunities
#     - May slightly increase compile time
#
option(EYA_COMPILE_OPTION_FUNCTION_SECTIONS
        "Enable function/data sections optimization" OFF)

# Option:
#
#     EYA_COMPILE_OPTION_BRANCH_PREDICTION
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_BRANCH_PREDICTION enables
#     advanced branch prediction optimizations.
#
# Usage:
#
#     ON: Enables branch prediction hints and optimizations
#     OFF: Uses standard branch handling
#
# Notes:
#
#     - Can improve performance on deep pipelines
#     - May increase code size slightly
#     - Most effective on modern speculative CPUs
#
option(EYA_COMPILE_OPTION_BRANCH_PREDICTION
        "Enable branch prediction optimizations" OFF)