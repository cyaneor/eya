# Verify current build type is not "Debug"
if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    # Exit script if not Debug configuration
    return()
endif()

# Option:
#
#     EYA_COMPILE_OPTION_DEBUG
#
# Description:
#
#     CMake option EYA_COMPILE_OPTION_DEBUG controls activation of compiler debugging flags
#     for generating debuggable binaries.
#
#     When enabled (default ON), configures the compiler to produce debug symbols and
#     disable optimizations, facilitating code analysis and error diagnostics during
#     development and testing phases.
#
# Usage:
#
#     ON: Enables debug compiler flags (recommended for development environments)
#     OFF: Disables debug features for potential performance improvements
#
# Notes:
#
#     - Debug symbols typically increase binary size by 15-30%
#     - Debug builds may exhibit 20-50% slower execution compared to optimized builds
#     - Required for accurate stack traces and memory leak detection
#     - Should be disabled in production releases via EYA_COMPILE_OPTION_DEBUG=OFF
#
option(EYA_COMPILE_OPTION_DEBUG
        "Enable compiler debugging flags and symbols generation" ON)