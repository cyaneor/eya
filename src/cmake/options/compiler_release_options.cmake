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