# --------------------------------------------------------------------------------------- #
# Compiler Flag Configuration for Build Tools                                             #
#                                                                                         #
# This script sets compiler-specific flags based on detected compiler (GCC, Clang, MSVC)  #
# and CMake options prefixed with EYA_COMPILE_OPTION_. Each enabled option translates to  #
# appropriate compiler-specific flags for the target build configuration.                 #
# --------------------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------------------- #
# Function to add a compilation option if it's not already present in the list             #
# Parameters:                                                                              #
#   VAR_NAME - Name of the variable containing compilation flags list                      #
#   OPTION_VALUE - Compilation flag to add                                                 #
#   STATUS_VAR (optional) - Name of the variable to return operation status                #
#                                                                                          #
# Returns status via STATUS_VAR (if provided):                                             #
#   "OK" - Option was successfully added                                                   #
#   "SKIPPED" - Option was already present in the list                                     #
# ---------------------------------------------------------------------------------------- #
function(add_compile_option_if_missing VAR_NAME OPTION_VALUE)
    # Initialize status variable (if provided as third parameter)
    set(STATUS_VAR "")
    if (ARGC GREATER 2)
        set(STATUS_VAR "${ARGV2}")
    endif ()

    # Default status: SKIPPED (if flag exists)
    set(STATUS_FLAG "SKIPPED")

    # Check if the flag is already in the list
    if (NOT "${OPTION_VALUE}" IN_LIST ${VAR_NAME})
        # Add flag to the list and update parent scope
        list(APPEND ${VAR_NAME} ${OPTION_VALUE})
        set(${VAR_NAME} "${${VAR_NAME}}" PARENT_SCOPE)
        set(STATUS_FLAG "OK") # Successfully added
    endif ()

    # If status variable was requested, set its value
    if (STATUS_VAR)
        set(${STATUS_VAR} "${STATUS_FLAG}" PARENT_SCOPE)
    endif ()
endfunction()


# ---------------------------------------------------------------------------------------- #
# Function to add a linker option if it's not already present in the list                  #
# Parameters:                                                                              #
#   VAR_NAME - Name of the variable containing linker flags list                           #
#   OPTION_VALUE - Linker flag to add                                                      #
#   STATUS_VAR (optional) - Name of the variable to return operation status                #
#                                                                                          #
# Returns status via STATUS_VAR (if provided):                                             #
#   "OK" - Option was successfully added                                                   #
#   "SKIPPED" - Option was already present in the list                                     #
# ---------------------------------------------------------------------------------------- #
function(add_link_option_if_missing VAR_NAME OPTION_VALUE)
    # Initialize status variable (if provided as third parameter)
    set(STATUS_VAR "")
    if (ARGC GREATER 2)
        set(STATUS_VAR "${ARGV2}")
    endif ()

    # Default status: SKIPPED (if flag exists)
    set(STATUS_FLAG "SKIPPED")

    # Check if the flag is already in the list
    if (NOT "${OPTION_VALUE}" IN_LIST ${VAR_NAME})
        # Add flag to the list and update parent scope
        list(APPEND ${VAR_NAME} ${OPTION_VALUE})
        set(${VAR_NAME} "${${VAR_NAME}}" PARENT_SCOPE)
        set(STATUS_FLAG "OK")  # Successfully added
    endif ()

    # If status variable was requested, set its value
    if (STATUS_VAR)
        set(${STATUS_VAR} "${STATUS_FLAG}" PARENT_SCOPE)
    endif ()
endfunction()

# ---------------------------------------------------------------------------------------- #
# Function to add a library to link if it's not already present in the list                #
# Parameters:                                                                              #
#   VAR_NAME - Name of the variable containing libraries list                              #
#   OPTION_VALUE - Library to add                                                          #
#   STATUS_VAR (optional) - Name of the variable to return operation status                #
#                                                                                          #
# Returns status via STATUS_VAR (if provided):                                             #
#   "OK" - Library was successfully added                                                  #
#   "SKIPPED" - Library was already present in the list                                    #
# ---------------------------------------------------------------------------------------- #
function(add_link_library_if_missing VAR_NAME OPTION_VALUE)
    # Initialize status variable (if provided as third parameter)
    set(STATUS_VAR "")
    if (ARGC GREATER 2)
        set(STATUS_VAR "${ARGV2}")
    endif ()

    # Default status: SKIPPED (if library exists)
    set(STATUS_FLAG "SKIPPED")

    # Check if the library is already in the list
    if (NOT "${OPTION_VALUE}" IN_LIST ${VAR_NAME})
        # Add library to the list and update parent scope
        list(APPEND ${VAR_NAME} ${OPTION_VALUE})
        set(${VAR_NAME} "${${VAR_NAME}}" PARENT_SCOPE)
        set(STATUS_FLAG "OK")  # Successfully added
    endif ()

    # If status variable was requested, set its value
    if (STATUS_VAR)
        set(${STATUS_VAR} "${STATUS_FLAG}" PARENT_SCOPE)
    endif ()
endfunction()

function(process_compile_options CMAKE_OPTIONS C_COMPILER_ID OUT_COMPILE_OPTIONS OUT_LINK_OPTIONS OUT_LINK_LIBRARIES)
    # Initialize instruction set variables
    set(LOCAL_COMPILE_OPTION_AVX512 OFF)
    set(LOCAL_COMPILE_OPTION_AVX2 OFF)
    set(LOCAL_COMPILE_OPTION_SSE2 OFF)

    # First pass: collect which instruction sets are requested
    foreach (CMAKE_OPTION IN ITEMS ${CMAKE_OPTIONS})
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_AVX512" AND ${CMAKE_OPTION})
            set(LOCAL_COMPILE_OPTION_AVX512 ON)
        elseif (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_AVX2" AND ${CMAKE_OPTION})
            set(LOCAL_COMPILE_OPTION_AVX2 ON)
        elseif (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_SSE2" AND ${CMAKE_OPTION})
            set(LOCAL_COMPILE_OPTION_SSE2 ON)
        endif ()
    endforeach ()

    # Detect the C compiler type and set corresponding flags
    # Checks C_COMPILER_ID and sets the following variables:
    #   C_COMPILER_ID_IS_CLANG - for Clang compiler
    #   C_COMPILER_ID_IS_GNU   - for GCC (GNU Compiler Collection)
    #   C_COMPILER_ID_IS_MSVC  - for Microsoft Visual C++ Compiler
    if (C_COMPILER_ID MATCHES "Clang")
        set(C_COMPILER_ID_IS_CLANG TRUE)
    elseif (C_COMPILER_ID MATCHES "GNU")
        set(C_COMPILER_ID_IS_GNU TRUE)
    elseif (C_COMPILER_ID STREQUAL "MSVC")
        set(C_COMPILER_ID_IS_MSVC TRUE)
    endif ()

    # Set a common flag for GNU-like compilers
    # (includes Clang and GCC as they share most GNU-compatible flags)
    if (C_COMPILER_ID_IS_CLANG OR C_COMPILER_ID_IS_GNU)
        set(C_COMPILER_ID_IS_GNU_LIKE TRUE)
    endif ()

    # Initialize local variables
    set(LOCAL_COMPILE_OPTIONS "")
    set(LOCAL_LINK_OPTIONS "")
    set(LOCAL_LINK_LIBRARIES "")

    foreach (CMAKE_OPTION IN ITEMS ${CMAKE_OPTIONS})
        # Early continue if not our option
        if (NOT CMAKE_OPTION MATCHES "^EYA_COMPILE_OPTION_.*")
            continue()
        endif ()

        # Optimization Level Handling
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_OPTIMIZATION")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -O3)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /O2)
                endif ()
            else ()
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -O0)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /Od)
                endif ()
            endif ()
            continue()
        endif ()

        # Debug Symbols Configuration
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_DEBUG")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -g)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /Zi)
                endif ()
            endif ()
            continue()
        endif ()

        # Instruction Set Optimizations
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_SSE2")
            if (LOCAL_COMPILE_OPTION_SSE2 AND NOT LOCAL_COMPILE_OPTION_AVX2 AND NOT LOCAL_COMPILE_OPTION_AVX512)
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -msse2)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /arch:SSE2)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_AVX2")
            if (LOCAL_COMPILE_OPTION_AVX2 AND NOT LOCAL_COMPILE_OPTION_AVX512)
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -mavx2)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /arch:AVX2)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_AVX512")
            if (LOCAL_COMPILE_OPTION_AVX512)
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -mavx512f)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -mavx512bw)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -mavx512vl)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /arch:AVX512)
                endif ()
            endif ()
            continue()
        endif ()

        # Link-Time Optimization
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_LTO")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -flto=auto)
                elseif (C_COMPILER_ID_IS_CLANG)
                    find_program(LLD_LINKER lld)
                    if (LLD_LINKER)
                        add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -flto=auto)
                        add_link_option_if_missing(LOCAL_LINK_OPTIONS -fuse-ld=lld)
                    else ()
                        message(WARNING "LLD linker not found - disabling LTO for Clang")
                    endif ()
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /GL)
                    add_link_option_if_missing(LOCAL_LINK_OPTIONS /LTCG)
                endif ()
            endif ()
            continue()
        endif ()

        # Loop Unrolling
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_UNROLL_LOOPS")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -funroll-loops)
                endif ()
            endif ()
            continue()
        endif ()

        # Security Features
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_STACK_PROTECTOR")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fstack-protector)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /GS)
                endif ()
            else ()
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fno-stack-protector)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /GS-)
                endif ()
            endif ()
            continue()
        endif ()

        # Position Independent Code
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_PIC")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (${EYA_LIBRARY_OPTION_STATIC_BUILD})
                    message(FATAL_ERROR "PIC incompatible with static builds")
                endif ()
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fPIC)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_THREAD_SAFETY")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -pthread)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_FAST_MATH")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -ffast-math)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fno-math-errno)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -funsafe-math-optimizations)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /fp:fast)
                endif ()
            endif ()
            continue()
        endif ()

        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_NATIVE_TUNE")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -march=native)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -mtune=native)
                endif ()
            endif ()
            continue()
        endif ()

        # Branch Prediction Optimizations
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_BRANCH_PREDICTION")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    find_library(GCOV_LIBRARY gcov)
                    if (GCOV_LIBRARY)
                        add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fprofile-arcs)
                        add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fpredictive-commoning)
                        find_library(GCONV_LIBRARY gconv)
                        if (GCONV_LIBRARY)
                            add_link_library_if_missing(LOCAL_LINK_LIBRARIES gconv)
                        else ()
                            message(WARNING "Library gconv not found - branch prediction optimizations may be limited")
                        endif ()
                    endif ()
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /Qspectre)
                endif ()
            endif ()
            continue()
        endif ()

        # Memory Optimizations
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_MEMORY_OPT")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fprefetch-loop-arrays)
                elseif (C_COMPILER_ID_IS_MSVC)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS /Oi)
                endif ()
            endif ()
            continue()
        endif ()

        # Visibility Hidden (reduces binary size)
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_VISIBILITY_HIDDEN")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fvisibility=hidden)
                endif ()
            endif ()
            continue()
        endif ()

        # Add the handling for the new option
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_TREE_VECTORIZE")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -ftree-vectorize)
                endif ()
            else ()
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fno-tree-vectorize)
                endif ()
            endif ()
            continue()
        endif ()

        # Disable Semantic Interposition
        if (CMAKE_OPTION STREQUAL "EYA_COMPILE_OPTION_NO_SEMANTIC_INTERPOSITION")
            if (${CMAKE_OPTION} STREQUAL "ON")
                if (C_COMPILER_ID_IS_GNU_LIKE)
                    add_compile_option_if_missing(LOCAL_COMPILE_OPTIONS -fno-semantic-interposition)
                endif ()
            endif ()
            continue()
        endif ()
    endforeach ()

    # Return values to parent scope
    set(${OUT_COMPILE_OPTIONS} "${LOCAL_COMPILE_OPTIONS}" PARENT_SCOPE)
    set(${OUT_LINK_OPTIONS} "${LOCAL_LINK_OPTIONS}" PARENT_SCOPE)
    set(${OUT_LINK_LIBRARIES} "${LOCAL_LINK_LIBRARIES}" PARENT_SCOPE)
endfunction()