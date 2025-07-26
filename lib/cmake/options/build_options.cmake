# ---------------------------------------------------------------------------------------- #
# Build Configuration Settings                                                             #
#                                                                                          #
# This section defines compiler options based on the build type (Debug/Release).           #
#                                                                                          #
# Debug configuration enables:                                                             #
#   - Debug flags                                                                          #
#   - Stack protection                                                                     #
#                                                                                          #
# Release configuration enables:                                                           #
#   - Optimizations (LTO, memory, loops, branch prediction)                                #
#   - CPU-specific tuning (native, vectorization, instruction sets)                       #
#   - Semantic interposition disabling                                                    #
# ---------------------------------------------------------------------------------------- #

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EYA_COMPILE_OPTION_DEBUG ON CACHE BOOL "Enable debug flags" FORCE)
    set(EYA_COMPILE_OPTION_OPTIMIZATION OFF CACHE BOOL "Enable optimizations")
    set(EYA_COMPILE_OPTION_LTO OFF CACHE BOOL "Enable LTO")
    set(EYA_COMPILE_OPTION_MEMORY_OPT OFF CACHE BOOL "Memory optimizations")
    set(EYA_COMPILE_OPTION_BRANCH_PREDICTION OFF CACHE BOOL "Branch prediction")
    set(EYA_COMPILE_OPTION_UNROLL_LOOPS OFF CACHE BOOL "Loop unrolling")
    set(EYA_COMPILE_OPTION_STACK_PROTECTOR ON CACHE BOOL "Stack protection")
    set(EYA_COMPILE_OPTION_NATIVE_TUNE OFF CACHE BOOL "Native CPU tuning")
    set(EYA_COMPILE_OPTION_TREE_VECTORIZE OFF CACHE BOOL "Tree vectorization")
    set(EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION OFF CACHE BOOL "Disable interposition")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(EYA_COMPILE_OPTION_DEBUG OFF CACHE BOOL "Enable debug flags")
    set(EYA_COMPILE_OPTION_OPTIMIZATION ON CACHE BOOL "Enable optimizations")
    set(EYA_COMPILE_OPTION_LTO ON CACHE BOOL "Enable LTO")
    set(EYA_COMPILE_OPTION_MEMORY_OPT ON CACHE BOOL "Memory optimizations")
    set(EYA_COMPILE_OPTION_BRANCH_PREDICTION ON CACHE BOOL "Branch prediction")
    set(EYA_COMPILE_OPTION_UNROLL_LOOPS ON CACHE BOOL "Loop unrolling")
    set(EYA_COMPILE_OPTION_STACK_PROTECTOR OFF CACHE BOOL "Stack protection")
    set(EYA_COMPILE_OPTION_NATIVE_TUNE ON CACHE BOOL "Native CPU tuning")
    set(EYA_COMPILE_OPTION_TREE_VECTORIZE ON CACHE BOOL "Tree vectorization")
    set(EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION ON CACHE BOOL "Disable interposition")
    set(EYA_COMPILE_OPTION_SSE2 ON CACHE BOOL "Enable SSE2 instruction set support")
    set(EYA_COMPILE_OPTION_AVX2 ON CACHE BOOL "Enable AVX2 instruction set support")
    set(EYA_COMPILE_OPTION_AVX512 OFF CACHE BOOL "Enable AVX-512 instruction set support")
endif ()